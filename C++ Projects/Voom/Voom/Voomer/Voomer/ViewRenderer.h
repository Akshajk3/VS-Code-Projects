#pragma once

#include <SDL2/SDL.h>
#include <map>
#include<string>
#include <list>

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

    struct SolidSegmentRange
    {
        int XStart;
        int XEnd;
    };

    struct SoldSegmentData
    {
        Seg& seg;
        int XStart;
        int XEnd;
    };


    void RenderAutoMap();
    void Render3DView();
    void DrawSolidWall(SoldSegmentData &visibleSeg);

    void ClipSolidWalls(Seg& seg, int V1XScreen, int V2XScreen);
    void StoreWallRange(Seg& seg, int V1XScreen, int V2XScreen);
    
    int AngleToScreen(Angle angle);
    int RemapXToScreen(int XPosition);
    int RemapYToScreen(int YPosition);
    
    int m_RenderXSize;
    int m_RenderYSize;
    int m_AutoMapScaleFactor;
    
    SDL_Color GetWallColor(std::string textureName);

    Map* m_Map;
    Player* m_Player;
    
    SDL_Renderer* m_Renderer;

    std::list<SolidSegmentRange> m_SolidWallRanges;
    std::map<std::string, SDL_Color> m_WallColor;
};
