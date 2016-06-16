#pragma once
#include "GameObject.h"
#include "MenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "GameStateMachine.h"
#include "StateParser.h"
#include <iostream>


const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void MenuState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool MenuState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/button.png", "playbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/exit.png", "exitbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	StateParser stateParser;
	stateParser.parseState("text.xml", s_menuID, &m_gameObjects, &m_textureIDList);
	
	return true;
}

bool MenuState::onExit()
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

	TheTextureManager::Instance()->clearFromTextureMap("playbutton");

	TheTextureManager::Instance()->clearFromTextureMap("exitbutton");
	return true;
}

void MenuState::s_menuToPlay()
{
	TheGame::Instance()->setState(State::Play);
}

void MenuState::s_exitFromMenu()
{
	TheGame::Instance()->quit();
}