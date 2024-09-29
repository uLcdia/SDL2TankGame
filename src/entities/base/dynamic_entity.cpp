#include "dynamic_entity.h"

DynamicEntity::DynamicEntity(double x, double y, double angle, std::shared_ptr<TextureInfo> textureInfo, double scale)
    : Entity(x, y, std::move(textureInfo)),
      m_vx(0), m_vy(0),
      m_rotationSpeed(0),
      m_angle(angle),
      m_scale(scale) 
{}

void DynamicEntity::update(double deltaTime) {
    m_x += m_vx * deltaTime;
    m_y += m_vy * deltaTime;
    m_angle = std::fmod(m_angle + m_rotationSpeed * deltaTime, 360.0);
}

void DynamicEntity::render(SDL_Renderer* renderer) const {
    SDL_Rect destRect = getRect();
    SDL_RenderCopyEx(renderer, m_textureInfo->texture, nullptr, &destRect, m_angle, nullptr, SDL_FLIP_NONE);
}

SDL_Rect DynamicEntity::getRect() const {
    return {
        static_cast<int>(m_x - getScaledWidth() / 2),
        static_cast<int>(m_y - getScaledHeight() / 2),
        getScaledWidth(),
        getScaledHeight()
    };
}

std::array<SDL_Point, 4> DynamicEntity::getVertices() const {
    std::array<SDL_Point, 4> vertices;
    SDL_Rect rect = getRect();
    double angle = getAngle() * M_PI / 180.0; // Convert angle to radians

    // Calculate the center of the rectangle
    double centerX = rect.x + rect.w / 2.0;
    double centerY = rect.y + rect.h / 2.0;

    // Calculate the rotated positions of the vertices
    auto rotatePoint = [centerX, centerY, angle](double x, double y) {
        double dx = x - centerX;
        double dy = y - centerY;
        double rotatedX = centerX + (dx * std::cos(angle) - dy * std::sin(angle));
        double rotatedY = centerY + (dx * std::sin(angle) + dy * std::cos(angle));
        return SDL_Point{static_cast<int>(rotatedX), static_cast<int>(rotatedY)};
    };

    vertices[0] = rotatePoint(rect.x, rect.y);
    vertices[1] = rotatePoint(rect.x + rect.w, rect.y);
    vertices[2] = rotatePoint(rect.x + rect.w, rect.y + rect.h);
    vertices[3] = rotatePoint(rect.x, rect.y + rect.h);

    return vertices;
}

bool DynamicEntity::checkSATCollision(const Entity& other) const {
    auto vertices1 = getVertices();
    auto vertices2 = other.getVertices();

    // Get the axes, in the form of vectors
    auto getAxes = [](const std::array<SDL_Point, 4>& vertices) {
        std::array<SDL_Point, 4> axes;
        for (std::size_t i = 0; i < vertices.size(); ++i) {
            SDL_Point p1 = vertices[i];
            SDL_Point p2 = vertices[(i + 1) % vertices.size()];
            SDL_Point edge = {p2.x - p1.x, p2.y - p1.y};
            axes[i] = {-edge.y, edge.x}; // Perpendicular vector
        }
        return axes;
    };

    // Get the projection interval of the vertices on the axis
    /*
     min -> |____________ <- vertex 1
            |           /\
            |          /  \
            |         /    \
            |        /      \
            |       /        \
            |      /          \
            |_____/____________\ <- vertex 2
            |    /             /
            |   /             /
            |__/ <- vertex 3 /
            |  \            /
            |   \          /
            |    \        /
            |     \      /
            |      \    /
            |       \  /
     max -> |________\/ <- vertex 4
            |
            ^ axis
    */
    auto project = [](const std::array<SDL_Point, 4>& vertices, const SDL_Point& axis) {
        double min = (vertices[0].x * axis.x + vertices[0].y * axis.y);
        double max = min;
        // Calculate the projection of the 4 vertices on 1 axis
        for (const auto& vertex : vertices) {
            double projection = (vertex.x * axis.x + vertex.y * axis.y);
            if (projection < min) min = projection;
            if (projection > max) max = projection;
        }
        return std::make_pair(min, max);
    };

    // Check if the two intervals overlap
    /* 
    Example of an overlapping situation:
        ------------------------------------
        ^ proj1.first         proj1.second ^
                  ------------------------------------
                  ^ proj2.first         proj2.second ^
     */
    auto overlap = [](const std::pair<double, double>& proj1, const std::pair<double, double>& proj2) {
        return proj1.second > proj2.first && proj2.second > proj1.first;
    };

    auto axes1 = getAxes(vertices1);
    auto axes2 = getAxes(vertices2);

    for (const auto& axis : axes1) {
        auto proj1 = project(vertices1, axis);
        auto proj2 = project(vertices2, axis);
        if (!overlap(proj1, proj2)) return false;
    }

    for (const auto& axis : axes2) {
        auto proj1 = project(vertices1, axis);
        auto proj2 = project(vertices2, axis);
        if (!overlap(proj1, proj2)) return false;
    }

    return true;
}

bool DynamicEntity::collidesWith(const Entity& other) const {
    return checkSATCollision(other);
}

bool DynamicEntity::collidesWith(const DynamicEntity& other) const {
    return checkSATCollision(other);
}