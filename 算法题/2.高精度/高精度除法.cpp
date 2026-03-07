#include <string>
#include <iostream>
using namespace std;

const int N = 1e6 + 10;

int a[N],c[N];long long b;
int la,lc;

void div(int* c,int* a,long long b)
{
long long t=0;
for(int i=la - 1;i>=0;i--)
{
//计算当前的被除数
	t=t*10+a[i];
    c[i]=t/b;
    t%=b;
}
while(lc>1&&!c[lc-1]) lc--;
}

int main()
{
string x; cin>>x>>b;
long long k=b;
int lb=0;
while(k)
{
	k/=10;
    lb++;
}
la=x.size(),lc=la;

for(int i=0;i<la;i++) a[la - 1 - i]=x[i]-'0';
div(c,a,b);

for(int i=lc-1;i>=0;i--) cout<<c[i];

return 0;
}