/** 队列
 * 
 * Author: Charles Shan
 * Date: 2022.07.17
 * Version: 1.0
 * 
 *  内容包括:
 *  带头结点的单链表的定义
 *  LinkQueueInit          初始化
 *  LinkQueueEmpty         判空
 *  LinkQueueEn            入队
 *  LinkQueueDe            出队
 *  LinkQueueGet           取队列元素
 *  QueueLength            求队长
 *  QueueDestroy           销毁操作
 *  QueuePrint             输出操作
 */

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

typedef Element DataType;

typedef struct
{
    ListNode *front, *rear;
}LinkQueue;

// 初始化 - 带头节点 - 队列
bool LinkQueueInit(LinkQueue &Q){
	Q.rear = (ListNode*)malloc(sizeof(ListNode));
	//if(Q.rear == NULL) 
	//	return NULL;
	Q.front = Q.rear;
	Q.front->next = NULL;
	return true;
}

// 判空 - 带头节点
bool LinkQueueEmpty(LinkQueue Q){
	return Q.rear == Q.front;
}

// 入队 - 带头节点
void LinkQueueEn(LinkQueue &Q, Element x){
	// 创建新节点
    ListNode *s = (ListNode*)malloc(sizeof(ListNode));
	s->next = NULL;
	ele_copy(s->data,x);
	// 尾插
	Q.rear->next = s;
	// 修改尾指针
	Q.rear = s;
}

// 出队 - 带头节点
bool LinkQueueDe(LinkQueue &Q,Element &x){
	// 空队
	if(Q.rear==Q.front)return false;
	// 获取第一个节点
    ListNode *s = Q.front->next;
	// 获取数据并返回
	ele_copy(x,s->data);
	// 改变front
	Q.front->next = s->next;
	// 改变rear - 最后一个节点
	if(s->next==NULL)
		Q.rear = Q.front;
	// 释放第一个节点
	free(s);
	return true;
}

// 取队列元素 - 带头节点
bool LinkQueueGet(LinkQueue Q,Element &x){
	if(Q.rear==Q.front)return false;
	ele_copy(x,Q.front->next->data);
	return true;
}

// QueueLength
int LinkQueueLength(LinkQueue Q){
	int length=0;
    ListNode* q = Q.front;
	while(q!=Q.rear){
		q = q->next;
		length++;
	}
	return length;
}

// QueueDestroy
void LinkQueueDestroy(LinkQueue &Q){
	Element e;
	while(!LinkQueueEmpty(Q)){
		LinkQueueDe(Q,e);
	}
}

// QueuePrint
void LinkQueuePrint(LinkQueue Q){
    ListNode* p = Q.front;
	while(p->next){
		printf("%ld ",ele_get_weight(p->next->data));
		p = p->next;
	}
	printf("\n");
}

void test_list_queue(){
    printf("队列 - 单链表实现\n");
    Element e;

    // 队列 - 带头结点
    LinkQueue Q;

    // 初始化
    printf("初始化\n");
    LinkQueueInit(Q);

    // 判空
    printf("判空 : %d\n",LinkQueueEmpty(Q));

    // 入队
    LinkQueueEn(Q, ele_build(10));
    LinkQueueEn(Q, ele_build(20));
    LinkQueueEn(Q, ele_build(30));
    LinkQueueEn(Q, ele_build(40));
    printf("入队 : ");
    LinkQueuePrint(Q);

    // 判空
    printf("判空 : %d\n",LinkQueueEmpty(Q));

    // 出队
    LinkQueueDe(Q,e);
    printf("出队 %ld : ",ele_get_weight(e));
    LinkQueuePrint(Q);

    // 取队列元素 - 带头节点
    LinkQueueGet(Q,e);
    printf("取队头元素的值 : %ld\n",ele_get_weight(e));

    // 求队长
    printf("求队长 : %d\n",LinkQueueLength(Q));

    // 销毁
    printf("销毁\n");
    LinkQueueDestroy(Q);
}
