#include "SceneHandler.hpp"
#include "Game.hpp"

SceneHandler::SceneHandler()
    : m_currentScene(nullptr), m_nextScene(nullptr), m_fading(false), m_alpha(0.f) {
}

SceneHandler::~SceneHandler() {
}

void SceneHandler::setScene(std::unique_ptr<Scene> scene, bool fade) noexcept {
    m_nextScene = std::move(scene);
    m_fading = fade;

    if (fade && !m_currentScene) {
        // This is the first scene, so start with full black overlay if fading
        m_alpha = 1.f;
    }
}

void SceneHandler::update(Game& game, float deltaTime) {
    // Handle fading in between switching scenes
    if (m_fading) {
        if (m_nextScene && m_alpha < 1.f) {
            // Haven't yet switched to next scene
            m_alpha += m_fadeRate * deltaTime;
        }
        else if (m_nextScene && m_alpha >= 0.99f) {
            // Finished fading to black, switch scene here
            m_alpha = 1.f;

            switchScenes(game);
        }
        else if (!m_nextScene && m_alpha > 0.f) {
            // Fading back to scene
            m_alpha -= m_fadeRate * deltaTime;
        }
        else if (!m_nextScene && m_alpha < 0.001f) {
            // Finished fading
            m_alpha = 0.f;
            m_fading = false;
        }

        m_fadeBox.setSize(static_cast<sf::Vector2f>(game.getRenderWindow().getSize()));
        m_fadeBox.setFillColor(sf::Color(0, 0, 0, m_alpha * 255));
    }

    // Handle switching scenes without fading
    if (m_nextScene) {
        switchScenes(game);
    }

    // Render the current scene
    if (m_currentScene) {
        m_currentScene->update(game, deltaTime);
    }
}

void SceneHandler::draw(sf::RenderWindow& window) noexcept {
    if (m_currentScene) {
        m_currentScene->draw(window);
    }
}

void SceneHandler::drawFade(sf::RenderWindow& window) noexcept {
    if (m_fading) {
        window.draw(m_fadeBox);
    }
}

void SceneHandler::switchScenes(Game& game) {
    game.getGui().removeAllWidgets();
    m_currentScene = std::move(m_nextScene);
    m_nextScene = nullptr;

    // Let exceptions from here propogate to Game.run to generate a crash report
    m_currentScene->initialize(game);
}
