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
}

void GameScene::update(Game&, float) noexcept {
}

void GameScene::draw(sf::RenderWindow& window) noexcept {
    window.draw(m_text);
}
