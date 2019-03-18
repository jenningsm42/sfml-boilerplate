#ifndef GAMEOBJECTCOLLECTION_H
#define GAMEOBJECTCOLLECTION_H

#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class GameObject;

using GameObjectMap = std::unordered_map<std::string, std::shared_ptr<GameObject>>;
using GameObjectList = std::vector<std::shared_ptr<GameObject>>;
using GameObjectDrawOrder = std::map<int, GameObjectList>;

class GameObjectCollection {
public:
    class iterator {
    public:
        iterator(
            GameObjectDrawOrder::const_iterator drawOrderIt,
            GameObjectDrawOrder::const_iterator drawOrderEnd,
            GameObjectList::const_iterator objectIt);

        iterator operator++();

        bool operator != (const iterator& other) const;

        const std::shared_ptr<GameObject>& operator* () const;

    private:
        GameObjectDrawOrder::const_iterator m_drawOrderIt;
        GameObjectDrawOrder::const_iterator m_drawOrderEnd;
        GameObjectList::const_iterator m_objectIt;
    };

    void addObject(const std::string& name, std::shared_ptr<GameObject>, int zIndex = 0);

    std::weak_ptr<GameObject> getObject(const std::string& name) const noexcept;

    iterator begin() const;
    iterator end() const;

private:
    GameObjectMap m_gameObjectMap;
    GameObjectDrawOrder m_gameObjectDrawOrder;
};


#endif // GAMEOBJECTCOLLECTION_H