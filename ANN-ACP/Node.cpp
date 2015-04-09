#include "Node.h"

Node::Node(std::vector<MyPoint*>* points_list, Node* parent, double** lbb) 
{
	points.insert(points.end(), points_list->begin(), points_list->end());
	dim = points[0]->dimension;
	this->parent = parent;
	if (parent != nullptr)
		this->deep = parent->deep + 1;
	else
		deep = 0;
	if (lbb == nullptr) {
		this->lbb = new double*[dim];
		double* temp;
		for (int i = 0; i < dim; ++ i)
		{
			temp = new double[2];
			temp[0] = std::numeric_limits<double>::min();
			temp[1] = std::numeric_limits<double>::max();
			this->lbb[i] = temp;
		}
	}
	else 
		this->lbb = lbb;
	L = 10;
	this->tbb = new double*[dim];
	for (int i = 0; i < dim; ++ i) 
		tbb[i] = new double[2];
	this->m = 0;
	this->leftNode = nullptr;
	this->rightNode = nullptr;
	split_node();
}

void Node::split_node()
{
	for (int i = 0; i < dim; ++ i)
	{
		tbb[i][0] = points[0]->vector[i];
		tbb[i][1] = points[0]->vector[i];
	}

	for (int i = 0; i < dim; ++ i)
		for (int j = 0; j < points.size(); ++ j) {
			if (tbb[i][0] > points[j]->vector[i])
				tbb[i][0] = points[j]->vector[i];
			if (tbb[i][1] < points[j]->vector[i])
				tbb[i][1] = points[j]->vector[i];
		}

	if (points.size() > L) {
		double delta = tbb[0][1] - tbb[0][0];
		for (int i = 1; i < dim; ++ i) {
			if (delta < tbb[i][1] - tbb[i][0]) {
				delta = tbb[i][1] - tbb[i][0];
				m = i;
			}
		}
		std::vector<double> coords;
		for(auto i = points.begin(); i < points.end(); i++) {
			coords.push_back((*i)->vector[m]);
		}
		std::nth_element(coords.begin(), coords.begin() + coords.size() / 2, coords.end());
		this->median = coords[coords.size() / 2];

		double** lbb_left = new double*[dim];
		double** lbb_right= new double*[dim];
		for (int i = 0; i < dim; ++ i)
		{
			lbb_left[i] = lbb[i];
			lbb_right[i] = lbb[i];
		}
		lbb_left[m] = new double[2];
		lbb_right[m] = new double[2];
		for (int i = 0; i < 2; ++ i)
		{
			lbb_left[m][i] = lbb[m][i];
			lbb_right[m][i] = lbb[m][i];
		}
		lbb_left[m][1] = median;
		lbb_right[m][0] = median;

		std::vector<MyPoint*> points_left;
		std::vector<MyPoint*> points_right;

		for (auto i = points.begin(); i < points.end(); i++)
			if ((*i)->vector[m] < median)
				points_left.push_back(*i);
			else
				points_right.push_back(*i);

		if (points_left.size() != 0 && points_right.size() != 0)
		{
			leftNode = new Node(&points_left, this, lbb_left);
			rightNode = new Node(&points_right, this, lbb_right);
		}
	}
}

bool Node::is_parent(Node* node)
{
	Node* temp = node;
	while (temp != nullptr) 
	{
		if (temp->parent == this)
			return true;
		temp = temp->parent;
	}
	return false;
}

Node::~Node(void)
{
	delete leftNode;
	delete rightNode;
}
