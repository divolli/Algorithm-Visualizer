#include "VisualizeEngine.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

void VisualizeEngine::handleInput(const sf::Event& event) {
    if (!currentVisualizer) return;

    // Handle global controls first
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Space:
                if (isPaused()) {
                    resume();
                } else {
                    pause();
                }
                return; // Don't pass to visualizer

            case sf::Keyboard::Right:
                if (isPaused()) {
                    step(); // Single step when paused
                }
                return;

            case sf::Keyboard::Up:
                setSpeed(std::min(5.0f, globalSpeedMultiplier + 0.1f));
                return;

            case sf::Keyboard::Down:
                setSpeed(std::max(0.1f, globalSpeedMultiplier - 0.1f));
                return;
        }
    }

    // Pass event to current visualizer for algorithm-specific handling
    currentVisualizer->handleInput(event);
}

void VisualizeEngine::update(float dt) {
    if (currentVisualizer) {
        currentVisualizer->update(dt);
    }
}

void VisualizeEngine::reset() {
    if (currentVisualizer) {
        currentVisualizer->reset();
        std::cout << "[Engine] Algorithm reset.\n";
    }
}

void VisualizeEngine::render(sf::RenderTarget& target) const {
    if (currentVisualizer) {
        // Reserve space for UI overlay (top 130px)
        currentVisualizer->render(target);
    }
}

void VisualizeEngine::set_visualizer(std::unique_ptr<AlgorithmVisualizer> newVisualizer) {
    if (newVisualizer) {
        std::cout << "[Engine] Switching to: " << newVisualizer->getAlgorithmName() << "\n";
        currentVisualizer = std::move(newVisualizer);
        currentVisualizer->setSpeed(globalSpeedMultiplier);
    } else {
        std::cout << "[Engine] Warning: Attempted to set null visualizer.\n";
    }
}

void VisualizeEngine::SetRandomData(size_t length, int min, int max) {
    if (currentVisualizer) {
        currentVisualizer->SetRandomData(length, min, max);
        std::cout << "[Engine] Set random data: " << length << " elements [" << min << ", " << max << "]\n";
    }
}

void VisualizeEngine::SetData(const std::vector<int>& userData) {
    if (currentVisualizer) {
        currentVisualizer->SetData(userData);
        std::cout << "[Engine] Set custom data with " << userData.size() << " elements.\n";
    }
}

void VisualizeEngine::setSpeed(float speedMultiplier) {
    globalSpeedMultiplier = std::clamp(speedMultiplier, 0.1f, 5.0f);
    if (currentVisualizer) {
        currentVisualizer->setSpeed(globalSpeedMultiplier);
    }
    std::cout << "[Engine] Speed set to: " << globalSpeedMultiplier << "x\n";
}

void VisualizeEngine::pause() {
    if (currentVisualizer) {
        currentVisualizer->pause();
        std::cout << "[Engine] Algorithm paused.\n";
    }
}

void VisualizeEngine::resume() {
    if (currentVisualizer) {
        currentVisualizer->resume();
        std::cout << "[Engine] Algorithm resumed.\n";
    }
}

void VisualizeEngine::step() {
    if (currentVisualizer) {
        currentVisualizer->step();
    }
}

VisualizationInfo VisualizeEngine::getVisualizationInfo() const {
    if (currentVisualizer) {
        return currentVisualizer->getVisualizationInfo();
    }
    return {}; // Return default VisualizationInfo
}

std::string VisualizeEngine::getCurrentAlgorithmName() const {
    if (currentVisualizer) {
        return currentVisualizer->getAlgorithmName();
    }
    return "No Algorithm";
}

bool VisualizeEngine::isComplete() const {
    return currentVisualizer ? currentVisualizer->isComplete() : false;
}

bool VisualizeEngine::isPaused() const {
    return currentVisualizer ? currentVisualizer->isPaused() : false;
}

const std::vector<int>& VisualizeEngine::getCurrentData() const {
    if (currentVisualizer) {
        return currentVisualizer->getCurrentData();
    }
    static const std::vector<int> empty;
    return empty;
}
