#include <string>
#include <iostream>

using namespace std;

const int N = 1e6 + 10;

int arr1[N],arr2[N],c[N];
int la,lb,lc;

void add(int c[],int arr1[],int arr2[])
{
	for(int i=0;i<lc;i++)
{
c[i]+=arr1[i]+arr2[i];
c[i+1]+=c[i]/10;
c[i]%=10;
}
if(c[lc]) lc++;
}

int main()
{
string a,b; cin>>a>>b;
la=a.size(),lb=b.size(),lc=max(la,lb);

for(int i=0;i<la;i++) arr1[la-i-1]=a[i]-'0';
for(int i=0;i<lb;i++) arr2[lb-i-1]=b[i]-'0';

add(c,arr1,arr2);

for(int i=lc-1;i>=0;i--) cout<<c[i];

return 0;
}