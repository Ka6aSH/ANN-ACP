#include "Node.h"
#include "IAlgorithm.h"
#include <queue>

#pragma once
struct Triple {
    double dist;
    Node* next;
    Node* prev;
};

class CompareTriple {
    public:
    bool operator()(Triple& t1, Triple& t2)
    {
		if (t1.dist < t2.dist) return true;
		return false;
    }
};

class BBF : public IAlgorithm
{
public:
	std::vector<MyPoint*>* points;
	Node* root;
	std::priority_queue<Triple, std::vector<Triple>, CompareTriple> pq;
	int node_count;
	double eps;
	double (*distance_func)(const MyPoint*, const MyPoint*);

	BBF(std::vector<MyPoint*>* points, double eps, double(*distance)(const MyPoint*, const MyPoint*));
	Node* find_leaf(MyPoint* q);
	Node* lca(Node* node1, Node* node2);
	void push_if_better(
		Node* next, 
		Node* prev,
		Node* node_q,
		MyPoint* q, 
		double dist);
	virtual MyPoint* ANN(MyPoint* q);
	virtual std::vector<MyPoint*>* ENN(MyPoint* q);
	~BBF(void);
};

