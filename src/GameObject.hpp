#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <memory>
#include <unordered_map>

#include <SFML/Graphics/Drawable.hpp>

class Game;
class GameObjectCollection;

class GameObject : public sf::Drawable {
public:
    virtual void update(Game&, GameObjectCollection&, float deltaTime) noexcept = 0;

private:
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;
};

#endif // GAMEOBJECT_H