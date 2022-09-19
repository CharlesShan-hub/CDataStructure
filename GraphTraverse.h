#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include "AdjacencyMatrix.h" // 邻接矩阵
//typedef MGraph Graph; 不能正常运行，可能因为先import的邻接矩阵
//#include "AdjacencyList.h" // 邻接表
typedef LGraph Graph;

void visit(int v){
	printf("%d ",v);
}

// 广度优先遍历辅助数组
bool BFSvisited[MaxVerNum]={0};

// 广度优先遍历(顶点)
void BFS(Graph G, int v, bool init=true){
	/** 初始化广度优先遍历辅助数组
	 * 1. 如果需要初始化则将所有位置为未访问
	 * 2. 不需要初始化的情况:BFS遍历森林
	 */
	if(init)
		for(int i=1;i<GetVexnum(G)+1;i++)
			BFSvisited[i]=false;
	/** 广度优先遍历辅助队列 
	 * 1. 开启BFS访问结点(首结点
	 * 2. 依次访问结点(队列出队) , 结点的子节点如果未访问就入队
	 */
	LinkQueue Q;
    LinkQueueInit(Q);
	visit(v);
	BFSvisited[v]=true;
    LinkQueueEn(Q, ele_build(v));
    Element e;
	while(!LinkQueueEmpty(Q)){
        LinkQueueDe(Q,e);
        v = ele_get_weight(e);
		for(int w=FirstNeighbor(G,v);w>=0;w=NextNeighbor(G,v,w)){
			if(!BFSvisited[w]){
				visit(w);
				BFSvisited[w]=true;
                LinkQueueEn(Q, ele_build(w));
			}
		}
	}
}

// 广度优先遍历(图)
void BFSTraverse(Graph G){
	for(int i=1;i<GetVexnum(G)+1;i++)
			BFSvisited[i]=false;
	for(int i=1;i<GetVexnum(G)+1;i++)
		if(!BFSvisited[i])
			BFS(G,i,false);
}

// 深度优先遍历辅助队列
bool DFSvisited[MaxVerNum] = {false};

// 深度优先遍历(点)
void DFS(Graph G, int v, bool init=true,bool print=false){
	if(init)
		for(int i=1;i<GetVexnum(G)+1;i++)
			DFSvisited[i]=false;
	if(!print) visit(v);
	DFSvisited[v]=true;
	for(int w=FirstNeighbor(G,v);w>=0;w=NextNeighbor(G,v,w))
		if(!DFSvisited[w])
			DFS(G,w,false,print);
    if(print) printf("%2d ", v);
}

// 深度优先遍历(图)
void DFSTraverse(Graph G,bool print=false){
	for(int i=1;i<GetVexnum(G)+1;i++)
			DFSvisited[i]=false;
	for(int i=1;i<GetVexnum(G)+1;i++)
		if(!DFSvisited[i])
			DFS(G,i,false,print);
}

void test_graph_traverse()
{
	printf("图的遍历\n");
	Graph G;
	TestInit(G);

	printf("\n广度优先遍历(2):");
	BFS(G,2);
	printf("\n广度优先遍历(5):");
	BFS(G,5);
	printf("\n广度优先遍历(7):");
	BFS(G,7);
	printf("\n广度优先遍历(图):");
	BFSTraverse(G);

	printf("\n深度优先遍历(2):");
	DFS(G,2);
	printf("\n深度优先遍历(图):");
	DFSTraverse(G);
}
