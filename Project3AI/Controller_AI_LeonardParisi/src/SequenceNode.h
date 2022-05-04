#pragma once
#include "iNode.h"

class SequenceNode : public iNode { 
public:
	SequenceNode(std::vector<iNode*> children) : iNode(children) { }

	virtual NodeState Evaluate() {
		for (auto node = children.begin(); node < children.end(); node++) {
			switch ((*node)->Evaluate()) {
			case Failure:
				return Failure;
			case Running:
				return Running;
			case Success:
			default:
				continue;
			}
		}

		return Success;
	}
};