#include "vector"
#include "queue"
#include "iostream"
#include "unordered_map"

struct GraphNode
{
	//每一个节点都有指向其临近节点的一系列指针
	std::vector<GraphNode*> mAdjacent;
};

struct Graph
{
	//一个包含一系列节点的图
	std::vector<GraphNode*> mNodes;
};

struct WeightedEdge
{
	// 拥有这条边的节点
	struct WeightedGraphNode* mFrom;
	struct WeightedGraphNode* mTo;
	// 边的权重
	float mWeight;
};


struct WeightedGraphNode
{
	//存储外部边
	std::vector<WeightedEdge*> mEdges;
};


