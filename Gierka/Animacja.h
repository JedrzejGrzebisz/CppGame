#pragma once
#include <SFML/Graphics.hpp>
class Animacja
{
public:
	Animacja(sf::Texture *_texture, sf::Vector2u _imageCount, float _switchTime);
	
	void Update(int row, float deltaTime, bool faceRight);
	
	~Animacja();

public:

	sf::IntRect uvRect;

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
	float totalTime;
	float switchTime;
};

