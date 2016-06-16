#include "MainMenuState.h"
#include "MenuButton.h"
#include "StateParser.h"
#include "TextureManager.h"

const std::string MainMenuState::s_menuID = "MENU";

bool MainMenuState::OnEnter()
{
	// parse the state
	StateParser stateParser;
	stateParser.parseState("text.xml", s_menuID, &m_gameObjects, &m_textureIDList);
	m_callbacks.push_back(0);
	m_callbacks.push_back(MenuToPlay);
	m_callbacks.push_back(ExitFromMenu);
	
	setCallbacks(m_callbacks);
	std::cout << "entering MenuState\n";
	return true;
}

bool MainMenuState::OnExit()
{
	// clear the texture manager
	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}
	return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
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

void MainMenuState::Update()
{
	MenuState::update();
}
void MainMenuState::Render()
{
	MenuState::render();
}


void MainMenuState::MenuToPlay(){}
void MainMenuState::ExitFromMenu(){}