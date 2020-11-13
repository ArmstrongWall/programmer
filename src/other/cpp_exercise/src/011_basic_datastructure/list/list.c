#include "list.h"
#include <stdio.h>
#include <stdlib.h>

char *g_MetroLine11Station[10] = { "HuaQiao", "GuangMingLu",
								 "ZhaoFengLu", "AnTing",
								 "QiCheCheng", "EastChangji" };

/* 1.��ʼ�����Ա����õ�����ı�ͷָ��Ϊ�� */
void  InitList(TNode** ppNode)//ָ���ָ��
{
	*ppNode = NULL;//*pNode ��һ��ָ�룬��Ϊ��
	printf("Init List OK \r\n\r\n");
}

/* 2.�������Ա�*/
TNode* ListCreat(TNode* pHead,int iList_Length)
{
	TNode *pCurrent, *pNew;
	int i=0;

	pHead = (TNode*)malloc(sizeof(TNode));//����TNode��С���ڴ�

	if (pHead == NULL)
	{
		printf("creat Head error");
		return NULL;
	}

	pCurrent = pHead;//�Ƚ�ͷָ��ָ�����ڵ�ָ��

	for (i = 0; i < iList_Length; i++)
	{
		pNew = (TNode*)malloc(sizeof(TNode));//�����µĽڵ�ָ��

		if (pNew == NULL)
		{
			printf("creat new Node error");
			return NULL;
		}


		//printf("Input No.%d Station name:", i + 1);

		pNew->cpStationName = g_MetroLine11Station[i];//������ֵ������վ���Ƹ�ֵ
		//pNew->cpStationName = GetString();//�ֶ���ֵ������վ���Ƹ�ֵ

		pNew->ptNext = NULL;//�µĽڵ����һ��ָ��Ϊ��
		pCurrent->ptNext = pNew;//�����ڽڵ��ָ����ָ����һ���ڵ�

		pCurrent = pNew;//�ٰ��½ڵ��ָ�븳ֵ�����ڵĽڵ�ָ�룬ע�⣬һ��Ҫ�������һ����
	}

	return pHead;
}

/* 3.��ӡ��������ı���*/
void  ListDispaly(TNode* pHead)
{
	TNode* pDisplayCurrent;

	pDisplayCurrent = pHead->ptNext;

	if (pDisplayCurrent == NULL)
	{
		printf("Display List erroe\r\n");
	}

	while (pDisplayCurrent)
	{
		printf("%s\r\n", pDisplayCurrent->cpStationName);
		pDisplayCurrent = pDisplayCurrent->ptNext;		//���´���ָ��
	}

}

/* 4.������Ա�L�е�����Ԫ�أ����ͷŵ�����L�����еĽ�㣬ʹ֮��Ϊһ���ձ� */


TNode*  InsertNode(TNode* pHead, TNode* pNew, int iPosition)
{
	TNode* pCurrenTNode;
	int i=0;
	pCurrenTNode = (TNode*)malloc(sizeof(TNode));//����TNode��С���ڴ�

	if (iPosition <= 0)
	{
		printf("Positon must be a positive number\r\n");
		return NULL;
	}

	if (pCurrenTNode == NULL)
	{
		printf("InserTNode erroe\r\n");
		return NULL;
	}
	pCurrenTNode = pHead;
	for (i = 0; i < iPosition; i++)
	{
		pCurrenTNode = pCurrenTNode->ptNext;//�����ƶ�iPosition��λ��
		if (pCurrenTNode == NULL)//�ж��ƶ�λ���Ƿ��Ѿ�������������
		{
			printf("please input length less than list \r\n");
			return NULL;
			break;

		}
	}

	pNew->ptNext = pCurrenTNode->ptNext;   //�Ƚ��Ͻڵ�
	pCurrenTNode->ptNext = pNew;         //�ٶ��������µ�ָ���

	return pHead;
}
char* GetString()//����Ļ�������ⳤ�ȵ��ַ���
{

	char cTemp, *cpString;

	int iTimes = 1;
	cpString = (char*)malloc(sizeof(char));//�ȷ���һ���ڴ� 

	while ((cTemp = getchar()) != '\n')//����������ѭ����ȡ�ַ���ֱ�����뻻�н���
	{
		iTimes++;
		cpString = (char*)realloc(cpString, sizeof(char)*iTimes);//ʹ��realloc�����ڴ�
		*(cpString + iTimes - 2) = cTemp;//��������ַ�������
		*(cpString + iTimes - 1) = '\0';//����ַ���������
	}

	return cpString;

}


