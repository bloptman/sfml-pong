#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main()
{
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Pong", Style::Fullscreen);

	int score = 0;
	int lives = 3;

	Bat bat(1920 / 2, 1080 - 20);
	Ball ball(1920 / 2, 0);

	Text hud;

	Font font;
	font.loadFromFile("assets/fonts/DS-DIGI.ttf");

	hud.setFont(font);
	hud.setCharacterSize(75);
	hud.setFillColor(Color::White);

	Clock clock;

	while (window.isOpen())
	{
		// Handle player input

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			bat.moveLeft();
		}

		else
		{
			bat.stopLeft();
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			bat.moveRight();
		}

		else
		{
			bat.stopRight();
		}

		// Update the bat, ball, and HUD

		Time dt = clock.restart();
		bat.update(dt);
		ball.update(dt);

		std::stringstream ss;
		ss << "Score:" << score << " Lives: " << lives;

		hud.setString(ss.str());

		// Handle the ball hitting the bottom.
		if (ball.getPosition().top > window.getSize().y)
		{
			ball.reboundBottom();
			lives--;

			if (lives < 1)
			{
				score = 0;
				lives = 3;
			}
		}

		// Handle the ball hitting the top.
		if (ball.getPosition().top < 0)
		{
			ball.reboundBatorTop();
			score++;
		}


		// Handle the ball hitting the sides.
		if
			(
			ball.getPosition().left < 0 or 
			ball.getPosition().left + ball.getPosition().width > window.getSize().x
			)
		{
			ball.reboundSides();
		}

		// Handle the ball hitting the bat.
		if (ball.getPosition().intersects(bat.getPosition()))
		{
			ball.reboundBatorTop();
		}
	
		// Draw the bat, ball, and HUD

		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.display();
	}
	return 0;
}