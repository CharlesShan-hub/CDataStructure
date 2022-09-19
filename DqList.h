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

// 链式储存类型定义
#define InitSize 3 // 默认最大长度
typedef Element DataType;
typedef struct
{
    DataType* data;
    int Max;
    int length;
}DqList;

// 初始化
void ListInit(DqList &L)
{
    // 创造空间(默认InitSize大小)
    L.data = (DataType*)malloc(sizeof(DataType)*InitSize); // C type
    // L.data = new int[InitSize]; // C++ type
    // 默认初始值为0
    for(int i=0; i<InitSize; i++)
        ele_init(L.data[i],0);
    //长度为0
    L.length = 0;
    //最大容量
    L.Max = InitSize;
}

// 增加动态数组的长度
void IncreaseSize(DqList &L, int len)
{
    // 寄存用的指针
    DataType* temp = L.data;
    // 申请新空间
    L.data = (DataType*)malloc(sizeof(DataType)*(len+L.Max));
    // 复制数据
    for(int i=0;i<L.length;i++){
        L.data[i] = temp[i];
    }
    // 增加长度
    L.Max = L.Max+len;
    // 释放原内存
    free(temp);
}

// 判空
bool ListEmpty(DqList L){
    return L.length==0;
}

// 插入操作
bool ListInsertIndex(DqList &L, int i, DataType e)
{
    // 判断i是否有效
    if(i<1||i>L.length+1){
        printf("invaled i: i=%d,length=%d\n",i,L.length);
        return false;
    }
    // 判断是否栈满
    if(L.length >= L.Max){
        printf("adding new space...\n");
        IncreaseSize(L,InitSize);
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
bool ListDeleteIndex(DqList &L, int i)
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
bool GetItem(DqList L, int i, DataType &e)
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
int LocateElem(DqList &L, DataType e)
{
    for(int i=0;i<L.length; i++)
        if(ele_equal(L.data[i],e))
            return i+1; // 注意返回的是位序(下标+1)
    return 0;
}

// 打印
void ListPrint(DqList L){
    for(int i=0;i<L.length;i++)
        printf("%2ld ", ele_get_weight(L.data[i]));
    printf("\n");
}

// 求表长
int ListLength(DqList L){
    return L.length;
}

// 测试部分
void test_dynamic_sequence_list()
{
    printf("线性表 - 顺序表 - 动态分配\n");
    DataType e;

    // 顺序存储 - 静态分配
    DqList L;

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