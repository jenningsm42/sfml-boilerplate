#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>

#include "InputHandler.hpp"

class Game;

class Scene {
    public:
        virtual void initialize(Game&) = 0;
        virtual void update(Game&, float deltaTime) noexcept = 0;
        virtual void draw(sf::RenderWindow&) noexcept = 0;
};

#endif
