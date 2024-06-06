#pragma once

class Ocean : public KdGameObject
{
public:
	Ocean() { Init(); }
	~Ocean() {}

	void Init()override;
	void DrawLit()override;

private:
	std::shared_ptr<KdModelData> m_model;

};