#pragma once
#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "BaseCreator.h"

class AnimatedGraphic : public SDLGameObject
{
public:
	AnimatedGraphic();
	virtual ~AnimatedGraphic() {}
	virtual void update();
	virtual void draw();
	virtual void clean();
	virtual void load(const LoaderParams* pParams);
protected:
	int m_animSpeed;
};

class AnimatedGraphicCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new AnimatedGraphic();
	}
};