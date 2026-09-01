#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<string>
#include<bitset>
#include<unordered_map>
using namespace std;



const int N=500010;
typedef long long ll;

bitset<110>a[N];
unordered_map<bitset<110>,vector<int>>mp;

int n,k,m,f;

int l[N],r[N];

void solve(){
   cin>>n>>k>>m>>f;
   for(int i=1;i<=k;++i){
      for(int i=1;i<=m;++i){
        int x;
        cin>>x;
        a[x][i]=1;
      }
   }
   for(int i=1;i<=n;++i){
    mp[a[i]].push_back(i);
   }
   for(int i=1;i<=f;++i){
    bitset<110>tem;
    string s;
    cin>>s;
    cerr << s << "\n";
    
    for(int j=0;j<s.size();++j){
        if(s[j]=='Y')tem[j+1]=1;
    }
    if(mp[tem].size()==1){
        cout<<mp[tem][0]<<endl;
    }
    else cout<<0<<endl; 
   }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}