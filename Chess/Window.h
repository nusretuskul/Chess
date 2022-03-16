#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <SFML/Graphics.hpp>

class Window
{
public:
	Window(std::string, int, int);
	~Window();

	void setFrameLimit(int);
	bool pollEvent(sf::Event&);
	void clear(sf::Color = sf::Color::White);
	void display();
	void render(sf::Shape&);
	sf::Vector2i getMousePosition();

	sf::RenderWindow& getWindow();
	int getWidth();
	int getHeight();

private:
	sf::RenderWindow window;
	int width, height;
};

#endif