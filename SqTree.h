/** 二叉树 - 顺序存储
 *
 * Author: Charles Shan
 * Date: 2022.09.13
 * Version: 2.0
 *
 *  内容包括:
 *  顺序存储的树的定义
 *  InitTree              初始化
 *  FindLeftChild         找到左孩子(返回下标)
 *  FindRightChild        找到右孩子(返回下标)
 *  FindParent            找到双亲(返回下标)
 *  InsertLeftTree        左插
 *  InsertRightTree       右插
 *  FindLevel             计算层数
 *  GetTreeData           获取本层结点对应数据
 *  TestInit              构建测试树
 */

#include<stdio.h>
#include<stdbool.h>
#include <math.h>

#define MAXSIZE 128
typedef struct
{
	Element data[MAXSIZE];
	bool isEmpty[MAXSIZE];
}Tree;

void InitTree(Tree &t){
	for(int i=0;i<MAXSIZE;i++)
		t.isEmpty[i]=true;
}

//下面是几个常考基本操作
int FindLeftChild(Tree t,int m){
	if(m*2<=MAXSIZE && t.isEmpty[m*2]==false)
		return m*2;
	else
		return 0;
}

int FindRightChild(Tree t,int m){
	if(m*2+1<=MAXSIZE && t.isEmpty[m*2+1]==false)
		return m*2+1;
	else
		return 0;
}

int FindParent(int m){
	return m/2;
}

int FindLevel(int m){
	return int(log(m)/log(2))+1;
}

bool InsertLeftTree(Tree &T,int parent,Element e){
    if(parent*2>MAXSIZE) return false;
    T.data[parent*2] = e;
    return true;
}

bool InsertRightTree(Tree &T,int parent,Element e){
    if(parent*2+1>MAXSIZE) return false;
    T.data[parent*2+1] = e;
    return true;
}

Element GetTreeData(Tree T,int m){
    return T.data[m];
}

void TestInit(Tree &t) {
    for (int i = 1; i < 13; i++){//存储1-12在1-12下标（为了让下表与索引一致）
        t.isEmpty[i] = false;
        t.data[i] = ele_build(i);
    }
}

void test_sequence_tree(){
    printf("二叉树 - 顺序存储\n");
	Tree t;
	InitTree(t);
	TestInit(t);
	printf("寻找左孩子:3-%d\n",FindLeftChild(t,3));
	printf("寻找右孩子:3-%d\n",FindRightChild(t,3));
	printf("寻找父结点:3-%d\n",FindParent(3));
	printf("寻找所在层:3-%d\n",FindLevel(3));
	printf("寻找所在层:5-%d\n",FindLevel(5));
    printf("寻找所在层:9-%d\n",FindLevel(9));
}