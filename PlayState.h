#pragma once
#include "GameState.h"
#include <vector>
#include "MenuState.h"
#include "MenuButton.h"

class GameObject;
class SDLGameObject;

class PlayState : public MenuState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_playID; }
private:
	virtual void setCallbacks(const std::vector<Callback>& callbacks);
	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
	static const std::string s_playID;
	std::vector<GameObject*> m_gameObjects;
};