#pragma once
#include <vector>

enum NodeState {
	Failure, Success, Running
};

class iNode {
public:
	// creates an empty node
	iNode() : parent(nullptr) {}

	// creates a node with children
	iNode(std::vector<iNode*> children) : parent(nullptr), children(children) {}

	~iNode() {
		for (unsigned int i = 0; i < children.size(); i++) {
			delete(children[i]);
		}
	}

	// set's this node's parent to be the given node
	void SetParent(iNode* parent) {
		this->parent = parent;
	}

	// evaluates the node and returns the node's state
	virtual NodeState Evaluate() = 0;
protected:
	iNode* parent;
	std::vector<iNode*> children; 
private:
	// sets the node's parent to this node, 
	// and adds the node to this node's list of children
	void AttachNode(iNode* node) {
		node->SetParent(this);
		this->children.push_back(node);
	}
};