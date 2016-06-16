#pragma once
#include "Player.h"
#include "InputHandler.h"

Player::Player() : AnimatedGraphic()
{
}

void Player::draw()
{
	AnimatedGraphic::draw();
}

void Player::update()
{
	m_velocity.setX(0);
	m_velocity.setY(0);
	handleInput();
	AnimatedGraphic::update();
}

void Player::handleInput()
{
	Vector2D* target = TheInputHandler::Instance()->getMousePosition();
	m_velocity = *target - m_position;
	m_velocity /= 50;
}

void Player::clean()
{
	SDLGameObject::clean();
}

void Player::load(const LoaderParams* pParam)
{
	AnimatedGraphic::load(pParam);
}
