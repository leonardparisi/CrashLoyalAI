#pragma once
#include "iNode.h"

enum Operand {
	LessThan, LessThanOrEqualTo, EqualTo, GreaterThan, GreaterThanOrEqualTo
};

class NumericConditionNode : public iNode {
public:
	NumericConditionNode(float threshold, Operand operand) : threshold(threshold), operand(operand) {}
	virtual NodeState Evaluate() = 0;
protected:
	float threshold;
	Operand operand;

	bool Compare(float input) {
		switch (operand) {
			case LessThan:
				return input < threshold;
			case LessThanOrEqualTo:
				return input <= threshold;
			case GreaterThan:
				return input > threshold;
			case GreaterThanOrEqualTo:
				return input >= threshold;
			case EqualTo:
			default:
				return input = threshold;
		}
	}
};