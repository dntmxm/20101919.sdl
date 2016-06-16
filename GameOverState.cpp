#pragma once
#include "GameOverState.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObject.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "StateParser.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

bool GameOverState::onEnter()
{

	StateParser stateParser;
	stateParser.parseState("text.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_gameOverToMain);
	m_callbacks.push_back(s_restartPlay);

	setCallbacks(m_callbacks);
	return true;
}
void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
	// go through the game objects
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		// if they are of type MenuButton then assign a callback based on the id passed in from the file
		if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setcallback(callbacks[pButton->getcallbackID()]);
		}
	}
}
bool GameOverState::onExit()
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

	return true;
}
void GameOverState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}
void GameOverState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

void GameOverState::s_gameOverToMain()
{
	//TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
	TheGame::Instance()->setState(State::Menu);
}

void GameOverState::s_restartPlay()
{
	//TheGame::Instance()->getStateMachine()->changeState(new PlayState());
	TheGame::Instance()->setState(State::Play);
}