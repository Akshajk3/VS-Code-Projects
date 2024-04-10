#pragma once

#include "Angle.h"
#include "DataTypes.h"
#include "ViewRenderer.h"

class Player
{
public:
    Player(ViewRenderer* renderer, int ID);
    ~Player();
    
    void SetXPosition(int xPos);
    void SetYPosition(int yPos);
    void SetAngle(int angle);
    void RotateLeft();
    void RotateRight();
    void RenderAutoMap();
    
    int GetID();
    int GetXPosition();
    int GetYPosition();
    
    Angle GetAngle();
    Angle AngleToVertex(Vertex& vertex);
    
    bool ClipVertexesInFOV(Vertex& V1, Vertex& V2, Angle& V1Angle, Angle& V2Angle);
    
protected:
    int m_PlayerID;
    int m_XPosition;
    int m_YPositoin;
    int m_FOV;
    int m_RotationSpeed;
    int m_MoveSpeed;
    
    Angle m_Angle;
    ViewRenderer* m_ViewRenderer;
};
