class IUIElement {
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update(const sf::Vector2f& mousePos) = 0;
    virtual bool handleClick(const sf::Vector2f& mousePos) = 0;
    virtual ~IUIElement() = default;
};
