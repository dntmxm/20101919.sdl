#pragma once
#include "GameState.h"

#include <vector>
class GameObject;
class MenuState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_menuID; }
protected:
	typedef void(*Callback)();
	virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;
	std::vector<Callback> m_callbacks;

private:
	static const std::string s_menuID;
	std::vector<GameObject*> m_gameObjects;

	static void s_menuToPlay();
	static void s_exitFromMenu();
	
};