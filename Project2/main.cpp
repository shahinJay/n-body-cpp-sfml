#include <SFML/Graphics.hpp>




int main() {
	sf::RenderWindow window(sf::VideoMode({ 800,800 }), "my window");

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		

		sf::CircleShape shape(50.f);
		shape.setFillColor(sf::Color::Black);

		window.clear(sf::Color::Cyan);
		window.display();
	}
}