#pragma once
#include "MenuButton.h"
#include "GameObject.h"
#include "PauseState.h"
#include "Game.h"
#include "MenuState.h"
#include "GameStateMachine.h"
#include "InputHandler.h"
#include "PlayState.h"
#include "StateParser.h"

const std::string PauseState::s_pauseID = "PAUSE";
bool PauseState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/resume.png",
		"resumebutton", TheGame::Instance()->getRenderer())) {
		return false;
	}

	if (!TheTextureManager::Instance()->load("assets/main.png",
		"mainbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	// parse the state
	StateParser stateParser;
	stateParser.parseState("text.xml", s_pauseID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_pauseToMain);
	m_callbacks.push_back(s_resumePlay);

	setCallbacks(m_callbacks);

	return true;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
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

bool PauseState::onExit()
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
	TheTextureManager::Instance()->clearFromTextureMap("resumebutton");
	TheTextureManager::Instance()->clearFromTextureMap("mainbutton");

	// reset the mouse button states to false

	TheInputHandler::Instance()->reset();

	std::cout << "exiting PauseState\n";

	return true;
}

void PauseState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}
void PauseState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}
void PauseState::s_pauseToMain()
{
	/*TheGame::Instance()->getStateMachine()->changeState(
		new MenuState());*/
	TheGame::Instance()->setState(State::Menu);
}
void PauseState::s_resumePlay()
{
	/*TheGame::Instance()->getStateMachine()->changeState(
		new PlayState());*/
	TheGame::Instance()->setState(State::Play);
}