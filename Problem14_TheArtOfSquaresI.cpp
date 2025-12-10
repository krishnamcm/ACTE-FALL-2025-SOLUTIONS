#include <bits/stdc++.h>
using namespace std;

int n, m;          
int ans;  //best answer so far
int h[20]; //h[i]=current filled height in column i

void dfs(int cnt) 
{
    //prune if current count is not better than best answer
    if(cnt>=ans){return;}

    //find the leftmost column with the smallest height
    int minHeight=INT_MAX;
    int col=-1;
    for (int i=0; i<m; ++i) 
    {
        if(h[i]<minHeight) 
        {
            minHeight=h[i];
            col=i;
        }
    }

    //if all columns are completely filled, update answer
    if(minHeight==n) 
    {
        ans=min(ans, cnt);
        return;
    }

    //maximum possible square size that fits starting at (col, minHeight)
    int maxS=min(n - minHeight, m - col);

    //try squares from largest to smallest 
    for (int s=maxS; s>=1; --s) 
    {
        //check if these colums have the same minheight
        bool ok=true;
        for (int i=col; i<col+s; ++i) 
        {
            if(h[i] != minHeight) 
            {
                ok=false;
                break;
            }
        }
        if(!ok) continue;

        //place the square: increase heights of these columns by s
        for (int i=col; i<col+s; ++i) h[i] += s;
        dfs(cnt+1);
        //backtrack: restore heights
        for (int i=col; i<col+s; ++i) h[i] -= s;
    }
}

int main() 
{
    freopen("input1.in","r",stdin);
    freopen("output1.out","w",stdout);
    int t;
    cin>>t;
    while (t--) 
    {
        cin>>n>>m;
        memset(h, 0, sizeof(h));
        ans=INT_MAX;
        dfs(0);
        cout<<ans<<endl;
    }
    return 0;
}
