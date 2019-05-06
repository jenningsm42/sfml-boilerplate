#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>

#include "GameObjectCollection.hpp"

class Game;

class Scene {
public:
    virtual void initialize(Game&) = 0;

    void update(Game&, float deltaTime) noexcept;

    void draw(sf::RenderWindow&) noexcept;

protected:
    GameObjectCollection m_gameObjects;
};

#endif // SCENE_H
