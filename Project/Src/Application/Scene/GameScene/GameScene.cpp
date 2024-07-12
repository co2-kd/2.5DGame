#include "GameScene.h"
#include"../SceneManager.h"
#include"../../main.h"

#include"../../Object/Player/Player.h"
#include"../../Object/Back/Back.h"
#include"../../Object/Ocean/Ocean.h"
#include"../../Object/Mousehit/Mousehit.h"
#include"../../Object/Enemy/Enemy.h"
#include"../../Object/Cloud/Cloud.h"
#include"../../Object/Cloud2/Cloud2.h"
#include"../../Object/P_Bullet/P_Bullet.h"

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
	Math::Vector3 cameraPos = { 0.0f,50.0f,-200.0f };
	//Math::Vector3 cameraPos = { 0.0f,0.0f,-200.0f };
	if (playerPos.x > 1400.0f)
	{
		playerPos.x = 1400.0f;
	}
	else if (playerPos.x < -1400.0f)
	{
		playerPos.x = -1400.0f;
	}
	if (playerPos.y > 1200.0f)
	{
		playerPos.y = 1200.0f;
	}
	transMat = Math::Matrix::CreateTranslation(cameraPos += playerPos);
	Math::Matrix rotateMat;
	rotateMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(15));
	//rotateMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));
	Math::Matrix cameraMat;
	cameraMat = rotateMat * transMat;
	m_camera->SetCameraMatrix(cameraMat);

	m_mousehit.lock()->SetTarget(m_player);
	//m_player.lock()->SetTarget(m_mousehit);
	//if (Application::Instance().GetEnemyCnt() >= 5)
	//{
	//	SceneManager::Instance().SetNextScene
	//	(
	//		SceneManager::SceneType::
	//	);
	//}
}

void GameScene::Init()
{
	//カメラの実体化
	m_camera = std::make_unique<KdCamera>();	//視野角設定
	//m_camera = std::make_unique<KdCamera>();
	//平行光（ディレクショナルライト）								↓方向		↓色
	KdShaderManager::Instance().WorkAmbientController().SetDirLight({ 0,-1,0.1f }, { 3,3,3 });

	////画面全体が暗いときに触る
	////環境光(アンビエントライト)※デフォルト値は0.3					    				 ↓↓↓↓
	//KdShaderManager::Instance().WorkAmbientController().SetAmbientLight({ 1,1,1,1 });

	//フォグ(霧)													 ↓距離 ↓高さ
	KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false, false);
	//距離フォグ														↓霧の色　↓密度
	KdShaderManager::Instance().WorkAmbientController().SetDistanceFog({ 1,1,1 }, 0.05);
	//高さフォグ													  ↓色　   ↓上 ↓下 ↓カメラとの距離
	KdShaderManager::Instance().WorkAmbientController().SetheightFog({ 0,0.3f,1 }, -20, -50, 0);
	//mousehit
	std::shared_ptr<Mousehit> mousehit = std::make_shared<Mousehit>();
	mousehit->Init();
	mousehit->SetTarget(m_player);
	m_objList.push_back(mousehit);
	m_mousehit = mousehit;
	//プレイヤー
	std::shared_ptr<Player> player;
	//プレイヤークラスを実体化（実体化したアドレスをポインタへ）
	player = std::make_shared<Player>();
	player->Init();
	player->SetCamera(m_camera);
	player->SetTarget(mousehit);
	//オブジェクトリストに登録
	m_objList.push_back(player);
	m_player = player;

	//敵
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
	enemy->Init();
	enemy->SetTarget(player);
	enemy->SetPos({ 0,1000,0 });
	m_objList.push_back(enemy);
	std::shared_ptr<Enemy> enemy2 = std::make_shared<Enemy>();
	enemy2->Init();
	enemy2->SetTarget(player);
	enemy2->SetPos({ 1000,800,0 });
	m_objList.push_back(enemy2);
	std::shared_ptr<Enemy> enemy3 = std::make_shared<Enemy>();
	enemy3->Init();
	enemy3->SetTarget(player);
	enemy3->SetPos({ 1000,-800,0 });
	m_objList.push_back(enemy3);
	std::shared_ptr<Enemy> enemy4 = std::make_shared<Enemy>();
	enemy4->Init();
	enemy4->SetTarget(player);
	enemy4->SetPos({ -1000,800,0 });
	m_objList.push_back(enemy4);
	std::shared_ptr<Enemy> enemy5 = std::make_shared<Enemy>();
	enemy5->Init();
	enemy5->SetTarget(player);
	enemy5->SetPos({ -1000,-800,0 });
	m_objList.push_back(enemy5);

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
	//雲
	std::shared_ptr<Cloud> cloud = std::make_shared<Cloud>();
	cloud->SetScale({ 6000, 2000, 1 });
	cloud->SetPos({ 0, -1200, 970 });
	cloud->SetColor({1,1,1,0.8});
	cloud->Init();
	m_objList.push_back(cloud);
	std::shared_ptr<Cloud2> cloud2 = std::make_shared<Cloud2>();
	cloud2->SetScale({ 6000, 2000, 1 });
	cloud2->SetPos({ 0, -1000, 940 });
	cloud2->SetColor({ 1,1,1,0.8 });
	cloud2->Init();
	m_objList.push_back(cloud2);

	std::shared_ptr<Cloud> cloud3 = std::make_shared<Cloud>();
	cloud3->SetScale({ 6000, -1500, 1 });
	cloud3->SetPos({ 0, 900, 900 });
	cloud3->SetColor({ 1,1,1,1 });
	cloud3->Init();
	m_objList.push_back(cloud3);	
	std::shared_ptr<Cloud2> cloud4 = std::make_shared<Cloud2>();
	cloud4->SetScale({ -6000, -1500, 1 });
	cloud4->SetPos({ 0, 800, 700 });
	cloud4->SetColor({ 1,1,1,0.8 });
	cloud4->Init();
	m_objList.push_back(cloud4);	
	std::shared_ptr<Cloud2> cloud5 = std::make_shared<Cloud2>();
	cloud5->SetScale({ 6000, -700, 1 });
	cloud5->SetPos({ 0, 1000, -20 });
	cloud5->SetColor({ 1,1,1,0.7 });
	cloud5->Init();
	m_objList.push_back(cloud5);
	std::shared_ptr<Cloud2> cloud6 = std::make_shared<Cloud2>();
	cloud6->SetScale({ 6000, -1000, 1 });
	cloud6->SetPos({ 0, 1000, 100 });
	cloud6->SetColor({ 1,1,1,0.7 });
	cloud6->Init();
	m_objList.push_back(cloud5);
}
