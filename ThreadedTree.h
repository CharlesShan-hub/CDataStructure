#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
typedef struct ThreadNode
{
	int data;
	struct ThreadNode *lchild,*rchild;
	bool ltag,rtag; // 左右线索标志
	struct ThreadNode *parent; // 变成了 三叉链表
}ThreadNode,*ThreadTree;

// 全局变量pre,指向当前访问结点的前驱
ThreadNode *_pre = NULL;


/**
 * Part 1
 * 
 * Construct Test Tree
 * 
 */


ThreadNode* NewNode(int data){
	ThreadNode *T = (ThreadNode*)malloc(sizeof(ThreadNode));
	if(T==NULL){
		//printf("Memory run out!");
		return NULL;
	}else{
		//printf("Put [%d] at %p\n",data,T);
	}
	T->data = data;
	T->lchild = NULL;
	T->rchild = NULL;
	T->ltag = false;
	T->rtag = false;
	T->parent=NULL;
	return T;
}

ThreadTree LeftInsert(ThreadTree T, int data){
	if(T==NULL)
		return T;
	ThreadNode *p = NewNode(data);
	T->lchild=p;
	T->lchild->parent=T;
	return T;
}

ThreadTree RightInsert(ThreadTree T, int data){
	if(T==NULL)
		return T;
	ThreadNode *p = NewNode(data);
	T->rchild=p;
	T->rchild->parent=T;
	return T;
}

ThreadTree ThreadTestInit(){
	ThreadTree T = NewNode(1);
	LeftInsert(T,2);
	RightInsert(T,3);
	LeftInsert(T->lchild,4);
	RightInsert(T->lchild,5);
	LeftInsert(T->rchild,6);
	RightInsert(T->lchild->lchild,7);
	printf("\n初始化:\n"
		"      A-1\n"
		"     /   \\\n"
		"    B-2   C-3\n"
		"   / \\     /\n"
		"  D-4 E-5 F-6\n"
		"  \\\n"
		"   G-7\n");
	return T;
}

void DeleteTree(ThreadTree &T){
	if(T!=NULL){
		if(T->ltag==0)
			DeleteTree(T->lchild);
		if(T->rtag==0)
			DeleteTree(T->rchild);
		free(T);
	}
}


/**
 * Part 2
 * 
 * Visit Function
 * 
 */


void Visit(ThreadNode *T){
	printf("%d ",T->data);
}

void TreeVisit(ThreadNode *q){
	Visit(q);
	if(q->lchild == NULL){
		q->lchild = _pre;
		q->ltag=1;
	}
	if(_pre!=NULL && _pre->rchild==NULL){
		_pre->rchild = q;
		_pre->rtag = 1;
	}
	_pre = q;
}


/**
 * Part 3
 * 
 * Pre Order Functions
 * 
 */


void PreOrder1(ThreadTree T){
	if(T!=NULL){
		Visit(T);
		if(T->ltag==0)
			PreOrder1(T->lchild);
		if(T->rtag==0)
		PreOrder1(T->rchild);
	}
}

ThreadNode *PreFirstNode(ThreadNode *p){
	return p;
}

ThreadNode *PreLastNode(ThreadNode *p){
	while(p->ltag==0 || p->rtag==0){
		if(p->rtag==0)
			p=p->rchild;
		else
			p=p->lchild;
	}
	return p;
}

ThreadNode *PreNextNode(ThreadNode *p){
	if(p->rtag==1)// 是叶子结点
		return p->rchild;
	else
		if(p->ltag==0) // 有左孩子
			return p->lchild;
		else // 有右孩子
			return p->rchild;
}

ThreadNode *PrePreNode(ThreadNode *p){
	if(p->ltag==1)
		return p->lchild;
	else{
		ThreadNode *parent = p->parent;
		if(parent==NULL) // 已经是第一个了
			return NULL;
		if(parent->lchild==p){ // p是左孩子
			return parent;
		}else if(parent->ltag==1){ // p是右孩子+无左孩子
			return parent;
		}else // p是右孩子 + 有左孩子
			return PreLastNode(parent->lchild);
	}
}

void PreOrder2(ThreadTree T){
	//for(ThreadNode *p=PreFirstNode(T);p!=NULL;p=PreNextNode(p))
	for(ThreadNode *p=T;p!=NULL;p=PreNextNode(p))
		Visit(p);
}

void PreOrder3(ThreadTree T){
	for(ThreadNode *p=PreLastNode(T);p!=NULL;p=PrePreNode(p))
		Visit(p);
}

void PreTree(ThreadTree T){
	if(T!=NULL){
		TreeVisit(T);
		if(T->ltag==0)
			PreTree(T->lchild);
		if(T->rtag==0)
			PreTree(T->rchild);
	}
}

void CreatPreTree(ThreadTree T){
	_pre = NULL;
	if(T!=NULL){
		PreTree(T);
		_pre->rchild=NULL;
		_pre->rtag = 1;
	}
}


/**
 * Part 4
 * 
 * Mid Order Functions
 * 
 */


void MidOrder1(ThreadTree T){
	if(T!=NULL){
		if(T->ltag==0)
			MidOrder1(T->lchild);
		Visit(T);
		if(T->rtag==0)
			MidOrder1(T->rchild);
	}
}

ThreadNode *MidFirstNode(ThreadNode *p){
	// 循环找到最左下结点
	while(p->ltag==0) p=p->lchild;
	return p;
}

ThreadNode *MidNextNode(ThreadNode *p){
	// 后继
	if(p->rtag==0) return MidFirstNode(p->rchild);
	else return p->rchild;
}

void MidOrder2(ThreadTree T){
	for(ThreadNode *p=MidFirstNode(T);p!=NULL;p=MidNextNode(p))
		Visit(p);
}

ThreadNode *MidLastNode(ThreadNode *p){
    // 循环找到最右下结点
    while(p->rtag==0) p=p->rchild;
    return p;
}

ThreadNode *MidPreNode(ThreadNode *p){
    // 前驱
    if(p->ltag==0) return MidLastNode(p->lchild);
    else return p->lchild;
}

void MidOrder3(ThreadTree T){
	for(ThreadNode *p=MidLastNode(T);p!=NULL;p=MidPreNode(p))
		Visit(p);
}

void MidTree(ThreadTree T){
	if(T!=NULL){
		//if(T->ltag==0)
			MidTree(T->lchild);
		TreeVisit(T);
		//if(T->rtag==0)
			MidTree(T->rchild);
	}
}

void CreatMidTree(ThreadTree T){
	_pre = NULL;
	if(T!=NULL){
		MidTree(T);
		_pre->rchild=NULL;
		_pre->rtag = 1;
	}
}

/**
 * Part 5
 * 
 * Last Order Functions
 * 
 */

void LastOrder1(ThreadTree T){
	if(T!=NULL){
		if(T->ltag==0)
			LastOrder1(T->lchild);
		if(T->rtag==0)
			LastOrder1(T->rchild);
		Visit(T);
	}
}

ThreadNode *LastFirstNode(ThreadNode *q){
	while(q->ltag==0 || q->rtag==0)
		if(q->ltag==0)
			q = q->lchild;
		else
			q = q->rchild;
	return q;
}

ThreadNode *LastLastNode(ThreadNode *q){
	return q;
}

ThreadNode *LastNextNode(ThreadNode *q){
	if(q->rtag==1)
		return q->rchild;
	ThreadNode *parent = q->parent;
	if(parent==NULL)
		return NULL;
	if(parent->rchild==q)
		return parent;
	return LastFirstNode(parent->rchild);
}

ThreadNode *LastPreNode(ThreadNode *q){
	if(q->ltag==1)
		return q->lchild;
	if(q->rtag==0)
		return q->rchild;
	else
		return q->lchild;
}

void LastOrder2(ThreadTree T){
	for(ThreadNode *q=LastFirstNode(T);q!=NULL;q=LastNextNode(q))
		Visit(q);
}

void LastOrder3(ThreadTree T){
	//for(ThreadNode *q=LastLastNode(T);q!=NULL;q=LastPreNode(q))
	for(ThreadNode *q=T;q!=NULL;q=LastPreNode(q))
		Visit(q);
}

void LastTree(ThreadTree T){
	if(T!=NULL){
		//if(T->ltag==0)
			LastTree(T->lchild);
		//if(T->rtag==0)
			LastTree(T->rchild);
		TreeVisit(T);
	}
}

void CreatLastTree(ThreadTree T){
	_pre = NULL;
	if(T!=NULL){
		LastTree(T);
		//_pre->rchild=NULL;
		//_pre->rtag = 1;
		//printf("\n[%d]\n",_pre->data);
	}
}

void test_threaded_tree(){
    printf("线索二叉树 - (仅作展示)");
	// 先序
	ThreadTree T1 = ThreadTestInit();

	printf("\n构建先序线索树:");
	CreatPreTree(T1);

	printf("\n先序遍历-O(n):");
	PreOrder1(T1);

	printf("\n先序遍历-O(1):");
	PreOrder2(T1);

	printf("\n先序遍历-O(1):");
	PreOrder3(T1);

	DeleteTree(T1);
	printf("\n");

	// 中序
	ThreadTree T2 = ThreadTestInit();

	printf("\n构建中序线索树:");
	CreatMidTree(T2);

	printf("\n中序遍历-O(n):");
	MidOrder1(T2);

	printf("\n中序遍历-O(1):");
	MidOrder2(T2);

	printf("\n中序遍历-O(1):");
	MidOrder3(T2);

	DeleteTree(T2);

	printf("\n");

	// 后序
	ThreadTree T3 = ThreadTestInit();

	printf("\n构建后序线索树:");
	CreatLastTree(T3);

	printf("\n后序遍历-O(n):");
	LastOrder1(T3);

	printf("\n后序遍历-O(1):");
	LastOrder2(T3);

	printf("\n后序遍历-O(1):");
	LastOrder3(T3);

	DeleteTree(T3);
	printf("\n");
}
