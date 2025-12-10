#include <bits/stdc++.h>
using namespace std;

//GAINING BRANCHES
//essentially, all we need to do is check whether the current number of branches is divisible by the previous number of branches.
//This is because if the tree grows n branches for every branch it already has, the number of branches is:
// n+(n*k) where n is the initial number of branches and k is the growth. Notice that it will always be divisible by n. 
//we can exploit this property to write the solution.  if it doesn't satisfy this property, then it's not fractal

//LOOSING BRANCHES
//Notice that a tree can only ever lose one branch for every branch it already has
//that process will make it zero branches. As a result, if we see zero, we terminate. if there is a number after zero, then it's obviously not fractal. 


void solve() 
{
    int n;
    cin>>n;

    int prev;
    cin>>prev;

    bool fractal=true;
    for(int i=1; i<n; i++) 
    {
        int cur;
        cin>>cur;
        if(prev==0) 
        {
            if(cur!=0) 
            {
                fractal=false;
                for(int j=i+1; j<n; j++) {cin>>cur;} //read in the rest of them, so it doesn't cause some error
                break;
            }
        } 
        else 
        {
            if(cur%prev!=0) 
            {
                fractal=false;
                for(int j=i+1; j<n; j++){cin>>cur;}
                break;
            }
        }

        prev=cur; //update prev with the current one
    }
    cout<<(fractal?"YES":"NO")<<endl;
}

int main() 
{

    int t;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}
