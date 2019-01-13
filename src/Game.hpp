#ifndef GAME_H
#define GAME_H
#include <memory>

#include <SFML/Graphics.hpp>

#include "AssetCache.hpp"
#include "InputHandler.hpp"
#include "SceneHandler.hpp"
#include "Scene.hpp"

class Game {
    public:
        Game();
        Game(const Game&) = delete;
        ~Game();

        void run();

        AssetCache& getAssetCache() noexcept;
        SceneHandler& getSceneHandler() noexcept;
        sf::RenderWindow& getRenderWindow() noexcept;

    private:
        AssetCache m_assetCache;
        InputHandler m_inputHandler;
        SceneHandler m_sceneHandler;
        sf::RenderWindow m_window;

        void update(float deltaTime);
        void draw();
        void writeCrashReport(const std::exception&);
};

#endif // GAME_H
