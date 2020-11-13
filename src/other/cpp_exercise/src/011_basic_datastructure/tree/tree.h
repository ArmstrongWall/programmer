#ifndef TREE_H
#define TREE_H

typedef struct TChairman
{
	char* cName;
	struct TChairman* ptleft;
	struct TChairman* ptright;

}TreeNode,*ptTreeNode;

extern char *g_MetroLine11Station[10];


#endif
