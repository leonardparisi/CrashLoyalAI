#pragma once
#include "iNode.h"
#include <iPlayer.h>
#include <Constants.h>
#include "DeployMobNode.h"
#include <map>

class DeployReinforcementMobNode : public iNode {
public:
    enum Region {
        Left, Right
    };

    DeployReinforcementMobNode(iPlayer* player) : player(player) { 
        bestMobsToDefend = GetBestMobsToDefend();
    }

    virtual NodeState Evaluate() {
        // create danger map
        std::map<Region, float> dangerMap = CreateDangerMap();

        // and then pick the one that's most dangerous
        float mostDanger = 0;
        Region mostDangerousRegion;

        for (auto it = dangerMap.begin(); it != dangerMap.end(); ++it) {
            if (it->second > mostDanger) {
                mostDanger = it->second;
                mostDangerousRegion = it->first;
            }
        }

        if (mostDanger > 0) {
            return DeployBestMobToDefendRegion(mostDangerousRegion);
        }

        return Failure;
    }

private:
    iPlayer* player;
    std::vector<iEntityStats::MobType> bestMobsToDefend;

    // maps a certain 'danger' factor to each region to determine which region needs reinforcement
    std::map<Region, float> CreateDangerMap() {
        std::map<Region, float> dangerMap = { { Left, 0 }, { Right,0 } };

        for (unsigned int i = 0; i < player->getNumOpponentMobs(); ++i) {
            iPlayer::EntityData mob = player->getOpponentMob(i);
            if (mob.m_Position.x < GAME_GRID_WIDTH / 2) {
                auto dangerValue = dangerMap.find(Left);
                dangerValue->second += mob.m_Stats.getElixirCost();
            }
            else {
                auto dangerValue = dangerMap.find(Right);
                dangerValue->second += mob.m_Stats.getElixirCost();
            }
        }

        for (unsigned int i = 0; i < player->getNumMobs(); ++i) {
            iPlayer::EntityData mob = player->getMob(i);
            if (mob.m_Position.x < GAME_GRID_WIDTH / 2) {
                auto dangerValue = dangerMap.find(Left);
                dangerValue->second -= mob.m_Stats.getElixirCost();
            }
            else {
                auto dangerValue = dangerMap.find(Right);
                dangerValue->second -= mob.m_Stats.getElixirCost();
            }
        }

        return dangerMap;
    }

    // creates an array of mobs that are best for defending
    std::vector<iEntityStats::MobType> GetBestMobsToDefend() {
        std::vector<iEntityStats::MobType> bestMobsToDefend;
        float bestUtilityScore = -1;

        // find best mobs to defend
        for (int mobTypeInt = 0; mobTypeInt < iEntityStats::MobType::numMobTypes; mobTypeInt++) {
            iEntityStats::MobType mobType = static_cast<iEntityStats::MobType>(mobTypeInt);
            const iEntityStats& mobStats = iEntityStats::getStats(mobType);
            float utilityScore = CalculateUtilityScoreForMob(mobStats);

            if (utilityScore > bestUtilityScore) {
                bestUtilityScore = utilityScore;
                bestMobsToDefend.clear();
            }

            if (utilityScore >= bestUtilityScore) {
                bestMobsToDefend.push_back(mobType);
            }
        }
        return bestMobsToDefend;
    }

    // deploys a mob to defend a certain region
    NodeState DeployBestMobToDefendRegion(Region region) {
        iEntityStats::MobType mob = bestMobsToDefend.size() > 0 ? bestMobsToDefend[std::rand() % bestMobsToDefend.size()] : iEntityStats::MobType::InvalidMobType;
        DeployMobNode deployMobNode(player, GetPositionOfReinforcement(region), mob);
        return deployMobNode.Evaluate();
    }

    // gets the position of where to deploy a mob based on the region that needs defending
    Vec2 GetPositionOfReinforcement(Region region) {
        float randomYOffset = (std::rand() % 5) - 2;
        float randomXOffset = (std::rand() % 3) - 1;
        switch (region) {
            case Region::Left:
                return Vec2 { 1.0f + randomXOffset, NorthPrincessY + randomYOffset };
            case Region::Right:
                return Vec2{ GAME_GRID_WIDTH - 1.0f + randomXOffset, NorthPrincessY + randomYOffset };
            default:
                throw std::invalid_argument("A reinforcement position for a given region was undefined.");
        }
    }

    // This function can be edited in the future to allow for better counterplay.
    // For example, if the incoming attack is mainly X units, we might want to assign
    // the units who counter X units a higher utility score.
    float CalculateUtilityScoreForMob(const iEntityStats& mobStats) {
        if (mobStats.getTargetType() == iEntityStats::TargetType::Building) {
            return 0;
        }
        return mobStats.getDamage() / mobStats.getElixirCost();
    }
};