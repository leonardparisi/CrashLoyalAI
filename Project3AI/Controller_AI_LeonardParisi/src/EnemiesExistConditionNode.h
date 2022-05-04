#pragma once
#include "NumericConditionNode.h"
#include <iPlayer.h>

class EnemiesExistConditionNode : public NumericConditionNode {
public:
	EnemiesExistConditionNode(iPlayer* player) :NumericConditionNode(0, Operand::GreaterThan), player(player) { }

	virtual NodeState Evaluate() {
		if (Compare((float) player->getNumOpponentMobs())) {
			return NodeState::Success;
		}
		return NodeState::Failure;
	}
private:
	iPlayer* player;
};
