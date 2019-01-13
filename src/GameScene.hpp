#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <memory>
#include "Scene.hpp"

class GameScene : public Scene {
    public:
        void initialize(Game&) override;
        void update(Game&, float deltaTime) noexcept override;
        void draw(sf::RenderWindow&) noexcept override;

    private:
        sf::Text m_text;
};

#endif // GAMESCENE_H
