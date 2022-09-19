/** 邻接矩阵（图）
 * 
 * Author: Charles Shan
 * Date: 2022.07.17
 * Version: 1.0
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

/**
 * 定义
 *
 * EdgeElement 边元素
 * GraphNode 结点
 * MGraph 图
 *
 */

#define EdgeElementNone 0  // 节点元素为空
#define EdgeElementInf -1  // 节点元素位无穷
#define MaxVerNum 50       // 邻接矩阵表示法中节点最大个数
#define EdgeWeight int     // 边的权重默认为int

typedef struct EdgeElement
{
    // Weight is the value of an Element
    EdgeWeight weight;
    // Others to be defind here
    // ...
}EdgeElement;
typedef struct GraphNode
{
	Element data;                           // 数据元素
	bool valid;                             // 有效
}GraphNode;
typedef struct
{
	GraphNode Vex[MaxVerNum];               // 顶点
	EdgeElement Edge[MaxVerNum][MaxVerNum]; // 邻接矩阵
	int vexnum,arcnum;                      // 图当前顶点数和边数/弧数
	bool weight;                            // 是否为带权图
}MGraph;
int edge_ele_get_weight(EdgeElement e){
    return e.weight;
}

void edge_ele_set_weight(EdgeElement &e,EdgeWeight weight){
    e.weight = weight;
}

EdgeElement edge_ele_init(EdgeWeight weight){
    EdgeElement e;
    edge_ele_set_weight(e,weight);
    return e;
}

void edge_ele_copy(EdgeElement &to, EdgeElement from){
    edge_ele_set_weight(to,from.weight);
}

bool edge_ele_equal(EdgeElement e1, EdgeElement e2){
    return e1.weight == e2.weight;
}

bool edge_ele_none(EdgeElement e){
    return e.weight == EdgeElementNone;
}

bool edge_ele_inf(EdgeElement e){
    return e.weight == EdgeElementInf;
}

/**
 * 图的操作
 *
 */

void UnWeightGraphInit(MGraph &G){
	G.vexnum = 0;
	G.arcnum = 0;
	G.weight = false;
	for(int i=0;i<MaxVerNum;i++){
		G.Vex[i].valid = false;
		for(int j=0;j<MaxVerNum;j++)
			edge_ele_set_weight(G.Edge[i][j],EdgeElementNone);
	}
}

void WeightGraphInit(MGraph &G){
	G.vexnum = 0;
	G.arcnum = 0;
	G.weight = true;
	for(int i=0;i<MaxVerNum;i++){
		G.Vex[i].valid = false;
		for(int j=0;j<MaxVerNum;j++)
			edge_ele_set_weight(G.Edge[i][j],EdgeElementInf);
	}
}

EdgeWeight GetWeight(MGraph G,int i,int j){
	return edge_ele_get_weight(G.Edge[i][j]);
}

bool AddNode(MGraph &G,Element e){
	int i = 1;
	while(G.Vex[i].valid==true) i++;
	if(i==MaxVerNum) return false;
	ele_copy(G.Vex[i].data,e);
	G.Vex[i].valid = true;
	G.vexnum++;
	return true;
}

void DeleteNode(MGraph &G,int x){
	G.Vex[x].valid = false;
	for(int i=1;i<MaxVerNum;i++){
		edge_ele_set_weight(G.Edge[x][i],G.weight?EdgeElementInf:EdgeElementNone);
		edge_ele_set_weight(G.Edge[i][x],G.weight?EdgeElementInf:EdgeElementNone);
	}
	G.vexnum--;
}

bool AddEdgeDirected(MGraph &G,int x,int y,EdgeElement value){
    if(edge_ele_none(value)) return false;
	edge_ele_copy(G.Edge[x][y],value);
    return true;
}

bool AddEdge(MGraph &G,int x,int y,EdgeElement value){
	if(edge_ele_none(value)) return false;
	edge_ele_copy(G.Edge[x][y],value);
	edge_ele_copy(G.Edge[y][x],value);
	return true;
}

void PrintGraph(MGraph G){
	int temp=0,templ=0,tempr=0;
	// 上表头
	printf("    ");
	for(int i=1;i<G.vexnum+1;i++){
		if(G.Vex[i+temp].valid==false){
			temp++;
			i--;
		}else{
			printf(" %2ld",ele_get_weight(G.Vex[i+temp].data));
		}
	}
	printf("\n   |");
	for(int i=1;i<G.vexnum+1;i++)
		printf("---");
	printf("\n");
	// 内容与左表头
	tempr=0;
	for(int i=1;i<G.vexnum+1;i++){
		if(G.Vex[i+tempr].valid==false){
			tempr++;
			i--;
			continue;
		}else
			printf(" %ld |",ele_get_weight(G.Vex[i+tempr].data));
		templ=0;
		for(int j=1;j<G.vexnum+1;j++){
			if(G.Vex[j+templ].valid==false){
				templ++;
				j--;
				continue;
			}
			if((i+tempr)==(j+templ))
				printf("  \\");
			else if(edge_ele_inf(G.Edge[i+tempr][j+templ]))
				printf("  .");
			else
				printf(" %2d",GetWeight(G,i+tempr,j+templ));
				
		}
		printf("\n");
	}
}

int FirstNeighbor(MGraph G,int v){
	for(int i=1;i<G.vexnum+1;i++)
		if(!edge_ele_none(G.Edge[v][i]) && !edge_ele_inf(G.Edge[v][i]) && G.Vex[i].valid)
			return i;
	return 0;
}

int NextNeighbor(MGraph G,int v, int h){
	for(int i=h+1;i<G.vexnum+1;i++)
		if(!edge_ele_none(G.Edge[v][i]) && !edge_ele_inf(G.Edge[v][i]) && G.Vex[i].valid)
			return i;
	return 0;
}

int FirstNeighborValue(MGraph G,int v,EdgeWeight &value){
	for(int i=1;i<G.vexnum+1;i++)
		if(!edge_ele_none(G.Edge[v][i]) && !edge_ele_inf(G.Edge[v][i]) && G.Vex[i].valid){
			value = GetWeight(G,v,i);
			return i;
		}
	return -1;
}

int NextNeighborValue(MGraph G,int v, int h,EdgeWeight &value){
	for(int i=h+1;i<G.vexnum+1;i++)
		if(!edge_ele_none(G.Edge[v][i]) && !edge_ele_inf(G.Edge[v][i]) && G.Vex[i].valid){
			value = GetWeight(G,v,i);
			return i;
		}
	return -1;
}

int GetVexnum(MGraph G){
    return G.vexnum;
}

int GetIndegree(MGraph G,int n){
	if(G.Vex[n].valid==false)
		return -1;
	int count=0;
	for(int i=1;i<MaxVerNum;i++)
		if(!edge_ele_none(G.Edge[i][n]) && !edge_ele_inf(G.Edge[i][n]) && G.Vex[i].valid)
			count++;
	return count;
}

void TestInit(MGraph &G){
	// 初始化
	//WeightGraphInit(G);
	UnWeightGraphInit(G);

	// 构建一些边与结点;
	int temp[] = {1,2,3,4,5,6,7,8};
	for(int i=0;i<sizeof(temp)/sizeof(temp[0]);i++)
		AddNode(G,ele_build(temp[i]));
	AddEdge(G,1,2,edge_ele_init(1));
	AddEdge(G,2,6,edge_ele_init(1));
	AddEdge(G,6,3,edge_ele_init(1));
	AddEdge(G,6,7,edge_ele_init(1));
	AddEdge(G,3,7,edge_ele_init(1));
	AddEdge(G,3,4,edge_ele_init(1));
	AddEdge(G,4,7,edge_ele_init(1));
	AddEdge(G,4,8,edge_ele_init(1));
	AddEdge(G,7,8,edge_ele_init(1));
	PrintGraph(G);
	printf(
		"\n 1 - 2   3 - 4\n"
		"     | / | / |\n"
		" 5   6 - 7 - 8\n");
}

typedef double FloydCost[MaxVerNum][MaxVerNum];

void GetFloWeight(MGraph G,FloydCost &Cost){
	for(int i=1;i<GetVexnum(G)+1;i++)
		for(int j=1;j<GetVexnum(G)+1;j++){
			if(!edge_ele_none(G.Edge[i][j]) && !edge_ele_inf(G.Edge[i][j]))
				Cost[i][j]=GetWeight(G,i,j);
		}
}

void test_adjacency_matrix(){
	printf("图(邻接矩阵)测试\n");
	// 创造图
    MGraph G;
	TestInit(G);

	// 获取邻居
	int value = 0;
	printf("\n获取3的第一个邻居 : %d\n",FirstNeighbor(G,3));
	FirstNeighborValue(G,3,value);
	printf("获取3的第一个邻居的值 : %d\n",value);
	printf("获取3的下一个邻居 : %d\n",NextNeighbor(G,3,FirstNeighbor(G,3)));
	NextNeighborValue(G,3,FirstNeighbor(G,3),value);
	printf("获取3的下一个邻居的值 : %d\n",value);

	// 测试入度
	printf("结点3的入度 : %d \n",GetIndegree(G,3));

	// 删除一些结点与边
	printf("\n删除一些结点(2)与边(6,3):\n");
	DeleteNode(G,2);
	PrintGraph(G);
}
