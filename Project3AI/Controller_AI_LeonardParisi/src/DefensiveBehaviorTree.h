#pragma once
#include "iBehaviorTree.h"
#include "ElixirConditionNode.h"
#include "SequenceNode.h"
#include "SelectorNode.h"
#include "EnemiesExistConditionNode.h"
#include "RandomWeightedSelectorNode.h"
#include "EmptyNode.h"
#include "DeployReinforcementMobNode.h"


static const Vec2 ksGiantPosLeft(LEFT_BRIDGE_CENTER_X, RIVER_TOP_Y - 0.5f);
static const Vec2 ksArcherPosLeft(LEFT_BRIDGE_CENTER_X, 0.f);
static const Vec2 ksGiantPosRight(RIGHT_BRIDGE_CENTER_X, RIVER_TOP_Y - 0.5f);
static const Vec2 ksArcherPosRight(RIGHT_BRIDGE_CENTER_X, 0.f);

class DefensiveBehaviorTree : public iBehaviorTree {
public:
	DefensiveBehaviorTree(iPlayer* player) : player(player) {
		AssignRootNode();
	}

protected:
	// builds a behavior tree that models Kevin Dill's AI.
	// this was to ensure my behavior tree structure works.
	virtual iNode* SetupTree() {
		SequenceNode* defensiveSequence = new SequenceNode({
			new EnemiesExistConditionNode(player),
			new DeployReinforcementMobNode(player)
		});

		RandomWeightedSelectorNode* offensiveSequence = new RandomWeightedSelectorNode({
			// Do nothing 98% of the time
			new EmptyNode(), 
			// Deploy giant and two archers on the left 1% of the time
			new SequenceNode({
				new ElixirConditionNode(10.0f, Operand::GreaterThanOrEqualTo, player),
				new DeployMobNode(player, ksGiantPosLeft, iEntityStats::Giant),
				new DeployMobNode(player, ksArcherPosLeft, iEntityStats::Archer),
				new DeployMobNode(player, ksArcherPosLeft, iEntityStats::Archer)
			}),
			// Deploy giant and two archers on the right 1% of the time
			new SequenceNode({
				new ElixirConditionNode(10.0f, Operand::GreaterThanOrEqualTo, player),
				new DeployMobNode(player, ksGiantPosRight, iEntityStats::Giant),
				new DeployMobNode(player, ksArcherPosRight, iEntityStats::Archer),
				new DeployMobNode(player, ksArcherPosRight, iEntityStats::Archer)
			})
		}, { 998, 1, 1 });
		
		return new SelectorNode({ 
			defensiveSequence,
			offensiveSequence
		});
	}
private:
	iPlayer* player;
};
