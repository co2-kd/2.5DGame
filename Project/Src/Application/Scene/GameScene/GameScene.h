#pragma once

#include"../BaseScene/BaseScene.h"

class Player;

class Mousehit;

class GameScene : public BaseScene
{
public :

	GameScene() { Init(); }
	~GameScene() override {}

private:

	void Event() override;
	void Init() override;
	//std::shared_ptr<KdCamera> m_camera = nullptr;
	std::weak_ptr<Player> m_player;
	std::weak_ptr<Mousehit> m_mousehit;
};
