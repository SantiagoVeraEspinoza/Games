//
//  main.cpp
//  FPS
//
//  Created by Santiago Vera on 03/08/20.
//  Copyright © 2020 Mistic_Lion. All rights reserved.
//

#include "olcConsoleGameEngineSDL.h"
#include <math.h>
using namespace std;

class Demo : public olcConsoleGameEngine{
    
private:
    
    wstring Map;
    
    float fPlayerX = 8.0f;
    float fPlayerY = 8.0f;
    float fPlayerAngle = 0.0f;
    
    
    int nMapWidth = 32;
    int nMapHeight = 32;
    
    float fFOV = M_PI/5.0f;
    
    float fDepthDistance = 20.0f;
    
public:
    
    Demo(){
        
    }
    
    ~Demo(){
        
    }
    
    virtual bool OnUserCreate(){
        
        Map += L"################################";
        Map += L"#..............##..............#";
        Map += L"#..............##..............#";
        Map += L"#..............##..............#";
        Map += L"#..............#...............#";
        Map += L"#.......##.....#.....#####.....#";
        Map += L"#..............#.....#.........#";
        Map += L"#....#...#...........#...#.....#";
        Map += L"#....#...#...............#.....#";
        Map += L"#....#...#...........#...#.....#";
        Map += L"#....#..##...........#####.....#";
        Map += L"#..............................#";
        Map += L"#..............................#";
        Map += L"#......##########..............#";
        Map += L"#..............................#";
        Map += L"#...............#######....#####";
        Map += L"#######..........##.........####";
        Map += L"#..............................#";
        Map += L"#...............#..............#";
        Map += L"#...............#..............#";
        Map += L"#..............................#";
        Map += L"#....##................###.....#";
        Map += L"#....#.........#...............#";
        Map += L"#....#...#...........#...#.....#";
        Map += L"#....#...#...........#...#.....#";
        Map += L"#....#...#...........#...#.....#";
        Map += L"#....#####...........#####.....#";
        Map += L"#..............................#";
        Map += L"#..............................#";
        Map += L"#..............................#";
        Map += L"#..............................#";
        Map += L"################################";
        
        return true;
    }
    
    void DrawWall(){
        
        for (int x=0; x<ScreenWidth(); x++){
            
            float fRayAngle = (fPlayerAngle-fFOV/2.0f)+(((float)x/(float)ScreenWidth())*fFOV);
            
            float fDistanceToWall = 0.0f;
            bool bHitWall = false;
            
            float fEyeX = sinf(fRayAngle);
            float fEyeY = cosf(fRayAngle);
            
            while (!bHitWall and fDistanceToWall<fDepthDistance){
                
                fDistanceToWall += 0.005f;
                
                int nTestX = (int)(fPlayerX+fEyeX*fDistanceToWall);
                int nTestY = (int)(fPlayerY+fEyeY*fDistanceToWall);
                
                if(nTestX<0 or nTestX>=nMapWidth or nTestY<0 or nTestY>=nMapHeight){
                    bHitWall = true;
                    fDistanceToWall=fDepthDistance;
                }
                else{
                    if(Map[nTestY*nMapWidth+nTestX] == '#'){
                        bHitWall = true;
                    }
                }
            }
            
            int nCeiling = (float)(ScreenHeight()/2.0) - (ScreenHeight()/((float)fDistanceToWall));
            int nFloor = ScreenHeight()-nCeiling;
            
            short nShade = FG_WHITE;
            
            if(fDistanceToWall < fDepthDistance/3.0f) nShade=FG_WHITE;
            else if(fDistanceToWall < fDepthDistance/2.0f) nShade=FG_GREY;
            else if(fDistanceToWall < fDepthDistance) nShade=FG_DARK_GREY;
            
            for(int y=0; y<ScreenHeight(); y++){
                if (y<nCeiling) Draw(x,y,FG_BLACK);
                else if (y>=nCeiling and y<=nFloor) Draw(x,y,nShade);
                else Draw(x,y,FG_BLACK);
                
            }
            
        }
        
    }
    
    void MovePlayer(){
        if(GetKey(VK_W).bHeld){
            fPlayerX += sinf(fPlayerAngle)*0.452;
            fPlayerY += cosf(fPlayerAngle)*0.452;
            
            if(Map[(int)fPlayerY*nMapWidth+(int)fPlayerX] == '#'){
                fPlayerX -= sinf(fPlayerAngle)*0.452;
                fPlayerY -= cosf(fPlayerAngle)*0.452;
            }
        }
        if(GetKey(VK_S).bHeld){
            fPlayerX -= sinf(fPlayerAngle)*0.452;
            fPlayerY -= cosf(fPlayerAngle)*0.452;
            
            if(Map[(int)fPlayerY*nMapWidth+(int)fPlayerX] == '#'){
                fPlayerX += sinf(fPlayerAngle)*0.452;
                fPlayerY += cosf(fPlayerAngle)*0.452; 
            }
        }
        if(GetKey(VK_A).bHeld){
            fPlayerX -= cosf(fPlayerAngle)*0.252;
            fPlayerY += sinf(fPlayerAngle)*0.252;
            
            if(Map[(int)fPlayerY*nMapWidth+(int)fPlayerX] == '#'){
                fPlayerX += cosf(fPlayerAngle)*0.252;
                fPlayerY -= sinf(fPlayerAngle)*0.252;
            }
        }
        if(GetKey(VK_D).bHeld){
            fPlayerX += cosf(fPlayerAngle)*0.252;
            fPlayerY -= sinf(fPlayerAngle)*0.252;
            
            if(Map[(int)fPlayerY*nMapWidth+(int)fPlayerX] == '#'){
                fPlayerX -= cosf(fPlayerAngle)*0.252;
                fPlayerY += sinf(fPlayerAngle)*0.252;
            }
        }
        if(GetKey(VK_LEFT).bHeld){
            fPlayerAngle -= (0.1015f);
        }
        if(GetKey(VK_RIGHT).bHeld){
            fPlayerAngle += (0.1015f);
        }
    }
    
    
    void GameMethod(){
        Fill(0, 0, ScreenWidth(), ScreenHeight(), FG_BLACK);
        
        DrawWall();
        MovePlayer();
        
    }
    
    virtual bool OnUserUpdate(float fElapsedTime){
        
        GameMethod();
        
        return true;
    }
};


int main(){
    
    Demo Juego;
    
    if (Juego.ConstructConsole(320, 240, 4, 4)){
        Juego.Start();
    }
    
}
