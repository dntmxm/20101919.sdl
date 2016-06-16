#pragma once
#include "AnimatedGraphic.h"
#include "BaseCreator.h"

class Player : public AnimatedGraphic
{

public:
	Player();
	virtual ~Player() {}
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(const LoaderParams *pParams);
private:
	void handleInput();
};

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Player();
	}
};
