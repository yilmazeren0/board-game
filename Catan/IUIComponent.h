#include <SFML/Graphics.hpp>

class IUIComponent {
public:
    virtual ~IUIComponent() = default;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update(sf::Vector2f mousePosition) = 0;
    virtual bool isHovered() const = 0;
};