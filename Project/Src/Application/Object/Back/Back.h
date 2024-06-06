#pragma once

class Back : public KdGameObject
{
public:
	Back() { Init(); }
	~Back(){}

	void DrawUnLit()override;
	void Init()override;

private:
	KdSquarePolygon m_polygon;
};