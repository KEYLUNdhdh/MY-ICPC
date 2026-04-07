// #include <iostream>
// #include <string>
// using namespace std;

// int main()
// {
//     for (int i = 0;i <=100;i++)
//     {
//         cout << "? " << i << endl;
//         cout.flush();
//         string g;
//         cin >> g;
//         if (g == "NO")
//             continue;
//         if (g == "YES" || i == 100)
//             {
//                 cout << "! " << i << endl;
//                 cout.flush();
//                 exit(0);
//             }
//     }
// }

#include <iostream>
#include <string>
#include <cstdlib> // 用于 exit(0)

using namespace std;

int main()
{
    // 目标值域是 [0, 100]。我们从 0 遍历到 99，共 100 次询问。
    // 如果这些数都被排除了，则答案必然是 100。
    for (int i = 0; i <= 99; ++i)
    {
        // 1. 发起交互询问 ? i
        cout << "? " << i << endl; // endl 自动包含换行符
        cout.flush();              // 刷新缓冲区，确保交互器立即收到询问

        // 2. 读取交互器反馈
        string feedback;
        if (!(cin >> feedback))
        {
            // 如果读取失败（例如交互结束），则退出
            return 0;
        }

        // 3. 处理反馈
        if (feedback == "YES")
        {
            // 找到了 s = i
            // 宣布答案 ! i 并退出
            cout << "! " << i << endl;
            cout.flush();
            return 0; // 或 exit(0);
        }
        // 如果 feedback == "NO"，则 i 被排除，s != i，继续下一个 i
    }

    // 执行到这里，说明从 i=0 到 i=99 的 100 次询问全部返回了 NO。
    // 这意味着 s != 0, s != 1, ..., s != 99。
    // 根据值域 [0, 100]，唯一的可能性就是 s = 100。
    // 此时我们用完了 100 次询问。

    // 宣布最终断言的答案 ! 100
    cout << "! " << 100 << endl;
    cout.flush();

    return 0; // 成功找到答案并退出
}