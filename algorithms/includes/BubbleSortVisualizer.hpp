#pragma once
#include "../../core/visualizer/AlgorithmVisualizer.hpp"
#include <vector>

class BubbleSortVisualizer : public AlgorithmVisualizer {
private:
    size_t outerIndex = 0;      // idx -> outerIndex (more descriptive)
    size_t innerIndex = 0;      // jdx -> innerIndex
    float delayTimer = 0.0f;

    // Animation state
    bool isComparing = false;
    bool isSwapping = false;

public:
    // Core virtual methods
    void handleInput(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;
    void reset() override;

    // Data management
    void SetRandomData(size_t length, int min, int max) override;
    void SetData(const std::vector<int>& userData) override;

    // Information methods
    VisualizationInfo getVisualizationInfo() const override;
    std::string getAlgorithmName() const override { return "Bubble Sort"; }
    void setSpeed(float speedMultiplier) override;
    void pause() override;
    void resume() override;
    void step() override;

    // State queries
    const std::vector<int>& getCurrentData() const override { return data; }
    bool isComplete() const override { return currentState == AlgorithmState::Completed; }
    bool isPaused() const override { return currentState == AlgorithmState::Paused; }

private:
    void performOneStep();
    void updateHighlighting();
    float getCurrentDelay() const { return baseDelay / speedMultiplier; }
};
