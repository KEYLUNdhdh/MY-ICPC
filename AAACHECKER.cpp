#include <bits/stdc++.h>
#include <format>
using namespace std;
using i64 = long long;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
static mt19937_64 rng(time(0));
int ra(int min = 0, int max = 1e9)
{ // 随机数生成器
    return std::uniform_int_distribution<int>(min, max)(rng);
}
class CodeChecker
{
#define AC cout << "\n \t\033[32m Accepted \033[0m \n";
#define WA cout << "\n \t\033[31m Wrong Answer !!! \033[0m \n";
    void run_submit()
    {
        FILE *fp = _popen(R"(.\tools\submit.exe < .\data\data.in > .\data\submit.out)", "r");
        if (fp)
            _pclose(fp);
    }
    bool checker()
    {
#define LOG(x) log << #x << " = " << x << "\n";
        ifstream input(R"(.\data\data.in)");
        ifstream output(R"(.\data\submit.out)");
        ofstream log(R"(.\data\checker.log)");
        int T;
        input >> T;
        for (int tt = 1; tt <= T; tt++)
        {
            int n;
            input >> n; // 读取刚才 generator 生成的 n
            vector<int> init(n);
            i64 ans = 0;
            output >> ans;
            vector<int> a(n);
            i64 tmp = 0;
            i64 maxx = 0;
            for (int i = 0; i < n; i++)
                input >> a[i];
            init = a;
            for (int i = 1; i <= n;i++)
            {
                for (int j = 1; j <= n;j++)
                {
                    reverse(a.begin(), a.begin() + i);
                    reverse(a.end() - j, a.end());
                    for (int k = 0; k < n - 1;k++)
                        tmp += abs(a[k] - a[k + 1]);
                    maxx = max(maxx, tmp);
                    a = init;
                    tmp = 0;
                }
            }
            if(maxx == ans)
            {
                return true;
            }
            else
            {
                cout << "\033[31m" << "ANSWER SHOULD BE " << maxx;
                return false;
            }
        }
        return true;
    }//"\033[31m"
    void generator()
    {
        ofstream ofs(R"(.\data\data.in)");
        int T = 1;
        ofs << T << "\n";
        while (T--)
        {
            int n = ra(2, 50);
            ofs << n << "\n";
            for (int i = 0;i < n;i++)
                ofs << ra(1, 1500) << " ";
            ofs << "\n";
        }
    }
    void read_and_print_file(const string &file_path)
    {
        cout << file_path << ":\n";
        ifstream ifs(file_path);
        string buf;
        while (getline(ifs, buf))
            cout << "\t" << buf << "\n";
        ifs.close();
    }

public:
    string submit_cpp_path;
    CodeChecker(string s) : submit_cpp_path(s) {};
    void check()
    {
        system(format(R"(g++ -O2 "{}" -o .\tools\submit.exe -std=c++23)", submit_cpp_path).c_str());
        int t = 0;
        while (true)
        {
            cout << "test: " << t++;
            // generator 输出数据
            generator();
            // submit 输出数据
            run_submit();
            if (checker() == false)
            {
                WA;
                read_and_print_file(R"(.\data\data.in)");
                read_and_print_file(R"(.\data\submit.out)");
                read_and_print_file(R"(.\data\checker.log)");
                cout.flush();
                system("pause");
                return;
            }
            AC;
            cout.flush();
        }
    }
    void bat()
    {
    }
};
string path = R"(C:\Users\KEYLUN\OneDrive\vscode\AAAAATMPPP.cpp)";
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    CodeChecker codechecker(path);
    codechecker.check();
}