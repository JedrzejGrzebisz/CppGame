#include "Gracz.h"
#include "Przeciwnik.h"


Gracz::Gracz(sf::Texture *_texture, sf::Vector2u _imageCount, float _switchTime, float _speed) : animation(_texture, _imageCount, _switchTime)
{
	speed = _speed;
	row = 0;
	faceRight = true;
	zwrot_prawo = false;
	body.setSize(sf::Vector2f(96.0f, 96.0f));
	body.setPosition(1000.0f, 600.0f);
	body.setTexture(_texture);
}

void Gracz::Update(float deltaTime)
{
	sf::Vector2f ruch(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		ruch.x -= speed * deltaTime;
		zwrot_prawo = false;
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		ruch.x += speed * deltaTime;
		zwrot_prawo = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		
		body.move(0.0f, -0.8f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{

		body.move(0.0f, 0.8f);
	}
	if (ruch.x == 0)
	{
		row = 1;
	}
	else
	{
		row = 1;
		if (ruch.x < 0)
		{
			faceRight = true;
		}
		else
		{
			faceRight = false;
		}
	}

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(ruch);
}

void Gracz::Draw(sf::RenderWindow &okno)
{
	okno.draw(body);
}

float Gracz::pozycja_x()
{
	return body.getPosition().x;
}

float Gracz::pozycja_y()
{
	return body.getPosition().y;
}

void Gracz::czyKolizja(Przeciwnik przeciwnik)
{
	if ((przeciwnik.getLeft() < body.getPosition().x) && (przeciwnik.getTop() < body.getPosition().y + body.getSize().y)
		&& (przeciwnik.getDown() > body.getPosition().y) && (przeciwnik.getRight() >= body.getPosition().x))
	{
		kolizja = true;
	}
}


Gracz::~Gracz()
{
}