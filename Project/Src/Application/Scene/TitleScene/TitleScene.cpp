#include "TitleScene.h"
#include "../SceneManager.h"
#include"../../main.h"
void TitleScene::Event()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Game
		);
	}

	Rect = { 0,0,1280,720 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&Tex, 0, 0);
}

void TitleScene::Init()
{
	Tex.Load("Asset/Textures/images.png");
}