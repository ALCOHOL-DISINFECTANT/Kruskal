#include<stdio.h>

#define VERMAX 50
#define EDGEMAX 200

typedef struct EdgeType
{
	int from, to;//�ߵ���������
	int weight;//�ߵ�Ȩֵ
}Edge_T;

typedef struct EdgeGraph
{
	int verNUM, edgeNUM;//ͼ�Ķ������ͱ���
}Edge_G;

int FindRoot(int v, int ar[]);//Ѱ������
void quickSort(Edge_T ar[], int left, int right);//����������
void Kruskal(Edge_T ar[], Edge_G inform);//Kruskal�㷨����
Edge_G input(Edge_T ar[]);//������Ϣ


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
	Edge_G inform;//�����������Ϣ 
	
	printf("�����붥������ͱߵĸ�����");
	scanf("%d %d", &ver, &edge);
	
	inform.verNUM = ver;
	inform.edgeNUM = edge;

	for(i = 0;i < edge; i++)
	{
		printf("������ߵ���㡢�յ�ı��(��Χ0-%d)��Ȩֵ��" ,ver-1);
		scanf("%d %d %d",&ver1, &ver2, &edge1);
		
		if(ver1 < 0 || ver1 > 5 || ver2 < 0 || ver2 > 5)
		{
			printf("������������Χ�� 0-%d �ĵ���\n",ver-1);
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
	printf("���������\n"); 
	
	for(i = 0;i < edge;i++)
		printf("    %d %d %d\n",edgeM[i].from, edgeM[i].to, edgeM[i].weight);
		
	return inform;//���ص���ߵ���Ϣ 
}
void quickSort(Edge_T edgeM[EDGEMAX], int L, int R)//�õݹ�ķ�ʽ�������� 
{
	if(L > R)
		return;
	
	int left, right;
	Edge_T Pivot;
	
	left = L;
	right = R;
	
	Pivot.from = edgeM[left].from;//ѡ��һ������Ϊ�м��� 
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
	quickSort(edgeM, L, right-1);//����Pivot��ߵ��� 
	quickSort(edgeM, right+1, R);//����Pivot�ұߵ��� 
}
void Kruskal(Edge_T edgeM[EDGEMAX], Edge_G inform)//Kruskal�㷨���� 
{
	int i, vex1, vex2, parent[VERMAX];
	
	for(i = 0;i < inform.verNUM;i++)
		parent[i] = -1;
	
	printf("��С������Ϊ: ");
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
	printf("\n��������Ϊ��\n");
	
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

