#include <bits/stdc++.h>

using namespace std;
using ll=long long;


//If you're curious, there are a few versions of this problem that are NP-Hard, 
//The wikipedia page on tiling problems is a good read if you're interested

//my the variables were all renamed for the sake of readability and clarity, but you probably would want shorter names in actual competition code

vector<int> sizes;     //rescaled sizes
vector<ll> areas;      //areas of the rescaled squares
int n;                      
int best_count=INT_MAX;   

//backtracking to check if we can tile an L x L square with given counts.
//counts: map from size to count
//grid: L x L grid, 0=empty, 1=filled
//filled: number of filled cells (to speed up)
bool backtrack(int L, vector<int>& sizes_desc, vector<vector<int>>& grid, int filled, vector<int>& counts) 
{
    if(filled==L*L){return true;}

    //find first empty cell (top-left order)
    int x=-1, y=-1;
    for(int i=0; i<L&&x==-1; ++i) 
    {
        for(int j=0; j<L&&x==-1; ++j) 
        {
            if(grid[i][j]==0){x=i;y=j;}
        }
    }
    if(x==-1){return true;}

    //try sizes in decending order
    for(int s:sizes_desc) 
    {
        if(counts[s]==0){continue;}
        if(x+s>L || y+s>L){continue;}

        //check if the sxs square can be placed
        bool can_place=true;
        for(int i=x; i<x+s&&can_place; ++i) 
        {
            for(int j=y; j<y+s&&can_place; ++j) 
            {
                if(grid[i][j]!=0){can_place=false;}
            }
        }
        if(!can_place){continue;}

        //place the square
        for(int i=x; i<x+s; ++i)
        {
            for(int j=y; j<y+s; ++j){grid[i][j]=1;}
        }
            
        counts[s]--;
        filled+=s*s;

        if(backtrack(L, sizes_desc, grid, filled, counts)){return true;}

        //backtracking step
        counts[s]++;
        filled-=s*s;
        for(int i=x; i<x+s; ++i)
        {
            for(int j=y; j<y+s; ++j){grid[i][j]=0;}
        }
            
    }
    return false;
}

//check if we can tile an L x L square with the given counts per size.
//sizes: asending original sizes
//size_count: vector of same length as sizes, count_per_size[i]=count for sizes[i]
bool can_tile(int L, const vector<int>& sizes, const vector<int>& size_count) 
{
    //put sizes in descending order for backtracking
    vector<int> sizes_desc;
    vector<pair<int, int>> szeCntPairs;
    for(int i=0; i<n; ++i) 
    {
        if(size_count[i]>0) {szeCntPairs.push_back({sizes[i], size_count[i]});}
    }
    sort(szeCntPairs.begin(), szeCntPairs.end(), greater<pair<int,int>>());
    vector<int> counts_map(256, 0);

    int max_size=*max_element(sizes.begin(), sizes.end());
    vector<int> cntsArr(max_size+1, 0);
    for(auto& p:szeCntPairs) {sizes_desc.push_back(p.first); cntsArr[p.first]=p.second;}

    vector<vector<int>> grid(L, vector<int>(L, 0));
    return backtrack(L, sizes_desc, grid, 0, cntsArr);
}

int main() 
{
      cin>>n;
    vector<int> original(n);
    for(int i=0; i<n; ++i) {cin>>original[i];}
    sort(original.begin(), original.end());

    //only one size, -> answer is trivially 1
    if(n==1) {cout<<1<<endl; return 0;}

    //change the scale size so the smallest rescales to 1
    int min_side=original[0];
    sizes.resize(n);
    for(int i=0; i<n; ++i) {sizes[i]=original[i]/min_side;}

    //find the areas
    areas.resize(n);
    for(int i=0; i<n; ++i) {areas[i]=(ll)sizes[i]*sizes[i];}

    //precompute sum of areas of all except the largest square
    ll sum_small_areas=0;
    for(int i=0; i<n-1; ++i) {sum_small_areas+=areas[i];}
    ll area_largest=areas[n-1];

    //Search over number of largest squares used
    for(int k=1; k <= 10; ++k) 
    {
        //lower bound for L
        ll min_area=k*area_largest+sum_small_areas;
        ll L_lower=(ll)ceil(sqrt(min_area));

        for(ll L=L_lower; L <= L_lower+1000; ++L) 
        {
            ll total_area=L*L;
            ll T=total_area-k*area_largest;
            if(T<sum_small_areas){continue;}

            //use one of each small square. in a greedy fahsion, fill the rest after that
            ll R=T-sum_small_areas;
            vector<int> counts(n,0);
            counts[n-1]=k; //largest squares
            bool ok=true;

            for(int i=n-2; i >= 0; --i) 
            {
                ll take=R / areas[i];
                counts[i]=1+take; 
                R-=take*areas[i];
            }
            //just check for the smallest area
            if(R!=0){continue;}

            //Compute total count
            int total_count=0;
            for(int i=0; i<n; ++i){total_count+=counts[i];}
            if(total_count >= best_count){continue;}

            //check if we can tile here
            if(can_tile((int)L, sizes, counts)) 
            {
                best_count=total_count;
                break;
                //break since we found a solution and increse L, and total_count increases
            }
        }
        if(best_count!=INT_MAX){} //I can't remember why i put this here, but the code doesn't work whenever I remove it (on my computer atleast)
    }

    cout<<best_count<<endl;
    return 0;
}
