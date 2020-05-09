#pragma once
#include <SFML/Graphics.hpp>
#include "Animacja.h"
#include "Przeciwnik.h"
class Gracz
{
public:
	Gracz(sf::Texture *_texture, sf::Vector2u _imageCount, float _switchTime, float speed);
	~Gracz();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow &okno);
	float pozycja_x();
	float pozycja_y();
	void czyKolizja(Przeciwnik przeciwnik);
	bool zwrot_prawo;
	bool kolizja = false;
	
private:
	sf::RectangleShape body;
	Animacja animation;
	unsigned int row;
	float speed;
	bool faceRight;
};

