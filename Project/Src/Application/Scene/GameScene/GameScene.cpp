#include "GameScene.h"
#include"../SceneManager.h"

#include"../../Object/Player/Player.h"
#include"../../Object/Back/Back.h"
#include"../../Object/Ocean/Ocean.h"

void GameScene::Event()
{
	//カメラ処理
	Math::Vector3 playerPos;
	//m_playerに代入されているアドレス先はまだありますか？
	//expired 有効期限
	if (m_player.expired() == false)
	{
		playerPos = m_player.lock()->GetPos();
	}

	Math::Matrix transMat;
	Math::Vector3 cameraPos = { 0.0f,3.0f,-20.0f };
	transMat = Math::Matrix::CreateTranslation(cameraPos += playerPos);
	m_camera->SetCameraMatrix(transMat);
}

void GameScene::Init()
{
	//カメラの実体化
	m_camera = std::make_unique<KdCamera>();
	//平行光（ディレクショナルライト）								↓方向		↓色
	KdShaderManager::Instance().WorkAmbientController().SetDirLight({ 0,-1,0.1f }, { 2,2,2 });

	////画面全体が暗いときに触る
	////環境光(アンビエントライト)※デフォルト値は0.3					    				 ↓↓↓↓
	//KdShaderManager::Instance().WorkAmbientController().SetAmbientLight({ 1,1,1,1 });

	//フォグ(霧)													 ↓距離 ↓高さ
	KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false, false);
	//距離フォグ														↓霧の色　↓密度
	KdShaderManager::Instance().WorkAmbientController().SetDistanceFog({ 1,1,1 }, 0.05);
	//高さフォグ													  ↓色　   ↓上 ↓下 ↓カメラとの距離
	KdShaderManager::Instance().WorkAmbientController().SetheightFog({ 0,0.3f,1 }, -20, -50, 0);

	//プレイヤー
	std::shared_ptr<Player> player;
	//プレイヤークラスを実体化（実体化したアドレスをポインタへ）
	player = std::make_shared<Player>();
	//オブジェクトリストに登録
	m_objList.push_back(player);
	m_player = player;

	//ステージ
	//①ポインタを作る（作っただけで使い物にならない）
	std::shared_ptr<Ocean> ocean;
	//②ステージクラスを実体化（実体化したアドレスをポインタへ）
	ocean = std::make_shared<Ocean>();

	//③オブジェクトリストに登録
	m_objList.push_back(ocean);

	//背景==============================================
	std::shared_ptr<Back> back;
	//背景クラスを実体化（実体化したアドレスをポインタへ）
	back = std::make_shared<Back>();
	//オブジェクトリストに登録
	m_objList.push_back(back);
}
