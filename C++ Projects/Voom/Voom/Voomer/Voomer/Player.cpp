#include "Player.h"

#include <cmath>

Player::Player(ViewRenderer* renderer, int ID)
    : m_PlayerID(ID), m_FOV(90), m_RotationSpeed(4), m_MoveSpeed(2)
{
    
}

Player::~Player()
{
    
}

void Player::SetXPosition(int xPos)
{
    m_XPosition = xPos;
}

void Player::SetYPosition(int yPos)
{
    m_YPosition = yPos;
}

void Player::SetAngle(int angle)
{
    m_Angle = angle;
}

int Player::GetXPosition()
{
    return m_XPosition;
}

int Player::GetYPosition()
{
    return m_YPosition;
}

Angle Player::GetAngle()
{
    return m_Angle;
}

int Player::GetID()
{
    return m_PlayerID;
}

Angle Player::AngleToVertex(Vertex &vertex)
{
    float Vdx = vertex.xPos - m_XPosition;
    float Vdy = vertex.yPos - m_YPosition;
    
    Angle VertexAngle(atan2f(Vdy, Vdx) * 180 / PI);
    
    return VertexAngle;
}

bool Player::ClipVertexesInFOV(Vertex &V1, Vertex &V2, Angle &V1Angle, Angle &V2Angle)
{
    V1Angle = AngleToVertex(V1);
    V2Angle = AngleToVertex(V2);
    
    Angle V1ToV2Span = V1Angle - V2Angle;
    
    if (V1ToV2Span >= 180)
    {
        return false;
    }
    
    V1Angle = V1Angle - m_Angle;
    V2Angle = V1Angle - m_Angle;
    
    Angle HalfFOV = m_FOV / 2;
    
    Angle V1Moved = V1Angle + HalfFOV;
    
    if (V1Moved > m_FOV)
    {
        Angle V1MovedAngle = V1Moved - m_FOV;
        
        if (V1MovedAngle >= V1ToV2Span)
        {
            return false;
        }
        
        V1Angle = HalfFOV;
    }
    
    Angle V2Moved = V2Angle + HalfFOV;
    
    if (V2Moved > m_FOV)
    {
        V2Angle = -HalfFOV;
    }
    
    V1Angle += 90;
    V2Angle += 90;
    
    return true;
}

void Player::RotateLeft()
{
    m_Angle += (0.1875f * m_RotationSpeed);
}

void Player::RotateRight()
{
    m_Angle -= (0.1875f * m_RotationSpeed);
}

void Player::RenderAutoMap()
{
    m_ViewRenderer->SetDrawColor(255, 0, 0);
    m_ViewRenderer->DrawLine(m_XPosition, m_YPosition, m_XPosition + 5, m_YPosition + 5);
}
