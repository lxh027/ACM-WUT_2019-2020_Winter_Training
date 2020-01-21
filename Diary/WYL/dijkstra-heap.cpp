#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<cstring>
#include<queue>
#define N 10002
#define M 500005
#define INF 0x3f3f3f3f
using namespace std;
struct Misaka{
	int v,w,next;
}edge[M];
int dis[N],last[N],n,m,edges;
struct Mikoto{
	int num,dis;
	bool operator <(const Mikoto b)const
	{
		return dis>b.dis;
	}
};
priority_queue<Mikoto> pq;
void addedge(int u,int v,int w)
{
	edges++;
	edge[edges].v=v;
	edge[edges].w=w;
	edge[edges].next=last[u];
	last[u]=edges;
}
void dijkstra(int st)
{
	int u,v,w,k,di;
	memset(dis,0x3f,sizeof(dis));
	dis[st]=0;
	pq.push((Mikoto){st,0});
	while(!pq.empty())
	{
		u=pq.top().num;
		//printf("%d",u);
		di=pq.top().dis;
		pq.pop();
		if(di>dis[u])continue;
		k=last[u];
		while(k>0)
		{
			v=edge[k].v;
			w=edge[k].w;
			if(dis[v]>dis[u]+w)
			{
				dis[v]=dis[u]+w;
				pq.push((Mikoto){v,dis[v]});
			}
			k=edge[k].next;
		}
	}
}
int main()
{   
	int st;
	scanf("%d%d%d",&n,&m,&st);
	for(int i=1;i<=m;i++)
	{
		int t1,t2,t3;
		scanf("%d%d%d",&t1,&t2,&t3);
		addedge(t1,t2,t3);
	}
	dijkstra(st);
	for(int i=1;i<=n;i++)
	if(dis[i]!=INF)printf("%d ",dis[i]);
	else printf("2147483647 ");
	printf("1121");
	return 0;
}
