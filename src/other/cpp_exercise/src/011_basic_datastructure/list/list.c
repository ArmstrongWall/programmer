#include "list.h"
#include <stdio.h>
#include <stdlib.h>

char *g_MetroLine11Station[10] = { "HuaQiao", "GuangMingLu",
								 "ZhaoFengLu", "AnTing",
								 "QiCheCheng", "EastChangji" };

/* 1.初始化线性表，即置单链表的表头指针为空 */
void  InitList(TNode** ppNode)//指针的指针
{
	*ppNode = NULL;//*pNode 是一个指针，置为空
	printf("Init List OK \r\n\r\n");
}

/* 2.创建线性表*/
TNode* ListCreat(TNode* pHead,int iList_Length)
{
	TNode *pCurrent, *pNew;
	int i=0;

	pHead = (TNode*)malloc(sizeof(TNode));//开辟TNode大小的内存

	if (pHead == NULL)
	{
		printf("creat Head error");
		return NULL;
	}

	pCurrent = pHead;//先将头指针指向现在的指针

	for (i = 0; i < iList_Length; i++)
	{
		pNew = (TNode*)malloc(sizeof(TNode));//创建新的节点指针

		if (pNew == NULL)
		{
			printf("creat new Node error");
			return NULL;
		}


		//printf("Input No.%d Station name:", i + 1);

		pNew->cpStationName = g_MetroLine11Station[i];//索引赋值，地铁站名称赋值
		//pNew->cpStationName = GetString();//手动赋值，地铁站名称赋值

		pNew->ptNext = NULL;//新的节点的下一个指针为空
		pCurrent->ptNext = pNew;//将现在节点的指针域指向下一个节点

		pCurrent = pNew;//再把新节点的指针赋值给现在的节点指针，注意，一定要先完成上一步。
	}

	return pHead;
}

/* 3.打印链表，链表的遍历*/
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
		pDisplayCurrent = pDisplayCurrent->ptNext;		//向下传递指针
	}

}

/* 4.清除线性表L中的所有元素，即释放单链表L中所有的结点，使之成为一个空表 */


TNode*  InsertNode(TNode* pHead, TNode* pNew, int iPosition)
{
	TNode* pCurrenTNode;
	int i=0;
	pCurrenTNode = (TNode*)malloc(sizeof(TNode));//开辟TNode大小的内存

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
		pCurrenTNode = pCurrenTNode->ptNext;//往后移动iPosition个位置
		if (pCurrenTNode == NULL)//判断移动位置是否已经超过了链表长度
		{
			printf("please input length less than list \r\n");
			return NULL;
			break;

		}
	}

	pNew->ptNext = pCurrenTNode->ptNext;   //先接上节点
	pCurrenTNode->ptNext = pNew;         //再断链，换新的指向点

	return pHead;
}
char* GetString()//从屏幕输入任意长度的字符串
{

	char cTemp, *cpString;

	int iTimes = 1;
	cpString = (char*)malloc(sizeof(char));//先分配一点内存 

	while ((cTemp = getchar()) != '\n')//从输入流中循环获取字符，直到输入换行结束
	{
		iTimes++;
		cpString = (char*)realloc(cpString, sizeof(char)*iTimes);//使用realloc增加内存
		*(cpString + iTimes - 2) = cTemp;//将输入的字符串复制
		*(cpString + iTimes - 1) = '\0';//添加字符串结束符
	}

	return cpString;

}


