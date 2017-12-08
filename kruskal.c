/*******************************************************
*                      ������                        *
*  �� �ƣ���С������Kruskal �㷨                       *
*  �� �ݣ�����Kruskal �㷨������С��������             *
*  �� �ߣ������� 2014220701004                         *
*  ʱ �䣺2015.06.05                                   *
********************************************************/

#include <stdio.h>
#define max 20

int arcvisited[36];    //Kruskal��������飬�Է�ֹ���ֻ�·��Ĭ�϶���Ϊ6��

typedef struct acr	   //���Ķ���
{
	int pre;		   //����һ���
	int bak;		   //������һ�ڵ�
	int weight;		   //����Ȩ��
}edg;

typedef struct ArcCell //ͼ���ڽӾ���Ľṹ���壬ArcCellΪ�����ÿ��Ԫ��	
{
	int adj;		   //�ߵ�Ȩֵ
}ArcCell,AdjMatrix[6][6];//Ĭ�϶���Ϊ6��

typedef struct		   //ͼ��Graph���ı�ʾ	
{
	AdjMatrix arcs;	   //ͼ���ڽӾ���	
	int vexnum,arcnum; //ͼ�Ķ�����Ŀ���ߵ���Ŀ
}MGraph_L;


//������ͨͼ�ж����������ĸ��ڵ�������arcvisited�е����
int find(int arcvisited[],int f)  
{
	while(arcvisited[f]>0)
		f = arcvisited[f];

	return f;
}


//��Kruskal�㷨������n�������ͼedgs����С������
void kruscal_arc(MGraph_L G)
{
	edg edgs[36]={10000};
	int i,j,k=0;
	int x,y,m,n;
	int buf,edf;

    for(i=0;i!= G.vexnum;++i)    //ͨ��ͼG���ڽӾ����ʾ������ñߵ�����
		for(j=i;j!=G.vexnum;++j)
		{
			if(G.arcs[i][j].adj!=10000)
			{                    //ת���ߵı�ʾ
				edgs[k].pre = i;
				edgs[k].bak = j;
				edgs[k].weight = G.arcs[i][j].adj;
				++k;
			}
		}

	for(i=0;i != G.arcnum;++i)   //��ʼ���ʱ�־
		arcvisited[i] = 0;

	printf("��С·�������л�Ϊ��\n");

	for(j = 0;j != G.arcnum;++j)
	{
		m = 10000;
		for(i=0;i!=G.arcnum;++i)
		{
			if(edgs[i].weight<m) //���Ȩֵ��С�ı�
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


//������
int main()
{
	int a,b,arcsnum,t,weight,chioce;
	MGraph_L G;          //����ͼG

	while(1)
	{
		printf("-------------��С������ϵͳ------------\n"
			"	1.�û�¼��ԭͼ��Ϣ\n"
			"	2.�˳�ϵͳ\n"
			"��ѡ��");
		scanf("%d",&chioce);

		switch(chioce)
		{
		case 1:
			for(a=0;a<6;a++)     //��ʼ���ߵ�Ȩֵ
		    for(b=0;b<6;b++)
			G.arcs[a][b].adj=10000;

	        printf("������ͼ�ı�����");
	        scanf("%d",&arcsnum);

	        G.arcnum=arcsnum;
	        G.vexnum=6;

	        for(t=1;t<=arcsnum;t++)
	       {
			   printf("������ÿ���ߵ������㼰��Ȩֵ������<2,3,10>):");
		       fflush(stdin);   //ˢ�±�׼���뻺�����������뻺������Ķ�������
		       scanf("<%d,%d,%d>",&a,&b,&weight);

		       G.arcs[a][b].adj=weight;
		       G.arcs[b][a].adj=weight;
	       }

	       kruscal_arc(G);
		   break;
	    case 2:
			printf("\nϵͳ���˳���ллʹ�ã�");
			return 0;
		default:
			break;
		}
	}

	return 0;
}