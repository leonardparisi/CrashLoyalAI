#pragma once
#include "iNode.h"

class SelectorNode : public iNode {
public:
	SelectorNode(std::vector<iNode*> children) : iNode(children) { }

	virtual NodeState Evaluate() {
		for (auto node = children.begin(); node < children.end(); node++) {
			switch ((*node)->Evaluate()) {
			case Success:
				return Success;
			case Running:
				return Running;
			case Failure:
			default:
				continue;
			}
		}

		return Success;
	}
};