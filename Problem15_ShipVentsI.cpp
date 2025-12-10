#include <bits/stdc++.h>

using ll=long long;
using namespace std;

unordered_map<int, vector<int>>graph;
unordered_map<int, ll>memo;

ll countPaths(int node, int target) 
{
    if(node==target){return 1;}
    if(memo.find(node)!=memo.end()){return memo[node];}
    
    ll total=0;
    for(int neighbor:graph[node]) {total+=countPaths(neighbor, target);}
    
    memo[node]=total;
    return total;
}

int main() 
{
    freopen("input1.in","r",stdin);
    freopen("output1.out","w",stdout);
    int n, a, b;
    cin>>n>>a>>b;
    
    for(int i=0; i<n; i++) 
    {
        int p, q;
        cin>>p>>q;
        graph[p].push_back(q);
    }
    
    // for(auto &k:graph)
    // {
    //     cout<<k.first<<"->"<<endl;
    //     for(auto &u:k.second){cout<<'u ';}
    //     cout<<endl;
    // } //this just prints the graph (uncomment it if you want it to print the graph out)


    // count the paths using dfs combined with memoization
    ll result=countPaths(a, b);
    
    cout<<result<<endl;
    return 0;
}
