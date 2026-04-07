#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t,r,c,s;
    cin >> t;
    while(t--)
    {
        cin >> r >> c >> s;
        deque<string> st;
        st.push_back("/\\");
        st.push_back("\\/");
        for(int k = 1; k < s;k++)
        {
            int orilen = st.size();
            for (int i = 0; i < orilen / 2;i++)
            {
                st.push_back("." + st[i] + ".");
            }
            st.push_back("/" + string((k) * 2, '*') + "\\");
            for (int i = 0;i < orilen;i++)
                st.pop_front();
            for (int i = st.size() - 1; i >= 0;i--)
            {
                string tp = st[i];
                int pos = tp.find('/');
                // if(pos != string::npos)
                tp[pos] = '\\';
                pos = tp.rfind('\\');
                // if(pos != string::npos)
                tp[pos] = '/';
                st.push_back(tp);
            }
        }
        for (int k = 0; k < r;k++)
        {
            for (int i = 0; i < st.size();i++)
            {
                for (int j = 0; j < c;j++)
                {
                    cout << st[i];
                }
                cout << "\n";
            }
        }
        cout << "\n";
    }
}