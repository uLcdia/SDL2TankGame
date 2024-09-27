#ifndef TURRET_H
#define TURRET_H

#include "../tank_movements.h"
#include "../../base/dynamic_entity.h"
#include "../../../properties/tank_property.h"
#include "../cartridge/cartridge.h"
#include <SDL.h>
#include <vector>

class Turret : public DynamicEntity {
public:
    Turret(const TankProperty& tankProperty, double x, double y, std::shared_ptr<TextureInfo> texture);
    
    void update(double deltaTime) override;
    void render(SDL_Renderer* renderer) const override;

    void rotate(TankMovements::Rotation rotation, double deltaTime, double rotationSpeed);

    void fire(const Cartridge::FireCallback& fireCallback, std::string shooter);

    void addCartridge(const Cartridge& cartridge);
    void cycleCartridge();
    const Cartridge* getCurrentCartridge() const;

private:
    std::vector<Cartridge> m_cartridges;
    std::size_t m_currentCartridgeIndex;

    static constexpr double PROJECTILE_SPAWN_DISTANCE = 65.0; // distance from the turret's pivot point to the spawn point of the projectile
};

#endif // TURRET_H