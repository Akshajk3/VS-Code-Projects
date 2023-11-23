#pragma once

class Player
{
public:
	Player(int iID);
	~Player();

	void SetXPosition(int XPosition);
	void SetYPosition(int YPosition);
	void SetAngle(int Angle);

	int GetID();
	int GetXPosition();
	int GetYPosition();
	int GetAngle();

protected:
	int m_PlayerID;
	int m_XPosition;
	int m_YPosition;
	int m_Angle;
};