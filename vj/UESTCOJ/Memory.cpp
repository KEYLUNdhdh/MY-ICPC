    #include <iostream>
    #include <vector>
    #define int long long
    using namespace std;
   
    signed main()
    {
        ios::sync_with_stdio(0);
        vector<bool> used(1000000, false);
        used[3] = true;
        vector<int> res;
        res.push_back(1);
        res.push_back(2);
        int n;
        cin >> n;
        for (int k = 2; k < n; k++)
        {
            int next = res[k - 1] + 1;
            while (true)
            {
                bool ok = true;
                for (int i = 0; i < k;i++)
                {
                    int sum = res[i] + next;
                    if (used[sum])
                    {
                        ok = false;
                        break;
                    }
                }
                if (ok)
                {
                    for (int i = 0; i < k;i++)
                    {
                        used[res[i] + next] = true;
                    }
                    res.push_back(next);
                    break;
                }
                next++;
            }
        }

        for (int i = 0; i < n;i++)
        {
            cout << res[i];
            if (i != n - 1)
                cout << " ";
        }
        cout << endl;
    }