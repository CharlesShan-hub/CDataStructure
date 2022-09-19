/** 线性表 - 单链表 - 带头结点
 * 
 * Author: Charles Shan
 * Date: 2022.09.09
 * Version: 2.0
 * 
 *  内容包括:
 *  带头结点的单链表的定义
 *  ListInit              初始化
 *  ListEmpty             判空
 *  ListElemGet           按位查找
 *  ListElemLocate        按值查找
 *  ListInsertNextNode    后插操作
 *  ListInsertPriorNode   前插操作
 *  ListInsertIndex       按位插入
 *  ListDeleteIndex       删除操作
 *  ListDeleteNode        删除指定结点
 *  ListPrint             输出操作
 *  ListLength            求表长
 *  ListDestroy           销毁操作
 */

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

typedef Element DataType;

typedef struct ListNode{ //结点类型定义
    DataType data; //结点的数据域
    struct ListNode *next;//结点的指针域
}ListNode,*LinkList;


// 初始化 - 带头结点
bool ListInit(LinkList &L)
{
    L = (ListNode*)malloc(sizeof(ListNode));
    if(L==NULL)
        return false; // 内存不足
    L->next = NULL;
    return true;
}


// 判空
bool ListEmpty(LinkList L)
{
    return (L->next==NULL);
}

// 按位查找
ListNode* ListElemGet(LinkList L, int i)
{
    // 判断i
    if(i<0) return NULL;
    // 寻找i
    ListNode* p = L;
    int j=0;
    while(p && j<i){
        p = p->next;
        j++;
    }
    return p;
}

// 按值查找
ListNode* ListElemLocate(LinkList L, Element e)
{
    ListNode* p = L->next;
    while(p && !ele_equal(p->data,e))
        p = p->next;
    return p;// 找到后返回该节点指针, 否则返回NULL
}

// 后插操作
bool ListInsertNextNode(ListNode* p, Element e)
{
    if(p==NULL) return false;
    ListNode* s = (ListNode*)malloc(sizeof(ListNode));
    if(s==NULL) return false; // 内存不足
    ele_copy(s->data,e);
    s->next = p->next;
    p->next = s;
    return true;
}

// 指定结点插入
bool ListInsertPriorNode(ListNode* p, Element e)
{
    // Step1. 先后插 (- 把自己的值先赋给后边)
    //if(!ListInsertNextNode(p,p->data)) return false;
    if(p==NULL) return false;
    ListNode* s = (ListNode*)malloc(sizeof(ListNode));
    if(s==NULL) return false; // 内存不足
    ele_copy(s->data,p->data);
    s->next = p->next;
    p->next = s;

    // Step2. 再交换data
    ele_copy(p->data,e);
    return true;
}

// 按位插入
bool ListInsertIndex(LinkList &L, int i, Element e)
{
    // i合法性判断
    if(i<1) return false;
    // 寻找添加位置
    ListNode* p = ListElemGet(L,i-1);
    /*
    ListNode* p = L; // 头节点算第零个结点
    int count = 0;
    while(p!=NULL && count<i-1){
        p = p->next; count++; 
    }
    */
    if(p==NULL) return false;
    // 添加结点
    ListInsertNextNode(p,e);
    /*
    ListNode* s = (ListNode*)malloc(sizeof(ListNode*));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
    */
    return true;
}

// 按位删除
bool ListDeleteIndex(LinkList &L, int i)
{ 
    // i合法性判断
    if(i<1) return false;
    // 找到i-1个结点
    ListNode* p =  ListElemGet(L,i-1);
    /*
    ListNode* p = L;
    int count=0;
    while(p!=NULL && count<i-1){
        p = p->next;count++;
    }
    */
    if(p==NULL) return false;
    if(p->next==NULL) return false; // p的后继没有后继
    // 删除这个结点
    ListNode* d = p->next;
    p->next = d->next;
    free(d);
    return true;
}

// 删除指定结点
bool ListDeleteNode(LinkList &L)
{
    // 用L的下一个节点代替L, 然后释放L的下一个节点
    if(L==NULL) return false;
    ListNode* p = L->next;
    if(p==NULL){ // L是最后一个
        p=L;
        L=NULL;
        free(p);
    }else{
        ele_copy(L->data,p->data);
        L->next = p->next;
        free(p);
    }
    return true;
}

// 输出操作
bool ListPrint(LinkList L){
    ListNode* p = L->next;
    if(p==NULL) return false;
    do{
        ele_print(p->data);
        p = p->next;
    }while(p!=NULL);
    printf("\n");
    return true;
}

// 求表长
int ListLength(LinkList L)
{
    ListNode* p = L->next;
    int i=0;
    while(p){
        p=p->next; i++;
    }
    return i;
}

// 销毁
void ListDestroy(LinkList &L)
{
    ListNode *p = L;
    ListNode *q = NULL;
    while(p){
        q=p;
        p = p->next;
        free(q);
    }
    L=NULL;
}

void test_single_linked_list(){
    printf("线性表 - 单链表 - 带头结点\n");

    // 单链表 - 带头结点
    LinkList L;

    // 初始化
    printf("初始化\n");
    ListInit(L);

    // 判空
    printf("判空 : %d\n",ListEmpty(L));

    // 添加结点
    ListInsertIndex(L, 1, ele_build(1));
    ListInsertIndex(L, 2, ele_build(2));
    printf("添加结点 : ");
    ListPrint(L);

    // 按照值查找
    printf("按照值查找 1 : %ld\n",ele_get_weight(ListElemLocate(L,ele_build(1))->data));
    printf("按照值查找 50(没有返回false) : %d\n",ListElemLocate(L,ele_build(50))!=NULL);

    // 指定结点插入
    ListInsertPriorNode(L->next->next, ele_build(5));  // L是头结点
    printf("指定结点插入 L->next->next 插入 5: ");
    ListPrint(L);

    // 后插操作
    ListInsertNextNode(L->next,ele_build(100));// 插到第二个
    printf("后插结点 L->next 插入 100: ");
    ListPrint(L);

    // 删除结点
    ListDeleteIndex(L,4);
    printf("删除节点 4号 : ");
    ListPrint(L);

    // 删除结点
    ListDeleteNode(L->next); // L->next是第一项
    printf("删除节点 L->next : ");
    ListPrint(L);

    // 求表长
    printf("求表长 : %d\n",ListLength(L));

    // 销毁
    ListDestroy(L);
    printf("销毁\n");
}
