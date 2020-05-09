#include "Przeciwnik.h"
#include <cstdlib>
#include <ctime>
#include <iostream>


Przeciwnik::Przeciwnik(sf::Texture *_tekstura, sf::Vector2f size)
{
	przeciwnik.setSize(size);
	przeciwnik.setTexture(_tekstura);
}


void Przeciwnik::ustawPozycja(sf::Vector2f pozycja)
{
	przeciwnik.setPosition(pozycja);
}

void Przeciwnik::czyKolizja(Pocisk pocisk)
{
	double nowyX;
	double nowyY;
	nowyX = rand() % 1320 + 10;
	nowyY = rand() % 500 + 50;

	if ((pocisk.getLeft() < przeciwnik.getPosition().x) && (pocisk.getTop() < przeciwnik.getPosition().y + przeciwnik.getSize().y)
		&& (pocisk.getDown() > przeciwnik.getPosition().y) && (pocisk.getRight() >= przeciwnik.getPosition().x))
	{
		
		przeciwnik.setPosition(nowyX, (-nowyY));
		kolizja = true;
		
	}
	
}

void Przeciwnik::Draw(sf::RenderWindow &okno)
{
	okno.draw(przeciwnik);
}

void Przeciwnik::opadanie(float speed)
{
	przeciwnik.move(0, speed);
}

double Przeciwnik::getTop()
{
	return przeciwnik.getPosition().y;
}

double Przeciwnik::getDown()
{
	return przeciwnik.getPosition().y + przeciwnik.getSize().y;
}

double Przeciwnik::getLeft()
{
	return przeciwnik.getPosition().x;
}

double Przeciwnik::getRight()
{
	return przeciwnik.getPosition().x + przeciwnik.getSize().x;
}


Przeciwnik::~Przeciwnik()
{
}