#pragma once
#include "SDLGameObject.h"
#include "BaseCreator.h"
#include "GameObjectFactory.h"

enum button_state
{
	MOUSE_OUT = 0,
	MOUSE_OVER = 1,
	CLICKED = 2
};
class MenuButton : public SDLGameObject
{
public:
	MenuButton();
	~MenuButton() {}
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(const LoaderParams *pParams);

	void setcallback(void(*callback)()) { m_callback = callback; }
	int getcallbackID() { return m_callbackID; }

private:
	void (*m_callback)();
	bool m_bReleased;
};

class MenuButtonCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new MenuButton();
	}
};
