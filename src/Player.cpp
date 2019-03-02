#include "Game.hpp"
#include "Player.hpp"

Player::Player() : m_x(200.f), m_y(200.f) {}

void Player::load(Game& game) {
    auto& cache = game.getAssetCache();

    auto texture = cache.getTexture("bandit.png");
    m_sprite.setTexture(*texture);
    m_sprite.setGridSize(8, 7);

    auto spriteBounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(spriteBounds.width / 2.f, spriteBounds.height / 2.f);
    m_sprite.setScale(2.f, 2.f);

    m_sprite.setPosition(m_x, m_y);

    m_sprite.addAnimation("idle", 0, 0, 4, 0.5f);
    m_sprite.addAnimation("run", 0, 1, 8, 0.15f);

    m_sprite.play("idle");
}

void Player::update(Game& game, const GameObjectCollection&, float deltaTime) noexcept {
    auto& input = game.getInputHandler();

    const bool movingLeft = input.getKeyDown(sf::Keyboard::Left);
    const bool movingRight = input.getKeyDown(sf::Keyboard::Right);

    if (movingLeft && !movingRight) {
        m_sprite.move(-m_speed * deltaTime, 0.f);
        m_sprite.play("run");
        m_sprite.setScale(2.f, 2.f);
    }
    else if (movingRight && !movingLeft) {
        m_sprite.move(m_speed * deltaTime, 0.f);
        m_sprite.play("run");
        m_sprite.setScale(-2.f, 2.f);
    }
    else {
        m_sprite.play("idle");
    }

    m_sprite.update(deltaTime);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}