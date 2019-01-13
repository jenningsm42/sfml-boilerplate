#include "Game.hpp"
#include "GameScene.hpp"
#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>

Game::Game() : m_assetCache("./data"), m_window(sf::VideoMode(800, 600), "GGJ 2019")
{
}

Game::~Game() {
}

void Game::run() {
    sf::Clock clock;

    // Set the first scene
    m_sceneHandler.setScene(std::make_unique<GameScene>());

    // Game loop
    while (m_window.isOpen()) {
        // Update user input
        sf::Event event;
        m_inputHandler.update();
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
            m_inputHandler.processEvent(event);
        }

        // Record time elapsed between frames for updates
        sf::Time elapsed = clock.restart();

        // Game tick - the update call
        update(elapsed.asSeconds());

        // Draw everything
        m_window.clear();
        m_sceneHandler.draw(m_window);
        // tgui.draw(m_window);
        m_sceneHandler.drawFade(m_window);
        m_window.display();
    }
}

AssetCache& Game::getAssetCache() noexcept {
    return m_assetCache;
}

SceneHandler& Game::getSceneHandler() noexcept {
    return m_sceneHandler;
}

sf::RenderWindow& Game::getRenderWindow() noexcept {
    return m_window;
}

void Game::update(float deltaTime) {
    try {
        m_sceneHandler.update(*this, deltaTime);
    } catch (const std::exception& ex) {
        writeCrashReport(ex);
        throw; // Crash the program
    }
}

void Game::writeCrashReport(const std::exception& ex) {
    // Get current time as a string
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    auto timeString = std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");

    // Write exception to file
    std::ofstream errorFile;
    errorFile.open("crash_report.txt", std::ofstream::out | std::ofstream::app);
    errorFile << "Game crash at " << timeString << std::endl;
    errorFile << ex.what() << std::endl;
    errorFile.close();
}
