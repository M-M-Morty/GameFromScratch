#include "vector"
#include "queue"
#include "iostream"
#include "unordered_map"

struct GraphNode
{
	//ÿһ���ڵ㶼��ָ�����ٽ��ڵ��һϵ��ָ��
	std::vector<GraphNode*> mAdjacent;
};

struct Graph
{
	//һ������һϵ�нڵ��ͼ
	std::vector<GraphNode*> mNodes;
};

struct WeightedEdge
{
	// ӵ�������ߵĽڵ�
	struct WeightedGraphNode* mFrom;
	struct WeightedGraphNode* mTo;
	// �ߵ�Ȩ��
	float mWeight;
};


struct WeightedGraphNode
{
	//�洢�ⲿ��
	std::vector<WeightedEdge*> mEdges;
};


