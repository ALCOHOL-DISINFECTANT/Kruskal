#include<stdio.h>

#define VERMAX 50
#define EDGEMAX 200

typedef struct EdgeType
{
	int from, to;//边的两个顶点
	int weight;//边的权值
}Edge_T;

typedef struct EdgeGraph
{
	int verNUM, edgeNUM;//图的顶点数和边数
}Edge_G;

int FindRoot(int v, int ar[]);//寻根函数
void quickSort(Edge_T ar[], int left, int right);//快速排序函数
void Kruskal(Edge_T ar[], Edge_G inform);//Kruskal算法函数
Edge_G input(Edge_T ar[]);//输入信息


int main()
{
	Edge_T edgeM[EDGEMAX];
	Edge_G inform;
	int i, j, ver, edge;
	
	inform = input(edgeM);
	Kruskal(edgeM, inform);
	
	return;	
}

Edge_G input(Edge_T edgeM[EDGEMAX])
{
	int ver, ver1, ver2, edge, edge1, i;
	Edge_G inform;//储存边与点的信息 
	
	printf("请输入顶点个数和边的个数：");
	scanf("%d %d", &ver, &edge);
	
	inform.verNUM = ver;
	inform.edgeNUM = edge;

	for(i = 0;i < edge; i++)
	{
		printf("请输入边的起点、终点的编号(范围0-%d)和权值：" ,ver-1);
		scanf("%d %d %d",&ver1, &ver2, &edge1);
		
		if(ver1 < 0 || ver1 > 5 || ver2 < 0 || ver2 > 5)
		{
			printf("请输入两个范围在 0-%d 的点编号\n",ver-1);
			continue;
		}
		else
		{
			edgeM[i].from = ver1;
			edgeM[i].to = ver2;
			edgeM[i].weight = edge1;
		}	
	}
		
	quickSort(edgeM, 0, edge-1);
	printf("经过排序后：\n"); 
	
	for(i = 0;i < edge;i++)
		printf("    %d %d %d\n",edgeM[i].from, edgeM[i].to, edgeM[i].weight);
		
	return inform;//返回点与边的信息 
}
void quickSort(Edge_T edgeM[EDGEMAX], int L, int R)//用递归的方式快速排序 
{
	if(L > R)
		return;
	
	int left, right;
	Edge_T Pivot;
	
	left = L;
	right = R;
	
	Pivot.from = edgeM[left].from;//选第一个数作为中间数 
	Pivot.to = edgeM[left].to;
	Pivot.weight = edgeM[left].weight;
		
	while(left < right)
	{
		while(left < right && edgeM[right].weight >= Pivot.weight)
			right--;
		if(left < right)
		{
			edgeM[left].weight = edgeM[right].weight;
			edgeM[left].from = edgeM[right].from;
			edgeM[left].to = edgeM[right].to;
		}
		while(left < right && edgeM[left].weight <= Pivot.weight)
			left++;
		if(left < right)
		{
			edgeM[right].weight = edgeM[left].weight;
			edgeM[right].from = edgeM[left].from;
			edgeM[right].to = edgeM[left].to;			
		}
		if(left >= right)
		{
			edgeM[left].weight = Pivot.weight;
			edgeM[left].from = Pivot.from;
			edgeM[left].to = Pivot.to;
		}		
	}
	quickSort(edgeM, L, right-1);//处理Pivot左边的数 
	quickSort(edgeM, right+1, R);//处理Pivot右边的数 
}
void Kruskal(Edge_T edgeM[EDGEMAX], Edge_G inform)//Kruskal算法核心 
{
	int i, vex1, vex2, parent[VERMAX];
	
	for(i = 0;i < inform.verNUM;i++)
		parent[i] = -1;
	
	printf("最小生成树为: ");
	for(i = 0;i < inform.edgeNUM;i++)
	{
		vex1 = FindRoot(edgeM[i].from, parent);
		vex2 = FindRoot(edgeM[i].to, parent);
		
		if(vex1 != vex2)
		{
			parent[vex2] = vex1;
			printf(" (%d, %d)%d  ",edgeM[i].from, edgeM[i].to, edgeM[i].weight);			
		}
	}
	printf("\n辅助数组为：\n");
	
	for(i = 0;i < inform.verNUM;i++)
		printf("%d ",i);
	printf("\n");
	for(i = 0;i < inform.verNUM;i++)
		printf("%d ",parent[i]);
	
	
}
int FindRoot(int v, int parent[VERMAX])
{
	int t;
	
	t = v;
	while(parent[t] > -1)
		t = parent[t];
	return t;
}

