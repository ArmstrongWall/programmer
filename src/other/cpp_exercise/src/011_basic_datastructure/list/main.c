#include <stdio.h>
#include <stdlib.h>
#include "list.h"


int main()
{

  
	ptNode MetroLine11;
	ptNode EastChangJi;

	InitList(&MetroLine11);
	MetroLine11 = ListCreat(MetroLine11,5);//´´½¨Á´±í

	EastChangJi = (TNode*)malloc(sizeof(TNode));
	if (EastChangJi == NULL)
	{
		printf("Node Error");
		return NULL;
	}
		
	EastChangJi->cpStationName = g_MetroLine11Station[5];
	EastChangJi->ptNext = NULL;

	

	
	ListDispaly(MetroLine11);

	printf("New Line\r\n\r\n");
	if (InsertNode(MetroLine11, EastChangJi, 4) != NULL)
	{
		ListDispaly(MetroLine11);
	}
	else
	{
		printf("error\r\n\r\n");
	}
	
		
}

