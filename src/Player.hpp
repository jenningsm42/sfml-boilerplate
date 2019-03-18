#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.hpp"
#include "AnimatedSprite.hpp"

class Game;

class Player : public GameObject {
public:
    Player();

    void load(Game&);

    void update(Game&, GameObjectCollection&, float deltaTime) noexcept override;

private:
    const float m_speed = 200.f;
    float m_x, m_y;
    AnimatedSprite m_sprite;

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;
};


#endif // PLAYER_H