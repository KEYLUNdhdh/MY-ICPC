#include <bits/stdc++.h>
using namespace std;
const int MAXN = 20;
//两个结构体中的who表示是谁说的
struct ck//说明a 与 b之间身份是相同还是不同
{
    int who, a, b, relation;
};
struct ck1//说明a是什么身份，0为Knight，1为Knave
{
    int who, a, identity;
};
signed main()
{
    int n, s;//n代表人数，s代表statement的个数
    cin >> n >> s;
    vector<ck> check;
    vector<ck1> check1;
    //利用哈希表建立映射
    unordered_map<int, string> mp;
    mp[0] = "Knight";
    mp[1] = "Knave";
    //利用lamba函数快速获取每个字母的数字id，便于存储
    auto getid = [&](char c) -> int
    {
        return c - 'A';
    };
    //读入每个statement
    for (int i = 0; i < s;i++)
    {
        char who;
        int op;
        cin >> who >> op;
        int person = getid(who);
        if(op == 1)//描述一个人是什么身份
        {
            char ch;
            string s;
            int identity = -1;
            cin >> ch >> s;
            if(s == "Knight")
                identity = 0;
            else
                identity = 1;
            check1.push_back({person, getid(ch), identity});
        }
        else if(op == 2)//描述两个人身份相同或者相反
        {
            char c1, c2;
            string s;
            cin >> c1 >> c2 >> s;
            int a = getid(c1);
            int b = getid(c2);
            int relation = (s == "same" ? 1 : 0);
            check.push_back({person, a, b, relation});
        }
    }
    int accepted_cnt = 0;//记录答案数量
    for (int i = 0; i < (1 << n);i++)
    {
        vector<int> asu(n);//这个用来记录我们假设的身份
        for (int j = 0; j < n;j++)
            asu[j] = (i >> j) & 1;
        int f = 1;
        // 2. 验证 check1 (who 说 a 是 identity)
        for(auto &[who, a, identity] : check1)
        {
            bool is_who_knight = (asu[who] == 0); // 说话人是不是骑士
            bool is_statement_true = (asu[a] == identity); // 这句话本身符不符合客观事实
            
            // 骑士必须说真话，无赖必须说假话。如果不一致，这套剧本就是错的。
            if(is_who_knight != is_statement_true) 
            {
                f = 0;
                break;
            }
        }
        if(!f) continue;

        // 3. 验证 check (who 说 a 和 b 的关系)
        for(auto &[who, a, b, relation] : check)
        {
            bool is_who_knight = (asu[who] == 0); // 说话人是不是骑士
            
            int actual_relation = (asu[a] == asu[b] ? 1 : 0); // 客观事实上，a 和 b 是否相同
            bool is_statement_true = (actual_relation == relation); // 这句话本身符不符合客观事实
            
            // 逻辑自洽验证
            if(is_who_knight != is_statement_true)
            {
                f = 0;
                break;
            }
        }

        // 如果 f == 1 走到了这里，说明状态 i 是一个满足所有条件的合法解
        if(f)
        {
            accepted_cnt++;
            cout <<"Answer " <<  accepted_cnt << ": ";
            for (int j = 0;j < n;j++)
                cout << (char)('A' + j) << ": " << mp[asu[j]] << " ";
            cout << endl;
        }
    }
    if(accepted_cnt == 0)//如果没有条件符合，则输出
        cout << "NO ANSWER FOUND!";
}