#pragma once
#include "AnimatedGraphic.h"
#include "BaseCreator.h"
#include "GameObjectFactory.h"

class Enemy : public AnimatedGraphic
{
public:
	Enemy();
	~Enemy(){}
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(const LoaderParams* pParam);
private:
	void handleInput();
};

class EnemyCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Enemy();
	}
};