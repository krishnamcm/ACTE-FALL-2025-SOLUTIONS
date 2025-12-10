#include <bits/stdc++.h>
using namespace std;

const double INF=1e18;

int main() 
{
    int n,a,b,c;
    cin>>n>>a>>b>>c;
    
    //Store edges for building graph
    vector<pair<pair<int,int>,int>> edges;
    set<int> nodes_set;
    nodes_set.insert(a);
    nodes_set.insert(b);
    nodes_set.insert(c);
    
    for(int i=0; i<n; i++) 
    {
        int u,v,p;
        cin>>u>>v>>p;
        edges.push_back({{u,v},p});
        nodes_set.insert(u);
        nodes_set.insert(v);
    }
    
    
    vector<int> nodes(nodes_set.begin(),nodes_set.end());
    unordered_map<int,int> node_index; //map node value to index for convenience
    
    //build adjacency list and indegree map
    unordered_map<int,vector<pair<int,double>>> graph; //graph[u]=list of(v,cost)
    unordered_map<int,int> indeg;
    
    for(auto& edge:edges) 
    {
        int u=edge.first.first;
        int v=edge.first.second;
        int p=edge.second;
        
        //calculate cost=-log(1-p/100.0)
        double cost=INF;
        double prob=p/100.0;
        if(prob<1.0){cost=-log(1.0-prob);}
        
        graph[u].push_back({v,cost});
        indeg[v]++; //increment indegree of v
        //Ensure all nodes appear in indeg map
        if(indeg.find(u) == indeg.end()) indeg[u]=0;
    }
    
    //topological sort
    queue<int> q;
    for(auto& entry:indeg){if(entry.second==0){q.push(entry.first);}}
    
    vector<int> topo_order;
    while(!q.empty()) 
    {
        int u=q.front();
        q.pop();
        topo_order.push_back(u);
        for(auto& edge:graph[u]) 
        {
            int v=edge.first;
            indeg[v]--;
            if(indeg[v]==0){q.push(v);}
        }
    }
    
    //apply dp from source a
    unordered_map<int,double> dist_a;
    unordered_map<int,int> pred_a;
    for(int node:nodes) 
    {
        dist_a[node]=INF;
        pred_a[node]=-1;
    }
    dist_a[a]=0.0;
    
    for(int u:topo_order) 
    {
        if(dist_a[u]<INF) 
        {
            for(auto& edge:graph[u]) 
            {
                int v=edge.first;
                double cost=edge.second;
                if(dist_a[u]+cost<dist_a[v]) 
                {
                    dist_a[v]=dist_a[u]+cost;
                    pred_a[v]=u;
                }
            }
        }
    }
    
    //reapply dp from node b
    unordered_map<int,double> dist_b;
    unordered_map<int,int> pred_b;
    for(int node:nodes) 
    {
        dist_b[node]=INF;
        pred_b[node]=-1;
    }
    dist_b[b]=0.0;
    
    for(int u:topo_order) 
    {
        if(dist_b[u]<INF) 
        {
            for(auto& edge:graph[u]) 
            {
                int v=edge.first;
                double cost=edge.second;
                if(dist_b[u]+cost<dist_b[v]) 
                {
                    dist_b[v]=dist_b[u]+cost;
                    pred_b[v]=u;
                }
            }
        }
    }
    
    //reconstruct path from a to b
    vector<int> path_ab;
    int cur=b;
    while(cur!=-1) 
    {
        path_ab.push_back(cur);
        cur=pred_a[cur];
    }
    reverse(path_ab.begin(),path_ab.end());
    
    //Reconstruct path from b to c
    vector<int> path_bc;
    cur=c;
    while(cur!=-1) 
    {
        path_bc.push_back(cur);
        cur=pred_b[cur];
    }
    reverse(path_bc.begin(),path_bc.end());
    
    //combine paths
    vector<int> full_path=path_ab;

    for(size_t i=1; i<path_bc.size(); i++) {full_path.push_back(path_bc[i]);}    
    for(size_t i=0; i<full_path.size(); i++) 
    {
        if(i>0){cout<<" ";}
        cout<<full_path[i];
    }
    cout<<endl;
    
    return 0;
}
