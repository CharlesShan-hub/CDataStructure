#include<stdio.h>

#include "CDataStructure.h"
#include "SqList.h"
#include "DqList.h"
#include "LList.h"
#include "LStack.h"
#include "LQueue.h"
#include "BracketCheck.h"
#include "ExpressionEvaluation.h"
#include "Notation.h"
#include "SqTree.h"
#include "LTree.h"
#include "TreeOperate.h"
#include "ThreadedTree.h"
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include "GraphTraverse.h"
#include "ShortestPath.h"
#include "TopologicalSort.h"
#include "BST.h"

void print_separate(){
    printf("\n\n============================\n");
}
int main(){
    printf("****************************\n");
    printf("****************************\n");
    printf("Chapter 1 - 顺序表\n");
    print_separate();
    test_state_sequence_list(); // 静态顺序表 SqList.h
    print_separate();
    test_dynamic_sequence_list(); // 动态顺序表 DqList.h
    print_separate();
    test_single_linked_list(); // 单链表(带头节点) LList.h

    printf("\n\n****************************\n");
    printf("****************************\n");
    printf("Chapter 2 - 栈与队列\n");
    print_separate();
    test_list_stack(); // 链式存储栈
    print_separate();
    test_list_queue(); // 链式存储队列
    print_separate();
    test_bracket_check(); // 括号匹配
    print_separate();
    test_expression_evaluation(); // 表达式求值
    print_separate();
    test_notation(); // 前缀中缀后缀表达式转换

    printf("\n\n****************************\n");
    printf("****************************\n");
    printf("Chapter 3 - 数与森林\n");
    print_separate();
    test_sequence_tree(); // 顺序存储的二叉树
    print_separate();
    test_link_tree();     // 链式存储的二叉树
    print_separate();
    test_tree_operate();  // 二叉树的遍历
    print_separate();
    test_threaded_tree(); // 线索二叉树(仅作展示)

    printf("\n\n****************************\n");
    printf("****************************\n");
    printf("Chapter 4 - 图\n");
    print_separate();
    test_adjacency_list(); // 邻接表
    print_separate();
    test_adjacency_matrix(); // 邻接矩阵
    print_separate();
    test_graph_traverse(); // 图的遍历
    print_separate();
    test_shortest_path(); // 最短路径
    print_separate();
    test_topological_sort(); // 拓扑排序

    printf("\n\n****************************\n");
    printf("****************************\n");
    printf("Chapter 5 - 查找\n");
    print_separate();
    test_BST();          // 二叉排序树
    print_separate();

    printf("\n\n****************************\n");
    printf("****************************\n");
    printf("Chapter 6 - 排序\n");
    print_separate();

}