#include <bits/stdc++.h>
using namespace std;

int main() 
{
    freopen("input1.in","r",stdin);
    freopen("output1.out","w",stdout);
    int k;
    string s;
    cin>>k>>s;

    string ans="";
    int count=1;

    for(int i=1; i<=s.size(); i++) 
    {
        if(i<s.size()&&s[i]==s[i-1]){count++;} 
        else 
        {

            while(count>k) 
            {
                ans+=to_string(k)+s[i-1];
                count-=k;
            }
            ans+=to_string(count)+s[i-1];
            count=1;
        }
    }
    cout<<ans;
    return 0;
}
