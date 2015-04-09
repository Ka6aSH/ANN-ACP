#include "BBF.h"

BBF::BBF(std::vector<MyPoint*>* points) : points(points), root(new Node(points))
{
}

Node* BBF::find_leaf(MyPoint* q) 
{
	Node* temp = root;
	Node* actual;
    while (temp != nullptr) {
        actual = temp;
        if (q->vector[temp->m] < temp->median)
            temp = temp->leftNode;
        else
            temp = temp->rightNode;
    }
    return actual;
}

Node* BBF::lca(Node* node1, Node* node2) 
{
    int h1 = node1->deep, h2 = node2->deep;
    Node* one = node1;
	Node* two = node2;
    while (h1 != h2) {
        if (h1 > h2) {
            one = one->parent;
            h1 --;
        } else {
            two = two->parent;
            h2 --;
        }
    }

    while (one != two) {
        one = one->parent;
        two = two->parent;
    }
    return one;
}

void BBF::push_if_better(Node* next, 
	Node* prev,
	Node* node_q,
	MyPoint* q, 
	double dist ) {
		double distance = std::numeric_limits<double>::max();
        int m;
        Node* parent;
		if (next->is_parent(prev)) {
			distance = std::min(std::abs(q->vector[0] - prev->lbb[0][0]), std::abs(q->vector[0] - prev->lbb[0][1]));
            for (int i = 1; i < q->dimension; ++ i) {
                distance = std::min(distance,
                        std::min(
                                std::abs(q->vector[i] - prev->lbb[i][0]),
                                std::abs(q->vector[i] - prev->lbb[i][1])));
            }
        } else {
            parent = lca(next, node_q);
            m = parent->m;
            distance = std::min(std::abs(q->vector[m] - next->tbb[m][0]), std::abs(q->vector[m] - next->tbb[m][1]));
        }
        if (distance < dist) {
			Triple t = {distance, next, prev};
			pq.push(t);
        }
}

MyPoint* BBF::ANN(MyPoint* q) 
{
	Node *node_q = find_leaf(q);
	
	MyPoint* result = node_q->points[0];
	double distance = l2_distance(result, q);
	double tempDistance;
	for (int i = 0; i < node_q->points.size(); ++i)
	{
		tempDistance = l2_distance(q, node_q->points[i]);
		if (tempDistance < distance) 
		{
			distance = tempDistance;
			result = node_q->points[i];
		}
	}

	if (distance == 0) {
		return result;
	}

	push_if_better(node_q->parent, node_q, node_q, q, distance);
	while (pq.size() != 0) 
	{
		Triple t = pq.top();
		pq.pop();
		if (t.dist >= distance) {
			return result;
		}
		if (t.next->leftNode != nullptr) {
			if (t.next->leftNode != t.prev) {
				push_if_better(t.next->leftNode, t.next, node_q, q, distance);
			}
			if (t.next->rightNode != t.prev) {
				push_if_better(t.next->rightNode, t.next, node_q, q, distance);
			}
			if (t.next->parent != nullptr && t.next->parent != t.prev) {
				push_if_better(t.next->parent, t.next, node_q, q, distance);
			}
		} else {
			for (int i = 0; i < t.next->points.size(); ++i)
			{
				tempDistance = l2_distance(q, t.next->points[i]);
				if (tempDistance < distance) 
				{
					distance = tempDistance;
					result = t.next->points[i];
				}
			}
		}
	}
	return result;
}

BBF::~BBF(void)
{
	delete root;
}
