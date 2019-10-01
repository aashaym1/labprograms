#include<bits/stdc++.h>
using namespace std;
#define int long long
#define fast ios_base::sync_with_stdio(NULL),cin.tie(0),cout.tie(0);
int n,m,K;
const int mod = 1e9+7;
int dp[1001][1001][11][2];

int f(string &a,string &b,int i,int j,int k,bool running){

  if(!a[i] ||!b[j]){
	if(k!=K)
	  return INT_MIN;
	return 0;
  }
  int &res=dp[i][j][k][running];
  if(res!=-1){
	return res;
  }
  
  res=0;
  
  if(running){
	if(a[i]==b[j]){
		res=max(res,f(a,b,i+1,j+1,k,running)+1);
		if(k<K)
	 	  res=max(res,f(a,b,i+1,j+1,k+1,running)+1);
        }
	res=max(res,f(a,b,i+1,j,k,0));
	res=max(res,f(a,b,i,j+1,k,0));
  }
  else{
	if(a[i]==b[j]){
		if(k<K)
		  res=max(res,f(a,b,i+1,j+1,k+1,1)+1);
	}
	res=max(res,f(a,b,i+1,j,k,0));
	res=max(res,f(a,b,i,j+1,k,0));
  }
  return res;
}

signed main(){
  
  fast;
  cin>>n>>m>>K;
  string a,b;
  cin>>a>>b;
  memset(dp,-1,sizeof(dp));

  cout<<f(a,b,0,0,0,0)<<endl;

}
