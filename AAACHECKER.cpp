#define NOMINMAX
#include <windows.h>

#include <bits/stdc++.h>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

using u64 = unsigned long long;
using i64 = long long;
struct ProcessResult
{
    bool launched = false;
    bool timed_out = false;
    DWORD exit_code = static_cast<DWORD>(-1);
    long long time_ms = 0;
    DWORD launch_error = 0;
};

struct CompareResult
{
    bool same = false;
    string message;
};

// ========================= 配置区 =========================

const fs::path CANDIDATE_CPP =
    LR"(C:\Users\KEYLUN\OneDrive\vscode\AAAcandidate.cpp)";

const fs::path BRUTE_CPP =
    LR"(C:\Users\KEYLUN\OneDrive\vscode\AAAbruteforce.cpp)";

// 临时目录放在 checker 当前工作目录下。
const fs::path WORK_DIRECTORY =
    fs::current_path() / L"stress_data";

// 单次运行超时。当前生成的是小数据，通常远低于这个时间。
constexpr DWORD RUN_TIMEOUT_MS = 5000;

// 是否在编译时定义 ONLINE_JUDGE，关闭模板里的 debug/cerr。
constexpr bool DEFINE_ONLINE_JUDGE = true;

// =========================================================

template<class T>
T random_integer(mt19937_64 &rng, T left, T right)
{
    return uniform_int_distribution<T>(left, right)(rng);
}

// Windows 命令行参数转义。
// 它只负责构造 CreateProcessW 的命令行，不经过 cmd.exe。
wstring quote_windows_argument(const wstring &argument)
{
    if (argument.empty())
        return L"\"\"";

    bool need_quotes = false;
    for (wchar_t ch : argument)
    {
        if (iswspace(ch) || ch == L'"')
        {
            need_quotes = true;
            break;
        }
    }

    if (!need_quotes)
        return argument;

    wstring result = L"\"";
    size_t backslashes = 0;

    for (wchar_t ch : argument)
    {
        if (ch == L'\\')
        {
            ++backslashes;
            continue;
        }

        if (ch == L'"')
        {
            result.append(backslashes * 2 + 1, L'\\');
            result.push_back(L'"');
            backslashes = 0;
            continue;
        }

        result.append(backslashes, L'\\');
        backslashes = 0;
        result.push_back(ch);
    }

    // 结尾位于引号前的反斜杠需要加倍。
    result.append(backslashes * 2, L'\\');
    result.push_back(L'"');
    return result;
}

wstring build_command_line(const vector<wstring> &arguments)
{
    wstring command;

    for (size_t i = 0; i < arguments.size(); ++i)
    {
        if (i != 0)
            command.push_back(L' ');
        command += quote_windows_argument(arguments[i]);
    }

    return command;
}

string windows_error_message(DWORD error_code)
{
    if (error_code == 0)
        return {};

    LPSTR buffer = nullptr;

    DWORD size = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        error_code,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPSTR>(&buffer),
        0,
        nullptr
    );

    string message;
    if (size != 0 && buffer != nullptr)
    {
        message.assign(buffer, size);
        LocalFree(buffer);

        while (!message.empty() &&
               (message.back() == '\r' ||
                message.back() == '\n' ||
                message.back() == ' '))
        {
            message.pop_back();
        }
    }
    else
    {
        message = "Unknown Windows error";
    }

    return message;
}

HANDLE open_input_handle(const fs::path &path)
{
    return CreateFileW(
        path.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );
}

HANDLE open_output_handle(const fs::path &path)
{
    return CreateFileW(
        path.c_str(),
        GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        nullptr,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );
}

// 不经过 system() 和 cmd.exe，直接启动进程。
// stdin/stdout/stderr 分别重定向到三个文件。
ProcessResult run_process(
    const vector<wstring> &arguments,
    const fs::path &input_path,
    const fs::path &output_path,
    const fs::path &error_path,
    DWORD timeout_ms,
    const fs::path &working_directory = {})
{
    ProcessResult result;

    HANDLE input_handle = open_input_handle(input_path);
    if (input_handle == INVALID_HANDLE_VALUE)
    {
        result.launch_error = GetLastError();
        return result;
    }

    HANDLE output_handle = open_output_handle(output_path);
    if (output_handle == INVALID_HANDLE_VALUE)
    {
        result.launch_error = GetLastError();
        CloseHandle(input_handle);
        return result;
    }

    HANDLE error_handle = open_output_handle(error_path);
    if (error_handle == INVALID_HANDLE_VALUE)
    {
        result.launch_error = GetLastError();
        CloseHandle(input_handle);
        CloseHandle(output_handle);
        return result;
    }

    // CreateProcessW 只继承可继承的句柄。
    SetHandleInformation(input_handle, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
    SetHandleInformation(output_handle, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
    SetHandleInformation(error_handle, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);

    STARTUPINFOW startup_info{};
    startup_info.cb = sizeof(startup_info);
    startup_info.dwFlags = STARTF_USESTDHANDLES;
    startup_info.hStdInput = input_handle;
    startup_info.hStdOutput = output_handle;
    startup_info.hStdError = error_handle;

    PROCESS_INFORMATION process_info{};

    wstring command_line = build_command_line(arguments);
    vector<wchar_t> mutable_command(
        command_line.begin(),
        command_line.end()
    );
    mutable_command.push_back(L'\0');

    const wchar_t *working_directory_ptr =
        working_directory.empty() ? nullptr : working_directory.c_str();

    auto start = chrono::steady_clock::now();

    BOOL created = CreateProcessW(
        nullptr,
        mutable_command.data(),
        nullptr,
        nullptr,
        TRUE,
        CREATE_NO_WINDOW,
        nullptr,
        working_directory_ptr,
        &startup_info,
        &process_info
    );

    if (!created)
    {
        result.launch_error = GetLastError();

        CloseHandle(input_handle);
        CloseHandle(output_handle);
        CloseHandle(error_handle);
        return result;
    }

    result.launched = true;

    DWORD wait_result =
        WaitForSingleObject(process_info.hProcess, timeout_ms);

    if (wait_result == WAIT_TIMEOUT)
    {
        result.timed_out = true;
        TerminateProcess(process_info.hProcess, 0xDEAD);
        WaitForSingleObject(process_info.hProcess, INFINITE);
    }
    else if (wait_result == WAIT_FAILED)
    {
        result.launch_error = GetLastError();
    }

    GetExitCodeProcess(process_info.hProcess, &result.exit_code);

    auto finish = chrono::steady_clock::now();
    result.time_ms =
        chrono::duration_cast<chrono::milliseconds>(
            finish - start
        ).count();

    CloseHandle(process_info.hThread);
    CloseHandle(process_info.hProcess);

    CloseHandle(input_handle);
    CloseHandle(output_handle);
    CloseHandle(error_handle);

    return result;
}

bool compile_cpp(
    const fs::path &source,
    const fs::path &executable,
    const fs::path &compile_stdout,
    const fs::path &compile_stderr)
{
    if (!fs::exists(source))
    {
        wcerr << L"Source file does not exist:\n"
              << fs::absolute(source).wstring() << L"\n";
        return false;
    }

    // 编译器不需要输入，使用 Windows 的 NUL 文件。
    fs::path null_input = L"NUL";

    vector<wstring> arguments = {
        L"g++.exe",
        L"-std=c++23",
        L"-O2",
        L"-pipe"
    };

    if (DEFINE_ONLINE_JUDGE)
        arguments.push_back(L"-DONLINE_JUDGE");

    arguments.push_back(source.wstring());
    arguments.push_back(L"-o");
    arguments.push_back(executable.wstring());

    wcout << L"Compiling:\n"
          << fs::absolute(source).wstring() << L"\n";

    ProcessResult result = run_process(
        arguments,
        null_input,
        compile_stdout,
        compile_stderr,
        120000
    );

    if (!result.launched)
    {
        cerr << "Failed to launch g++: "
             << windows_error_message(result.launch_error)
             << "\n";
        return false;
    }

    if (result.timed_out)
    {
        cerr << "Compilation timed out.\n";
        return false;
    }

    if (result.exit_code != 0)
    {
        cerr << "Compilation failed. Exit code: "
             << result.exit_code << "\n";
        return false;
    }

    if (!fs::exists(executable))
    {
        cerr << "Compiler returned success, but executable was not created.\n";
        return false;
    }

    return true;
}

void generate_input(ostream &out, mt19937_64 &rng)
{
    // int n = random_integer(rng, 1, 60);
    // int m = random_integer(rng, 1, 80) * 4;

    // vector<string> grid(n, string(m, '0'));
    int n = random_integer(rng, 1, 5000);
    out << n << "\n";
    for (int i = 0;i < n;i++)
        out << random_integer(rng, 1, 10000) << " ";
    out << "\n";
    for (int i = 0; i < n; i++)
        out << random_integer(rng, 1, 10000) << " ";

    // out << n << " " << m << "\n";
    // out << s;
    //     i64 lb = 0, ub = 1e18;
    // for (int i = 0;i < 2000;i++)
    //     out << random_integer(rng, lb, ub) << "\n";
}

// 按 token 比较。
// 忽略空格、换行、行尾空白差异。
CompareResult compare_output(
    const fs::path &expected_path,
    const fs::path &actual_path)
{
    ifstream expected(expected_path);
    ifstream actual(actual_path);

    if (!expected)
        return {false, "Cannot open brute output."};

    if (!actual)
        return {false, "Cannot open candidate output."};

    string expected_token;
    string actual_token;
    size_t token_id = 1;

    while (true)
    {
        bool has_expected =
            static_cast<bool>(expected >> expected_token);
        bool has_actual =
            static_cast<bool>(actual >> actual_token);

        if (!has_expected && !has_actual)
            return {true, {}};

        if (!has_expected)
        {
            return {
                false,
                "Candidate has extra output at token " +
                to_string(token_id) +
                ": " + actual_token
            };
        }

        if (!has_actual)
        {
            return {
                false,
                "Candidate output ended at token " +
                to_string(token_id) +
                ", expected: " + expected_token
            };
        }

        if (expected_token != actual_token)
        {
            return {
                false,
                "Mismatch at token " +
                to_string(token_id) +
                ", expected: " + expected_token +
                ", actual: " + actual_token
            };
        }

        ++token_id;
    }
}

void print_file(
    const fs::path &path,
    const string &title)
{
    cout << "\n========== " << title << " ==========\n";

    ifstream input(path);
    if (!input)
    {
        cout << "[Cannot open file]\n";
        return;
    }

    string line;
    while (getline(input, line))
        cout << line << '\n';
}

fs::path save_failed_case(
    const fs::path &work_directory,
    u64 seed,
    long long test_id)
{
    fs::path failed_directory =
        work_directory /
        (L"failed_seed_" + to_wstring(seed) +
         L"_test_" + to_wstring(test_id));

    fs::create_directories(failed_directory);

    const vector<fs::path> files = {
        L"input.txt",
        L"candidate.out",
        L"brute.out",
        L"candidate.err",
        L"brute.err"
    };

    for (const fs::path &file : files)
    {
        fs::path source = work_directory / file;
        fs::path target = failed_directory / file;

        if (fs::exists(source))
        {
            fs::copy_file(
                source,
                target,
                fs::copy_options::overwrite_existing
            );
        }
    }

    ofstream meta(failed_directory / L"meta.txt");
    meta << "seed = " << seed << '\n';
    meta << "test = " << test_id << '\n';

    return failed_directory;
}

void print_process_failure(
    const string &program_name,
    const ProcessResult &result,
    const fs::path &error_path)
{
    if (!result.launched)
    {
        cout << program_name << " launch failed.\n";
        cout << "Windows error code: "
             << result.launch_error << '\n';
        cout << "Reason: "
             << windows_error_message(result.launch_error)
             << '\n';
        return;
    }

    if (result.timed_out)
    {
        cout << program_name << " timed out after "
             << result.time_ms << " ms.\n";
    }
    else
    {
        cout << program_name << " exited with code "
             << result.exit_code << ".\n";
    }

    print_file(error_path, program_name + " STDERR");
}

signed main(int argc, char *argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    try
    {
        fs::create_directories(WORK_DIRECTORY);

        const fs::path candidate_exe =
            WORK_DIRECTORY / L"candidate.exe";
        const fs::path brute_exe =
            WORK_DIRECTORY / L"brute.exe";

        const fs::path input_file =
            WORK_DIRECTORY / L"input.txt";

        const fs::path candidate_output =
            WORK_DIRECTORY / L"candidate.out";
        const fs::path brute_output =
            WORK_DIRECTORY / L"brute.out";

        const fs::path candidate_error =
            WORK_DIRECTORY / L"candidate.err";
        const fs::path brute_error =
            WORK_DIRECTORY / L"brute.err";

        const fs::path candidate_compile_out =
            WORK_DIRECTORY / L"candidate_compile.out";
        const fs::path candidate_compile_err =
            WORK_DIRECTORY / L"candidate_compile.err";

        const fs::path brute_compile_out =
            WORK_DIRECTORY / L"brute_compile.out";
        const fs::path brute_compile_err =
            WORK_DIRECTORY / L"brute_compile.err";

        u64 seed;

        if (argc >= 2)
        {
            try
            {
                seed = stoull(argv[1]);
            }
            catch (...)
            {
                cerr << "Invalid seed: " << argv[1] << '\n';
                return 1;
            }
        }
        else
        {
            seed =
                chrono::steady_clock::now()
                    .time_since_epoch()
                    .count() ^
                static_cast<u64>(
                    reinterpret_cast<uintptr_t>(&seed)
                );
        }

        mt19937_64 rng(seed);

        cout << "Seed: " << seed << "\n\n";

        if (!compile_cpp(
                CANDIDATE_CPP,
                candidate_exe,
                candidate_compile_out,
                candidate_compile_err))
        {
            print_file(
                candidate_compile_out,
                "CANDIDATE COMPILE STDOUT"
            );
            print_file(
                candidate_compile_err,
                "CANDIDATE COMPILE STDERR"
            );
            return 1;
        }

        if (!compile_cpp(
                BRUTE_CPP,
                brute_exe,
                brute_compile_out,
                brute_compile_err))
        {
            print_file(
                brute_compile_out,
                "BRUTE COMPILE STDOUT"
            );
            print_file(
                brute_compile_err,
                "BRUTE COMPILE STDERR"
            );
            return 1;
        }

        cout << "\nStart stress testing.\n";

        for (long long test_id = 1; ; ++test_id)
        {
            {
                ofstream output(input_file);

                if (!output)
                {
                    cerr << "Cannot create input file:\n";
                    wcerr << fs::absolute(input_file).wstring()
                          << L'\n';
                    return 1;
                }

                generate_input(output, rng);
            }

            ProcessResult candidate_result =
                run_process(
                    {candidate_exe.wstring()},
                    input_file,
                    candidate_output,
                    candidate_error,
                    RUN_TIMEOUT_MS
                );

            if (!candidate_result.launched ||
                candidate_result.timed_out ||
                candidate_result.exit_code != 0)
            {
                cout << "\n\nCandidate failed on test "
                     << test_id << ".\n";

                print_process_failure(
                    "CANDIDATE",
                    candidate_result,
                    candidate_error
                );

                fs::path failed_directory =
                    save_failed_case(
                        WORK_DIRECTORY,
                        seed,
                        test_id
                    );

                print_file(input_file, "INPUT");

                wcout << L"\nFailed case saved to:\n"
                      << fs::absolute(failed_directory).wstring()
                      << L'\n';
                return 0;
            }

            ProcessResult brute_result =
                run_process(
                    {brute_exe.wstring()},
                    input_file,
                    brute_output,
                    brute_error,
                    RUN_TIMEOUT_MS
                );

            if (!brute_result.launched ||
                brute_result.timed_out ||
                brute_result.exit_code != 0)
            {
                cout << "\n\nBrute failed on test "
                     << test_id << ".\n";

                print_process_failure(
                    "BRUTE",
                    brute_result,
                    brute_error
                );

                fs::path failed_directory =
                    save_failed_case(
                        WORK_DIRECTORY,
                        seed,
                        test_id
                    );

                print_file(input_file, "INPUT");

                wcout << L"\nFailed case saved to:\n"
                      << fs::absolute(failed_directory).wstring()
                      << L'\n';
                return 0;
            }

            CompareResult comparison =
                compare_output(
                    brute_output,
                    candidate_output
                );

            cout << '\r'
                 << "Test " << test_id
                 << " | candidate: "
                 << candidate_result.time_ms << " ms"
                 << " | brute: "
                 << brute_result.time_ms << " ms"
                 << flush;

            if (!comparison.same)
            {
                cout << "\n\nWrong Answer on test "
                     << test_id << ".\n";
                cout << comparison.message << '\n';

                fs::path failed_directory =
                    save_failed_case(
                        WORK_DIRECTORY,
                        seed,
                        test_id
                    );

                print_file(input_file, "INPUT");
                print_file(brute_output, "BRUTE OUTPUT");
                print_file(candidate_output, "CANDIDATE OUTPUT");
                print_file(brute_error, "BRUTE STDERR");
                print_file(candidate_error, "CANDIDATE STDERR");

                wcout << L"\nFailed case saved to:\n"
                      << fs::absolute(failed_directory).wstring()
                      << L'\n';
                return 0;
            }
        }
    }
    catch (const fs::filesystem_error &error)
    {
        cerr << "\nFilesystem error:\n"
             << error.what() << '\n';
        return 1;
    }
    catch (const exception &error)
    {
        cerr << "\nUnhandled exception:\n"
             << error.what() << '\n';
        return 1;
    }
}
