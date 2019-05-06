#include "GameObject.hpp"
#include "Scene.hpp"

void Scene::update(Game& game, float deltaTime) noexcept {
    for (auto& object : m_gameObjects) {
        object->update(game, m_gameObjects, deltaTime);
    }
}

void Scene::draw(sf::RenderWindow& window) noexcept {
    for (auto& object : m_gameObjects) {
        window.draw(*object);
    }
}