#pragma once

class Player;

class Mousehit : public KdGameObject
{
public:
	Mousehit() { Init(); }
	virtual ~Mousehit()		override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
	void SetTarget(std::weak_ptr<Player> _target);

private:
	std::shared_ptr<KdModelWork> m_spModel = nullptr;

	std::weak_ptr<Player> m_target;

	Math::Vector3 m_pos;
};