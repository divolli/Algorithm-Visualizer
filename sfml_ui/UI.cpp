#include "UI.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>

MainMenuUI::MainMenuUI(sf::Font& font, sf::Vector2<unsigned int> windowSize) {
  setupUI(font, windowSize);
}


void MainMenuUI:: setupUI(sf::Font& font, sf::Vector2<unsigned int> windowSize){
  title.setFont(font);
  title.setString("Welcome to Algorithm Visualizer");
  title.setCharacterSize(36);
  title.setFillColor(sf::Color::Magenta);
  title.setPosition(windowSize.x / 2.f  - title.getGlobalBounds().width / 2.f, 100.f);

  const std::vector<std::pair<std::string, AlgorithmCategory>> categories = {
    {"Sorting", AlgorithmCategory::Sorting},
    {"Graphs", AlgorithmCategory::Graphs},
    {"Finance", AlgorithmCategory::Finance},
    {"Machine Learning", AlgorithmCategory::MachineLearning },
  };

  float btnWidth = 200.f;
  float btnHeight= 50.f;
  float gap = 20.f;
  float startY = 180.f;
  float centerX = windowSize.x / 2.f - btnWidth / 2.f;

  for (size_t i{}; i < categories.size(); ++i){
    UIButton btn;
    btn.shape.setSize({btnWidth, btnHeight});
    btn.shape.setPosition(centerX, startY + i * (btnHeight + gap));
    btn.shape.setFillColor(sf::Color(50, 50, 200));
    btn.shape.setOutlineColor(sf::Color::White);
    btn.shape.setOutlineThickness(2.f);

    btn.label.setFont(font);
    btn.label.setString(categories[i].first);
    btn.label.setCharacterSize(20);
    btn.label.setFillColor(sf::Color::White);
    btn.label.setPosition(
        btn.shape.getPosition().x + 20.f,
        btn.shape.getPosition().y + 10.f
    );
  }
}


void MainMenuUI::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {

        sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        for (const auto& btn : buttons) {
            if (btn.shape.getGlobalBounds().contains(mousePos)) {
                selectedCategory = btn.category;
                break;
            }
        }
    }
}


void MainMenuUI::render(sf::RenderTarget& target) const {
    target.draw(title);
    target.draw(subtitle);
    for (const auto& btn : buttons) {
        target.draw(btn.shape);
        target.draw(btn.label);
    }
}

AlgorithmCategory MainMenuUI::getSelectedCategory() const {
    return selectedCategory;
}
