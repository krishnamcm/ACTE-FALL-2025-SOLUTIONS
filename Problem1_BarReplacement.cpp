#include <bits/stdc++.h>

using namespace std;

int main()
{

    string s;
    cin>>s;
    string ans="";
    for(auto &k: s)
    {
        if(k=='|'){ans+=' ';}
        else {ans+=k;}
    }
    cout<<ans<<endl;
}
