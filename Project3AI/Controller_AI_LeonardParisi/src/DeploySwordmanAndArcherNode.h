#pragma once
#include "iNode.h"
#include <iPlayer.h>
#include <Constants.h>

static const Vec2 offensiveSwordsmanPos(LEFT_BRIDGE_CENTER_X, RIVER_TOP_Y - 0.5f);
static const Vec2 offensiveArcherPos(LEFT_BRIDGE_CENTER_X, RIVER_TOP_Y - 1.5f);

class DeploySwordmanAndArcherNode : public iNode {
public:

    DeploySwordmanAndArcherNode(iPlayer* player) : player(player) {}

    virtual NodeState Evaluate() {
        // convert the positions from player space to game space
        bool isNorth = player->isNorth();
        Vec2 giantPos_Game = offensiveSwordsmanPos.Player2Game(isNorth);
        Vec2 archerPos_Game = offensiveArcherPos.Player2Game(isNorth);

        // Create an archer and a swordman
        player->placeMob(iEntityStats::Swordsman, giantPos_Game);
        player->placeMob(iEntityStats::Archer, archerPos_Game);

        return Success;
    }
private:
    iPlayer* player;
};