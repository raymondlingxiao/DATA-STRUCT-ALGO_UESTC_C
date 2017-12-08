/*******************************************************
*                      程序简介                        *
*  名 称：最小生成树Kruskal 算法                       *
*  内 容：利用Kruskal 算法生成最小生成树等             *
*  作 者：李凌霄 2014220701004                         *
*  时 间：2015.06.05                                   *
********************************************************/

#include <stdio.h>
#define max 20

int arcvisited[36];    //Kruskal弧标记数组，以防止出现回路，默认顶点为6个

typedef struct acr	   //弧的定义
{
	int pre;		   //弧的一结点
	int bak;		   //弧的另一节点
	int weight;		   //弧的权重
}edg;

typedef struct ArcCell //图的邻接矩阵的结构定义，ArcCell为矩阵的每个元素	
{
	int adj;		   //边的权值
}ArcCell,AdjMatrix[6][6];//默认顶点为6个

typedef struct		   //图（Graph）的表示	
{
	AdjMatrix arcs;	   //图的邻接矩阵	
	int vexnum,arcnum; //图的顶点数目、边的数目
}MGraph_L;


//查找连通图中顶点所在树的根节点在数组arcvisited中的序号
int find(int arcvisited[],int f)  
{
	while(arcvisited[f]>0)
		f = arcvisited[f];

	return f;
}


//用Kruskal算法构造有n个顶点的图edgs的最小生成树
void kruscal_arc(MGraph_L G)
{
	edg edgs[36]={10000};
	int i,j,k=0;
	int x,y,m,n;
	int buf,edf;

    for(i=0;i!= G.vexnum;++i)    //通过图G的邻接矩阵表示法，求得边的数据
		for(j=i;j!=G.vexnum;++j)
		{
			if(G.arcs[i][j].adj!=10000)
			{                    //转换边的表示
				edgs[k].pre = i;
				edgs[k].bak = j;
				edgs[k].weight = G.arcs[i][j].adj;
				++k;
			}
		}

	for(i=0;i != G.arcnum;++i)   //初始访问标志
		arcvisited[i] = 0;

	printf("最小路径的所有弧为：\n");

	for(j = 0;j != G.arcnum;++j)
	{
		m = 10000;
		for(i=0;i!=G.arcnum;++i)
		{
			if(edgs[i].weight<m) //求得权值最小的边
			{
				m = edgs[i].weight;
				x = edgs[i].pre;
				y = edgs[i].bak;
				n = i;
			}
		}

		buf = find(arcvisited,x);
		edf = find(arcvisited,y);
		edgs[n].weight = 10000;

		if(buf!=edf)
		{
			arcvisited[buf] = edf;
			printf("(%d , %d) %d\n",x,y,m);
		}
	}
}


//主函数
int main()
{
	int a,b,arcsnum,t,weight,chioce;
	MGraph_L G;          //定义图G

	while(1)
	{
		printf("-------------最小生成树系统------------\n"
			"	1.用户录入原图信息\n"
			"	2.退出系统\n"
			"请选择：");
		scanf("%d",&chioce);

		switch(chioce)
		{
		case 1:
			for(a=0;a<6;a++)     //初始化边的权值
		    for(b=0;b<6;b++)
			G.arcs[a][b].adj=10000;

	        printf("请输入图的边数：");
	        scanf("%d",&arcsnum);

	        G.arcnum=arcsnum;
	        G.vexnum=6;

	        for(t=1;t<=arcsnum;t++)
	       {
			   printf("请输入每条边的两顶点及其权值（形如<2,3,10>):");
		       fflush(stdin);   //刷新标准输入缓冲区，把输入缓冲区里的东西丢弃
		       scanf("<%d,%d,%d>",&a,&b,&weight);

		       G.arcs[a][b].adj=weight;
		       G.arcs[b][a].adj=weight;
	       }

	       kruscal_arc(G);
		   break;
	    case 2:
			printf("\n系统已退出，谢谢使用！");
			return 0;
		default:
			break;
		}
	}

	return 0;
}