/*******************************************************
*                      程序简介                        *
*  名 称：哈夫曼树的构建及基本操作                     *
*  内 容：哈夫曼树的构建、哈夫曼编码的遍历及显示等     *
*  作 者：李凌霄	2014220701004                         *
*  时 间：2015.05.08                                   *
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 10000

char  file_address[100];        //全局文件地址保存数组

typedef struct hnode            // 哈夫曼树的节点结构定义
{
    int weight;
    int lchild, rchild, parent;
}THNode, * TpHTree;

typedef struct huffman_code     // 哈夫曼编码表元素结构定义
{
    int weight;                 // 元素对应权值
    char * pcode;               // 指向编码字符串的指针
}THCode, *TpHcodeTab;



//构建Huffman编码表
TpHcodeTab build_codesheet( TpHTree pht, int leaves_num ) // 根据哈夫曼树得到哈夫曼编码表
{
	int i, cid, pid, cursor, len;
	TpHcodeTab sheet;                                     //指向THCode类型数组的指针
	
	char * pch = (char *) malloc( leaves_num + 1 );       //为字符串结尾的'\0'分配空间
	if( !pch ){
		printf("分配空间失败！");
		exit(0);
	}
	memset( pch, 0, (leaves_num + 1) );                   // 对新分配的空间进行初始化清零操作
	
	sheet = ( TpHcodeTab )malloc( sizeof( THCode ) * leaves_num );
	if( !sheet ){
		printf("为哈夫曼编码表分配空间失败！");
		exit(0);
	}
	
	for( i = 0; i < leaves_num; ++i ){
		sheet[i].weight = pht[i].weight;
	}
	for( i = 0; i < leaves_num; ++i ){
		cursor = leaves_num;
		cid = i;
		pid = pht[cid].parent;
		
		while( pid!= -1 ){                                // 当父亲结点不为－1（即cid不为根结点时）            		
			if (pht[pid].lchild == cid)
				pch[--cursor] = '0';                      // 左分支编码为'0'
			else
				pch[--cursor] = '1';                      // 右分支编码为'1'
			cid = pid;
			pid = pht[cid].parent;				
		}
		len =  leaves_num - cursor + 1;
	
		sheet[i].pcode = ( char * )malloc( len );
		if( !sheet[i].pcode ){
			printf("为节点%d的哈夫曼编码分配内存空间失败！", i);
			exit(0);
		}
		memset( sheet[i].pcode, 0, len );
		strncpy( sheet[i].pcode, &pch[cursor], strlen(&pch[cursor]) );
	}
	
	free(pch);
	return sheet;
}



//选出数组中权值最小两棵子树
void select_mintree(TpHTree pht, int n, int *minA, int *minB)
{
	int id, min1 = -1, min2 = -1;             //最小值和次小值
	int wa = INT_MAX, wb = INT_MAX;

	for(id = 0; id <= n; id++){        
		if(pht[id].parent == -1){
			if( pht[id].weight < wa ){
				min2 = min1;
				min1 = id;
				wa = pht[id].weight;
			}
			else if(pht[id].weight < wb ){
				min2 = id;
				wb = pht[id].weight;
			}            
		}
	}
	*minA = min1;
	*minB = min2;
	return;
}



// 销毁Huffman编码表
void destroy_codesheet(TpHcodeTab sheet, int n)
{
    int i;
    for(i = 0; i < n; ++i)
        free(sheet[i].pcode);
    free(sheet);
    return;
}



//构建Huffman树
TpHTree create_huffman_tree( int weights[], int n )
{
	TpHTree pht;
	int minA, minB;             // 用于储存权值最小的两棵子树的序号
	int i, a = 0;
	
	if( n < 1 ){
		printf("没有叶子节点！\n");
		return 0;
	} 
	
	a = (2 * n) - 1;
	pht = ( TpHTree ) malloc( sizeof( THNode ) * a );
	if( !pht ){
		printf("分配数组空间失败！\n");
		exit(0);
	}
	
	for( i = 0; i < a; ++i )       // 哈夫曼数组初始化
	{	                           
		pht[i].weight = (i < n) ? weights[i] : 0;
		pht[i].lchild = -1;
		pht[i].rchild = -1;
		pht[i].parent = -1;
	}
	
	for( i = n; i < a; ++i )
	{
		select_mintree( pht, (i-1), &minA, &minB );
		
		pht[minA].parent = i;
		pht[minB].parent = i; 	
		pht[i].lchild = minA;
		pht[i].rchild = minB;
		pht[i].weight = pht[minA].weight + pht[minB].weight;
	}
	
	return pht;
}



// 从文本文件读入字符串，保存到数组 message 中 
int read_file(char  file_address[100], char *message)
{
	int str_len;              //字符串长度
	FILE * pFile = NULL;
	
	pFile = fopen( file_address, "r");	//打开文件 
	if(!pFile)	{
		printf("文件打开失败!\n");
		exit(0);
	}
	else{
		printf("文件打开成功!\n");
	}
	

	memset(message, 0, MAXSIZE);	     //清空缓冲区（准备从文件录入字符串） 
	
	if( fgets( message, MAXSIZE, pFile ) == NULL){
		printf( "fgets error\n" );
		exit(0);
	}
	else{
		printf( "文件读取成功！以下是具体内容：\n%s\n", message);
	}

	str_len = strlen(message);	
	fclose(pFile);
	
	return str_len;
}


// 统计字符串text中字符出现的频率
int calc_freq(char text[], int **freq, char **dict, int n)       //n为字符串长度
{
	int i, k;
	int char_num = 0;
	int * chars;          //存放 text中出现的不同种类的字符
	char * fre;	          //存放 text中出现的不同种类的字符的出现频率
	int times[256] = {0};

	for(i = 0; i < n; ++i)	    //统计各个字符出现的频率 
		times[text[i]]++;
	for(i = 0; i < 256; i++)	//统计不同字符的个数 
		if( times[i] > 0 )
			char_num++;

	chars = (int*)malloc(sizeof(int)*char_num);
	if( !chars ){
		printf("为频率数组分配空间失败！\n");
		exit(0);
	}
	
	fre = (char *)malloc(sizeof(char)*char_num);
	if( !fre ){
		printf("为字符数组分配空间失败！\n");
		exit(0);
	}
	
	k = 0;
	for(i = 0; i < 256; ++i){
		if( times[i] > 0 ){
			chars[k] = times[i];
			fre[k] = (char)i;
			k++;
		}
	}
	
	*freq = chars;
	*dict = fre;
	
	return char_num;//返回text中出现的不同种类的字符个数
} 


//主函数
int main(void)
{
	int i, msg_num,choice;
	char s;                     //清空缓存
	int leaves_num = 0;
	
	do
	{
		TpHTree pht = NULL;         //建立树根
		TpHcodeTab codesheet;       //建立编码表	
		char msg[MAXSIZE];          //建立信息数组
		int *weights = NULL;        //建立频率数组
		char *dict = NULL;          //建立字符数组	

		printf("***************哈夫曼树***************\n");
		printf("\n文件读取方式：\n"
			"1：用户手动输入信息\n"
			"2：系统读取文件录入信息\n""请选择：");
		scanf("%d",&choice);

		if(choice == 1)
		{
			printf("请输入信息：\n");
			scanf("%c",&s);         //清理键盘缓存
			gets(msg);
			msg_num = strlen(msg);
		}
		else
		{
			printf("输入文件地址（例如：F:\\\\filename.txt）:\n");
			scanf("%c",&s);                                     //清理键盘缓存
			gets(file_address);                                 //输入文件地址
			msg_num = read_file( file_address, msg);            //将文本文件读入到字符串 msg 中，返回值 msg_num 为 msg 字符串长度
		}
		leaves_num = calc_freq( msg, &weights, &dict, msg_num );//统计文本串中的字符频率，同时得到Huffman树的叶节点数
		pht = create_huffman_tree( weights, leaves_num );       //创建Huffman树
		codesheet = build_codesheet( pht, leaves_num );	        //构造Huffman编码表
		
		printf("\n哈夫曼编码表如下：\n");
		printf("字符    频数    编码\n");
		for(i = 0; i < leaves_num ; i++)
			printf("%4c    %-4d    %-6s\n", dict[i], codesheet[i].weight, codesheet[i].pcode);

		destroy_codesheet( codesheet,  leaves_num);             //销毁Huffman编码表

		if(pht)													//释放所有临时空间
			free(pht);	
		if(dict)
			free(dict);
		if(weights)
			free(weights);

		printf("\nY：继续\nN：结束\n"
			"\t请选择：");
		scanf("%c",&choice);
	}while(choice=='Y');

	if(choice=='N'){
		printf("程序已退出，谢谢使用！\n");
	}
	return 0;
}