#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N=1e5+7;
ll n,k,t[N],a[N],now,i,q,ans;
int main(){
    ios::sync_with_stdio(false);  
    cin.tie(0);  
    cin>>n>>k;
    t[1]=k+1,a[1]=1;
    for( i=2;t[i-1]<=n&&i<=k;i++){
        t[i]=t[i-1]*k+1;
        a[i]=a[i-1]*k+1;
        // cout<<i<<"->"<<t[i]<<" "<<a[i]<<"\n";
    }
    q=n;
    if(k<=1e5&&t[k]!=0&&n>=t[k]){
        cout<<a[k]+n-t[k];
        return 0;
    }
    // cout<<i<<' '<<t[i]<<"?\n";
    for(int now=i-1;now>=1;now--){
        if(t[now]>q) continue;
        // cout<<"now:"<<q<<" "<<t[now]<<"\n";
       i=q/t[now];
        ans+=i* a[now];
        q-=i*t[now];
    }
    cout<<ans;
}