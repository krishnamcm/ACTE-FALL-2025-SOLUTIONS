#include <bits/stdc++.h>

using namespace std;

//notice that the minimized distance to each point will be at the median

int main()
{
    int n;
    cin>>n;
    vector<int>v;

    for(int i=0; i<n; i++)
    {
        int a;
        cin>>a;
        v.push_back(a);
    }
    sort(v.begin(),v.end());
    
    if(n%2==1){cout<<v[n/2];} //if the number of elements is odd, we just take the middle one
    else
    {
        cout<<floor((v[(n/2)-1]+v[n/2])/2.0)<<endl;
        //else find the number in between the two middle numbers
    }
  return 0;

}
