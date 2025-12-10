#include <bits/stdc++.h>
using namespace std;

struct Sample //created a 'new' data type to better organize all the information (sort of like an object)
{
    int cal,sat,price;
    Sample(int c,int s,int p):cal(c),sat(s),price(p){}
};

int main() 
{
    
    int n,c,m,d;
    cin>>n>>c>>m>>d;
    
    vector<vector<Sample>> stations(n);
    
    //read stations data
    for (int i=0; i<n; i++) 
    {
        int k;
        cin>>k;
        for (int j=0; j<k; j++) 
        {
            int cal,sat,price;
            cin>>cal>>sat>>price;
            stations[i].push_back(Sample(cal,sat,price));
        }
    }
    
    //build graph and indegree for topological sort
    vector<vector<int>> graph(n);
    vector<int> indegree(n,0);
    vector<pair<int,int>> dependencies;
    
    for (int i=0; i<d; i++) 
    {
        int u,v;
        cin>>u>>v;
        u--; v--; //convert to 0-based indexing
        graph[u].push_back(v);
        indegree[v]++;
        dependencies.push_back({u,v});
    }
    
    //topological sort
    deque<int> q;
    for (int i=0; i<n; i++)
    {
        if (indegree[i]==0) 
        {
            q.push_back(i);
        }
    }
    
    vector<int> topo_order;
    
    while (!q.empty()) 
    {
        int node=q.front();
        q.pop_front();
        topo_order.push_back(node);
        
        for (int neighbor:graph[node]) 
        {
            indegree[neighbor]--;
            if (indegree[neighbor]==0) 
            {
                q.push_back(neighbor);
            }
        }
    }
    
    //if we couldn't process all nodes,there's a cycle
    if (topo_order.size()!=n) 
    {
        //Simplified: use all nodes in original order
        topo_order.clear();
        for (int i=0; i<n; i++) 
        {
            topo_order.push_back(i);
        }
    }
    
    //dp array:dp[cal][price]=max satisfaction
    //-1 is unreachable
    vector<vector<int>> dp(c+1,vector<int>(m+1,-1));
    dp[0][0]=0;
    
    //for each station in topological order
    for (int station_idx : topo_order) 
    {
        //create new DP
        vector<vector<int>> new_dp=dp;
        
        //get all prerequisites for this station
        vector<int> prereqs;
        for (auto& dep : dependencies) 
        {
            if (dep.second==station_idx) 
            {
                prereqs.push_back(dep.first);
            }
        }
        
        //try each sample from this station
        for (auto& sample : stations[station_idx]) 
        {
            int cal=sample.cal;
            int sat=sample.sat;
            int price=sample.price;
            
            for (int curr_cal=0; curr_cal<=c-cal; curr_cal++) 
            {
                for (int curr_price=0; curr_price<=m-price; curr_price++) 
                {
                    if (dp[curr_cal][curr_price]>=0) 
                    {
                        int new_cal=curr_cal+cal;
                        int new_price=curr_price+price;
                        int new_sat=dp[curr_cal][curr_price]+sat;
                        
                        if (new_cal<=c&&new_price<=m) 
                        {
                            if (new_dp[new_cal][new_price]<new_sat) 
                            {
                                new_dp[new_cal][new_price]=new_sat;
                            }
                        }
                    }
                }
            }
        }
        
        dp=move(new_dp);
    }
    
    //Find maximum satisfaction
    int max_sat=0;
    for (int i=0; i<=c; i++) 
    {
        for (int j=0; j<=m; j++) 
        {
            if (dp[i][j] > max_sat) 
            {
                max_sat=dp[i][j];
            }
        }
    }
    
    cout<<max_sat<<endl;
    
    return 0;
}
