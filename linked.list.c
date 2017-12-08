/*******************************************************
*                      ������                        *
*  �� �ƣ����Ա�Ļ�������                             *
*  �� �ݣ��������������롢ɾ��������ϲ���         *
*  �� �ߣ������� 2014220701004                         *
*  ʱ �䣺2015.04.03                                    *
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define success 1
#define failure 0


//����ѧ���ṹ
typedef struct stuInfo
{
	char stuName[10]; //����
	long age;         //���䣨19900101��
}STU;


//����������
typedef struct node
{
	STU data;
	struct node *next;
}ListNode,*ListNodePtr;

typedef ListNodePtr List,*ListPtr;

ListPtr L[10];             //������Ϣ��
int flag=0;                //�ļ���Ϣ�Ƿ��ȡ��־
ListNodePtr All_Over[10];  //��L��ֵ�����ⷢ������
void Init()                //��ʼ��L
{
	int i;
	
	for(i=0;i<10;i++)
	{
		All_Over[i]=(ListNodePtr)malloc(sizeof(ListNode));
		L[i]=&All_Over[i];
	}
}

int L_cnt=1; //ֻ�д��ļ���ȡ������Ϣ���浽L[0]����������Ϣ���浽L[L_cnt],L_cnt={1,2...9}


//�����ļ��Ƿ����
int Check_File()
{
	FILE *fp=fopen("G:\\stu.txt","r");

	if(!fp)
	{
		printf("ѧ����Ϣ��ʼ���ļ������ڣ�\n�뽫�ļ����G���²�����Ϊ��stu.txt��!\n");
		return failure;
	}
	else
	{
		fclose(fp);
		return success;
	}
}


//���ļ���ȡ��Ϣ
STU* readStuInfo(FILE* fp)
{
	STU* p=(STU*)malloc(sizeof(STU));
	fscanf(fp,"%s",p->stuName);//stuNameΪ���飬���ü�ȡ��ַ��
	fscanf(fp,"\t%ld\n",&p->age);
	
	return p;  //data=*p
}


//���ļ�д����Ϣ
void writeStuInfo(FILE* fp,STU* p)
{
	fprintf(fp,"%s\t",p->stuName);
	fprintf(fp,"%ld\n",p->age);

}


//���޸���Ϣ�����ı�
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


//ָ�붨λ,Ѱ��ĳ��ǰ��
int List_SetPosition(ListPtr L,int pos,ListNodePtr *ptr)//*ptrΪ��Ѱ�ҵ��ǰ��ָ��
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


//������
int List_Insert(ListPtr L,int pos,STU stu)//��pos��������
{
	int status;
	ListNodePtr pre,s;

	status=List_SetPosition(L,pos-1,&pre);//�ҵ���������ǰ��
	
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


//ɾ�����
int List_Remove(ListPtr L,int pos)//ɾ��pos���Ľ��
{
	int status;
	ListNodePtr pre,q;

	status=List_SetPosition(L,pos-1,&pre);//�ҵ���ɾ�����ǰ��

	if(status=success)
	{
		q=pre->next;
		pre->next=q->next;
		free(q);
	}
	return status;
}


//������Ϣ����
int List_Creat(ListPtr L,int choice)
{
	int i=0,j,res;
	char choose;
	ListNodePtr q,p;
	STU s[MAX];

	if(choice)     //�û��ֶ�������Ϣ
	{
		printf("�����������Ϣ�������������ԡ�Tab������������\n");
		do
		{
			scanf("%s\t%ld",s[i].stuName,&s[i].age);
			i++;
			printf("�Ƿ�������ϣ�\n��ѡ�񣺣�Y\tN��\n");
			getchar();     //���ռ��̻���
			choose=getchar();
		}while(i<MAX && choose=='Y');
	}
	else           //ϵͳ��ȡ�ı�������Ϣ
	{
		res=Check_File();

		if(res==success)     //�ļ���ȡ�ɹ�
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
			printf("��ȡ�ļ�ʧ�ܣ�\n");
			return failure;
		}
	}

	j=i-1;   //ָ�����һ������Ԫ��
	q=(ListNodePtr)malloc(sizeof(ListNode));//������ͷ���Ŀ�����
	q->next=NULL;

	while(j>=0)      //��������Ԫ��δ����
	{
		p=(ListNodePtr)malloc(sizeof(ListNode));
		if(!p)
		{
			printf("�ռ����ʧ�ܣ�\n");
			break;
		}

		p->data=s[j];
		p->next =q->next;
		q->next =p;
		j=j-1;
	}
	*L=q;
	printf("��Ϣ�����ɹ���\n");
}


//�������
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


//��������
void List_Destory(ListPtr L)
{
	List_Clear(L);
	free(*L);
}

//��������
int List_Sort(ListPtr L,int choose)  //ð�ݷ�����
{
	int i=0,j;
	ListNodePtr p,q,r=NULL;
	STU *s,*t,EX;    //EX���ڽ�������������Ϣ
	p=(*L)->next;
	if(!*L)
	{
		printf("δ�ҵ����ѧ����Ϣ��\n");
		return 0;
	}

	while(p)
	{
		i++;
		p=p->next ;
	}

	if(choose>0)  //����
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
				else if((s->age == t->age) && (!strcmp(s->stuName,t->stuName)))    //�����ظ���Ϣ
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

	else if(choose<0)  //����
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


//����ϲ�
int List_Merge(ListPtr La,ListPtr Lb)
{
	ListNodePtr p,q;

	if(!*La||!Lb)
	{
		printf("��Ϣ����");
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


//������Ϣ��ӡ
int List_Output(ListPtr L,int L_cnt,int pos)
{
	int i = 1;
	ListNodePtr p;
	STU s;

	if(!L)
	{
		printf("��Ϣ����\n");
		return failure;
	}

	p = (*L)->next;
	s = p->data;

	printf("ѧ����Ϣ��%d��\n",L_cnt+1);
	do
	{
		if(!pos){
		printf("ѧ��%d:%s\t%ld\n",i,s.stuName,s.age);
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
			printf("ѧ��%d:%s\t%ld\n",i,s.stuName,s.age);
		}
	}while( p );

	printf("����Ϊȫ��ѧ����Ϣ��\n");
	return success;
}


//��ʼ����
void start()
{
	printf("--------------ѧ����Ϣ����ѡ��-------------\n"
		"*1.ϵͳ�����ı�����ѧ����Ϣ��\n"
		"*2.�û�������Ϣ����ѧ����Ϣ��\n"
		"*3.ɾ��ѧ����Ϣ\n"
		"*4.����ѧ����Ϣ\n"
		"*5.�ϲ�����ѧ����Ϣ��\n"
		"*6.�˳�ϵͳ\n"
		"   ��ѡ��");
}


//������
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
			List_Creat(L[0],0);//ϵͳ���ļ������ı���Ϣ
			List_Output(L[0],0,0);//��ӡ����
			break;
			case 2:
			List_Creat( L[L_cnt],1 );           //�ֶ���������
			List_Output( L[L_cnt],L_cnt,0 );          //��ӡ����
			L_cnt++;
			break;
		case 3:
			if(flag)                 //�ж��Ƿ��Զ�������Ϣ��
			{
				List_Output( L[0],0,0 );	
				printf("��������Ҫɾ����ѧ����Ϣ��ţ�");
				scanf("%d",&choice);

				if(List_Remove(L[0],choice))     //ɾ�����
				{
					printf("ɾ���ɹ���\n");
					List_Output( L[0],0,0 );
				}
				else
					printf("ɾ��ʧ�ܣ�\n");
			}
			else
				printf("��Ϣ�ļ������ڣ�\n");
			break;
		case 4:
			if(flag)                 //�ж��Ƿ��Զ�������Ϣ��
			{
				List_Output( L[0],0,0 );

				printf("��������Ҫ������Ϣ����ţ��������ź󣩣�\n");
				scanf("%d",&choice);
				printf("�����������Ϣ�������������ԡ�Tab��������>:\n");
				scanf("%s\t%ld",stu.stuName,&stu.age);

				if(List_Insert(L[0],choice+1,stu))     //����ڵ�
				{
					printf("����ɹ���\n");
					List_Output( L[0],0,0 );
				}
				else
					printf("����ʧ�ܣ�\n");
			}
			break;
		case 5:
			printf("����Ҫ�ֶ�����������Ϣ��\n");
			List_Creat( L[L_cnt],1 );           //�ֶ���������1
			List_Sort( L[L_cnt],1 );            //��������
			List_Output( L[L_cnt],L_cnt,0 );
			L_cnt++;
			List_Creat( L[L_cnt],1 );           //�ֶ���������2
			List_Sort( L[L_cnt],1 );            //��������
			List_Output( L[L_cnt],L_cnt,0 );
			L_cnt++;

			List_Merge( L[L_cnt-2],L[L_cnt-1] );   //�ϲ���Ϣ��
			printf("�ϲ�����ɹ���\n");
			List_Output( L[L_cnt-2],L_cnt-2,0 );

			break;

		default:
			if(flag)     //���ļ���ȡ��Ϣ�ɹ�
			{
				printf("���������У����Ժ�\n");
				Info_Save(L[0]);
				List_Clear(L[0]);
				List_Destory(L[0]);
				printf("���ݱ���ɹ���\n");
			}
			for(choice=1;choice<10;choice++)
			{
				free(All_Over[choice]);
				All_Over[choice] = NULL;
			}
			printf("�ɹ�ϵͳ�˳���лл����ʹ�ã�\n");
			return 0;
		}
	}
}
/*------------------------лл����!---------------------------*/
