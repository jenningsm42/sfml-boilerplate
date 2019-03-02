#include "Scene.hpp"

void Scene::update(Game& game, float deltaTime) noexcept {
    for (auto& object : m_objects) {
        object.second->update(game, m_objects, deltaTime);
    }
}

void Scene::draw(sf::RenderWindow& window) noexcept {
    for (auto& object : m_objectsDrawOrder) {
        window.draw(*object.second);
    }
}

std::weak_ptr<GameObject> Scene::getObject(const std::string& name) noexcept {
    if (m_objects.find(name) != m_objects.end()) {
        return m_objects[name];
    }

    return std::weak_ptr<GameObject>();
}

void Scene::addObject(const std::string& name, std::shared_ptr<GameObject> object, int zIndex) {
    m_objects.emplace(name, object);
    m_objectsDrawOrder.emplace(zIndex, object);
}