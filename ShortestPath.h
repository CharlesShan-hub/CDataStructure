#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include "AdjacencyMatrix.h" // 邻接矩阵
//typedef MGraph Graph;
//#include "AdjacencyList.h" // 邻接表
typedef LGraph Graph;

/**************************************************************************/
/*                                  BFS                                   */
/**************************************************************************/
typedef int BFSArray[2][MaxVerNum];

void BFSTestInit(Graph &G,BFSArray &array,bool only_array = false){
	if(!only_array)InitGraph(G);
	for(int i=0;i<MaxVerNum;i++){
		array[0][i]=INFINITY;
		array[1][i]=-1;
	}
}

void BFSPrintf(BFSArray array,int length){
	for(int k=0;k<3;k++){
		if(k==0){
			printf("        |");
			for(int i=1;i<length+1;i++)
				printf(" %4d",i);
			printf("\n");
			continue;
		}
		else if(k==1)
			printf("   d[]  |");
		else
			printf(" path[] |");
		for(int i=1;i<length+1;i++){
			printf(" %4.1d",array[k-1][i]);
		}
		printf("\n");
	}
	printf("\n");
}

void BFS_MIN_Distance(Graph G,int u,BFSArray &array){
	bool visited[MaxVerNum]={0};
	LinkQueue Q;
    LinkQueueInit(Q);
	array[0][u] = 0; // visit
	visited[u] = true;
    LinkQueueEn(Q, ele_build(u));
    Element e;
	while(!LinkQueueEmpty(Q)){
        LinkQueueDe(Q,e);
		u = ele_get_weight(e);
		for(int w=FirstNeighbor(G,u);w>=0;w=NextNeighbor(G,u,w)){
			if(visited[w]) continue;
            array[0][w] = array[0][u]+1; // visit
            array[1][w] = u;             // visit
            visited[w]=true;
            LinkQueueEn(Q, ele_build(w));
		}
	}
}


/**************************************************************************/
/*                              Dijkstra                                  */
/**************************************************************************/
/*
typedef struct DijArray
{
	bool final[MaxVerNum];  // 是否找到最短路径(默认false)
	double dist[MaxVerNum]; // 最短路径长度(默认INFINITY-65536)
	int path[MaxVerNum];    // 路径前驱(-1表示未改变)
}DijArray;
*/

void DijTestInit(Graph &G,DijArray &array,bool only_array = false){
	if(!only_array)InitGraph(G);
	for(int i=0;i<MaxVerNum;i++){
		array.final[i] = false;
		array.dist[i] = INFINITY;
		array.path[i] = -1;
	}
}

void DijPrintf(DijArray array,int length, int tag){
	// 打印表头
	if(tag==0)
		printf("        |");
	else
		printf("  [%2d]  |",tag);
	for(int i=1;i<length+1;i++)
        if(tag==0 || tag!= i)
		    printf(" %4d",i);
        else
            printf(" %3d*",i);
	printf("\n");
	// 是否找到路径
	printf("  final |");
	for(int i=1;i<length+1;i++)
        if(array.final[i])
            printf("    √");
        else
            printf("    x");
	printf("\n");
	// 最短路径长度
	printf("  dist  |");
	for(int i=1;i<length+1;i++)
		if(array.dist[i]!=INFINITY)
			printf(" %4.1f",array.dist[i]);
		else
			printf(" %4s","x");
	printf("\n");
	// 路径上的前驱
	printf("  path  |");
	for(int i=1;i<length+1;i++){
        if(array.path[i]==-1)
            printf("    x");
        else
			printf(" %4d",array.path[i]);
	}
	printf("\n\n");
}

void dijkstra(Graph G,int start,DijArray &array){
	// start是位序,从1开始

	// 初始
	array.final[start] = true;  // 是否找到最短路径
	array.dist[start] = 0;      // 最短路径长度
	array.path[start] = -1;     // 路径前驱(-1表示未改变)
	DijPrintf(array,GetVexnum(G),start);
	// 进行n-1次循环
	double min_dist = INFINITY; // 用来寻找最小值点(值)
	int min_dist_id = 1;        // 用来寻找最小值点(点)
	int last_min_id = start;    // 用来寻找最小值点(上个点)
	int value;                  // 用来更新下一个点(值)
	for(int n=1;n<GetVexnum(G);n++){
		// 寻找dist最小的未标记结点
		min_dist = INFINITY;
		min_dist_id = -1;
		for(int i=1;i<GetVexnum(G)+1;i++){
			if(array.final[i])
				continue;
			if(array.dist[i]<=min_dist){
				min_dist = array.dist[i];
				min_dist_id = i;
			}
		}
        printf(" ->%d\n",min_dist_id);

		// 标记最小未标记点
		array.final[min_dist_id] = true;
		if(array.dist[min_dist_id]+array.dist[last_min_id]<array.dist[min_dist_id]) {
            array.dist[min_dist_id] += array.dist[last_min_id];
            array.path[min_dist_id] = last_min_id;
        }
		last_min_id = min_dist_id;

		// 寻找各是否可以进行路径替换
		if(array.dist[min_dist_id]==INFINITY)
			continue;
		for(int next=FirstNeighborValue(G,min_dist_id,value);
			next!=-1;next=NextNeighborValue(G,min_dist_id,next,value)){
			if(array.final[next]){
                printf("  %d->%d : Already In Path\n",min_dist_id,next);
                continue;
            }
            if(array.dist[min_dist_id]+value<array.dist[next]){
                printf("  %d->%d : %.1f+%d<%.1f\n",min_dist_id,next,array.dist[min_dist_id],value,array.dist[next]);
                array.dist[next] = array.dist[min_dist_id]+value;
				array.path[next] = min_dist_id;
			}else{
                printf("  %d->%d : %.1f+%d>=%.1f\n",min_dist_id,next,array.dist[min_dist_id],value,array.dist[next]);
            }
		}
			
		//printf("[[%d->%d %d]]",min_dist_id,value_min_id,value_min);
		
		// 打印结果
		DijPrintf(array,GetVexnum(G),min_dist_id);
	}
}

/**************************************************************************/
/*                                Floyd                                   */
/**************************************************************************/

typedef double FloydCost[MaxVerNum][MaxVerNum];

typedef int FloydPath[MaxVerNum][MaxVerNum];

void FloydTestInit(Graph &G,FloydCost &Cost,FloydPath &Path){
	InitGraph(G);
	for(int i=0;i<MaxVerNum;i++)
		for(int j=0;j<MaxVerNum;j++){
            Cost[i][j] = (i==j ? 0.0 : INFINITY);
			Path[i][j] = -1;
		}
}

void FloydPrintf(FloydCost Cost,FloydPath Path,int length,int tag){
	if(tag!=-1)
		printf("\n Cost(%d):\n ",tag);
	else
		printf("\n Cost:\n ");
	for(int i=1;i<length+1;i++){
		for(int j=1;j<length+1;j++){
			if(Cost[i][j]==INFINITY)
				printf(" %4s","x");
			else
				printf(" %4.1f",Cost[i][j]);
		}
		printf("\n ");
	}
	
	if(tag!=-1)
		printf("\n Path(%d)\n ",tag);
	else
		printf("\n Path\n ");
	for(int i=1;i<length+1;i++){
		for(int j=1;j<length+1;j++)
			if(Path[i][j]!=-1)
                printf(" %2d",Path[i][j]);
            else
                printf("  ·");
		printf("\n ");
	}
}

void floyd(Graph G,FloydCost &Cost,FloydPath &Path){
	for(int k=1; k<GetVexnum(G)+1; k++){
		for(int i=1; i<GetVexnum(G)+1; i++){
			for(int j=1; j<GetVexnum(G)+1; j++){
				if(Cost[i][j]>Cost[i][k]+Cost[k][j]){
					Cost[i][j]=Cost[i][k]+Cost[k][j];
					Path[i][j]=k;
				}
			}
		}
		FloydPrintf(Cost,Path,GetVexnum(G),k);
	}
}

/**************************************************************************/
/*                              Test Init                                 */
/**************************************************************************/

void BFSTestInit1(Graph &G,BFSArray &array){
	BFSTestInit(G,array);
	for(int i=1;i<9;i++)
		AddNode(G, ele_build(i));
	AddEdge(G,5,1,1);
	AddEdge(G,1,2,1);
	AddEdge(G,2,6,1);
	AddEdge(G,3,6,1);
	AddEdge(G,7,6,1);
	AddEdge(G,3,7,1);
	AddEdge(G,3,4,1);
	AddEdge(G,7,4,1);
	AddEdge(G,7,8,1);
	AddEdge(G,8,4,1);
	PrintGraph(G);
    printf("\n1 - 2   3 - 4"
           "\n|   | / | / |"
           "\n5   6 - 7 - 8\n");
    printf("\n BFS算法简介:"
           "\nd[] 代表从某一结点到另一结点的跳数"
           "\npath[] 代表下一跳地址");
}

void DijTestInit1(Graph &G,DijArray &array,int i){
	DijTestInit(G,array);
	for(int j=1;j<6;j++)
		AddNode(G, ele_build(j));
	AddEdgeDirected(G,1,2,10);
	AddEdgeDirected(G,1,5,5);
	AddEdgeDirected(G,2,3,1);
	AddEdgeDirected(G,2,5,2);
	AddEdgeDirected(G,3,4,4);
	AddEdgeDirected(G,4,1,7);
	AddEdgeDirected(G,4,3,6);
	AddEdgeDirected(G,5,2,3);
	AddEdgeDirected(G,5,3,9);
	AddEdgeDirected(G,5,4,2);
	PrintGraph(G);
	printf("\n");
	GetDijWeight(G,array,i);
    printf(" Dijkstra算法简介:"
           "\nfinal: 代表结点是否已经加入路径"
           "\npath: 代表下一跳地址\n");
}

void FloydTestInit1(Graph &G,FloydCost &Cost,FloydPath &Path){
	// 初始化图
	// 1 - 2
	//  \ / 
	//   3
	FloydTestInit(G,Cost,Path);
	AddNode(G, ele_build(1));
	AddNode(G, ele_build(2));
	AddNode(G, ele_build(3));
	AddEdgeDirected(G,1,2,6);
	AddEdgeDirected(G,2,1,10);
	AddEdgeDirected(G,1,3,13);
	AddEdgeDirected(G,3,1,5);
	AddEdgeDirected(G,2,3,4);
	PrintGraph(G);
	GetFloWeight(G,Cost);
}

void FloydTestInit2(Graph &G,FloydCost &Cost,FloydPath &Path){
	// 初始化图
	FloydTestInit(G,Cost,Path);
	AddNode(G, ele_build(1));
	AddNode(G, ele_build(2));
	AddNode(G, ele_build(3));
	AddNode(G, ele_build(4));
	AddNode(G, ele_build(5));
	AddEdgeDirected(G,3,2,1);
	AddEdgeDirected(G,2,4,1);
	AddEdgeDirected(G,1,3,1);
	AddEdgeDirected(G,2,5,5);
	AddEdgeDirected(G,3,5,7);
	AddEdgeDirected(G,1,5,10);
	AddEdgeDirected(G,4,5,1);
	PrintGraph(G);
	GetFloWeight(G,Cost);
}

void FloydTestInit3(Graph &G,FloydCost &Cost,FloydPath &Path){
	// 初始化图
	FloydTestInit(G,Cost,Path);
	printf(
		"      3         -----------\n"
		" /(7)   (7)\\    |1-3-2:14 |\n"
		"1-(6)-4-(6)-2   |1-4-2:12 |\n"
		" \\(1)   (1)/    |1-5-6-2:3|\n"
		"  5 -(1)- 9     -----------\n\n");
	FloydTestInit(G,Cost,Path);
	for(int i=1;i<7;i++)
		AddNode(G, ele_build(i));
	AddEdgeDirected(G,1,3,10);
	AddEdgeDirected(G,3,2,10);
	AddEdgeDirected(G,1,4,6);
	AddEdgeDirected(G,4,2,6);
	AddEdgeDirected(G,1,5,1);
	AddEdgeDirected(G,5,6,1);
	AddEdgeDirected(G,6,2,1);
	PrintGraph(G);
	GetFloWeight(G,Cost);
}

void test_shortest_path(){

	/* BFS算法案例 */
    printf("最短路径 - BFS\n");
    BFSArray bfs_array;   // 用于保存路径与长度

    Graph G1;
    BFSTestInit1(G1,bfs_array);
    printf("\nBFS算法(从2开始):\n");
    BFS_MIN_Distance(G1,2,bfs_array);
    BFSPrintf(bfs_array,GetVexnum(G1));

    BFSTestInit(G1,bfs_array,true);
    printf("\nBFS算法(从3开始):\n");
    BFS_MIN_Distance(G1,3,bfs_array);
    BFSPrintf(bfs_array,GetVexnum(G1));

	/* Dijkstra算法案例 */
    printf("最短路径 - Dijkstra\n");
    DijArray dij_array;

    Graph G2;
    DijTestInit1(G2,dij_array,1);
    printf("\nDijkstra算法(开始节点名称:1):\n");
    dijkstra(G2,1,dij_array);
    //DijTestInit(G2,dij_array,true);
    //GetDijWeight(G2,dij_array,2);
    DijTestInit1(G2,dij_array,2);
    printf("\nDijkstra算法(开始节点名称:2):\n");
    dijkstra(G2,2,dij_array);


	/* Floyd算法案例 */
    printf("最短路径 - floyd\n");
    FloydCost Cost; // 用来存储路径权重
    FloydPath Path; // 用来保存经过的结点

    Graph G3_1;
    FloydTestInit1(G3_1,Cost,Path);
    printf("\nfloyd算法:\n");
    floyd(G3_1,Cost,Path);

    printf("\n构建测试图2:\n\n");
    Graph G3_2;
    FloydTestInit2(G3_2,Cost,Path);
    printf("\nfloyd算法:\n");
    floyd(G3_2,Cost,Path);

    printf("\n构建测试图3:\n\n");
    Graph G3_3;
    FloydTestInit3(G3_3,Cost,Path);
    printf("\nfloyd算法:\n");
    floyd(G3_3,Cost,Path);
}