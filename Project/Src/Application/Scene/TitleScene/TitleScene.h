#pragma once

#include"../BaseScene/BaseScene.h"

class TitleScene : public BaseScene
{
public :

	TitleScene() { Init(); }
	~TitleScene() {}

private :

	void Event() override;
	void Init() override;

	KdTexture Tex;
	Math::Rectangle Rect;
	Math::Color Color;

};
