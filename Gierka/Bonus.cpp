#include "Bonus.h"
#include <cstdlib>
#include <ctime>

Bonus::Bonus(sf::Texture * _tekstura, sf::Vector2f size)
{
	bonus.setSize(size);
	bonus.setTexture(_tekstura);
}

void Bonus::ustawPozycja(sf::Vector2f pozycja)
{
	bonus.setPosition(pozycja);
}

void Bonus::czyKolizja(Pocisk pocisk)
{
	double nowyX;
	double nowyY;
	nowyX = rand() % 1320 + 10;
	nowyY = rand() % 500 + 100;

	if ((pocisk.getLeft() < bonus.getPosition().x) && (pocisk.getTop() < bonus.getPosition().y + bonus.getSize().y)
		&& (pocisk.getDown() > bonus.getPosition().y) && (pocisk.getRight() >= bonus.getPosition().x))
	{
		bonus.setPosition(nowyX, (-nowyY));
		kolizja = true;
	}
	
}

void Bonus::Draw(sf::RenderWindow & okno)
{
	okno.draw(bonus);
}

void Bonus::opadanie(float speed)
{
	bonus.move(0, speed);
}

double Bonus::getY()
{
	return bonus.getPosition().y;
}

Bonus::~Bonus()
{
}