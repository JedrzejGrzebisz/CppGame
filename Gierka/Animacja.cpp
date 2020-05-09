#include "Animacja.h"



Animacja::Animacja(sf::Texture *_texture, sf::Vector2u _imageCount, float _switchTime)
{
	imageCount = _imageCount;
	switchTime = _switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = _texture->getSize().x / (float)_imageCount.x;
	uvRect.height = _texture->getSize().y / (float)_imageCount.y;
}

void Animacja::Update(int row, float deltaTime, bool faceRight)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}

	
	uvRect.top = currentImage.y * uvRect.height;

	if (faceRight)
	{
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);

	}
}


Animacja::~Animacja()
{
}
