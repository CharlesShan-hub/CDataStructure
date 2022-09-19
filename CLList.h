/** 线性表 - 循环单链表 - 带头结点
 * 
 * Author: Charles Shan
 * Date: 202x.xx.xx
 * Version: x.x
 * 
 *  内容包括:
 *  带头结点的单链表的定义
 *  ListInit              初始化
 *  //ListEmpty             判空
 *  //ListElemGet           按位查找
 *  //ListElemLocate        按值查找
 *  //ListInsertNextNode    后插操作
 *  //ListInsertPriorNode   前插操作
 *  //ListInsertIndex       按位插入
 *  //ListDeleteIndex       删除操作
 *  //ListDeleteNode        删除指定结点
 *  //ListPrint             输出操作
 *  //ListLength            求表长
 *  //ListDestroy           销毁操作
 */

typedef Element DataType;

typedef struct ListNode{ //结点类型定义
    DataType data; //结点的数据域
    struct ListNode *next;//结点的指针域
}ListNode,*LinkList;

