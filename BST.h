#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef BiTNode BSTNode;
typedef BiTree BSTree;

BSTNode *BSTSearch(BSTree &_T,Element e,BSTree &father){
    BSTNode *T = _T;
    father=NULL;
	while(T!=NULL && ele_get_weight(T->data)!= ele_get_weight(e)){
        visit(T);
        if(ele_get_weight(e) < ele_get_weight(T->data))
        {father=T;T=T->lchild;}
        else
        {father=T;T=T->rchild;}
    }
	return T;
}

bool BSTInsert(BSTree &p,Element e){
    BSTNode *q = p;
	if(q==NULL){
        InitTree(p);
        SetTreeData(p,e);
        return true;
    }
    while(1){
        visit(q);
        if(ele_get_weight(e)< ele_get_weight(q->data))
            if(q->lchild == NULL)
                return InsertLeftTree(q,e);
            else
                q = q->lchild;
        else if(ele_get_weight(e)> ele_get_weight(q->data))
            if(q->rchild == NULL)
                return InsertRightTree(q,e);
            else
                q = q->rchild;
        else
            return false;
    }
}

bool BSTDelete1(BSTree &p,BSTree &father){
    if(father->rchild==p)
        father->rchild=NULL;
    else
        father->lchild=NULL;
    free(p);
    return true;
}

bool BSTDelete2(BSTree &p,BSTree &father){
    BSTNode *q = NULL;
    if(p->rchild==NULL)
        q=p->lchild;
    else
        q=p->rchild;
    if(father->rchild==p)
        father->rchild=q;
    else
        father->lchild=q;
    free(p);
    return true;
}

bool BSTDelete(BSTree &T, Element e){
    BSTNode *father;
    BSTNode *p = BSTSearch(T,e,father);
    if(p==NULL) return false;

    // 如果是叶子结点——直接删除
    if(p->rchild==NULL&&p->lchild==NULL){
        return BSTDelete1(p,father);
    }

    // 如果左子树或右子树为空
    if(p->rchild==NULL||p->lchild==NULL){
        return BSTDelete2(p,father);
    }

    // 左子树右子树都非空 - 找到左边的最右下或右边的最左下
    BSTNode *q = p->rchild;
    if(q->rchild==NULL && q->lchild==NULL){
        ele_copy(p->data,q->data);
        return BSTDelete1(q,p);
    }
    BSTNode *qf = p;
    while(1){
        if(q->lchild==NULL){
            ele_copy(p->data,q->data);
            break;
        }else{
            qf=q;
            q=q->lchild;
        }
    }
    if(q->rchild==NULL)
        return BSTDelete1(q,qf);
    else{
        ele_copy(q->data,q->rchild->data);
        return BSTDelete2(q,qf);
    }
}

BSTNode *BSTCreat(int arr[],int n){
	BSTree T = NULL;
	for(int count=0;count<n;count++){
        printf("Insert %d :",arr[count]);
        BSTInsert(T, ele_build(arr[count]));
        printf("\n先序遍历 : ");PreOrder(T);printf("\n\n");
    }
	return T;
}

void test_BST(){
    printf("二叉排序树\n\n");
	// 二叉排序树的构建
	printf("二叉排序树的构建\n");
	//BSTree T = TestInit();
	int num[] = {19,13,50,11,26,66,21,30,60,70};
	BSTree T = BSTCreat(num,int(sizeof(num)/sizeof(num[0])));
	printf("\n得到二叉排序树:\n"
		"      A-19\n"
		"     /    \\\n"
		"    B-13  C-50\n"
		"   /     /    \\\n"
		"  D-11  E-26   F-66\n"
		"       / \\     /  \\\n"
		"   G-21 H-30  I-60 J-70\n");

	// 寻找值为n的结点
	printf("\n寻找值为n的结点\n");
	printf("60是否存在: ");
    BSTNode *father;
    BSTSearch(T, ele_build(60),father);
	printf("\n71是否存在: ");
    BSTSearch(T, ele_build(71),father);
    printf("\n26是否存在: ");
    BSTSearch(T, ele_build(26),father);

	// 插入结点
	printf("\n\n插入结点\n");
	printf("插入71:");
	BSTInsert(T, ele_build(71));
	printf("\n插入31:");
	BSTInsert(T, ele_build(31));
	printf("\n      A-19\n"
		"     /    \\\n"
		"    B-13  C-50\n"
		"   /     /    \\\n"
		"  D-11  E-26   F-66\n"
		"       / \\     /  \\\n"
		"   G-21 H-30  I-60 J-70\n"
		"           \\        \\\n"
		"           K-31     L-71\n");

    // 删除结点
    printf("\n删除结点\n");
    printf("删除叶子结点 31 - 直接删除 - ");
    BSTDelete(T, ele_build(31));
    printf("\n先序遍历 : ");PreOrder(T);printf("\n");
    printf("中序遍历 : ");MidOrder(T);printf("\n");
    printf("\n删除结点左或右子树为空 13 - 用子树替代自己 - ");
    BSTDelete(T, ele_build(13));
    printf("\n先序遍历 : ");PreOrder(T);printf("\n");
    printf("中序遍历 : ");MidOrder(T);printf("\n");
    printf("\n删除结点左右子树非空 66 - 找右边最左下 - ");
    BSTDelete(T, ele_build(66));
    printf("\n先序遍历 : ");PreOrder(T);printf("\n");
    printf("中序遍历 : ");MidOrder(T);printf("\n");
    printf("\n删除结点左右子树非空 26 - 用子树替代自己 - ");
    BSTDelete(T, ele_build(26));
    printf("\n先序遍历 : ");PreOrder(T);printf("\n");
    printf("中序遍历 : ");MidOrder(T);printf("\n");

	DeleteTree(T);
}