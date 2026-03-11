#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

bool islet(int left,int right)
{
	return left<right&&left>='a'&&right<='z';
}
bool isdig(int left,int right)
{
	return left<right&&left>='0'&&right<='9';
}

int main()
{
int p1,p2,p3;string s,ret;
cin>>p1>>p2>>p3>>s;
ret.reserve(200);
for(int i=0;i<s.size();i++)
{
if(s[i]!='-')
{
	ret+=s[i];
}
else
{
	if(i==0||i==s.size()-1
		||!islet(s[i-1],s[i+1])&&!isdig(s[i-1],s[i+1]))
	{
		ret+='-';
	}
	else
	{
			string tmp;
			for(int j=s[i-1]+1;j<s[i+1];j++)
			{
			  char c=j;
              int k=p2;
              if(p1==2&&islet(s[i-1],s[i+1]))
                {
                	c-=32;
                }
                if(p1==3) c='*';
              while(k--)
              {
                tmp+=c;
              }
              
			}
			if(p3==2)
			reverse(tmp.begin(),tmp.end());
		ret+=tmp;
	}

}
}
cout<<ret;
	return 0;
}