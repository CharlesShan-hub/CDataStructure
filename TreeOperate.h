#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

void visit(BiTree T){
	printf("%ld ", ele_get_weight(T->data));
}

void PreOrder(BiTree T){
	if(T!=NULL){
		visit(T);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
}

void MidOrder(BiTree T){
	if(T!=NULL){
		MidOrder(T->lchild);
		visit(T);
		MidOrder(T->rchild);
	}
}

void LastOrder(BiTree T){
	if(T!=NULL){
		LastOrder(T->lchild);
		LastOrder(T->rchild);
		visit(T);
	}
}

void LevelOrder(BiTree T){
    if(T==NULL) return;
    LinkQueue Q;
    LinkQueueInit(Q);
    BiTree p;
    Element e;
    LinkQueueEn(Q, ele_build((long int)T));
    while(!LinkQueueEmpty(Q)){
        // 出队
        LinkQueueDe(Q,e);
        p = (BiTree)ele_get_weight(e);
        // 访问出队结点
        visit(p);
        // 左右孩子入队
        if(p->lchild!=NULL)
            LinkQueueEn(Q, ele_build((long int)(p->lchild)));
        if(p->rchild!=NULL)
            LinkQueueEn(Q, ele_build((long int)(p->rchild)));
    }
}

BiTree TestInit(){
    printf("\n构建测试树 : \n");
    printf("      A-1\n"
           "     /   \\\n"
           "    B-2   C-3\n"
           "   / \\    /\n"
           "  D-4 E-5 F-6\n"
           "  \\\n"
           "   G-7\n");
    BiTree T = NULL;
    InitTree(T);
    SetTreeData(T, ele_build(1));
    InsertLeftTree(T, ele_build(2));
    InsertRightTree(T, ele_build(3));
    InsertLeftTree(T->lchild, ele_build(4));
    InsertRightTree(T->lchild, ele_build(5));
    InsertLeftTree(T->rchild, ele_build(6));
    InsertLeftTree(T->lchild->lchild, ele_build(7));
	return T;
}

void test_tree_operate(){
	printf("二叉树的操作 - 遍历\n");
	BiTree T = TestInit();
	// 先序遍历
	printf("\n先序遍历:");
	PreOrder(T);

	// 中序遍历
	printf("\n中序遍历:");
	MidOrder(T);

	// 后续遍历
	printf("\n后序遍历:");
	LastOrder(T);

	// 层次遍历
	printf("\n层次遍历:");
	LevelOrder(T);

	// 删除
	DeleteTree(T);
	printf("\n");

}