#include "UI.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>

// ============================================================================
// NavigationBar Implementation
// ============================================================================
NavigationBar::NavigationBar(sf::Font& font, sf::Vector2<unsigned int> windowSize) {
    setupNavigation(font, windowSize);
}

void NavigationBar::setupNavigation(sf::Font& font, sf::Vector2<unsigned int> windowSize) {
    // Background bar
    background.setSize({static_cast<float>(windowSize.x), 40.f});
    background.setPosition(0, 0);
    background.setFillColor(sf::Color(40, 40, 40));

    // Back button
    backButtonShape.setSize({80.f, 30.f});
    backButtonShape.setPosition(10.f, 5.f);
    backButtonShape.setFillColor(sf::Color(100, 100, 100));
    backButtonShape.setOutlineColor(sf::Color::White);
    backButtonShape.setOutlineThickness(1.f);

    backButton.setFont(font);
    backButton.setString("← Back");
    backButton.setCharacterSize(16);
    backButton.setFillColor(sf::Color::White);
    backButton.setPosition(15.f, 10.f);

    // Current screen text
    currentScreenText.setFont(font);
    currentScreenText.setCharacterSize(18);
    currentScreenText.setFillColor(sf::Color::White);
    currentScreenText.setPosition(windowSize.x / 2.f, 10.f);
}

UIResult NavigationBar::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    UIResult result;

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});

        if (backButtonShape.getGlobalBounds().contains(mousePos)) {
            result.action = UIAction::GoBack;
        }
    }

    return result;
}

void NavigationBar::render(sf::RenderTarget& target) const {
    target.draw(background);
    target.draw(backButtonShape);
    target.draw(backButton);
    target.draw(currentScreenText);
}

void NavigationBar::setCurrentScreen(const std::string& screenName) {
    currentScreenText.setString(screenName);
    // Center the text
    sf::FloatRect bounds = currentScreenText.getGlobalBounds();
    currentScreenText.setPosition(640.f - bounds.width / 2.f, 10.f);
}

// ============================================================================
// MainMenuScreen Implementation
// ============================================================================
MainMenuScreen::MainMenuScreen(sf::Font& font, sf::Vector2<unsigned int> windowSize) {
    setupUI(font, windowSize);
}

void MainMenuScreen::setupUI(sf::Font& font, sf::Vector2<unsigned int> windowSize) {
    // Title
    title.setFont(font);
    title.setString("Algorithm Visualizer");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::Cyan);

    sf::FloatRect titleBounds = title.getGlobalBounds();
    title.setPosition(windowSize.x / 2.f - titleBounds.width / 2.f, 80.f);

    // Subtitle
    subtitle.setFont(font);
    subtitle.setString("Choose Algorithm Category");
    subtitle.setCharacterSize(24);
    subtitle.setFillColor(sf::Color::White);

    sf::FloatRect subtitleBounds = subtitle.getGlobalBounds();
    subtitle.setPosition(windowSize.x / 2.f - subtitleBounds.width / 2.f, 150.f);

    // Category buttons
    const std::vector<std::pair<std::string, AlgorithmCategory>> categories = {
        {"Sorting Algorithms", AlgorithmCategory::Sorting},
        {"Graph Algorithms", AlgorithmCategory::Graphs},
        {"Finance Algorithms", AlgorithmCategory::Finance},
        {"Machine Learning", AlgorithmCategory::MachineLearning}
    };

    float btnWidth = 300.f;
    float btnHeight = 60.f;
    float gap = 20.f;
    float startY = 220.f;
    float centerX = windowSize.x / 2.f - btnWidth / 2.f;

    for (size_t i = 0; i < categories.size(); ++i) {
        UIButton btn;
        btn.shape.setSize({btnWidth, btnHeight});
        btn.shape.setPosition(centerX, startY + i * (btnHeight + gap));
        btn.shape.setFillColor(sf::Color(60, 60, 120));
        btn.shape.setOutlineColor(sf::Color::White);
        btn.shape.setOutlineThickness(2.f);

        btn.label.setFont(font);
        btn.label.setString(categories[i].first);
        btn.label.setCharacterSize(20);
        btn.label.setFillColor(sf::Color::White);

        // Center text in button
        sf::FloatRect labelBounds = btn.label.getGlobalBounds();
        btn.label.setPosition(
            btn.shape.getPosition().x + btnWidth / 2.f - labelBounds.width / 2.f,
            btn.shape.getPosition().y + btnHeight / 2.f - labelBounds.height / 2.f - 5.f
        );

        btn.category = categories[i].second;
        buttons.push_back(btn);
    }
}

void MainMenuScreen::updateButtonHover(sf::Vector2f mousePos) {
    for (auto& btn : buttons) {
        bool wasHovered = btn.isHovered;
        btn.isHovered = btn.shape.getGlobalBounds().contains(mousePos);

        if (btn.isHovered && !wasHovered) {
            btn.shape.setFillColor(sf::Color(80, 80, 160));
        } else if (!btn.isHovered && wasHovered) {
            btn.shape.setFillColor(sf::Color(60, 60, 120));
        }
    }
}

UIResult MainMenuScreen::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    UIResult result;

    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
        updateButtonHover(mousePos);
    }

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});

        for (const auto& btn : buttons) {
            if (btn.shape.getGlobalBounds().contains(mousePos)) {
                result.action = UIAction::SelectCategory;
                result.category = btn.category;
                break;
            }
        }
    }

    return result;
}

void MainMenuScreen::render(sf::RenderTarget& target) const {
    target.draw(title);
    target.draw(subtitle);

    for (const auto& btn : buttons) {
        target.draw(btn.shape);
        target.draw(btn.label);
    }
}

// ============================================================================
// AlgorithmSelectionScreen Implementation
// ============================================================================
AlgorithmSelectionScreen::AlgorithmSelectionScreen(sf::Font& font, sf::Vector2<unsigned int> windowSize,
                                                 AlgorithmCategory category)
    : currentCategory(category) {
    navBar = std::make_unique<NavigationBar>(font, windowSize);
    setupUI(font, windowSize);
}

void AlgorithmSelectionScreen::setupUI(sf::Font& font, sf::Vector2<unsigned int> windowSize) {
    navBar->setCurrentScreen(getCategoryName() + " Algorithms");

    // Title
    title.setFont(font);
    title.setString(getCategoryName() + " Algorithms");
    title.setCharacterSize(36);
    title.setFillColor(sf::Color::Cyan);

    sf::FloatRect titleBounds = title.getGlobalBounds();
    title.setPosition(windowSize.x / 2.f - titleBounds.width / 2.f, 80.f);

    setupAlgorithmsForCategory(font);
}

void AlgorithmSelectionScreen::setupAlgorithmsForCategory(sf::Font& font) {
    algorithmButtons.clear();

    std::vector<std::tuple<std::string, AlgorithmType, bool>> algorithms;

    switch (currentCategory) {
        case AlgorithmCategory::Sorting:
            algorithms = {
                {"Bubble Sort", AlgorithmType::BubbleSort, true},
                {"Merge Sort", AlgorithmType::MergeSort, false},
                {"Quick Sort", AlgorithmType::QuickSort, false},
                {"Insertion Sort", AlgorithmType::InsertionSort, false},
                {"Selection Sort", AlgorithmType::SelectionSort, false}
            };
            break;
        case AlgorithmCategory::Graphs:
            algorithms = {
                {"Coming Soon...", AlgorithmType::None, false}
            };
            break;
        case AlgorithmCategory::Finance:
            algorithms = {
                {"Coming Soon...", AlgorithmType::None, false}
            };
            break;
        case AlgorithmCategory::MachineLearning:
            algorithms = {
                {"Coming Soon...", AlgorithmType::None, false}
            };
            break;
        default:
            break;
    }

    float btnWidth = 250.f;
    float btnHeight = 50.f;
    float gap = 15.f;
    float startY = 150.f;
    float centerX = 640.f - btnWidth / 2.f;

    for (size_t i = 0; i < algorithms.size(); ++i) {
        AlgorithmButton btn;
        btn.shape.setSize({btnWidth, btnHeight});
        btn.shape.setPosition(centerX, startY + i * (btnHeight + gap));

        btn.isImplemented = std::get<2>(algorithms[i]);
        if (btn.isImplemented) {
            btn.shape.setFillColor(sf::Color(50, 120, 50));
        } else {
            btn.shape.setFillColor(sf::Color(80, 80, 80));
        }
        btn.shape.setOutlineColor(sf::Color::White);
        btn.shape.setOutlineThickness(1.f);

        btn.label.setFont(font);
        btn.label.setString(std::get<0>(algorithms[i]));
        btn.label.setCharacterSize(18);
        btn.label.setFillColor(btn.isImplemented ? sf::Color::White : sf::Color(150, 150, 150));

        sf::FloatRect labelBounds = btn.label.getGlobalBounds();
        btn.label.setPosition(
            btn.shape.getPosition().x + btnWidth / 2.f - labelBounds.width / 2.f,
            btn.shape.getPosition().y + btnHeight / 2.f - labelBounds.height / 2.f - 3.f
        );

        btn.algorithm = std::get<1>(algorithms[i]);
        algorithmButtons.push_back(btn);
    }
}

void AlgorithmSelectionScreen::updateButtonHover(sf::Vector2f mousePos) {
    for (auto& btn : algorithmButtons) {
        if (!btn.isImplemented) continue;

        bool wasHovered = btn.isHovered;
        btn.isHovered = btn.shape.getGlobalBounds().contains(mousePos);

        if (btn.isHovered && !wasHovered) {
            btn.shape.setFillColor(sf::Color(70, 160, 70));
        } else if (!btn.isHovered && wasHovered) {
            btn.shape.setFillColor(sf::Color(50, 120, 50));
        }
    }
}

std::string AlgorithmSelectionScreen::getCategoryName() const {
    switch (currentCategory) {
        case AlgorithmCategory::Sorting: return "Sorting";
        case AlgorithmCategory::Graphs: return "Graph";
        case AlgorithmCategory::Finance: return "Finance";
        case AlgorithmCategory::MachineLearning: return "Machine Learning";
        default: return "Unknown";
    }
}

UIResult AlgorithmSelectionScreen::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    UIResult result;

    // Handle navigation bar events
    UIResult navResult = navBar->handleEvent(event, window);
    if (navResult.action != UIAction::None) {
        return navResult;
    }

    // Handle ESC key for going back
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        result.action = UIAction::GoBack;
        return result;
    }

    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
        updateButtonHover(mousePos);
    }

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});

        for (const auto& btn : algorithmButtons) {
            if (btn.isImplemented && btn.shape.getGlobalBounds().contains(mousePos)) {
                result.action = UIAction::SelectAlgorithm;
                result.algorithm = btn.algorithm;
                break;
            }
        }
    }

    return result;
}

void AlgorithmSelectionScreen::render(sf::RenderTarget& target) const {
    navBar->render(target);
    target.draw(title);

    for (const auto& btn : algorithmButtons) {
        target.draw(btn.shape);
        target.draw(btn.label);
    }
}

// ============================================================================
// VisualizationUI Implementation
// ============================================================================
VisualizationUI::VisualizationUI(sf::Font& font, sf::Vector2<unsigned int> windowSize) {
    navBar = std::make_unique<NavigationBar>(font, windowSize);
    setupUI(font, windowSize);
}

void VisualizationUI::setupUI(sf::Font& font, sf::Vector2<unsigned int> windowSize) {
    navBar->setCurrentScreen("Algorithm Visualization");

    // Algorithm name (top-left below nav bar)
    algorithmNameText.setFont(font);
    algorithmNameText.setCharacterSize(24);
    algorithmNameText.setFillColor(sf::Color::White);
    algorithmNameText.setPosition(20.f, 50.f);

    // Timer
    timerText.setFont(font);
    timerText.setCharacterSize(18);
    timerText.setFillColor(sf::Color::Yellow);
    timerText.setPosition(20.f, 80.f);

    // Operation text
    operationText.setFont(font);
    operationText.setCharacterSize(16);
    operationText.setFillColor(sf::Color::Green);
    operationText.setPosition(20.f, 105.f);

    // Controls help
    controlsHelpText.setFont(font);
    controlsHelpText.setString("Controls: R - Reset | ESC - Back | Space - Pause/Resume");
    controlsHelpText.setCharacterSize(14);
    controlsHelpText.setFillColor(sf::Color(200, 200, 200));
    controlsHelpText.setPosition(20.f, windowSize.y - 30.f);
}

UIResult VisualizationUI::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    UIResult result;

    // Handle navigation bar events
    UIResult navResult = navBar->handleEvent(event, window);
    if (navResult.action != UIAction::None) {
        return navResult;
    }

    // Handle keyboard shortcuts
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            result.action = UIAction::GoBack;
        } else if (event.key.code == sf::Keyboard::R) {
            result.action = UIAction::Reset;
        }
    }

    return result;
}

void VisualizationUI::render(sf::RenderTarget& target) const {
    navBar->render(target);
    target.draw(algorithmNameText);
    target.draw(timerText);
    target.draw(operationText);
    target.draw(controlsHelpText);
}

void VisualizationUI::setAlgorithmName(const std::string& name) {
    algorithmNameText.setString("Algorithm: " + name);
}

void VisualizationUI::setTimer(float seconds) {
    timerText.setString("Time: " + std::to_string(static_cast<int>(seconds)) + "s");
}

void VisualizationUI::setOperationText(const std::string& operation) {
    operationText.setString("Operation: " + operation);
}

// ============================================================================
// UIManager Implementation
// ============================================================================
UIManager::UIManager(sf::Font& font, sf::Vector2<unsigned int> windowSize)
    : font(&font), windowSize(windowSize) {
    mainMenuScreen = std::make_unique<MainMenuScreen>(font, windowSize);
}

UIResult UIManager::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    UIResult result;

    switch (currentScreen) {
        case CurrentScreen::MainMenu:
            result = mainMenuScreen->handleEvent(event, window);
            break;
        case CurrentScreen::AlgorithmSelection:
            if (algorithmSelectionScreen) {
                result = algorithmSelectionScreen->handleEvent(event, window);
            }
            break;
        case CurrentScreen::Visualization:
            if (visualizationUI) {
                result = visualizationUI->handleEvent(event, window);
            }
            break;
    }

    return result;
}

void UIManager::render(sf::RenderTarget& target) const {
    switch (currentScreen) {
        case CurrentScreen::MainMenu:
            mainMenuScreen->render(target);
            break;
        case CurrentScreen::AlgorithmSelection:
            if (algorithmSelectionScreen) {
                algorithmSelectionScreen->render(target);
            }
            break;
        case CurrentScreen::Visualization:
            if (visualizationUI) {
                visualizationUI->render(target);
            }
            break;
    }
}

void UIManager::update(float dt) {
    switch (currentScreen) {
        case CurrentScreen::MainMenu:
            mainMenuScreen->update(dt);
            break;
        case CurrentScreen::AlgorithmSelection:
            if (algorithmSelectionScreen) {
                algorithmSelectionScreen->update(dt);
            }
            break;
        case CurrentScreen::Visualization:
            if (visualizationUI) {
                // visualizationUI->update(dt);
            }
            break;
    }
}

void UIManager::showMainMenu() {
    currentScreen = CurrentScreen::MainMenu;
}

void UIManager::showAlgorithmSelection(AlgorithmCategory category) {
    algorithmSelectionScreen = std::make_unique<AlgorithmSelectionScreen>(*font, windowSize, category);
    currentScreen = CurrentScreen::AlgorithmSelection;
}

void UIManager::showVisualization(AlgorithmType algorithm) {
    visualizationUI = std::make_unique<VisualizationUI>(*font, windowSize);
    currentScreen = CurrentScreen::Visualization;
}

void UIManager::setAlgorithmName(const std::string& name) {
    if (visualizationUI) {
        visualizationUI->setAlgorithmName(name);
    }
}

void UIManager::setTimer(float seconds) {
    if (visualizationUI) {
        visualizationUI->setTimer(seconds);
    }
}

void UIManager::setOperationText(const std::string& operation) {
    if (visualizationUI) {
        visualizationUI->setOperationText(operation);
    }
}
