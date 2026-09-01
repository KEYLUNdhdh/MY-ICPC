#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N=67;
const int MAXN=1e6+7;
ll n,is_p[MAXN],x,y,sz[N],son[N],a[N],now, tag[N], top[N];
vector<int>e[N];
vector<ll> primes,isPrime;

void sieve(int n)
{
	isPrime.assign(n + 1, 1);
	isPrime[1] = 0;
	for (int i = 2; i <= n; ++i)
	{
		if (isPrime[i])
			primes.push_back(i);
		for (auto p : primes)
		{
			if(i * p > n)
				break;
			isPrime[i * p] = 0;
			if(i % p == 0)
				break;
		}
	}
}

void tree(int u, int p){
    sz[u]=1;
    for(int t:e[u]){
        if(t == p)
            continue;
        tree(t, u);
        sz[u]+=sz[t];
        if(sz[t]>sz[son[u]]) 
            son[u]=t;
    }
}

void dfs(int u, int p){
    // cout<<u<<'\n';
    if(e[u].empty()) return ;
    for(int t:e[u]){
        // cout<<"?";
        if(t == p)
            continue;
        if(t!=son[u]){
            // cout<<"t"<<t;
            a[t]= a[u] * tag[t];
            dfs(t, u);
        }
    }
    if(son[u])
    {
        a[son[u]]=a[u] * tag[u];
        tag[son[u]] = tag[u];
        dfs(son[u], u);
    }
}

void dfs2(int u, int t, int p)
{
    top[u] = t;
    if(!son[u])
        return;
    dfs2(son[u], t, u);
    for(int v : e[u])
    {
        if(v == p)
            continue;
        if(v != son[u])
            dfs2(v, v, u);
    }
}

int main(){
    ios::sync_with_stdio(false);  
    cin.tie(0);  
    cin>>n;
    sieve(1e5);
    tag[1] = 2;
    
    for (int i = 1; i < n; i++)
    {
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }

    tree(1, 0);
    dfs2(1, 1, 0);
    vector<int> cnt(n + 1, 0);
    vector<int> vis(n + 1, 0);
    vector<int> tp;
    for (int i = 1; i <= n; i++)
    {
        cnt[top[i]]++;
        if(!vis[top[i]])
        {
            vis[top[i]] = 1;
            tp.push_back(top[i]);
        }
    }

    sort(tp.begin(), tp.end(), [&](int x, int y){return cnt[x] > cnt[y];});
    for (int i = 0; i < tp.size();i++)
    {
        int cur = tp[i];
        tag[cur] = primes[now++];
    }
    for (int i = 1; i <= n;i++)
        cerr << tag[i] << " ";
    cerr << "\n";
    a[1] = 1;
    dfs(1, 0);
    
    for(int i=1;i<=n;i++)
        cout<<a[i]<<" ";
}








