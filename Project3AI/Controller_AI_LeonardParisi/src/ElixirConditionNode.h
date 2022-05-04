#pragma once
#include "NumericConditionNode.h"
#include <iPlayer.h>

class ElixirConditionNode : public NumericConditionNode {
public:
	ElixirConditionNode(float threshold, Operand operand, iPlayer* player):NumericConditionNode(threshold, operand), player(player) { }

	virtual NodeState Evaluate() {
		if (Compare(player->getElixir())) {
			return NodeState::Success;
		}
		return NodeState::Failure;
	}
private:
	iPlayer* player;
};
