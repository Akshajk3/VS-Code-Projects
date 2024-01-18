#pragma once

class Player
{
public:
	Player(int ID);
	~Player();

	void SetXPosition(int XPos);
	void SetYPosition(int YPos);
	void SetAngle(int Angle);

	int GetID();
	int GetXPosition();
	int GetYPosition();
	int GetAngle();

protected:
	int m_XPosition;
	int m_YPosition;
	int m_Angle;
	int m_ID;
};