#pragma once
#include <SFML/Graphics.hpp>

class Pocisk
{
public:
	Pocisk(sf::Vector2f size);
	~Pocisk();
	void strzal(float speed);
	double getRight();
	double getLeft();
	double getTop();
	double getDown();
	void Draw(sf::RenderWindow &okno);
	void ustawPozycja(sf::Vector2f pozycja);
	

private:
	sf::RectangleShape pocisk;
	
};

