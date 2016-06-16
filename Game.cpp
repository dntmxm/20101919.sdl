#include "Game.h"
#include <iostream>
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "MainMenuState.h"
#include "GameObjectFactory.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos,
	int width, int height, bool fullscreen)
{
	Uint32 flags;
	if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;
	else flags = SDL_WINDOW_SHOWN;

	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != 0)
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			m_bRunning = true;
		}
	}
	else {
		return false; // sdl could not initialize
	}
	

	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MainMenuState());

	TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
	TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
	TheGameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
	TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
	

	m_state = State::Menu;
	m_oldState = State::Menu;
	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	m_pGameStateMachine->render();

	SDL_RenderPresent(m_pRenderer);
}
void Game::quit()
{
	m_bRunning = false;
	clean();
}
void Game::clean()
{
	std::cout << "cleaning game\n";
	TheInputHandler::Instance()->clean();
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
void Game::update()
{
	m_pGameStateMachine->update();
	if (m_oldState == m_state) return;
	switch (m_state)
	{
	case State::Play :
		m_pGameStateMachine->changeState(new PlayState());
		break;
	case State::Menu :
		m_pGameStateMachine->changeState(new MainMenuState());
		break;
	case State::Pause:
		m_pGameStateMachine->changeState(new PauseState());
		break;
	case State::GameOver:
		m_pGameStateMachine->changeState(new GameOverState());
		break;
	default:
		break;
	}
	m_oldState = m_state;
}

void Game::handleEvents() {
	TheInputHandler::Instance()->update();
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		//m_pGameStateMachine->changeState(new PlayState());
		m_state = State::Play;
	}
}