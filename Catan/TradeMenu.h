class TradeMenu {
public:
    TradeMenu(sf::RenderWindow* window, sf::Font& font) 
        : m_window(window), m_font(font) {
        initializeBackground();
        initializeButtons();
    }

    void draw() {
        if (!m_isVisible) return;

        m_window->draw(m_background);
        
        // Draw all UI elements
        for (const auto& element : m_uiElements) {
            element->draw(*m_window);
        }
    }

    void update(const sf::Vector2f& mousePos) {
        if (!m_isVisible) return;

        // Update all UI elements
        for (auto& element : m_uiElements) {
            element->update(mousePos);
        }
    }

    void handleClick(const sf::Vector2f& mousePos) {
        if (!m_isVisible) return;

        // Handle clicks for all UI elements
        for (auto& element : m_uiElements) {
            if (element->handleClick(mousePos)) {
                // Handle the specific element click
                handleElementClick(element);
            }
        }
    }

    void toggle() {
        m_isVisible = !m_isVisible;
    }

private:
    void initializeBackground() {
        float screenWidth = m_window->getSize().x;
        float screenHeight = m_window->getSize().y;
        
        m_background.setSize(sf::Vector2f(screenWidth * 0.8f, screenHeight * 0.8f));
        m_background.setFillColor(sf::Color(30, 30, 30, 250));
        m_background.setPosition(
            screenWidth * 0.1f,
            screenHeight * 0.1f
        );
    }

    void initializeButtons() {
        // Create resource trading buttons
        for (int i = 0; i < NUM_RESOURCES; i++) {
            createResourceTradeControls(i);
        }

        // Create accept/cancel buttons
        createActionButtons();
    }

    void createResourceTradeControls(int resourceIndex) {
        float xPos = m_background.getPosition().x + 100 + (resourceIndex * 150);
        float yPos = m_background.getPosition().y + 100;

        // Add resource sprite
        auto resourceSprite = std::make_unique<ResourceSprite>(
            ResourceType(resourceIndex), 
            sf::Vector2f(xPos, yPos), 
            *m_textures
        );
        m_uiElements.push_back(std::move(resourceSprite));

        // Add +/- buttons for offering
        auto plusButton = std::make_unique<Button>(
            sf::Vector2f(xPos + 50, yPos + 50),
            "+",
            m_font
        );
        m_uiElements.push_back(std::move(plusButton));

        auto minusButton = std::make_unique<Button>(
            sf::Vector2f(xPos - 20, yPos + 50),
            "-", 
            m_font
        );
        m_uiElements.push_back(std::move(minusButton));
    }

private:
    sf::RenderWindow* m_window;
    sf::Font& m_font;
    sf::RectangleShape m_background;
    std::vector<std::unique_ptr<IUIElement>> m_uiElements;
    bool m_isVisible{false};
    static const size_t NUM_RESOURCES = 5;
};
