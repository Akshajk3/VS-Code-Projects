#include "ViewRenderer.h"

#include "Map.h"
#include "Player.h"

#define PI 3.14159265358979f

ViewRenderer::ViewRenderer(SDL_Renderer* renderer)
    : m_Renderer(renderer), m_AutoMapScaleFactor(15)
{
    
}

ViewRenderer::~ViewRenderer()
{
    
}

void ViewRenderer::Init(Map *map, Player *player)
{
    m_Map = map;
    m_Player = player;
    
    SDL_RenderGetLogicalSize(m_Renderer, &m_RenderXSize, &m_RenderYSize);
    --m_RenderXSize;
    --m_RenderYSize;
}

void ViewRenderer::Render(bool IsAutomap)
{
    if (IsAutomap)
    {
        RenderAutoMap();
    }
    else
    {
        Render3DView();
    }
    
    SDL_RenderPresent(m_Renderer);
}

void ViewRenderer::InitFrame()
{
    SetDrawColor(0, 0, 0);
    SDL_RenderClear(m_Renderer);
}

void ViewRenderer::AddWallInFOV(Seg seg, Angle V1Angle, Angle V2Angle)
{
    int V1XScreen = AngleToScreen(V1Angle);
    int V2XScreen = AngleToScreen(V2Angle);
    
    SDL_RenderDrawLine(m_Renderer, V1XScreen, 0, V1XScreen, m_RenderYSize);
    SDL_RenderDrawLine(m_Renderer, V2XScreen, 0, V2XScreen, m_RenderYSize);
}

void ViewRenderer::RenderAutoMap()
{
    m_Map->RenderAutoMap();
    m_Player->RenderAutoMap();
}

void ViewRenderer::Render3DView()
{
    m_Map->Render3DView();
}

void ViewRenderer::SetDrawColor(int R, int G, int B)
{
    SDL_SetRenderDrawColor(m_Renderer, R, G, B, SDL_ALPHA_OPAQUE);
}

void ViewRenderer::DrawRect(int X1, int Y1, int X2, int Y2)
{
    SDL_Rect Rect = {
        RemapXToScreen(X1),
        RemapYToScreen(Y1),
        RemapXToScreen(X2) - RemapXToScreen(X1) + 1,
        RemapYToScreen(Y2) - RemapYToScreen(Y1) + 1
    };
    
    SDL_RenderDrawRect(m_Renderer, &Rect);
}

void ViewRenderer::DrawLine(int X1, int Y1, int X2, int Y2)
{
    SDL_RenderDrawLine(m_Renderer,
                       RemapXToScreen(X1),
                       RemapYToScreen(Y1),
                       RemapXToScreen(X2),
                       RemapYToScreen(Y2));
}

int ViewRenderer::RemapXToScreen(int XPosition)
{
    return (XPosition + (-m_Map->GetXMin())) / m_AutoMapScaleFactor;
}

int ViewRenderer::RemapYToScreen(int YPosition)
{
    return m_RenderYSize - (YPosition + (-m_Map->GetYMin())) / m_AutoMapScaleFactor;
}

int ViewRenderer::AngleToScreen(Angle angle)
{
    int X = 0;
    
    if (angle > 90)
    {
        angle -= 90;
        X = 160 - round(tanf(angle.GetValue() * PI / 180.0f) * 160);
    }
    else
    {
        angle = 90 - angle.GetValue();
        X = round(tanf(angle.GetValue() * PI / 180.0f) * 160);
        X += 160;
    }
    
    return X;
}