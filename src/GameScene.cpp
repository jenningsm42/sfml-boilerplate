#include "GameScene.hpp"
#include "Game.hpp"

void GameScene::initialize(Game& game) {
    auto& cache = game.getAssetCache();
    auto font = cache.getFont("open_sans.ttf");
    m_text.setFont(*font);
    m_text.setString("Game scene");
}

void GameScene::update(Game&, float) noexcept {
}

void GameScene::draw(sf::RenderWindow& window) noexcept {
    window.draw(m_text);
}
