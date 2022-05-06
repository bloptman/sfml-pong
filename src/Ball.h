#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Ball
{

public:

	Ball(float startX, float startY);
	FloatRect getPosition();
	RectangleShape getShape();
	float getXVelocity();
	void reboundSides();
	void reboundBottom();
	void reboundBatorTop();
	void update(Time dt);

private:
	Vector2f m_Position;
	RectangleShape m_Shape;

	float m_Speed = 1000.0f;
	float m_DirectionX = .2f;
	float m_DirectionY = .2f;

};

#endif // BALL_H