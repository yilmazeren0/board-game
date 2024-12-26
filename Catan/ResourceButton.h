class ResourceButton {
public:
    ResourceButton();
    // Add other constructors and methods as needed
    
    // Common button functionality
    void setPosition(float x, float y);
    void draw(sf::RenderWindow& window);
    bool isClicked(const sf::Vector2f& mousePos);
    
private:
    sf::Sprite sprite;
    sf::Vector2f position;
    // Add other necessary members
};
