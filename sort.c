/*******************************************************
*                      ������                        *
*  �� �ƣ����������                                   *
*  �� �ݣ������������򡢶��ַ����ҵ�                 *
*  �� �ߣ������� 2014220701004                         *
*  ʱ �䣺2015.05.29                                   *
********************************************************/

#include <stdio.h>
#define MAX 100

int R[MAX];   //ȫ�����飬����¼����������ַ�


//Ѱ�һ���Ԫ
int Quick_Partition(int R[],int i,int j)
{//���������һ�λ��֣����λ��Ϊi���Ҷ�λ��Ϊj,����ԪѡΪR[i]
	R[0]=R[i];
	while(i<j)
	{
		while(i<j && R[j]>=R[0])
			j--;           //j������
		if(i<j)
		{
			R[i]=R[j];
			i++;           //�Ȼ���ԪС�ļ�¼���������
		}
		while(i<j && R[i]<=R[0])
			i++;           //i������
		if(i<j)
		{
			R[j]=R[i];
			j--;           //�Ȼ���Ԫ��ļ�¼�������ұ�
		}
	}
	R[i]=R[0];             //����Ԫ��¼������ȷλ��
	return i;
}


//��������
void Quick_Sort(int R[],int s,int t)
{                          //��˳���R[s..t]����������
	int i;                 //���廮��Ԫ
	
	i=Quick_Partition(R,s,t);      //���û��ֹ��̽�˳���һ��Ϊ��
    
	if(i>s)
		Quick_Sort(R,s,i-1);       //�ݹ���ÿ����������
	if(i<t)
		Quick_Sort(R,i+1,t);       //�ݹ���ÿ����������
}


//���ַ�����
int BinarySearch(int SL[],int key,int n)
{   //�ڳ���Ϊn�������SL�ж��ֲ�����ֵ����key������Ԫ��
	//���ҳɹ��򷵻�����������е�λ�ã�����ʧ���򷵻�0

	int low=1;
	int high=n;
	int mid=0;
	
	while(low<=high)
	{
		mid=(low+high)/2;
		if(key == SL[mid])
			return mid;
		else if(key > SL[mid])
			low=mid+1;
		else
			high=mid-1;
	}
	return 0;
}


//������
int main(void)
{
	int i,count=0,choice,data,result;

	while(1)
	{
		printf("-----------------���������----------------\n"
		"����ѡ�\n"
		"1.�����������������\n"
		"2.��������\n"
		"3.���ݲ���\n"
		"4.�˳�����\n"
		"	��ѡ��");

	scanf("%d",&choice);

	switch(choice)
	{
	case 1:
		printf("\n����������Ҫ�������ݵĸ�����");
	    scanf("%d",&count);
		if(count>=MAX)
		{
			printf("\n���ݹ��࣬�޷��������������룡\n");
			break;
		}
		else
		{
			printf("\n����������Ҫ���������:");
			for(i=1;i<=count;i++)
				scanf("%d",&R[i]);
			printf("���ݶ�ȡ�ɹ���\n");
		}
		break;
	case 2:
		Quick_Sort(R,1,count);
		printf("����ɹ���\n");
		printf("������������Ϊ��");
		for(i=1;i<=count;i++)
			printf("%d ",R[i]);
		printf("\n");
		break;
	case 3:
		printf("����������ҵ����ݣ�\n");
		scanf("%d",&data);
		result=BinarySearch(R,data,count);

		if(result)
		{
			printf("���ݲ��ҳɹ���\n"
				"����%dλ�����е�%dλ��\n",data,result);
		}
		else
			printf("����ʧ�ܣ�����Ҫ�������ݲ��ڱ������У�\n");
		break;
	case 4:
		printf("�������˳���ллʹ�ã�\n");
		return 0;
	default :
		return 0;
	}
	}
}