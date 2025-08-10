#include "SortingAlgorithms.hpp"
#include "SortingAlgorithms.hpp"
#include <random>
#include <SFML/Graphics.hpp>

void BubbleSort::handleInput(const sf::Event& event) {
    // Algorithm-specific input handling can go here
    // For now, let's handle space bar to pause/resume
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            // Toggle pause state or step through algorithm
        }
    }
}

void BubbleSort::update(float dt) {
    delayTimer += dt;

    // Only proceed if enough time has passed (for visualization speed control)
    const float DELAY_THRESHOLD = 0.1f; // 100ms delay between steps

    if (delayTimer >= DELAY_THRESHOLD && !isFinished()) {
        performBubbleSortStep();
        delayTimer = 0.0f;
    }
}

void BubbleSort::render(sf::RenderTarget& target) const {
    // Basic bar rendering for bubble sort visualization
    if (data.empty()) return;

    const float windowWidth = 800.0f;  // Assume window width
    const float windowHeight = 600.0f; // Assume window height
    const float barWidth = windowWidth / data.size();
    const float maxHeight = windowHeight * 0.8f;

    // Find max value for scaling
    int maxVal = *std::max_element(data.begin(), data.end());

    for (size_t i = 0; i < data.size(); ++i) {
        sf::RectangleShape bar;
        float barHeight = (static_cast<float>(data[i]) / maxVal) * maxHeight;

        bar.setSize(sf::Vector2f(barWidth - 2, barHeight));
        bar.setPosition(i * barWidth, windowHeight - barHeight);

        // Color coding for visualization
        if (isComparing && (i == outerIndex || i == innerIndex)) {
            bar.setFillColor(sf::Color::Red);    // Currently comparing
        } else if (isSwapping && (i == outerIndex || i == innerIndex)) {
            bar.setFillColor(sf::Color::Yellow); // Currently swapping
        } else if (i >= data.size() - outerIndex) {
            bar.setFillColor(sf::Color::Green);  // Already sorted
        } else {
            bar.setFillColor(sf::Color::Blue);   // Unsorted
        }

        target.draw(bar);
    }
}

void BubbleSort::reset(){
    outerIndex = 0;
    innerIndex = 0;
    isComparing = false;
    isSwapping = false;
    delayTimer = 0.0f;
}

void BubbleSort::SetRandomData(size_t length, int min, int max) {
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
}

// The core bubble sort logic
void BubbleSort::performBubbleSortStep() {
    if (isFinished()) return;

    isComparing = true;

    // Bubble sort algorithm logic
    if (innerIndex < data.size() - 1 - outerIndex) {
        if (data[innerIndex] > data[innerIndex + 1]) {
            // Need to swap
            isSwapping = true;
            std::swap(data[innerIndex], data[innerIndex + 1]);
        }
        innerIndex++;
    } else {
        // End of inner loop, move to next outer iteration
        outerIndex++;
        innerIndex = 0;
        isSwapping = false;
    }

    // Check if sorting is complete
    if (outerIndex >= data.size() - 1) {
        isComparing = false;
        isSwapping = false;
    }
}

bool BubbleSort::isFinished() const {
    return outerIndex >= data.size() - 1;
}
