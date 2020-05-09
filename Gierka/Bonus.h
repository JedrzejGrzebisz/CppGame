#pragma once
#include <SFML/Graphics.hpp>
#include "Pocisk.h"

class Bonus
{
public:
	Bonus(sf::Texture *_tekstura, sf::Vector2f size);
	~Bonus();
	void ustawPozycja(sf::Vector2f pozycja);
	void czyKolizja(Pocisk pocisk);
	void Draw(sf::RenderWindow &okno);
	void opadanie(float speed);
	double getY();
	bool kolizja = false;
	
	
private:
	sf::RectangleShape bonus;
};