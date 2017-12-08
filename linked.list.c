/*******************************************************
*                      程序简介                        *
*  名 称：线性表的基本操作                             *
*  内 容：链表创建，结点插入、删除，链表合并等         *
*  作 者：李凌霄 2014220701004                         *
*  时 间：2015.04.03                                    *
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define success 1
#define failure 0


//定义学生结构
typedef struct stuInfo
{
	char stuName[10]; //姓名
	long age;         //年龄（19900101）
}STU;


//定义链表结点
typedef struct node
{
	STU data;
	struct node *next;
}ListNode,*ListNodePtr;

typedef ListNodePtr List,*ListPtr;

ListPtr L[10];             //定义信息表
int flag=0;                //文件信息是否读取标志
ListNodePtr All_Over[10];  //给L赋值，避免发生错误
void Init()                //初始化L
{
	int i;
	
	for(i=0;i<10;i++)
	{
		All_Over[i]=(ListNodePtr)malloc(sizeof(ListNode));
		L[i]=&All_Over[i];
	}
}

int L_cnt=1; //只有从文件读取到的信息储存到L[0]，其他的信息储存到L[L_cnt],L_cnt={1,2...9}


//检验文件是否存在
int Check_File()
{
	FILE *fp=fopen("G:\\stu.txt","r");

	if(!fp)
	{
		printf("学生信息初始化文件不存在！\n请将文件存放G盘下并命名为“stu.txt”!\n");
		return failure;
	}
	else
	{
		fclose(fp);
		return success;
	}
}


//从文件读取信息
STU* readStuInfo(FILE* fp)
{
	STU* p=(STU*)malloc(sizeof(STU));
	fscanf(fp,"%s",p->stuName);//stuName为数组，不用加取地址符
	fscanf(fp,"\t%ld\n",&p->age);
	
	return p;  //data=*p
}


//向文件写入信息
void writeStuInfo(FILE* fp,STU* p)
{
	fprintf(fp,"%s\t",p->stuName);
	fprintf(fp,"%ld\n",p->age);

}


//将修改信息存入文本
void Info_Save(ListPtr L)
{
	ListNodePtr p,q;
	FILE *fp=fopen("G:\\stu.txt","w");
	p=(*L)->next;

	while(p)
	{
		writeStuInfo(fp,&p->data);
		p=p->next;
	}
	fclose(fp);
}


//指针定位,寻找某点前驱
int List_SetPosition(ListPtr L,int pos,ListNodePtr *ptr)//*ptr为待寻找点的前驱指针
{
	int flag=failure,i=0;
	ListNodePtr p=*L;

	while(p && i<pos)
	{
		p=p->next;
		i++;
	}
	if(p && i==pos)
	{
		*ptr=p;
		flag=success;
	}
	return flag;
}


//插入结点
int List_Insert(ListPtr L,int pos,STU stu)//在pos出插入结点
{
	int status;
	ListNodePtr pre,s;

	status=List_SetPosition(L,pos-1,&pre);//找到待插入点的前驱
	
	if(status==success)
	{
		s=(ListNodePtr)malloc(sizeof(ListNode));
		s->next=NULL;

		if(s)
		{
			s->data=stu;
			s->next=pre->next;
			pre->next=s;
		}
		else
			status=failure;
	}
	return status;
}


//删除结点
int List_Remove(ListPtr L,int pos)//删除pos处的结点
{
	int status;
	ListNodePtr pre,q;

	status=List_SetPosition(L,pos-1,&pre);//找到待删除点的前驱

	if(status=success)
	{
		q=pre->next;
		pre->next=q->next;
		free(q);
	}
	return status;
}


//创建信息链表
int List_Creat(ListPtr L,int choice)
{
	int i=0,j,res;
	char choose;
	ListNodePtr q,p;
	STU s[MAX];

	if(choice)     //用户手动创建信息
	{
		printf("请输入相关信息（姓名、年龄以‘Tab’键隔开）：\n");
		do
		{
			scanf("%s\t%ld",s[i].stuName,&s[i].age);
			i++;
			printf("是否输入完毕？\n请选择：（Y\tN）\n");
			getchar();     //吸收键盘缓存
			choose=getchar();
		}while(i<MAX && choose=='Y');
	}
	else           //系统读取文本创建信息
	{
		res=Check_File();

		if(res==success)     //文件读取成功
		{
			FILE *fp=fopen("G:\\stu.txt","r");

			while(!feof(fp) && i<MAX)
			{
				s[i]=*readStuInfo(fp);
				i++;
			}
			flag=1;
		}
		else
		{
			printf("读取文件失败！\n");
			return failure;
		}
	}

	j=i-1;   //指向最后一个数据元素
	q=(ListNodePtr)malloc(sizeof(ListNode));//建立带头结点的空链表
	q->next=NULL;

	while(j>=0)      //尚有数据元素未处理
	{
		p=(ListNodePtr)malloc(sizeof(ListNode));
		if(!p)
		{
			printf("空间分配失败！\n");
			break;
		}

		p->data=s[j];
		p->next =q->next;
		q->next =p;
		j=j-1;
	}
	*L=q;
	printf("信息表创建成功！\n");
}


//清空链表
int List_Clear(ListPtr L)
{
	ListNodePtr p=*L,q=p->next;

	while(q)
	{
		p->next=q->next;
		free(q);
		q=p->next;
	}
	return 0;
}


//销毁链表
void List_Destory(ListPtr L)
{
	List_Clear(L);
	free(*L);
}

//链表排序
int List_Sort(ListPtr L,int choose)  //冒泡法排序
{
	int i=0,j;
	ListNodePtr p,q,r=NULL;
	STU *s,*t,EX;    //EX用于交换两个数据信息
	p=(*L)->next;
	if(!*L)
	{
		printf("未找到相关学生信息！\n");
		return 0;
	}

	while(p)
	{
		i++;
		p=p->next ;
	}

	if(choose>0)  //升序
	{
		for(j=i;j>0;j--)
		{
			p = (*L)->next;
			q = p->next;
			s = &(p->data);
			t = &(q->data);
			
			while( q != r )
			{
				if(s->age > t->age)
				{
					EX = *s;
					*s = *t;
					*t = EX;
				}
				else if((s->age == t->age) && (!strcmp(s->stuName,t->stuName)))    //遇到重复信息
				{
					p->next = q->next;
					free(q);
					q = NULL;
				}

				p = p->next;    //p = q;
				q = p->next;    //q = q->next;
				s = &(p->data);
				if(q)
					t = &(q->data);
			}
			r = p;
		}
	}

	else if(choose<0)  //降序
	{
		for(j=i;j>0;j--)
		{
			p = (*L)->next;
			q = p->next;
			s = &(p->data);
			t = &(q->data);

			while( q != r )
			{
				if(s->age < t->age)
				{
					EX = *s;
					*s = *t;
					*t = EX;
				}
				else if((s->age == t->age) && (!strcmp(s->stuName,t->stuName)))
				{
					p->next = q->next;
					free(q);
					q = NULL;
				}

				p = p->next;    //p = q;
				q = p->next;    //q = q->next;
				s = &(p->data);
				if(q)
					t = &(q->data);
			}
			r = p;
		}
	}
}


//链表合并
int List_Merge(ListPtr La,ListPtr Lb)
{
	ListNodePtr p,q;

	if(!*La||!Lb)
	{
		printf("信息有误！");
		return 0;
	}

	p=(*La)->next;

	while(p)
	{
		q=p;
		p=p->next;
	}
	q->next=(*Lb)->next;
	free(*Lb);
	*Lb=NULL;

	List_Sort(La,-1);
}


//链表信息打印
int List_Output(ListPtr L,int L_cnt,int pos)
{
	int i = 1;
	ListNodePtr p;
	STU s;

	if(!L)
	{
		printf("信息有误！\n");
		return failure;
	}

	p = (*L)->next;
	s = p->data;

	printf("学生信息表%d：\n",L_cnt+1);
	do
	{
		if(!pos){
		printf("学生%d:%s\t%ld\n",i,s.stuName,s.age);
		i++;
		p = p->next;

		if(p)
			s = p->data;
		}
		else
		{
			while( p && i<pos )
			{
				i++;
				p = p->next;
			}
			s = p->data;
			printf("学生%d:%s\t%ld\n",i,s.stuName,s.age);
		}
	}while( p );

	printf("以上为全部学生信息！\n");
	return success;
}


//开始界面
void start()
{
	printf("--------------学生信息操作选项-------------\n"
		"*1.系统读入文本创建学生信息表\n"
		"*2.用户输入信息创建学生信息表\n"
		"*3.删除学生信息\n"
		"*4.插入学生信息\n"
		"*5.合并两个学生信息表\n"
		"*6.退出系统\n"
		"   请选择：");
}


//主函数
int main(void)
{
	int choice;
	STU stu;
	Init();

	while(1)
	{
		start();
		scanf("%d",&choice);

		switch(choice)
		{
		case 1:
			List_Creat(L[0],0);//系统从文件读入文本信息
			List_Output(L[0],0,0);//打印链表
			break;
			case 2:
			List_Creat( L[L_cnt],1 );           //手动创建链表
			List_Output( L[L_cnt],L_cnt,0 );          //打印链表
			L_cnt++;
			break;
		case 3:
			if(flag)                 //判断是否自动生成信息表
			{
				List_Output( L[0],0,0 );	
				printf("请输入您要删除的学生信息序号：");
				scanf("%d",&choice);

				if(List_Remove(L[0],choice))     //删除结点
				{
					printf("删除成功！\n");
					List_Output( L[0],0,0 );
				}
				else
					printf("删除失败！\n");
			}
			else
				printf("信息文件不存在！\n");
			break;
		case 4:
			if(flag)                 //判断是否自动生成信息表
			{
				List_Output( L[0],0,0 );

				printf("请输入您要插入信息的序号（插入该序号后）：\n");
				scanf("%d",&choice);
				printf("请输入相关信息（姓名、年龄以‘Tab’键隔开>:\n");
				scanf("%s\t%ld",stu.stuName,&stu.age);

				if(List_Insert(L[0],choice+1,stu))     //插入节点
				{
					printf("插入成功！\n");
					List_Output( L[0],0,0 );
				}
				else
					printf("插入失败！\n");
			}
			break;
		case 5:
			printf("您需要手动创建两个信息表：\n");
			List_Creat( L[L_cnt],1 );           //手动创建链表1
			List_Sort( L[L_cnt],1 );            //升序排序
			List_Output( L[L_cnt],L_cnt,0 );
			L_cnt++;
			List_Creat( L[L_cnt],1 );           //手动创建链表2
			List_Sort( L[L_cnt],1 );            //升序排序
			List_Output( L[L_cnt],L_cnt,0 );
			L_cnt++;

			List_Merge( L[L_cnt-2],L[L_cnt-1] );   //合并信息表
			printf("合并链表成功！\n");
			List_Output( L[L_cnt-2],L_cnt-2,0 );

			break;

		default:
			if(flag)     //从文件读取信息成功
			{
				printf("保存数据中，请稍后！\n");
				Info_Save(L[0]);
				List_Clear(L[0]);
				List_Destory(L[0]);
				printf("数据保存成功！\n");
			}
			for(choice=1;choice<10;choice++)
			{
				free(All_Over[choice]);
				All_Over[choice] = NULL;
			}
			printf("成功系统退出，谢谢您的使用！\n");
			return 0;
		}
	}
}
/*------------------------谢谢批阅!---------------------------*/
