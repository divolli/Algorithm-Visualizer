#include "../includes/BubbleSortVisualizer.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <random>
#include <iostream>

void BubbleSortVisualizer::handleInput(const sf::Event& event) {
    // Algorithm-specific input handling can go here
    // Global controls are handled by VisualizeEngine
}

void BubbleSortVisualizer::update(float dt) {
    if (currentState != AlgorithmState::Running) return;

    delayTimer += dt;

    if (delayTimer >= getCurrentDelay()) {
        performOneStep();
        delayTimer = 0.0f;
    }
}

void BubbleSortVisualizer::performOneStep() {
    if (currentState != AlgorithmState::Running || data.empty()) return;

    // Bubble sort logic
    if (innerIndex < data.size() - outerIndex - 1) {
        // Compare adjacent elements
        isComparing = true;
        updateVisualizationInfo("Comparing: " + std::to_string(data[innerIndex]) +
                              " > " + std::to_string(data[innerIndex + 1]) + "?");

        totalComparisons++;

        if (data[innerIndex] > data[innerIndex + 1]) {
            // Swap elements
            std::swap(data[innerIndex], data[innerIndex + 1]);
            totalSwaps++;
            isSwapping = true;
            updateVisualizationInfo("Swapping: " + std::to_string(data[innerIndex + 1]) +
                                  " and " + std::to_string(data[innerIndex]));
        } else {
            isSwapping = false;
        }

        innerIndex++;
    } else {
        // Move to next pass
        innerIndex = 0;
        outerIndex++;
        isComparing = false;
        isSwapping = false;

        if (outerIndex >= data.size() - 1) {
            // Sorting complete
            currentState = AlgorithmState::Completed;
            updateVisualizationInfo("Sorting completed! Total comparisons: " +
                                  std::to_string(totalComparisons) +
                                  ", Total swaps: " + std::to_string(totalSwaps));
            visualInfo.progress = 1.0f;
        } else {
            // Calculate progress
            visualInfo.progress = static_cast<float>(outerIndex) / (data.size() - 1);
            updateVisualizationInfo("Pass " + std::to_string(outerIndex + 1) +
                                  " of " + std::to_string(data.size() - 1));
        }
    }

    updateHighlighting();
}

void BubbleSortVisualizer::updateHighlighting() {
    visualInfo.highlightedIndices.clear();
    visualInfo.highlightColors.clear();

    if (currentState == AlgorithmState::Running && innerIndex < data.size() - 1) {
        // Highlight current comparison
        visualInfo.highlightedIndices.push_back(innerIndex);
        visualInfo.highlightedIndices.push_back(innerIndex + 1);

        if (isSwapping) {
            visualInfo.highlightColors.push_back(sf::Color::Red);   // Element being swapped
            visualInfo.highlightColors.push_back(sf::Color::Red);   // Element being swapped
        } else {
            visualInfo.highlightColors.push_back(sf::Color::Yellow); // Current comparison
            visualInfo.highlightColors.push_back(sf::Color::Yellow); // Current comparison
        }
    }

    // Highlight sorted portion (right side)
    for (size_t i = data.size() - outerIndex; i < data.size(); ++i) {
        visualInfo.highlightedIndices.push_back(i);
        visualInfo.highlightColors.push_back(sf::Color::Green); // Sorted elements
    }
}

void BubbleSortVisualizer::render(sf::RenderTarget& target) const {
    // Use the base class helper method for consistent rendering
    renderBars(target, 130.0f); // Reserve 130px for UI overlay
}

void BubbleSortVisualizer::reset() {
    outerIndex = 0;
    innerIndex = 0;
    delayTimer = 0.0f;
    totalComparisons = 0;
    totalSwaps = 0;
    isComparing = false;
    isSwapping = false;
    currentState = AlgorithmState::Ready;

    visualInfo = VisualizationInfo();
    visualInfo.currentOperation = "Ready to start";
    visualInfo.state = currentState;

    std::cout << "[BubbleSort] Reset completed.\n";
}

void BubbleSortVisualizer::SetRandomData(size_t length, int min, int max) {
    if (length < 2) {
        throw std::invalid_argument("Length must be at least 2 for sorting visualization.");
    }

    if (min > max) std::swap(min, max);

    data.clear();
    data.reserve(length);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(min, max);

    for (size_t i = 0; i < length; ++i) {
        data.push_back(distrib(gen));
    }

    reset(); // Reset state when new data is set
    currentState = AlgorithmState::Ready;
    updateVisualizationInfo("Data loaded: " + std::to_string(length) + " elements");

    std::cout << "[BubbleSort] Generated " << length << " random elements ["
              << min << ", " << max << "]\n";
}

void BubbleSortVisualizer::SetData(const std::vector<int>& userData) {
    data = userData;
    reset();
    currentState = AlgorithmState::Ready;
    updateVisualizationInfo("Custom data loaded: " + std::to_string(data.size()) + " elements");

    std::cout << "[BubbleSort] Loaded " << userData.size() << " custom elements.\n";
}

VisualizationInfo BubbleSortVisualizer::getVisualizationInfo() const {
    return visualInfo;
}

void BubbleSortVisualizer::setSpeed(float speedMultiplier) {
    this->speedMultiplier = std::clamp(speedMultiplier, 0.1f, 5.0f);
}

void BubbleSortVisualizer::pause() {
    if (currentState == AlgorithmState::Running) {
        currentState = AlgorithmState::Paused;
        updateVisualizationInfo("Paused");
    }
}

void BubbleSortVisualizer::resume() {
    if (currentState == AlgorithmState::Paused) {
        currentState = AlgorithmState::Running;
    } else if (currentState == AlgorithmState::Ready) {
        currentState = AlgorithmState::Running;
        updateVisualizationInfo("Starting Bubble Sort...");
    }
}

void BubbleSortVisualizer::step() {
    if (currentState == AlgorithmState::Paused || currentState == AlgorithmState::Ready) {
        AlgorithmState prevState = currentState;
        currentState = AlgorithmState::Running;
        performOneStep();
        if (currentState != AlgorithmState::Completed) {
            currentState = prevState; // Return to previous state after step
        }
    }
}
