#pragma once
#include "iNode.h"
#include <iPlayer.h>
#include <Constants.h>

class DeployMobNode : public iNode {
public:
    DeployMobNode(iPlayer* player, Vec2 position, iEntityStats::MobType mob) : player(player), position(position.Player2Game(player->isNorth())), mob(mob) {}

    virtual NodeState Evaluate() {
        switch (player->placeMob(mob, position)) {
            case iPlayer::PlacementResult::Success:
                return Success;
            default:
                return Failure;
        };
    }
private:
    iPlayer* player;
    Vec2 position;
    iEntityStats::MobType mob;
};