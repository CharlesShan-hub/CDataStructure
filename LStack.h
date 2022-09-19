/** 栈
 *
 * Author: Charles Shan
 * Date: 2022.09.10
 * Version: 1.0
 *
 *  内容包括:
 *  带头结点的单链表的定义
 *  LinkStackInit          初始化
 *  LinkStackEmpty         判空
 *  LinkStackEn            入队
 *  LinkStackDe            出队
 *  LinkStackGet           取队列元素
 *  StackLength            求队长
 *  StackDestroy           销毁操作
 *  StackPrint             输出操作
 */

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

typedef Element DataType;
typedef LinkList LinkStack;

// 初始化 - 带头节点 - 队列
bool LinkStackInit(LinkStack &S){
    return ListInit(S);
}

// 判空 - 带头节点
bool LinkStackEmpty(LinkStack S){
    return ListEmpty(S);
}

// 入栈 - 带头节点
bool LinkStackEn(LinkStack &S, Element x){
    return ListInsertNextNode(S, x);
}

// 出栈 - 带头节点
bool LinkStackDe(LinkStack &S,Element &x){
    if(ListElemGet(S,1)==NULL)
        return false;
    ele_copy(x,ListElemGet(S,1)->data);
    ListDeleteNode(S->next);
    return true;
}

// 取队列元素 - 带头节点
bool LinkStackGet(LinkStack S,Element &x){
    if(ListElemGet(S,1)==NULL)
        return false;
    ele_copy(x,ListElemGet(S,1)->data);
    return true;
}

// StackLength
int LinkStackLength(LinkStack S){
    return ListLength(S);
}

// StackDestroy
void LinkStackDestroy(LinkStack &S){
    ListDestroy(S);
}

// StackPrint
void LinkStackPrint(LinkStack S){
    ListPrint(S);
}

void test_list_stack(){
    printf("栈 - 单链表实现\n");
    Element e;

    // 栈 - 带头结点
    LinkStack S;

    // 初始化
    printf("初始化\n");
    LinkStackInit(S);

    // 判空
    printf("判空 : %d\n", LinkStackEmpty(S));

    // 入栈
    LinkStackEn(S, ele_build(10));
    LinkStackEn(S, ele_build(20));
    LinkStackEn(S, ele_build(30));
    LinkStackEn(S, ele_build(40));
    printf("入栈 : ");
    LinkStackPrint(S);

    // 判空
    printf("判空 : %d\n",LinkStackEmpty(S));

    // 出栈
    LinkStackDe(S,e);
    printf("出栈 %ld : ",ele_get_weight(e));
    LinkStackPrint(S);

    // 取队列元素 - 带头节点
    LinkStackGet(S,e);
    printf("取栈顶元素的值 : %ld\n",ele_get_weight(e));

    // 求队长
    printf("求栈长 : %d\n",LinkStackLength(S));

    // 销毁
    printf("销毁\n");
    LinkStackDestroy(S);
}
