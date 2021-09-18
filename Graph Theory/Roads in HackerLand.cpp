#include <iostream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <utility>
using namespace std;
vector<int> p(100001),rnk(100001,1),child(100001);
vector<long long int> sum(400020);
vector<pair<int,pair<int,int> > > ed;
vector<vector<pair<int,int> > > mst(100001);
int n,e;
bitset<100001> vis;
int find(int a){
    return p[a]==a?a:p[a]=find(p[a]);
}
bool same(int a,int b){
    return find(a)==find(b);
}
void merge(int a,int b){
    if(!same(a,b)){
        if(rnk[find(a)]>rnk[find(b)]){
            p[find(b)]=find(a);
        }
        else {
            p[find(a)]=find(b);
        }
        if(rnk[find(a)]==rnk[find(b)])
            rnk[find(b)]++;
    }
}
int dfs(int u){
    vis[u]=1;
    int ans=1;
    for(int i=0;i<mst[u].size();i++){
        if(!vis[mst[u][i].second]){
            ans+=dfs(mst[u][i].second);
            sum[mst[u][i].first]+=(long long)(n-child[mst[u][i].second])*child[mst[u][i].second];
        }
    }
    return child[u]=ans;
}
int main(){
    ios::sync_with_stdio(0);
    cin>>n>>e;
    for(int i=1;i<=n;i++)
        p[i]=i;
    for(int i=0;i<e;i++){
        int x,y,w;
        cin>>x>>y>>w;
        ed.push_back({w,{x,y}});
    }
    sort(ed.begin(),ed.end());
    for(int i=0;i<ed.size();i++){
        if(!same(ed[i].second.first,ed[i].second.second)){
            mst[ed[i].second.first].push_back({ed[i].first,ed[i].second.second});
            mst[ed[i].second.second].push_back({ed[i].first,ed[i].second.first});
            merge(ed[i].second.first,ed[i].second.second);
        }
    }
    dfs(1);
    for(int i=0;i<2*e+10;i++){
        sum[i+1]+=sum[i]/2; //hackerrank.com/whorahul
        sum[i]%=2;
    }
    int hsb=2*e+10;
    while(hsb>0&&sum[hsb]==0){
        hsb--;
    }
    for(int i=hsb;i>=0;i--)
        cout<<sum[i];
    cout<<endl;
    return 0;
}
