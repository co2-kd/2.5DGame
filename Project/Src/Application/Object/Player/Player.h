#pragma once

class Player : public KdGameObject
{
public:
	Player() { Init(); }
	virtual ~Player()override {}

	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void Init()override;

	void MousePos();

	void SetCamera(std::shared_ptr<KdCamera>camera) { m_wpCamera = camera; }
	void SetTarget(std::shared_ptr<KdGameObject> _target) { m_target = _target; }

	void ImguiUpdate()override;
private:

	std::shared_ptr<KdModelData> m_model = nullptr;

	std::weak_ptr<KdCamera> m_wpCamera;
	std::weak_ptr<KdGameObject> m_target;

	Math::Vector3 m_pos;

	Math::Vector3 m_TargetPos;

	Math::Vector3 m_dir;

	float m_thrust;
	float m_thrustspeed;
	float m_thrustoffspeed;
	float m_thrustMax;
	float m_thrustMin;

	Math::Vector3 m_inertia;
	Math::Vector3 m_modeldir;

	float m_speed;

	float m_anime;

	float m_scale;

	float m_gravity;

	float m_rotateX;
	float m_rotateY;
	float m_rotateZ;

	float m_deg;
	float m_targetdeg;
	float m_rad;

	float m_cooltime;

	POINT m_mouse;

	//UŒ‚•ûŒü
	Math::Vector3 m_attackDir;
	//‰Ÿ‚µ‚Á‚Ï–h~
	bool m_keyFlg;
};