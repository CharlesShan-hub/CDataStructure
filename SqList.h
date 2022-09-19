/** 线性表 - 顺序表 - 静态分配
 *
 * Author: Charles Shan
 * Date: 2022.09.10
 * Version: 2.0
 *
 *  内容包括:
 *  顺序储存类型定义
 *  ListInit              初始化
 *  ListEmpty             判空
 *  ListElemGet           按位查找
 *  *ListElemLocate        按值查找
 *  *ListInsertNextNode    后插操作
 *  *ListInsertPriorNode   前插操作
 *  ListInsertIndex       按位插入
 *  ListDeleteIndex       删除操作
 *  *ListDeleteNode        删除指定结点
 *  ListPrint             输出操作
 *  ListLength            求表长
 *  *ListDestroy           销毁操作
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 顺序储存类型定义
#define MaxSize 15 // 定义最大数量
typedef Element DataType;
typedef struct
{
    DataType data[MaxSize];
    int length;
}SqList;

// 初始化
void ListInit(SqList &L)
{
    // 默认初始值为0
    for(int i=0; i<MaxSize; i++)
        ele_set_weight(L.data[i],0);
    //长度为0
    L.length = 0;
}

// 判空
bool ListEmpty(SqList L){
    return L.length==0;
}

// 插入操作
bool ListInsertIndex(SqList &L, int i, DataType e)
{
    // 判断i是否有效
    if(i<1||i>L.length+1){
        printf("invaled i: i=%d,length=%d\n",i,L.length);
        return false;
    }
    // 判断是否栈满
    if(L.length >= MaxSize){
        printf("full\n");
        return false;
    }
    // 进行元素后移
    for(int j=L.length; j>=i; j--)
        ele_copy(L.data[j],L.data[j-1]);
    // 进行新元素插入
    ele_copy(L.data[i-1],e);
    // 线性表长度加一
    L.length++;
    return true;
}

// 删除操作
// 删除顺序表中第i（ l<=i<=L.length ）个位置的元素，
// 若成功则返回 true ，否则返回 false
bool ListDeleteIndex(SqList &L, int i)
{
    // 判断i是否有效
    if(i<1||i>L.length+1){
        printf("invaled i\n");
        return false;
    }
    // 后面元素前移
    for(int j=i; j<L.length; j++)
        ele_copy(L.data[j-1],L.data[j]);
    // 线性表长减一
    L.length--;
    return true;
}

// 按位查找
bool GetItem(SqList L, int i, DataType &e)
{
    //判断i是否有效
    if(i<1||i>L.length){

        printf("invaled i\n");
        return false;
    }
    ele_copy(e,L.data[i-1]);
    return true;
}

// 按值查找 - 返回位序(下标+1)
int LocateElem(SqList &L, DataType e)
{
    for(int i=0;i<L.length; i++)
        if(ele_equal(L.data[i],e))
            return i+1; // 注意返回的是位序(下标+1)
    return 0;
}

// 打印
void ListPrint(SqList L){
    for(int i=0;i<L.length;i++)
        printf("%2ld ", ele_get_weight(L.data[i]));
    printf("\n");
}

// 求表长
int ListLength(SqList L){
    return L.length;
}

// 测试部分
void test_state_sequence_list()
{
    printf("线性表 - 顺序表 - 静态分配\n");
    DataType e;

    // 顺序存储 - 静态分配
    SqList L;

    // 初始化
    printf("初始化\n");
    ListInit(L);

    // 判空
    printf("判空 : %d\n",ListEmpty(L));

    // 添加节点
    ListInsertIndex(L,1,ele_build(10));
    ListInsertIndex(L,2,ele_build(30));
    ListInsertIndex(L,2,ele_build(50));
    ListInsertIndex(L,2,ele_build(70));
    printf("添加节点 : ");
    ListPrint(L);

    // 删除结点
    printf("删除节点为序1 : ");
    ListDeleteIndex(L,1);
    ListPrint(L);

    // 按位查找
    printf("按位查找 6位(返回为false) : ");
    GetItem(L,6,e);
    GetItem(L,1,e);
    printf("按位查找 1位 : %ld\n", ele_get_weight(e));

    // 按值查找
    printf("按值查找 30 : %d\n",LocateElem(L, ele_build(30)));

    // 求表长
    printf("求表长 : %d\n", ListLength(L));

    // 判空
    printf("判空 : %d\n",ListEmpty(L));
}