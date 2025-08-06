#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <memory>
#include "visualizer/VisualizeEngine.hpp"
#include "../algorithms/includes/BubbleSortVisualizer.hpp"
#include "../sfml_ui/UI.hpp"

int main(void) {
    // SFML window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Algorithm Visualizer");
    window.setFramerateLimit(90);

    // Font
    sf::Font font;
    if (!font.loadFromFile("../assets/MonoRegular.ttf")) {
        std::cout << "Font file not found\n";
        return -1;
    }

    // Measure frame timing
    sf::Clock clock;
    sf::Clock visualizationTimer; // Timer for algorithm visualization

    // Initialize UI Manager
    UIManager uiManager(font, window.getSize());

    // Initialize Visualization Engine
    VisualizeEngine engine;
    bool isVisualizationActive = false;

    // MAIN LOOP
    while (window.isOpen()) {
        sf::Event event;

        // INPUT LOOP
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle UI events
            UIResult uiResult = uiManager.handleEvent(event, window);

            // Process UI actions
            switch (uiResult.action) {
                case UIAction::SelectCategory:
                    uiManager.showAlgorithmSelection(uiResult.category);
                    break;

                case UIAction::SelectAlgorithm:
                    // Initialize the algorithm based on selection
                    switch (uiResult.algorithm) {
                        case AlgorithmType::BubbleSort:
                            engine.set_visualizer(std::make_unique<BubbleSortVisualizer>());
                            engine.SetRandomData(75, -1000, 1000);
                            uiManager.setAlgorithmName("Bubble Sort");
                            break;
                        // Add more algorithms here as you implement them
                        default:
                            break;
                    }
                    uiManager.showVisualization(uiResult.algorithm);
                    isVisualizationActive = true;
                    visualizationTimer.restart();
                    break;

                case UIAction::GoBack:
                    if (isVisualizationActive) {
                        // Going back from visualization to algorithm selection
                        // We need to know which category we came from - you might want to store this
                        uiManager.showAlgorithmSelection(AlgorithmCategory::Sorting); // Default for now
                        isVisualizationActive = false;
                    } else {
                        // Going back to main menu
                        uiManager.showMainMenu();
                    }
                    break;

                case UIAction::Reset:
                    if (isVisualizationActive) {
                        engine.reset();
                        visualizationTimer.restart();
                    }
                    break;

                default:
                    break;
            }

            // Pass events to visualization engine if active
            if (isVisualizationActive) {
                engine.handleInput(event);
            }
        } // END INPUT LOOP

        // Time since last frame
        float dt = clock.restart().asSeconds();

        // Update UI
        uiManager.update(dt);

        // Update visualization if active
        if (isVisualizationActive) {
            engine.update(dt);

            // Update UI with current visualization info
            float currentTime = visualizationTimer.getElapsedTime().asSeconds();
            uiManager.setTimer(currentTime);

            // You can add more dynamic updates here, like:
            // uiManager.setOperationText(engine.getCurrentOperation());
        }

        // RENDER
        window.clear(sf::Color(30, 30, 30));

        if (isVisualizationActive) {
            // Render visualization first (background)
            engine.render(window);
            // Then render UI overlay
            uiManager.render(window);
        } else {
            // Just render UI for menu screens
            uiManager.render(window);
        }

        window.display();
    }

    return 0;
}
