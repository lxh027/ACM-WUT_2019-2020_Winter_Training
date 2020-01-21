#include<bits/stdc++.h>
#define debug(x) cerr<<#x<<x<<endl;
#define abs(a) a>0?a:-a
#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b
#define mms(a) memset(a,0,sizeof(a))
#define input(c) c=' ';while(c==' '||c=='\n')scanf("%c",&c);
#define num(c) c-'0'
#define ll long long
#define cha(a) a+'0'
#define debuga(a,n) for(int i=1;i<=n;i++)printf("%d ",a[i]); printf("\n");
#define buggg printf("BUG");
#define INF 0x3f3f3f3f

using namespace std;
int p,f,c,fmp[5005][505],fk[5005],target[5005];
int main()
{
//	freopen("out.out","w",stdout);
	scanf("%d%d%d",&p,&f,&c);
	for(int i=1;i<=f;i++)scanf("%d",&fk[i]);
	memset(fmp,0x3f,sizeof(fmp));
	memset(target,0,sizeof(target));
	for(int i=1;i<=p;i++)fmp[i][i]=0;
	for(int i=1;i<=c;i++)
	{
		int t1,t2,t3;
		scanf("%d%d%d",&t1,&t2,&t3);
		fmp[t1][t2]=fmp[t2][t1]=t3;
	}
	for(int k=1;k<=p;k++)
	{
		for(int i=1;i<=p;i++)
		{
			for(int j=1;j<=p;j++)
			{
				fmp[i][j]=min(fmp[i][j],fmp[i][k]+fmp[k][j]);
			}
		}
	}

	int ans=INF;
	int rs=0;
	for(int i=1;i<=p;i++)
	{
		for(int j=1;j<=f;j++)
		{
			target[i]+=fmp[i][fk[j]];
		 } 
		if(target[i]<ans){
			ans=target[i];
			rs=i; 
		}
	}
	printf("%d",rs);
	return 0;
}

