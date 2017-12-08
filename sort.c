/*******************************************************
*                      程序简介                        *
*  名 称：排序与查找                                   *
*  内 容：快速排序法排序、二分法查找等                 *
*  作 者：李凌霄 2014220701004                         *
*  时 间：2015.05.29                                   *
********************************************************/

#include <stdio.h>
#define MAX 100

int R[MAX];   //全局数组，用来录入所输入的字符


//寻找划分元
int Quick_Partition(int R[],int i,int j)
{//快速排序的一次划分，左端位置为i，右端位置为j,划分元选为R[i]
	R[0]=R[i];
	while(i<j)
	{
		while(i<j && R[j]>=R[0])
			j--;           //j往左移
		if(i<j)
		{
			R[i]=R[j];
			i++;           //比划分元小的记录交换到左边
		}
		while(i<j && R[i]<=R[0])
			i++;           //i往右移
		if(i<j)
		{
			R[j]=R[i];
			j--;           //比划分元大的记录交换到右边
		}
	}
	R[i]=R[0];             //划分元记录置入正确位置
	return i;
}


//快速排序
void Quick_Sort(int R[],int s,int t)
{                          //对顺序表R[s..t]做快速排序
	int i;                 //定义划分元
	
	i=Quick_Partition(R,s,t);      //调用划分过程将顺序表一分为二
    
	if(i>s)
		Quick_Sort(R,s,i-1);       //递归调用快速排序过程
	if(i<t)
		Quick_Sort(R,i+1,t);       //递归调用快速排序过程
}


//二分法查找
int BinarySearch(int SL[],int key,int n)
{   //在长度为n的有序表SL中二分查找其值等于key的数据元素
	//查找成功则返回其在有序表中的位置，查找失败则返回0

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


//主函数
int main(void)
{
	int i,count=0,choice,data,result;

	while(1)
	{
		printf("-----------------排序与查找----------------\n"
		"操作选项：\n"
		"1.输入待处理数据序列\n"
		"2.序列排序\n"
		"3.数据查找\n"
		"4.退出程序\n"
		"	请选择：");

	scanf("%d",&choice);

	switch(choice)
	{
	case 1:
		printf("\n请输入您想要处理数据的个数：");
	    scanf("%d",&count);
		if(count>=MAX)
		{
			printf("\n数据过多，无法处理，请重新输入！\n");
			break;
		}
		else
		{
			printf("\n请输入您想要处理的数据:");
			for(i=1;i<=count;i++)
				scanf("%d",&R[i]);
			printf("数据读取成功！\n");
		}
		break;
	case 2:
		Quick_Sort(R,1,count);
		printf("排序成功！\n");
		printf("经排序后的序列为：");
		for(i=1;i<=count;i++)
			printf("%d ",R[i]);
		printf("\n");
		break;
	case 3:
		printf("请输入待查找的数据：\n");
		scanf("%d",&data);
		result=BinarySearch(R,data,count);

		if(result)
		{
			printf("数据查找成功！\n"
				"数据%d位于序列第%d位！\n",data,result);
		}
		else
			printf("查找失败！您所要查找数据不在本序列中！\n");
		break;
	case 4:
		printf("程序已退出，谢谢使用！\n");
		return 0;
	default :
		return 0;
	}
	}
}