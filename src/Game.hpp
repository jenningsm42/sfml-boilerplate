#ifndef GAME_H
#define GAME_H
#include <memory>

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

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
        InputHandler& getInputHandler() noexcept;
        sf::RenderWindow& getRenderWindow() noexcept;
        tgui::Gui& getGui() noexcept;

    private:
        AssetCache m_assetCache;
        InputHandler m_inputHandler;
        SceneHandler m_sceneHandler;
        sf::RenderWindow m_window;
        tgui::Gui m_gui;

        void update(float deltaTime);
        void draw();
        void writeCrashReport(const std::exception&);
};

#endif // GAME_H
