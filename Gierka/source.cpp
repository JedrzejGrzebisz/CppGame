#include <SFML/Graphics.hpp>
#include <cmath>
#include <SFML/Window.hpp>
#include <iostream>
#include "Gracz.h"
#include "Pocisk.h"
#include "Przeciwnik.h"
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include "Bonus.h"

#include <SFML/Audio.hpp>



int main()
{
	srand(time(NULL));
	int mana_licznik = 150;
	int zdrowie_licznik = 200;

	//Tworzenie okna
	sf::RenderWindow okno(sf::VideoMode(1366, 768), "Gra SFML", sf::Style::Fullscreen);
	std::cout << okno.getSize().x << std::endl;
	std::cout << okno.getSize().y << std::endl;
	
	//Wypelnianie okna tlem
	sf::Texture tlo;
	tlo.loadFromFile("grafiki/tlo2.jpg");
	sf::Sprite obraz;
	obraz.setTexture(tlo);
	obraz.setPosition(0, 0);

	//Dodawanie czcionki
	sf::Font arial;
	arial.loadFromFile("grafiki/arial.ttf");
	
	//Tworzenie obrazu - przegrana
	sf::Texture przegrana;
	przegrana.loadFromFile("grafiki/przegrana.png");
	sf::Sprite game_over;
	game_over.setTexture(przegrana);
	game_over.setPosition(0, 0);
	
	//Tworzenie napisu - instrukcja
	sf::Text napis_1("Witaj w grze!\n Celem rozgrywki jest zbijanie spadajacych z nieba smokow.\n Przepuszczenie smoka kosztuje 5 pkt zdrowia, a wystrzelenie pocisku 1 pkt many.\n Z nieba spadaja takze fiolki many(dodaje 10pkt) oraz zdrowia(15 pkt).\n Sterowanie WSAD, strzal SPACJA.\n Aby zagrac wylacz instrukcje(klawisz K) oraz wcisnij Enter.\n By wyswietlic instrukcje oraz zapauzowac gre wcisnij klawisz I.\n Aby wlaczyc/wylaczyc muzyke wcisnij klawisz M/N. Aby wyjsc z gry nacisnij klawisz ESCSPE.\n Powodzenia!", arial, 30);
	napis_1.setFillColor(sf::Color::Black);
	napis_1.setPosition(30.0f, 250.0f);

	//Dodawanie muzyki
	sf::Music pokemon;
	pokemon.openFromFile("grafiki/pokemonmusic.ogg");

	//Stworzenie bohatera
	sf::Texture ludek;
	ludek.loadFromFile("grafiki/character.png");
	Gracz gracz(&ludek, sf::Vector2u(4, 4), 0.2f, 500.0f);

	//Stworzenie bonusu
	sf::Texture bonus1;
	sf::Texture bonus2;
	bonus1.loadFromFile("grafiki/bonus1.png");
	bonus2.loadFromFile("grafiki/bonus2.png");
	Bonus mana(&bonus1, sf::Vector2f(43.0f, 60.0f));
	Bonus zdrowie(&bonus2, sf::Vector2f(43.0f, 60.0f));
	
	double mx = rand() % 1320 + 10;
	double my = rand() % 600 + 400;
	mana.ustawPozycja(sf::Vector2f(mx, (-my)));

	double zx = rand() % 1320 + 10;
	double zy = rand() % 600 + 400;
	zdrowie.ustawPozycja(sf::Vector2f(zx, (-zy)));

	//Stworzenie 3 losowo umiejscowionych przeciwnikow, umieszczenie ich w wektorze
	sf::Texture wrog0;
	sf::Texture wrog1;
	sf::Texture wrog2;
	
	wrog0.loadFromFile("grafiki/smok1.png");
	wrog1.loadFromFile("grafiki/smok2.png");
	wrog2.loadFromFile("grafiki/smok3.png");

	std::vector<Przeciwnik> przeciwnicy;
	for (int i = 0; i < 15; i++)
	{
		double x = rand() % 1320 + 10;
		double y = rand() % 500 + 50;
		
		if (i < 5)
		{
			
			Przeciwnik przeciwnik(&wrog0, sf::Vector2f(50.0f, 50.0f));
			przeciwnik.ustawPozycja(sf::Vector2f(x, (-y)));
			przeciwnicy.push_back(przeciwnik);
		}
		else if (i>=5 && i<10)
		{
			
			Przeciwnik przeciwnik(&wrog2, sf::Vector2f(50.0f, 50.0f));
			przeciwnik.ustawPozycja(sf::Vector2f(x, (-y)));
			przeciwnicy.push_back(przeciwnik);
		}
		else if (i>=10)
		{
			
			Przeciwnik przeciwnik(&wrog1, sf::Vector2f(50.0f, 50.0f));
			przeciwnik.ustawPozycja(sf::Vector2f(x, (-y)));
			przeciwnicy.push_back(przeciwnik);
		}
	}
	
	
	//Utworzenie wektora pociskow(lecacych w lewo lub w prawo)
	std::vector<Pocisk> pociskLewyVec;
	std::vector<Pocisk> pociskPrawyVec;
	
	//Petla gry i potrzebne zmienne
	float deltaTime = 0.0f;
	sf::Clock zegar;
	bool napis_instrukcja = true;
	bool strzela = false;
	bool graj = false;
	
	while (okno.isOpen())
	{
		deltaTime = zegar.restart().asSeconds();
		
		//Zdarzenie - obsluga klawiatury
		sf::Event event;
		
		while (okno.pollEvent(event))
		{
			//Wyjscie z gry
			if ((event.type == sf::Event::Closed) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			{
				okno.close();
			}
			
			//Muzyka ON
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M)
			{
				pokemon.play();
			}
			
			//Muzyka OFF
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N)
			{
				pokemon.pause();
			}

			//Instrukcja ON
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I)
			{
				napis_instrukcja = true;
				
			}

			//Instrukcja OFF
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::K)
			{
				napis_instrukcja = false;
			}

			//Odpauzowanie
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
			{
				graj = true;
			}

			//Strzelanie
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			{
				strzela = true;
			}
		
		}
		
		gracz.Update(deltaTime); //animacja gracza
		okno.clear(sf::Color::Black);
		
		//Rysowanie obiektow na scenie(tlo, gracz, fiolki many i zdrowia, przeciwnicy oraz instrukcja)

		okno.draw(obraz);
		gracz.Draw(okno);
		mana.Draw(okno);
		zdrowie.Draw(okno);
		
		for (int i = 0; i < 15; i++)
		{
			przeciwnicy[i].Draw(okno);
		}
		
		if (napis_instrukcja)
		{
			okno.draw(napis_1);
		}
		
		//Poruszanie sie przeciwnikow i bonusow
		for (int i = 0; i < 15; i++)
		{
			if (graj && (!napis_instrukcja))
				przeciwnicy[i].opadanie(0.11f);
		}
		if (graj && (!napis_instrukcja))
		{
			mana.opadanie(0.11f);
			zdrowie.opadanie(0.11f);
		}

		//Strzelanie na spacje(stworzenie pocisku) lecacych w lewo/prawo
		if (strzela)
		{
			if (!gracz.zwrot_prawo)
			{
				Pocisk nowyPociskL(sf::Vector2f(30.0, 4.0));
				nowyPociskL.ustawPozycja(sf::Vector2f(gracz.pozycja_x() + 5, gracz.pozycja_y() + 27));
				pociskLewyVec.push_back(nowyPociskL);
				mana_licznik--;
			}
			else if (gracz.zwrot_prawo)
			{
				Pocisk nowyPociskP(sf::Vector2f(30.0, 4.0));
				nowyPociskP.ustawPozycja(sf::Vector2f(gracz.pozycja_x() + 60, gracz.pozycja_y() + 27));
				pociskPrawyVec.push_back(nowyPociskP);
				mana_licznik--;
			}
				strzela = false;
		}

		//Rysowanie pocisku(lewe), usuwanie po opuszczeniu ekranu
		for (int i = 0; i < pociskLewyVec.size(); i++)
		{
			pociskLewyVec[i].Draw(okno);
			pociskLewyVec[i].strzal(-1.7);
			for (auto it = pociskLewyVec.begin(); it != pociskLewyVec.end();)
			{
				if (pociskLewyVec[i].getLeft() < 0)
					it = pociskLewyVec.erase(it);
				else
					it++;
			}
			
		}
		
		//Rysowanie pocisku(prawe), usuwanie po opuszczeniu ekranu
		for (int i = 0; i < pociskPrawyVec.size(); i++)
		{
			pociskPrawyVec[i].Draw(okno);
			pociskPrawyVec[i].strzal(1.7);
			for (auto it = pociskPrawyVec.begin(); it != pociskPrawyVec.end();)
			{
				if (pociskPrawyVec[i].getRight() > 1366)
					it = pociskPrawyVec.erase(it);
				else
					it++;
			}
			
		}

		//Sprawdzenie kolizji z przeciwnikiem - pociski lewe
		for (int i = 0; i < pociskLewyVec.size(); i++)
		{
			
			mana.czyKolizja(pociskLewyVec[i]);
			zdrowie.czyKolizja(pociskLewyVec[i]);
			for (int j = 0; j < 15; j++)
			{
				przeciwnicy[j].czyKolizja(pociskLewyVec[i]);
			}
		}
		
		//Sprawdzenie kolizji z przeciwnikiem - pociski prawe
		for (int i = 0; i < pociskPrawyVec.size(); i++)
		{
			mana.czyKolizja(pociskPrawyVec[i]);
			zdrowie.czyKolizja(pociskPrawyVec[i]);
			for (int j = 0; j < 15; j++) 
			{
				przeciwnicy[j].czyKolizja(pociskPrawyVec[i]);
			}
		}

		//Zdobycie many
		if (mana.kolizja)
		{
			mana_licznik = mana_licznik + 10;
			mana.kolizja = false;
		}

		//Zdobycie zdrowia
		if (zdrowie.kolizja)
		{
			zdrowie_licznik = zdrowie_licznik + 15;
			zdrowie.kolizja = false;
		}

		//Puszczenie przeciwnika - stracenie 5 zdrowia
		for (int i = 0; i < przeciwnicy.size(); i++)
		{
			if (przeciwnicy[i].getTop() > 750)
			{
				double x = rand() % 1320 + 10;
				double y = rand() % 500 + 50;
				przeciwnicy[i].ustawPozycja(sf::Vector2f(x, (-y)));
				zdrowie_licznik = zdrowie_licznik - 5;
			}
		}

		//Przepuszczenie many i zdrowia(ponownie pojawiaja sie pozniej niz przy zestrzeleniu)
		if (mana.getY() > 750)
		{
			double x = rand() % 1340 + 10;
			double y = rand() % 600 + 400;
			mana.ustawPozycja(sf::Vector2f(x, (-y)));
		}

		if (zdrowie.getY() > 750)
		{
			double x = rand() % 1340 + 10;
			double y = rand() % 600 + 400;
			zdrowie.ustawPozycja(sf::Vector2f(x, (-y)));
		}
		
		//Tworzenie licznika many na ekranie
		sf::Text napis_manaT("Mana(pociski): ", arial, 30);
		napis_manaT.setFillColor(sf::Color::Blue);
		napis_manaT.setPosition(30.0f, 15.0f);

		std::stringstream ss1;
		ss1 << mana_licznik;
		sf::Text napis_manaL(ss1.str().c_str(), arial, 70);
		napis_manaL.setFillColor(sf::Color::Blue);
		napis_manaL.setPosition(30.0f, 40.0f);

		//Tworzenie licznika zdrowia na ekranie
		sf::Text napis_zdrowieT("Zdrowie: ", arial, 30);
		napis_zdrowieT.setFillColor(sf::Color::Red);
		napis_zdrowieT.setPosition(1200.0f, 15.0f);

		std::stringstream ss2;
		ss2 << zdrowie_licznik;
		sf::Text napis_zdrowieL(ss2.str().c_str(), arial, 70);
		napis_zdrowieL.setFillColor(sf::Color::Red);
		napis_zdrowieL.setPosition(1200.0f, 40.0f);
		
		//Umieszczenie napisow i licznikow na scenie
		okno.draw(napis_manaL);
		okno.draw(napis_manaT);
		okno.draw(napis_zdrowieL);
		okno.draw(napis_zdrowieT);

		//Koniec gry gdy konczy sie mana lub zdrowie
		if (mana_licznik <= 0 || zdrowie_licznik <= 0)
			okno.draw(game_over);
			
		
		okno.display();
	} 


	return 0;
}

