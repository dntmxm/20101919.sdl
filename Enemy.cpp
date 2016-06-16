#pragma once
#include "Enemy.h"
#include "InputHandler.h"

Enemy::Enemy() : AnimatedGraphic()
{
	m_velocity.setX(2);
	m_velocity.setX(0.001f);
}

void Enemy::draw()
{
	AnimatedGraphic::draw();
}

void Enemy::update()
{
	if (m_position.getY() < 0) {
		m_velocity.setY(2);
	}
	else if (m_position.getY() > 400) {
		m_velocity.setY(-2);
	}
	AnimatedGraphic::update();
}

void Enemy::clean()
{
	AnimatedGraphic::clean();
}

void Enemy::handleInput()
{
	/*if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
	{
		m_velocity.setX(1);
	}
	Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
	m_velocity = (*vec - m_position) / 100;*/
}

void Enemy::load(const LoaderParams* pParam)
{
	AnimatedGraphic::load(pParam);
	m_velocity.setY(2);
}