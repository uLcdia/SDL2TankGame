#ifndef PROJECTILE_PARSER_H
#define PROJECTILE_PARSER_H

#include "../properties/projectile_property.h"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

class ProjectileParser {
public:
    ProjectileParser(const std::string& filename);
    bool parse();

    const std::vector<ProjectileProperty>& getProjectiles() const { return m_projectiles; };

private:
    std::string m_filename;

    std::vector<ProjectileProperty> m_projectiles;

    void parseJson(const nlohmann::json& j);

    ProjectileProperty parseProjectile(const nlohmann::json& j);
};

#endif // PROJECTILE_PARSER_H