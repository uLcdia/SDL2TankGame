#ifndef TANK_PARSER_H
#define TANK_PARSER_H

#include "../properties/tank_property.h"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <unordered_map>

class TankParser {
public:
    TankParser(const std::string& filename);
    bool parse();

    const TankProperty& getPlayerTank() const { return m_playerTank; };
    const std::vector<TankProperty>& getEnemyTanks() const { return m_enemyTanks; };

private:
    std::string m_filename;

    TankProperty m_playerTank;
    std::vector<TankProperty> m_enemyTanks;

    void parseJson(const nlohmann::json& j);

    TankProperty parseTank(const nlohmann::json& j);
};

#endif // TANK_PARSER_H