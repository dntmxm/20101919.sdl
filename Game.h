#ifndef _GAME_H_
#define _GAME_H_

#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include "GameObject.h"
#include "GameEnum.h"

class GameObject;
class GameStateMachine;

class Game
{
public:
	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		else
			return s_pInstance;
	}
	~Game() {}
	bool init(const char* title, int xpos, int ypos,int width, int height, bool fullscreen);
	void render();
	void update();
	void handleEvents();
	void clean();
	void quit();
	bool running() { return m_bRunning; }
	SDL_Renderer* getRenderer() { return m_pRenderer; }
	GameStateMachine* getStateMachine() { return m_pGameStateMachine; }
	
	void setState(State _state) { m_state = _state; }
	
private:
	Game() {}
	static Game* s_pInstance;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;

	GameObject* m_go;
	GameObject* m_player;
	GameObject* m_enemy;
	GameStateMachine* m_pGameStateMachine;
	
	State m_state;
	State m_oldState;
};

typedef Game TheGame;

#endif