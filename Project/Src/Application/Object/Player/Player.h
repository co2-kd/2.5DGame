#pragma once

class Player : public KdGameObject
{
public:
	Player() { Init(); }
	~Player()override {}

	void Update()override;
	void DrawLit()override;
	void Init()override;
private:

	std::shared_ptr<KdModelData> m_model = nullptr;

	Math::Vector3 m_pos;

	float m_anime = 0;

	float m_dir = 1;

	float m_gravity = 0;
};