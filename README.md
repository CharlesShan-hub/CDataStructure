# README
## 基础元素与线性表

* ✅Element
  * `CDataStructure.h`
  * 定义了元素数据单元的结构，默认包涵`weight`参数（默认为int类型）。并提供结点的`weight`设置与获取、结点比较、结点复制等API。
* ✅SqList
  * `SqList.h`
  * 静态顺序表(Static Sequence List)
* ✅DqList
  * `DqList.h`
  * 动态顺序表(Dynamic Sequence List)
* ✅ListNode,*LinkList
  * `LList.h`
  * 带头节点的单链表(Single Linked List)
* ❌CListNode,*CLinkList
  * `CLList.h`
  * 带头节点的循环单链表(Single Circular Linked List)
* ❌DListNode,*DLinkList
  * `DLList.h`
  * 带头节点的双链表(Double Linked List)
* ❌DCListNode,*DCLinkList
  * `DCLList.h`
  * 带头节点的循环单链表(Double Circular Linked List)
* ❌SListNode,SLList
  * `SLList.h`
  * 静态链表(Static Linked List)

## 栈与队列
* ❌SqStack
  * `SqStack.h`
  * 顺序表实现的栈
* ❌ShareStack
  * `ShStack.h`
  * 共享栈(顺序表)
* ✅LinkStack
  * `LStack.h`
  * 带头节点的单链表实现的栈
* ❌SqQueue
  * `SqQueue.h`
  * 顺序表实现的队列
* ✅LinkQueue
  * `LQueue.h`,前置``LList.h``
  * 带头节点的单链表实现的队列
* ✅括号匹配算法
  * `BracketCheck.h`
* ✅表达式求值
  * `ExpressionEvaluation.h`

## 树
* ❌SqTree
  * `SqTree.h`
  * 顺序表实现的二叉树
* ❌LinkTree
  * `LTree.h`
  * 链表实现的二叉树
* ❌ThrTree
  * `ThrTree.h`
  * 线索二叉树

## 图
* ✅VNode,*LGraph,*AdjList
  * `AdjacencyList.h`
  * 链表实现的图（邻接矩阵）
* ✅EdgeElement
  * `AdjacencyMatrix.h`
  * 定义了图的结点，默认包涵`weight`参数（默认为int类型）。并提供结点的`weight`设置与获取、结点比较、结点复制等API。
* ✅MGraph
  * `AdjacencyMatrix.h`
  * 顺序表实现的图（邻接矩阵）
  * (邻接表与邻接矩阵二选一)

## 查找


## 排序
