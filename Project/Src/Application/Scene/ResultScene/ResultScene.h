#pragma once

#include"../BaseScene/BaseScene.h"

class ResultScene : public BaseScene
{
public:

	ResultScene() { Init(); }
	~ResultScene() {}

private:

	void Event() override;
	void Init() override;

	KdTexture Tex;
	Math::Matrix Mat;
	Math::Rectangle Rect;
	Math::Color Color;
};
