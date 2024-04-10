#pragma once

#include <SDL2/SDL.h>

#include "Angle.h"

#include "DataTypes.h"

class Map;
class Player;

class ViewRenderer
{
public:
    ViewRenderer(SDL_Renderer* renderer);
    ~ViewRenderer();
    
    void Init(Map* map, Player* player);
    void Render(bool IsAutomap);
    void AddWallInFOV(Seg seg, Angle V1Angle, Angle V2Angle);
    void InitFrame();
    void SetDrawColor(int R, int G, int B);
    void DrawRect(int X1, int Y1, int X2, int Y2);
    void DrawLine(int X1, int Y1, int X2, int Y2);
    
protected:
    void RenderAutoMap();
    void Render3DView();
    
    int AngleToScreen(Angle angle);
    int RemapXToScreen(int XPosition);
    int RemapYToScreen(int YPosition);
    
    int m_RenderXSize;
    int m_RenderYSize;
    int m_AutoMapScaleFactor;
    
    Map* m_Map;
    Player* m_Player;
    
    SDL_Renderer* m_Renderer;
};
