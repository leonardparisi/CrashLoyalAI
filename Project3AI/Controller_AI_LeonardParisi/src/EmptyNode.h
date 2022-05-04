#pragma once
#include "iNode.h"

class EmptyNode : public iNode {
public:
	EmptyNode() : iNode() { }

	virtual NodeState Evaluate() {
		return Success;
	}
};