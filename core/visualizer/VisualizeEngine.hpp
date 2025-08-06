#pragma once
#include "AlgorithmVisualizer.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>

class VisualizeEngine {
private:
    std::unique_ptr<AlgorithmVisualizer> currentVisualizer = nullptr;
    float globalSpeedMultiplier = 1.0f;

public:
    // Core functionality
    void handleInput(const sf::Event& event);
    void update(float dt);
    void reset();
    void render(sf::RenderTarget& target) const;

    // Visualizer management
    void set_visualizer(std::unique_ptr<AlgorithmVisualizer> newVisualizer);

    // Data management
    void SetRandomData(size_t length, int min, int max);
    void SetData(const std::vector<int>& userData);

    // New control methods
    void setSpeed(float speedMultiplier);
    void pause();
    void resume();
    void step(); // Execute one step

    // Information retrieval
    VisualizationInfo getVisualizationInfo() const;
    std::string getCurrentAlgorithmName() const;
    bool hasVisualizer() const { return currentVisualizer != nullptr; }
    bool isComplete() const;
    bool isPaused() const;

    // Get current data state (for external analysis or debugging)
    const std::vector<int>& getCurrentData() const;
};
