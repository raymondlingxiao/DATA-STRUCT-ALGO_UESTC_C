/*******************************************************
*                      ������                        *
*  �� �ƣ����������Ĺ�������������                     *
*  �� �ݣ����������Ĺ���������������ı�������ʾ��     *
*  �� �ߣ�������	2014220701004                         *
*  ʱ �䣺2015.05.08                                   *
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 10000

char  file_address[100];        //ȫ���ļ���ַ��������

typedef struct hnode            // ���������Ľڵ�ṹ����
{
    int weight;
    int lchild, rchild, parent;
}THNode, * TpHTree;

typedef struct huffman_code     // �����������Ԫ�ؽṹ����
{
    int weight;                 // Ԫ�ض�ӦȨֵ
    char * pcode;               // ָ������ַ�����ָ��
}THCode, *TpHcodeTab;



//����Huffman�����
TpHcodeTab build_codesheet( TpHTree pht, int leaves_num ) // ���ݹ��������õ������������
{
	int i, cid, pid, cursor, len;
	TpHcodeTab sheet;                                     //ָ��THCode���������ָ��
	
	char * pch = (char *) malloc( leaves_num + 1 );       //Ϊ�ַ�����β��'\0'����ռ�
	if( !pch ){
		printf("����ռ�ʧ�ܣ�");
		exit(0);
	}
	memset( pch, 0, (leaves_num + 1) );                   // ���·���Ŀռ���г�ʼ���������
	
	sheet = ( TpHcodeTab )malloc( sizeof( THCode ) * leaves_num );
	if( !sheet ){
		printf("Ϊ��������������ռ�ʧ�ܣ�");
		exit(0);
	}
	
	for( i = 0; i < leaves_num; ++i ){
		sheet[i].weight = pht[i].weight;
	}
	for( i = 0; i < leaves_num; ++i ){
		cursor = leaves_num;
		cid = i;
		pid = pht[cid].parent;
		
		while( pid!= -1 ){                                // �����׽�㲻Ϊ��1����cid��Ϊ�����ʱ��            		
			if (pht[pid].lchild == cid)
				pch[--cursor] = '0';                      // ���֧����Ϊ'0'
			else
				pch[--cursor] = '1';                      // �ҷ�֧����Ϊ'1'
			cid = pid;
			pid = pht[cid].parent;				
		}
		len =  leaves_num - cursor + 1;
	
		sheet[i].pcode = ( char * )malloc( len );
		if( !sheet[i].pcode ){
			printf("Ϊ�ڵ�%d�Ĺ�������������ڴ�ռ�ʧ�ܣ�", i);
			exit(0);
		}
		memset( sheet[i].pcode, 0, len );
		strncpy( sheet[i].pcode, &pch[cursor], strlen(&pch[cursor]) );
	}
	
	free(pch);
	return sheet;
}



//ѡ��������Ȩֵ��С��������
void select_mintree(TpHTree pht, int n, int *minA, int *minB)
{
	int id, min1 = -1, min2 = -1;             //��Сֵ�ʹ�Сֵ
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



// ����Huffman�����
void destroy_codesheet(TpHcodeTab sheet, int n)
{
    int i;
    for(i = 0; i < n; ++i)
        free(sheet[i].pcode);
    free(sheet);
    return;
}



//����Huffman��
TpHTree create_huffman_tree( int weights[], int n )
{
	TpHTree pht;
	int minA, minB;             // ���ڴ���Ȩֵ��С���������������
	int i, a = 0;
	
	if( n < 1 ){
		printf("û��Ҷ�ӽڵ㣡\n");
		return 0;
	} 
	
	a = (2 * n) - 1;
	pht = ( TpHTree ) malloc( sizeof( THNode ) * a );
	if( !pht ){
		printf("��������ռ�ʧ�ܣ�\n");
		exit(0);
	}
	
	for( i = 0; i < a; ++i )       // �����������ʼ��
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



// ���ı��ļ������ַ��������浽���� message �� 
int read_file(char  file_address[100], char *message)
{
	int str_len;              //�ַ�������
	FILE * pFile = NULL;
	
	pFile = fopen( file_address, "r");	//���ļ� 
	if(!pFile)	{
		printf("�ļ���ʧ��!\n");
		exit(0);
	}
	else{
		printf("�ļ��򿪳ɹ�!\n");
	}
	

	memset(message, 0, MAXSIZE);	     //��ջ�������׼�����ļ�¼���ַ����� 
	
	if( fgets( message, MAXSIZE, pFile ) == NULL){
		printf( "fgets error\n" );
		exit(0);
	}
	else{
		printf( "�ļ���ȡ�ɹ��������Ǿ������ݣ�\n%s\n", message);
	}

	str_len = strlen(message);	
	fclose(pFile);
	
	return str_len;
}


// ͳ���ַ���text���ַ����ֵ�Ƶ��
int calc_freq(char text[], int **freq, char **dict, int n)       //nΪ�ַ�������
{
	int i, k;
	int char_num = 0;
	int * chars;          //��� text�г��ֵĲ�ͬ������ַ�
	char * fre;	          //��� text�г��ֵĲ�ͬ������ַ��ĳ���Ƶ��
	int times[256] = {0};

	for(i = 0; i < n; ++i)	    //ͳ�Ƹ����ַ����ֵ�Ƶ�� 
		times[text[i]]++;
	for(i = 0; i < 256; i++)	//ͳ�Ʋ�ͬ�ַ��ĸ��� 
		if( times[i] > 0 )
			char_num++;

	chars = (int*)malloc(sizeof(int)*char_num);
	if( !chars ){
		printf("ΪƵ���������ռ�ʧ�ܣ�\n");
		exit(0);
	}
	
	fre = (char *)malloc(sizeof(char)*char_num);
	if( !fre ){
		printf("Ϊ�ַ��������ռ�ʧ�ܣ�\n");
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
	
	return char_num;//����text�г��ֵĲ�ͬ������ַ�����
} 


//������
int main(void)
{
	int i, msg_num,choice;
	char s;                     //��ջ���
	int leaves_num = 0;
	
	do
	{
		TpHTree pht = NULL;         //��������
		TpHcodeTab codesheet;       //���������	
		char msg[MAXSIZE];          //������Ϣ����
		int *weights = NULL;        //����Ƶ������
		char *dict = NULL;          //�����ַ�����	

		printf("***************��������***************\n");
		printf("\n�ļ���ȡ��ʽ��\n"
			"1���û��ֶ�������Ϣ\n"
			"2��ϵͳ��ȡ�ļ�¼����Ϣ\n""��ѡ��");
		scanf("%d",&choice);

		if(choice == 1)
		{
			printf("��������Ϣ��\n");
			scanf("%c",&s);         //������̻���
			gets(msg);
			msg_num = strlen(msg);
		}
		else
		{
			printf("�����ļ���ַ�����磺F:\\\\filename.txt��:\n");
			scanf("%c",&s);                                     //������̻���
			gets(file_address);                                 //�����ļ���ַ
			msg_num = read_file( file_address, msg);            //���ı��ļ����뵽�ַ��� msg �У�����ֵ msg_num Ϊ msg �ַ�������
		}
		leaves_num = calc_freq( msg, &weights, &dict, msg_num );//ͳ���ı����е��ַ�Ƶ�ʣ�ͬʱ�õ�Huffman����Ҷ�ڵ���
		pht = create_huffman_tree( weights, leaves_num );       //����Huffman��
		codesheet = build_codesheet( pht, leaves_num );	        //����Huffman�����
		
		printf("\n��������������£�\n");
		printf("�ַ�    Ƶ��    ����\n");
		for(i = 0; i < leaves_num ; i++)
			printf("%4c    %-4d    %-6s\n", dict[i], codesheet[i].weight, codesheet[i].pcode);

		destroy_codesheet( codesheet,  leaves_num);             //����Huffman�����

		if(pht)													//�ͷ�������ʱ�ռ�
			free(pht);	
		if(dict)
			free(dict);
		if(weights)
			free(weights);

		printf("\nY������\nN������\n"
			"\t��ѡ��");
		scanf("%c",&choice);
	}while(choice=='Y');

	if(choice=='N'){
		printf("�������˳���ллʹ�ã�\n");
	}
	return 0;
}