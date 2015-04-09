#include "Node.h"
#include <queue>
#include "Functions.h"

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

class BBF
{
public:
	std::vector<MyPoint*>* points;
	Node* root;
	std::priority_queue<Triple, std::vector<Triple>, CompareTriple> pq;

	BBF(std::vector<MyPoint*>* points);
	Node* find_leaf(MyPoint* q);
	Node* lca(Node* node1, Node* node2);
	void push_if_better(
		Node* next, 
		Node* prev,
		Node* node_q,
		MyPoint* q, 
		double dist);
	MyPoint* ANN(MyPoint* q);
	~BBF(void);
};

