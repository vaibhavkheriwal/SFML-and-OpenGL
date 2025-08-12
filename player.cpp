#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	//window
	sf::RenderWindow windowObj(sf::VideoMode(800, 600), "Player");
	windowObj.setFramerateLimit(60);

	//player
	float playerRadius = 50.f;
	sf::CircleShape player(playerRadius);
	player.setFillColor(sf::Color::Green);
	player.setPosition(sf::Vector2f(350, 250));
	float playerSpeed = 5.f;

	//wall
	sf::RectangleShape wall(sf::Vector2f(100, 30));
	wall.setPosition(sf::Vector2f(350, 30));
	wall.setFillColor(sf::Color::Yellow);

	//font
	sf::Font fontObj;
	if (!fontObj.loadFromFile("font/ManufacturingConsent-Regular.ttf"))
	{
		std::cout << "Font failed to load.";
		return 1;
	}

	//text
	sf::Text outputText;
	outputText.setFont(fontObj);
	outputText.setFillColor(sf::Color::White);
	outputText.setCharacterSize(30);
	outputText.setPosition(790, 10);
	outputText.setString("FPS: 00");

	//text box colider
	sf::FloatRect outputTextColider = outputText.getLocalBounds();

	//clock
	sf::Clock clockObj;

	//gameloop
	while (windowObj.isOpen())
	{
		//check all event, one by one
		sf::Event eventObj;
		while (windowObj.pollEvent(eventObj))
		{
			if (eventObj.type == sf::Event::Closed)
			{
				windowObj.close();
			}
		}

		//wall
		if (player.getGlobalBounds().intersects(wall.getGlobalBounds()))
		{
			wall.setFillColor(sf::Color::Red);
		}

		//get player position
		sf::Vector2f playerPosition = player.getPosition();

		//move
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (playerPosition.y > 0)
			{
				player.move(sf::Vector2f(0.f, -playerSpeed));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (playerPosition.y + playerRadius * 2 < 600)
			{
				player.move(sf::Vector2f(0.f, playerSpeed));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (playerPosition.x > 0)
			{
				player.move(sf::Vector2f(-playerSpeed, 0.f));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (playerPosition.x + playerRadius * 2 < 800)
			{
				player.move(sf::Vector2f(playerSpeed, 0.f));
			}
		}

		//fps
		float timePerFrame = clockObj.restart().asSeconds();
		timePerFrame = 1.f / timePerFrame;
		outputText.setString("FPS: " + std::to_string(static_cast<int>(timePerFrame)));

		//set text origin to top right
		outputText.setOrigin(outputTextColider.left + outputTextColider.width, outputTextColider.top);

		//display
		windowObj.clear();
		windowObj.draw(player);
		windowObj.draw(wall);
		windowObj.draw(outputText);
		windowObj.display();
	}
	return 0;
}