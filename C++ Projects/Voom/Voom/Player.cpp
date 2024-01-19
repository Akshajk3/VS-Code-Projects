#include "Player.h"

Player::Player(int ID)
	: m_ID(ID)
{
	
}

Player::~Player()
{

}

void Player::SetXPosition(int XPos)
{
	m_XPosition = XPos;
}

void Player::SetYPosition(int YPos)\
{
	m_YPosition = YPos;
}

void Player::SetAngle(int Angle)
{
	m_Angle = Angle;
}

int Player::GetXPosition()
{
	return m_XPosition;
}

int Player::GetYPosition()
{
	return m_YPosition;
}

int Player::GetAngle()
{
	return m_Angle;
}

int Player::GetID()
{
	return m_ID;
}
