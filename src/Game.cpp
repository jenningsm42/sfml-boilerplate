#include "Game.hpp"
#include "GameScene.hpp"
#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>

Game::Game() : m_assetCache("./data"), m_window(sf::VideoMode(800, 600), "GGJ 2019") {
    m_gui.setTarget(m_window);
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
            else if (event.type == sf::Event::Resized) {
                // Update the view to the new size of the window
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                m_window.setView(sf::View(visibleArea));
                m_gui.setView(sf::View(visibleArea));
            }

            m_inputHandler.processEvent(event);
            m_gui.handleEvent(event);
        }

        // Record time elapsed between frames for updates
        sf::Time elapsed = clock.restart();

        // Game tick - the update call
        update(elapsed.asSeconds());

        // Draw everything
        m_window.clear();

        // Everything in the scene
        m_sceneHandler.draw(m_window);

        // Foreground objects - the GUI and screen overlay
        m_gui.draw();
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

InputHandler& Game::getInputHandler() noexcept {
    return m_inputHandler;
}

sf::RenderWindow& Game::getRenderWindow() noexcept {
    return m_window;
}

tgui::Gui& Game::getGui() noexcept {
    return m_gui;
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
