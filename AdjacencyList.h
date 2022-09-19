/** 邻接矩阵（图）
 *
 * Author: Charles Shan
 * Date: 2022.09.10
 * Version: 2.0
 *
 *  内容包括:
 *  邻接矩阵结点与邻接矩阵的定义
 *  UnWeightGraphInit      无权图初始化
 *  WeightGraphInit        带权图初始化
 *  GetWeight              获取边的权重
 *  AddNode                添加(指定下标)结点
 *  DeleteNode             删除(指定下标)节点
 *  AddEdgeDirected        添加有向边
 *  AddEdge                添加边
 *  PrintGraph             打印图
 *  FirstNeighbor          寻找第一个邻居的下标(没有返回0)
 *  NextNeighbor           寻找某邻居后的下一个邻居下标(没有返回0)
 *  FirstNeighborValue     寻找第一个邻居的下标(没有返回0)与值
 *  NextNeighborValue      寻找某邻居后的下一个邻居下标(没有返回0)与值
 *  GetVexnum              获取结点数
 *  GetIndegree            入度
 *  TestInit               构建测试图
 */

/** old
 * Adjacent(G,x,y):判断是否存在边<x,y>
 * Neighbors(G,x):列出图G中与结点x邻接的边
 * InsertVertex(G,x):插入x
 * DeleteVertex(G,x):删除x
 * AddEdge(G,x,y):插入连接
 * RemoveEdge(G,x,y):删除连接
 * FirstNeighbor(G,x):x的第一个邻接点,不存在返回-1
 * NextNeighbor(G,x,y):x的下一个邻接点(假设y是x的邻接点),如果y是最后一个,返回-1
 * GetEdgeValue(G,x,y):获取<x,y>边的权值
 * SetEdgeValue(G,x,y,v):设置G中边<x,y>边的权值为v
 */

#define MaxVerNum 50
#define NONE 0
#define EdgeWeight int     // 边的权重默认为int

typedef struct ArcNode
{
    int adjvex;           // 边/弧指向哪个节点
    struct ArcNode *next; // 指向下一条弧的指针
    EdgeWeight value;     // 权值(默认为1)
    // other info
}ArcNode;

typedef struct VNode{
    Element data;        // 顶点数据
    ArcNode *first;      // 第一条边/弧
    int indegree;        // 入度
    //data
}VNode,LGraph[MaxVerNum],AdjList[MaxVerNum];

// 为了方便,Graph的第一个结点数据存放结点数量

bool AddEdgeDirected(AdjList &G,int x,int y,EdgeWeight value){
    ArcNode *p = NULL;
    ArcNode *q = NULL;
    // 头插x-y
    q = (ArcNode*)malloc(sizeof(ArcNode));
    q->adjvex = y;
    q->value = value;
    p = G[x].first;
    G[x].first = q;
    G[x].first->next = p;
    G[y].indegree++;
    return true;
}

bool AddEdge(AdjList &G,int x,int y,EdgeWeight value){
    AddEdgeDirected(G,x,y,value);
    AddEdgeDirected(G,y,x,value);
    return true;
}

bool AddNode(AdjList &G,Element data){
    ArcNode *p = NULL;
    int count = 1;
    while(ele_get_weight(G[count].data)!=NONE){
        count++;
    }
    G[count].data=data;
    ele_set_weight(G[0].data, ele_get_weight(G[0].data)+1);
    G[count].indegree=0;
    return true;
}

int FirstNeighbor(AdjList G,int v){
    if(G[v].first==NULL)
        return -1;
    else
        return G[v].first->adjvex;
}

int NextNeighbor(AdjList G,int v, int h){
    ArcNode *p=G[v].first;
    while(p!=NULL && p->adjvex!=h)
        p=p->next;
    if(p->next==NULL)
        return -1;
    else
        return p->next->adjvex;
}

int FirstNeighborValue(AdjList G,int v,int &value){
    if(G[v].first==NULL)
        return -1;
    else{
        value = G[v].first->value;
        return G[v].first->adjvex;
    }
}

int NextNeighborValue(AdjList G,int v, int h,int &value){
    ArcNode *p=G[v].first;
    while(p!=NULL && p->adjvex!=h)
        p=p->next;
    if(p->next==NULL)
        return -1;
    else{
        value = p->next->value;
        return p->next->adjvex;
    }
}

void PrintGraph(AdjList G){
    ArcNode *p = NULL;
    for(int i=1;i<MaxVerNum;i++){
        if(ele_get_weight(G[i].data)!=NONE){
            printf(" %ld ",ele_get_weight(G[i].data));
            if(G[i].first!=NULL)
                printf("-> ");
            for(p=G[i].first;p!=NULL;p=p->next)
                printf("%d(%2d) ",p->adjvex,p->value);
            printf("\n");
        }
    }
}

int GetVexnum(AdjList G){
    return int(ele_get_weight(G[0].data));
}

void InitGraph(AdjList &G){
    for(int i=0;i<MaxVerNum;i++){
        ele_init(G[i].data,NONE);
        G[i].first = NULL;
    }
}

void TestInit(AdjList &G){
    // 构建新图
    InitGraph(G);
    // 构建一些边与结点;
    int temp[] = {1,2,3,4,5,6,7,8};
    for(int i=0;i<sizeof(temp)/sizeof(temp[0]);i++)
        ele_init(G[i+1].data,temp[i]);
    ele_init(G[0].data,8);
    //AddEdge(G,5,1,1);
    AddEdge(G,1,2,1);
    AddEdge(G,2,6,1);
    AddEdge(G,6,3,1);
    AddEdge(G,6,7,1);
    AddEdge(G,3,7,1);
    AddEdge(G,3,4,1);
    AddEdge(G,4,7,1);
    AddEdge(G,4,8,1);
    AddEdge(G,7,8,1);

    PrintGraph(G);
    printf(
        "\n 1 - 2   3 - 4\n"
        "     | / | / |\n"
        " 5   6 - 7 - 8\n");
}

void test_adjacency_list()
{
    printf("图(邻接表)测试\n");
    LGraph G;
    TestInit(G);

    printf("\n获取5的第一个邻居 :%d\n",FirstNeighbor(G,5));
    printf("获取3的第一个邻居 :%d\n",FirstNeighbor(G,3));
    printf("获取3的第二个邻居 : %d\n",NextNeighbor(G,3,4));
    printf("获取3的第三个邻居 : %d\n",NextNeighbor(G,3,7));
    printf("获取3的第四个邻居 : %d\n",NextNeighbor(G,3,6));
    printf("获取图的结点个数: %d\n",GetVexnum(G));
}


typedef double FloydCost[MaxVerNum][MaxVerNum];

void GetFloWeight(LGraph G,FloydCost &Cost){
    ArcNode *p = NULL;
    for(int i=1,j=1;i<MaxVerNum;i++){
        if(ele_get_weight(G[i].data)!=NONE){
            j=1;
            for(p=G[i].first;p!=NULL;p=p->next){
                Cost[i][p->adjvex]=p->value;
                j++;
            }
        }
    }
}

typedef struct DijArray
{
    bool final[MaxVerNum];  // 是否找到最短路径
    double dist[MaxVerNum]; // 最短路径长度
    int path[MaxVerNum];    // 路径前驱(-1表示未改变)
}DijArray;

void GetDijWeight(LGraph G,DijArray &Array,int i){
    for(ArcNode *p=G[i].first;p!=NULL;p=p->next){
        Array.dist[p->adjvex]=p->value;
        Array.path[p->adjvex]=i;
    }
}

int GetIndegree(LGraph G,int i){
    return G[i].indegree;
}