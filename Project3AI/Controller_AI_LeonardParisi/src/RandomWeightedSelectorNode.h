#pragma once
#include "iNode.h"
#include <numeric>
#include <stdexcept>

// a node that randomly selects one of its children
class RandomWeightedSelectorNode : public iNode {
public:
	// the total of the weights should add up to 100
	// and the values reprecent a percent chance of the node getting evaluated
	RandomWeightedSelectorNode(std::vector<iNode*> children, std::vector<int> weights) : 
		iNode(children), 
		weights(weights), 
		sumOfWeights( 
			std::accumulate(weights.begin(), weights.end(), 0, [](int num1, int num2) {return num1 + num2; })
		) {
		if (weights.size() != children.size()) {
			throw std::invalid_argument("The number of weights should equal the number of child nodes.");
		}
	}

	// tries to evaluate a random child
	virtual NodeState Evaluate() {

		// pick random number
		int randomChoice = std::rand() % sumOfWeights;

		// go through all of the choices
		for (unsigned int i = 0; i < children.size(); ++i) {
			int weight = weights[i];
			// if the choice is less than the weight, it means we are ready to make a choiec
			// and evaluate the node
			if (randomChoice < weight) {
				return children[i]->Evaluate();
			}
			// otherwise subtract the weight from the randomChoice number and keep going
			randomChoice -= weight;
		}

		// it should never reach this point
		return Failure;
	}
private:
	std::vector<int> weights;
	int sumOfWeights;
};