#pragma once
class Cloud2 : public KdGameObject
{
public:
	Cloud2() { /*Init();*/ }
	~Cloud2() {}

	void DrawUnLit()override;
	void Init()override;


	void SetScale(Math::Vector3 _scale) { m_scale = _scale; }
	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
	void SetColor(Math::Color _color) { m_color = _color; }

private:
	KdSquarePolygon m_polygon;
	Math::Vector3 m_scale;
	Math::Vector3 m_pos;
	Math::Color m_color = {1,1,1,1};
};