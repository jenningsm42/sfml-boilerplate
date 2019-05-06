#include "GameScene.hpp"
#include "Game.hpp"
#include "Player.hpp"

void GameScene::initialize(Game& game) {
    auto& gui = game.getGui();

    auto label = tgui::Label::create("Game Scene");
    label->setPosition(10, 10);
    label->setTextSize(24);
    gui.add(label);

    auto player = std::make_shared<Player>();
    player->load(game);
    m_gameObjects.addObject("player", player);
}
