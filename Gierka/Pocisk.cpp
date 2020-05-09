#include "Pocisk.h"



Pocisk::Pocisk(sf::Vector2f size)
{
	pocisk.setSize(size);
	pocisk.setFillColor(sf::Color::Red);
}

void Pocisk::strzal(float speed)
{
	pocisk.move(speed, 0);
}

double Pocisk::getRight()
{
	return pocisk.getPosition().x + pocisk.getSize().x;
}

double Pocisk::getLeft()
{
	return pocisk.getPosition().x;
}

double Pocisk::getTop()
{
	return pocisk.getPosition().y;
}

double Pocisk::getDown()
{
	return pocisk.getPosition().y + pocisk.getSize().y;
}

void Pocisk::Draw(sf::RenderWindow & okno)
{
	okno.draw(pocisk);
}

void Pocisk::ustawPozycja(sf::Vector2f pozycja)
{
	pocisk.setPosition(pozycja);
}

Pocisk::~Pocisk()
{
}