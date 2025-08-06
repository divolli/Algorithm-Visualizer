#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include <memory>

enum class AlgorithmCategory {
    Sorting,
    Graphs,
    Finance,
    MachineLearning,
    None // default
};

enum class AlgorithmType {
    BubbleSort,
    MergeSort,
    QuickSort,
    InsertionSort,
    SelectionSort,
    // Add more as you implement them
    None
};

enum class UIAction {
    None,
    SelectCategory,
    SelectAlgorithm,
    GoBack,
    StartVisualization,
    Reset
};

struct UIResult {
    UIAction action = UIAction::None;
    AlgorithmCategory category = AlgorithmCategory::None;
    AlgorithmType algorithm = AlgorithmType::None;
};

// Base UI Screen class
class UIScreen {
public:
    virtual ~UIScreen() = default;
    virtual UIResult handleEvent(const sf::Event& event, sf::RenderWindow& window) = 0;
    virtual void render(sf::RenderTarget& target) const = 0;
    virtual void update(float dt) {} // Optional update for animations
};

// Navigation Bar - appears on all screens except main menu
class NavigationBar {
public:
    NavigationBar(sf::Font& font, sf::Vector2<unsigned int> windowSize);
    UIResult handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void render(sf::RenderTarget& target) const;
    void setCurrentScreen(const std::string& screenName);

private:
    sf::RectangleShape background;
    sf::Text backButton;
    sf::Text currentScreenText;
    sf::RectangleShape backButtonShape;

    void setupNavigation(sf::Font& font, sf::Vector2<unsigned int> windowSize);
};

// Main Menu Screen
class MainMenuScreen : public UIScreen {
public:
    MainMenuScreen(sf::Font& font, sf::Vector2<unsigned int> windowSize);
    UIResult handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
    void render(sf::RenderTarget& target) const override;

private:
    sf::Text title;
    sf::Text subtitle;

    struct UIButton {
        sf::RectangleShape shape;
        sf::Text label;
        AlgorithmCategory category;
        bool isHovered = false;
    };

    std::vector<UIButton> buttons;
    void setupUI(sf::Font& font, sf::Vector2<unsigned int> windowSize);
    void updateButtonHover(sf::Vector2f mousePos);
};

// Algorithm Selection Screen
class AlgorithmSelectionScreen : public UIScreen {
public:
    AlgorithmSelectionScreen(sf::Font& font, sf::Vector2<unsigned int> windowSize,
                           AlgorithmCategory category);
    UIResult handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
    void render(sf::RenderTarget& target) const override;

private:
    sf::Text title;
    AlgorithmCategory currentCategory;
    std::unique_ptr<NavigationBar> navBar;

    struct AlgorithmButton {
        sf::RectangleShape shape;
        sf::Text label;
        AlgorithmType algorithm;
        bool isImplemented;
        bool isHovered = false;
    };

    std::vector<AlgorithmButton> algorithmButtons;
    void setupUI(sf::Font& font, sf::Vector2<unsigned int> windowSize);
    void setupAlgorithmsForCategory(sf::Font& font);
    void updateButtonHover(sf::Vector2f mousePos);
    std::string getCategoryName() const;
};

// Visualization Screen UI Elements
class VisualizationUI {
public:
    VisualizationUI(sf::Font& font, sf::Vector2<unsigned int> windowSize);
    UIResult handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void render(sf::RenderTarget& target) const;
    void setAlgorithmName(const std::string& name);
    void setTimer(float seconds);
    void setOperationText(const std::string& operation);

private:
    std::unique_ptr<NavigationBar> navBar;
    sf::Text algorithmNameText;
    sf::Text timerText;
    sf::Text operationText;
    sf::Text controlsHelpText;

    void setupUI(sf::Font& font, sf::Vector2<unsigned int> windowSize);
};

// Main UI Manager class
class UIManager {
public:
    UIManager(sf::Font& font, sf::Vector2<unsigned int> windowSize);
    UIResult handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void render(sf::RenderTarget& target) const;
    void update(float dt);

    // Screen management
    void showMainMenu();
    void showAlgorithmSelection(AlgorithmCategory category);
    void showVisualization(AlgorithmType algorithm);

    // Visualization UI methods
    void setAlgorithmName(const std::string& name);
    void setTimer(float seconds);
    void setOperationText(const std::string& operation);

private:
    enum class CurrentScreen {
        MainMenu,
        AlgorithmSelection,
        Visualization
    };

    CurrentScreen currentScreen = CurrentScreen::MainMenu;
    std::unique_ptr<MainMenuScreen> mainMenuScreen;
    std::unique_ptr<AlgorithmSelectionScreen> algorithmSelectionScreen;
    std::unique_ptr<VisualizationUI> visualizationUI;

    sf::Font* font;
    sf::Vector2<unsigned int> windowSize;
};
