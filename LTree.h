/** 二叉树 - 链式存储
 *
 * Author: Charles Shan
 * Date: 2022.09.13
 * Version: 2.0
 *
 *  内容包括:
 *  链式存储的树的定义
 *  InitTree              初始化
 *  FindLeftChild         找到左孩子(返回指针)
 *  FindRightChild        找到右孩子(返回指针)
 *  InsertLeftTree        左插
 *  InsertRightTree       右插
 *  GetTreeData           获取本层结点对应数据
 *  SetTreeData           设置本层结点对应数据
 *
 *  TestInit              构建测试树
 */

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef Element DataType;
typedef struct BiTNode
{
    DataType data;
	struct BiTNode *lchild;
	struct BiTNode *rchild;
	//struct BiTNode *parent; // 变成了 三叉链表
}BiTNode,*BiTree;

bool InitTree(BiTree &N){
    N = (BiTree)malloc(sizeof(BiTNode));
    if(N==NULL) return false;
    N->rchild = NULL;
    N->lchild = NULL;
    return true;
}

BiTree FindLeftChild(BiTree T){
    return T->lchild;
}

BiTree FindRightChild(BiTree T){
    return T->rchild;
}

DataType GetTreeData(BiTNode *N){
    return N->data;
}

void SetTreeData(BiTNode *N, DataType e){
    N->data = e;
}

bool InsertLeftTree(BiTree &N,Element e){
    BiTNode *p = (BiTree)malloc(sizeof(BiTNode));
    if(p==NULL) return false;
    p->data = e;
    p->rchild = NULL;
    p->lchild = NULL;
    N->lchild = p;
    return true;
}

bool InsertRightTree(BiTree &N,Element e){
    BiTNode *p = (BiTree)malloc(sizeof(BiTNode));
    if(p==NULL) return false;
    p->data = e;
    p->rchild = NULL;
    p->lchild = NULL;
    N->rchild = p;
    return true;
}

void DeleteTree(BiTree &T){
    if(T!=NULL){
        //if(T->ltag==0)
        DeleteTree(T->lchild);
        //if(T->rtag==0)
        DeleteTree(T->rchild);
        free(T);
    }
}

void TestInit(BiTree &root) {
    // 插入根结点
    SetTreeData(root, ele_build(1));

    // 插入孩子结点
    InsertLeftTree(root, ele_build(3));
    InsertRightTree(root, ele_build(5));
}

void test_link_tree(){
    printf("二叉树 - 链式存储\n");
	BiTree T;
    InitTree(T);
    TestInit(T);

    printf("T : %ld\n", ele_get_weight(GetTreeData(T)));
    printf("T->lchild : %ld\n",ele_get_weight(GetTreeData(FindLeftChild(T))));
    printf("T->rchild : %ld\n",ele_get_weight(GetTreeData(FindRightChild(T))));

    printf("销毁\n");DeleteTree(T);
}