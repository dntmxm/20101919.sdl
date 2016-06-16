#pragma once
#include "PlayState.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "GameStateMachine.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "Enemy.h"
#include "SDLGameObject.h"
#include "GameOverState.h"
#include "StateParser.h"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->pushState(new PauseState());
	}

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}

	if (checkCollision(
		dynamic_cast<SDLGameObject*>(m_gameObjects[0]),
		dynamic_cast<SDLGameObject*>(m_gameObjects[1])))
	{
		/*TheGame::Instance()->getStateMachine()->changeState(new GameOverState());*/
		TheGame::Instance()->setState(State::GameOver);
	}
}

void PlayState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PlayState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/helicopter.png", "helicopter", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/helicopter2.png", "helicopter2", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	StateParser stateParser;
	stateParser.parseState("text.xml", s_playID, &m_gameObjects, &m_textureIDList);

	return true;
}

bool PlayState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	
	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}

	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("helicopter");
	TheTextureManager::Instance()->clearFromTextureMap("helicopter2");
	std::cout << "exiting PlayState\n";
	return true;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB;

	int rightA, rightB;

	int topA, topB;

	int bottomA, bottomB;

	leftA = p1->getPosition().getX();

	rightA = p1->getPosition().getX() + p1->getWidth();

	topA = p1->getPosition().getY();

	bottomA = p1->getPosition().getY() + p1->getHeight();

	//Calculate the sides of rect B

	leftB = p2->getPosition().getX();

	rightB = p2->getPosition().getX() + p2->getWidth();

	topB = p2->getPosition().getY();

	bottomB = p2->getPosition().getY() + p2->getHeight();

	//If any of the sides from A are outside of B
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }

	return true;
}