#include "GameObjectCollection.hpp"

std::weak_ptr<GameObject> GameObjectCollection::getObject(const std::string& name) const noexcept {
    if (m_gameObjectMap.find(name) != m_gameObjectMap.end()) {
        return m_gameObjectMap.at(name);
    }

    return std::weak_ptr<GameObject>();
}

void GameObjectCollection::addObject(const std::string& name, std::shared_ptr<GameObject> object, int zIndex) {
    m_gameObjectMap.emplace(name, object);
    m_gameObjectDrawOrder[zIndex].push_back(object);
}

GameObjectCollection::iterator GameObjectCollection::begin() const {
    auto drawOrderIt = m_gameObjectDrawOrder.begin();
    return iterator(drawOrderIt, m_gameObjectDrawOrder.end(), drawOrderIt->second.begin());
}

GameObjectCollection::iterator GameObjectCollection::end() const {
    auto drawOrderIt = m_gameObjectDrawOrder.end();
    return iterator(drawOrderIt, m_gameObjectDrawOrder.end(), drawOrderIt->second.end());
}

GameObjectCollection::iterator::iterator(
    GameObjectDrawOrder::const_iterator drawOrderIt,
    GameObjectDrawOrder::const_iterator drawOrderEnd,
    GameObjectList::const_iterator objectIt)
    : m_drawOrderIt(drawOrderIt), m_drawOrderEnd(drawOrderEnd), m_objectIt(objectIt) {
}

GameObjectCollection::iterator GameObjectCollection::iterator::operator++() {
    if (++m_objectIt == m_drawOrderIt->second.end()) {
        if (++m_drawOrderIt == m_drawOrderEnd) {
            m_objectIt = m_drawOrderIt->second.end();
        }
    }
    return *this;
}

bool GameObjectCollection::iterator::operator != (const GameObjectCollection::iterator& other) const {
    return m_drawOrderIt != other.m_drawOrderIt || m_objectIt != other.m_objectIt;
}

const std::shared_ptr<GameObject>& GameObjectCollection::iterator::operator*() const {
    return *m_objectIt;
}
