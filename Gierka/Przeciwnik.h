#pragma once
#include <SFML/Graphics.hpp>
#include "Pocisk.h"
class Przeciwnik
{
public:
	Przeciwnik(sf::Texture *_tekstura, sf::Vector2f size);
	~Przeciwnik();
	void ustawPozycja(sf::Vector2f pozycja);
	void czyKolizja(Pocisk pocisk);
	void Draw(sf::RenderWindow &okno);
	void opadanie(float speed);
	double getTop();
	double getDown();
	double getLeft();
	double getRight();
	bool kolizja = false;
	
	
private:
	sf::RectangleShape przeciwnik;
	
	
};

