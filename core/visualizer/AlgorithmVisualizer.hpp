#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include <string>

// Enum for different algorithm states
enum class AlgorithmState {
    Ready,      // Algorithm is ready to start
    Running,    // Algorithm is currently executing
    Paused,     // Algorithm is paused
    Completed,  // Algorithm has finished
    Stopped     // Algorithm was stopped/reset
};

// Structure to hold visualization info that can be passed to UI
struct VisualizationInfo {
    std::string currentOperation = "Ready";
    int comparisons = 0;
    int swaps = 0;
    float progress = 0.0f; // 0.0 to 1.0
    AlgorithmState state = AlgorithmState::Ready;
    std::vector<size_t> highlightedIndices; // Indices to highlight during operations
    std::vector<sf::Color> highlightColors; // Colors for highlighted indices
};

class AlgorithmVisualizer {
public:
    virtual ~AlgorithmVisualizer() = default;

    // Core methods
    virtual void render(sf::RenderTarget& target) const = 0;
    virtual void handleInput(const sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void reset() = 0;

    // Data management
    virtual void SetRandomData(size_t length, int min, int max) = 0;
    virtual void SetData(const std::vector<int>& UserData) = 0;

    // New methods for better integration with UI
    virtual VisualizationInfo getVisualizationInfo() const = 0;
    virtual std::string getAlgorithmName() const = 0;
    virtual void setSpeed(float speedMultiplier) = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void step() = 0; // Execute one step manually

    // Optional: Get current data state (useful for debugging or external analysis)
    virtual const std::vector<int>& getCurrentData() const = 0;
    virtual bool isComplete() const = 0;
    virtual bool isPaused() const = 0;

protected:
    // Common properties that derived classes can use
    std::vector<int> data;
    AlgorithmState currentState = AlgorithmState::Ready;
    float baseDelay = 0.5f; // Base delay between steps
    float speedMultiplier = 1.0f;
    int totalComparisons = 0;
    int totalSwaps = 0;
    VisualizationInfo visualInfo;

    // Helper method for consistent bar rendering
    void renderBars(sf::RenderTarget& target, float yOffset = 0.0f) const {
        if (data.empty()) return;

        sf::Vector2u size = target.getSize();
        float width = static_cast<float>(size.x);
        float height = static_cast<float>(size.y) - yOffset; // Account for UI overlay

        float barWidth = width / static_cast<float>(data.size());

        // Find min and max for proper scaling
        auto [minIt, maxIt] = std::minmax_element(data.begin(), data.end());
        int minValue = *minIt;
        int maxValue = *maxIt;

        if (minValue == maxValue) {
            maxValue = minValue + 1; // Prevent division by zero
        }

        for (size_t i = 0; i < data.size(); ++i) {
            // Scale bar height properly for negative values
            float normalizedValue;
            float barHeight;
            float yPos;

            if (minValue < 0) {
                // Handle negative values: scale to [0, 1] range
                normalizedValue = static_cast<float>(data[i] - minValue) / (maxValue - minValue);
                barHeight = normalizedValue * (height * 0.8f); // Use 80% of height
                yPos = yOffset + height - barHeight;
            } else {
                // All positive values
                normalizedValue = static_cast<float>(data[i]) / maxValue;
                barHeight = normalizedValue * (height * 0.8f);
                yPos = yOffset + height - barHeight;
            }

            float xPos = i * barWidth;

            sf::RectangleShape bar;
            bar.setSize(sf::Vector2f(std::max(1.0f, barWidth - 1.0f), barHeight));
            bar.setPosition(xPos, yPos);

            // Set color based on highlighting
            sf::Color barColor = sf::Color::White; // Default color

            // Check if this index should be highlighted
            for (size_t j = 0; j < visualInfo.highlightedIndices.size(); ++j) {
                if (visualInfo.highlightedIndices[j] == i && j < visualInfo.highlightColors.size()) {
                    barColor = visualInfo.highlightColors[j];
                    break;
                }
            }

            bar.setFillColor(barColor);
            target.draw(bar);
        }
    }

    // Helper to update visualization info
    void updateVisualizationInfo(const std::string& operation) {
        visualInfo.currentOperation = operation;
        visualInfo.comparisons = totalComparisons;
        visualInfo.swaps = totalSwaps;
        visualInfo.state = currentState;
    }
};
