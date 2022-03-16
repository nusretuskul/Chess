#include "Window.h"

Window::Window(std::string _title, int _width, int _height) : width(_width), height(_height)
{
	sf::VideoMode _vm(width, height);
	window.create(_vm, sf::String(_title), sf::Style::Default);
}

Window::~Window()
{

}

void Window::setFrameLimit(int _limit)
{
	window.setFramerateLimit(_limit);
}

bool Window::pollEvent(sf::Event& _event)
{
	return window.pollEvent(_event);
}

void Window::clear(sf::Color _color)
{
	window.clear(_color);
}

void Window::display()
{
	window.display();
}

void Window::render(sf::Shape& _shape)
{
	window.draw(_shape);
}

sf::Vector2i Window::getMousePosition()
{
	return sf::Mouse::getPosition(window);
}

sf::RenderWindow& Window::getWindow()
{
	return window;
}

int Window::getWidth()
{
	return width;
}

int Window::getHeight()
{
	return height;
}