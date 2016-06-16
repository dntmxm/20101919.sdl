#pragma once
#include "GameState.h"
#include <vector>
class GameObject;
class SDLGameObject;

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_playID; }
private:
	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
	static const std::string s_playID;
	std::vector<GameObject*> m_gameObjects;
};