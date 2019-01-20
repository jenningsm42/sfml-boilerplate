#include "GameScene.hpp"
#include "Game.hpp"

void GameScene::initialize(Game& game) {
    auto& cache = game.getAssetCache();
    auto& gui = game.getGui();

    auto font = cache.getFont("open_sans.ttf");
    m_text.setFont(*font);
    m_text.setString("Game scene");

    auto button = tgui::Button::create("Test Button");
    button->setPosition(100, 100);
    gui.add(button);

    auto adventurerTexture = cache.getTexture("bandit.png");
    m_sprite.setTexture(*adventurerTexture);
    m_sprite.setGridSize(8, 7);
    m_sprite.setScale(2.f, 2.f);

    m_sprite.setPosition(200, 200);

    m_sprite.addAnimation("idle", 0, 0, 4, 0.5f);
    m_sprite.addAnimation("run", 0, 1, 8, 0.18f);

    m_sprite.play("idle");
}

void GameScene::update(Game&, float deltaTime) noexcept {
    m_sprite.update(deltaTime);
}

void GameScene::draw(sf::RenderWindow& window) noexcept {
    window.draw(m_sprite);
    window.draw(m_text);
}
