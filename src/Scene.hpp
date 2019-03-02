#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>

#include "GameObject.hpp"

class Game;

class Scene {
public:
    virtual void initialize(Game&) = 0;

    void update(Game&, float deltaTime) noexcept;

    void draw(sf::RenderWindow&) noexcept;

    std::weak_ptr<GameObject> getObject(const std::string& name) noexcept;

protected:
    GameObjectCollection m_objects;

    void addObject(const std::string& name, std::shared_ptr<GameObject>, int zIndex = 0);

private:
    std::map<int, std::shared_ptr<GameObject>> m_objectsDrawOrder;
};

#endif // SCENE_H
