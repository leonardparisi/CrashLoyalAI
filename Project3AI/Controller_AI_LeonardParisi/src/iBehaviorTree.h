#pragma once

#include "iNode.h"

class iBehaviorTree {
public:
	// evaluates the behavior tree
	void Evaluate() {
		if (root != nullptr)
			root->Evaluate();
	}

	~iBehaviorTree() {
		delete(root);
	}

protected:
	// builds the behavior tree 
	virtual iNode* SetupTree() = 0;
	void AssignRootNode() {
		root = SetupTree();
	}
private:
	iNode* root;
};