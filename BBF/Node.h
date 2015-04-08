#include "MyPoint.h"
#include <limits.h>
#include <math.h>
#include <algorithm>
#pragma once
class Node
{
public:
	std::vector<MyPoint*> points;
	// 0 min 1 max
	double** tbb;
	double** lbb;
	Node* leftNode;
	Node* rightNode;
	Node* parent;
	double median;
	int m;
	int deep;
	int L;
	int dim;

	Node(std::vector<MyPoint*>* points, Node* parent = nullptr, double** lbb = nullptr);
	bool is_parent(Node* parent);
	~Node(void);

private:
	void split_node();
};

