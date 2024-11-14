/**
 * Description: Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem,
 * so that an expression of the type $(a||b)\&\&(!a||c)\&\&(d||!b)\&\&...$
 * Negated variables are represented by bit-inversions (\texttt{\tilde{}x}).
 * Usage:
 *  TwoSat ts(number of boolean variables);
 *  maxn twice the limit
 * Time: O(N+E), where N is the number of boolean variables, and E is the number of clauses.
 */
#pragma once

const int maxn=1e6+9;
struct twosat{
    vector<int>*a,*ra;
    vector<int>_a[maxn],_ra[maxn];
    int *vis,_vis[maxn];
    int *id,_id[maxn];
    int ans[maxn];
    vector<int>topo;
    int n;
    twosat(int _n){
    n=_n;
    a=_a+n+5;
    ra=_ra+n+5;
    id=_id+n+5;
    vis=_vis+n+5;
    topo.clear();
    }
    void addor(int u,int v){
    a[u].pb(v);
    ra[v].pb(u);
    }
    void add(int u,int v){
    addor(-u,v);
    addor(-v,u);
    }
    void dfs(int u){
    vis[u]=1;
    for (auto v:a[u]){
        if (!vis[v]){
            dfs(v);
        }
    }
    topo.pb(u);
    }
    void scc(int u,int cnt){
    vis[u]=0;
    id[u]=cnt;
    for (auto v:ra[u]){
        if (vis[v]){
            scc(v,cnt);
        }
    }
    }
    bool check(){
    for1(i,1,n){
    if (!vis[i])dfs(i);
    if (!vis[-i])dfs(-i);
    }
    reverse(all(topo));
    int cnt=0;
    for (auto v:topo){
        if (vis[v]){
            scc(v,++cnt);
        }
    }
    for1(i,1,n){
    if (id[i]==id[-i])return 0;
    }
    for1(i,1,n){
    ans[i]=id[i]>id[-i];
    }
    return 1;
    }
};
