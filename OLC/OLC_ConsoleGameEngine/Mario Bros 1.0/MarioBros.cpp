//
//  main.cpp
//  MarioBros 1.2
//
//  Created by Santiago Vera on 28/08/20.
//  Copyright © 2020 Mistic_Lion. All rights reserved.
//

#include <iostream>
#include "olcConsoleGameEngineSDL.h"
using namespace std;

class Game : public olcConsoleGameEngine{
    
private:
    float cont=0;
    int cont2=0;
    int jumpcont=0;
    
    int TileSize=16;
    
    int VisibleTilesLong=16;
    int VisibleTilesHigh=15;
    
    float fPPosX=0;
    float fPPosY=(240-TileSize*2)-105;
    float fVelX=2;
    float fVelY=8;
    float fAccelX=0.9;
    float fAccelY=0.03;
    
    bool HasJumped=false;
    bool HasJumped2=false;
    
    float fCameraX=fPPosX;
    float fCameraY=0;
    
    bool bPlayerDirection=true;
    
    int MarioSpriteType=0;
    
    wstring TestSprite;
    
    struct PlayerSpriteObject{
        bool HasFliped=false;
        wstring Sprite;
        int SpriteWidth;
        int SpriteHeight;
    };
    
    vector<PlayerSpriteObject> MarioSprites;
    
    struct LevelObj{
        wstring Level;
        int WidthinTiles=16;
        int HeightinTiles=8;
    };
    
    LevelObj Level_1;
    
    struct BlockObj{
        wstring BlockSprite;
        float SpriteWidth=0;
        float SpriteHeight=0;
    };
    
    vector<BlockObj> BlockSprites;
    
    
public:
    
    Game(){
        
    }
    
    ~Game(){
        
    }
    
    void DrawSpriteFromString(wstring Sprite, int xPos, int yPos, int SpriteWidth=12, int SpriteHeight=16){
        
        for(int y=0; y<SpriteHeight; y++){
            for(int x=0; x<SpriteWidth; x++){
                int i=(y*SpriteWidth)+x;
                
                switch (Sprite[i]) {
                    case '.':
                        break;
                        
                    case 'r':
                        Draw(x+xPos, y+yPos, FG_RED);
                        break;
                        
                    case 'b':
                        Draw(x+xPos, y+yPos, FG_BLUE);
                        break;
                        
                    case 'c':
                        Draw(x+xPos, y+yPos, FG_CYAN);
                        break;
                        
                    case 'g':
                        Draw(x+xPos, y+yPos, FG_GREEN);
                        break;
                        
                    case 'w':
                        Draw(x+xPos, y+yPos, FG_WHITE);
                        break;
                        
                    case 'm':
                        Draw(x+xPos, y+yPos, FG_MAGENTA);
                        break;
                        
                    case 'p':
                        Draw(x+xPos, y+yPos, FG_BLACK);
                        break;
                        
                    case 'q':
                        Draw(x+xPos, y+yPos, FG_GREY);
                        break;
                        
                    case 'y':
                        Draw(x+xPos, y+yPos, FG_YELLOW);
                        break;
                        
                    case 'R':
                        Draw(x+xPos, y+yPos, FG_DARK_RED);
                        break;
                        
                    case 'B':
                        Draw(x+xPos, y+yPos, FG_DARK_BLUE);
                        break;
                        
                        
                    case 'C':
                        Draw(x+xPos, y+yPos, FG_DARK_CYAN);
                        break;
                        
                    case 'G':
                        Draw(x+xPos, y+yPos, FG_DARK_GREEN);
                        break;
                        
                    case 'M':
                        Draw(x+xPos, y+yPos, FG_DARK_MAGENTA);
                        break;
                        
                    case 'Y':
                        Draw(x+xPos, y+yPos, FG_DARK_YELLOW);
                        break;
                        
                    default:
                        break;
                }
                
            }
        }
    }
    
    void DrawLevel(wstring Level, int WidthinTiles, int HeightinTiles){
        for(int iy=0-TileSize; iy<VisibleTilesHigh*TileSize; iy++){
            for(int ix=0-TileSize; ix<VisibleTilesLong*TileSize; ix++){
                
                int ID=((((int)(iy+fCameraY))/TileSize)*WidthinTiles)+((ix+fCameraX)/TileSize);
                
                if(((ix+fCameraX)/TileSize)==(int)((ix+fCameraX)/TileSize) and ((iy+fCameraY)/16)==(int)((iy+fCameraY)/ 16)){
                    switch (Level_1.Level[ID]) {
                        case 'B':
                            DrawSpriteFromString(BlockSprites[0].BlockSprite, ix, iy, 16, 16);
                            break;
                        
                        default:
                            break;
                    }
                }
            }
        }
    }
    
    bool MirrorString(wstring &Sprite, bool &HasFliped, int SpriteWidth=12, int SpriteHeight=16){
        for(int y=0; y<SpriteHeight; y++){
            for(int x=0; x<SpriteWidth/2; x++){
                int i=(y*SpriteWidth)+x;
                int i2=(y*SpriteWidth)+(SpriteWidth-x-1);
                
                char Char1=Sprite[i];
                char Char2=Sprite[i2];
                
                Sprite[i] = Char2;
                Sprite[i2] = Char1;
                
            }
        }
        
        if(HasFliped)HasFliped=false;
        else if (!HasFliped) HasFliped=true;
        
        return true;
    }
    
    virtual bool OnUserCreate(){
        
        //Level Objects
        
        Level_1.Level += L".................................";
        Level_1.Level += L".................................";
        Level_1.Level += L".................................";
        Level_1.Level += L".................................";
        Level_1.Level += L".................................";
        Level_1.Level += L".................................";
        Level_1.Level += L".................................";
        Level_1.Level += L"....BBB................B....B....";
        Level_1.Level += L"................B...........B....";
        Level_1.Level += L"............................B....";
        Level_1.Level += L"............................B....";
        Level_1.Level += L"....B.........B.............B....";
        Level_1.Level += L"....B.....B........B........B....";
        Level_1.Level += L"....B.......................B....";
        Level_1.Level += L"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB";
        Level_1.WidthinTiles=33;
        Level_1.HeightinTiles=15;
        
        //Block Objects
        
        TestSprite += L"RrrrrrrrrpRrrrrR";
        TestSprite += L"rRRRRRRRRprRRRRp";
        TestSprite += L"rRRRRRRRRprRRRRp";
        TestSprite += L"rRRRRRRRRprRRRRp";
        TestSprite += L"rRRRRRRRRprpRRRp";
        TestSprite += L"rRRRRRRRRpRppppR";
        TestSprite += L"rRRRRRRRRprrrrrp";
        TestSprite += L"rRRRRRRRRprRRRRp";
        TestSprite += L"rRRRRRRRRprRRRRp";
        TestSprite += L"rRRRRRRRRprRRRRp";
        TestSprite += L"ppRRRRRRprRRRRRp";
        TestSprite += L"rrppRRRRprRRRRRp";
        TestSprite += L"rRrrpppprRRRRRRp";
        TestSprite += L"rRRRrrrprRRRRRRp";
        TestSprite += L"rRRRRRRprRRRRRpp";
        TestSprite += L"RppppppRrppppppR";
        BlockSprites.push_back({TestSprite, 16, 16});
        TestSprite.clear();
        
        //Player Objects
        
        TestSprite += L"...rrrrr....";
        TestSprite += L"...rrrrr....";
        TestSprite += L"..rrrrrrrrr.";
        TestSprite += L"..pppYYpY...";
        TestSprite += L".pYpYYYpYYY.";
        TestSprite += L".pYppYYYpYYY";
        TestSprite += L"..pYYYYpppp.";
        TestSprite += L"...YYYYYY...";
        TestSprite += L"..rrbrrbrr..";
        TestSprite += L".rrrbrrbrrr.";
        TestSprite += L"rrrrbbbbrrrr";
        TestSprite += L"YYrbybbybrYY";
        TestSprite += L"YYYbbbbbbYYY";
        TestSprite += L"YYbbbbbbbbYY";
        TestSprite += L"..bbb..bbb..";
        TestSprite += L".qqq....qqq.";
        TestSprite += L"qqqq....qqqq";
        MarioSprites.push_back({false, TestSprite, 12, 16});
        TestSprite.clear();
        
        TestSprite += L".............YYYY";
        TestSprite += L"......rrrrrr.YYYY";
        TestSprite += L".....rrrrrrrrrYYY";
        TestSprite += L".....pppYYpYYRRRR";
        TestSprite += L"....pYpYYYpYYRRRR";
        TestSprite += L"....pYppYYYpYYYRR";
        TestSprite += L"....ppYYYYpppppR.";
        TestSprite += L"......YYYYYYYRR..";
        TestSprite += L"..rrrrrbrrrbRR...";
        TestSprite += L".rrrrrrrbrrrbb.qq";
        TestSprite += L"YYrrrrrrbbbbbb.qq";
        TestSprite += L"YYYYbbrbbybbybqqq";
        TestSprite += L".YYqbbbbbbbbbbqqq";
        TestSprite += L"..qqqbbbbbbbbbqqq";
        TestSprite += L".qqqbbbbbbbb.....";
        TestSprite += L".qq.bbbbb........";
        MarioSprites.push_back({false, TestSprite, 17, 16});
        TestSprite.clear();
        
        return true;
    }
    
    bool MoveRight(float XSpeed=2, float YSpeed=8){
        if(GetKey(VK_D).bHeld){
            if(fPPosX<ScreenWidth()/2 or fCameraX>=((Level_1.WidthinTiles)*TileSize)-ScreenWidth()){
                if(fPPosX+MarioSprites[MarioSpriteType].SpriteWidth<ScreenWidth())fPPosX = fPPosX+XSpeed;
            }
            if(fPPosX>=ScreenWidth()/2 and fCameraX<((Level_1.WidthinTiles)*TileSize)-ScreenWidth()) fCameraX = fCameraX+XSpeed;
        }
        return true;
    }
    
    bool MoveLeft(float XSpeed=2, float YSpeed=8){
        if(GetKey(VK_A).bHeld){
            if(fPPosX>0 and fPPosX>ScreenWidth()/2)fPPosX = fPPosX-XSpeed;
            if(fCameraX>0 and fPPosX<(ScreenWidth()/2)+1)fCameraX = fCameraX-XSpeed;
        }
        if(GetKey(VK_A).bHeld and fCameraX<=0 and fPPosX>0){
            fPPosX = fPPosX-XSpeed;
        }
        return true;
    }
    
    void MoveMario(float XSpeed=2, float YSpeed=8){
        if(GetKey(VK_W).bHeld){
            fPPosY++;
        }
        if(GetKey(VK_SPACE).bPressed and ColisionFall()){
            HasJumped=true;
            HasJumped2=true;
        }
        if(HasJumped){
            if(!ColisionFall() or jumpcont<5) ControlJumpSpeed();
            if(ColisionFall() and jumpcont>=5){
                fVelY=8;
                HasJumped=false;
                jumpcont=0;
            }
        }
        
        //if(!ColisionLine(-1, 1)){
          //  MoveRight();
       // }
       // MoveLeft();
        
        if (!ColisionMoveRight()) MoveRight();
        MoveLeft();
        
        
        //if(ColisionLine(-1, -TileSize)) cout<<"Colisiona Derecha";
        
        //while(ColisionLine(-1)) fPPosX--;
        //while(ColisionLine(-1, -(TileSize-2))) fPPosX++;
        //while(ColisionFall(-(TileSize-2))){
           // fPPosY++;
           // HasJumped=false;
           // HasJumped2=false;
        //}
    }
    
    bool ColisionDetection(float fPPosX, float fPPosY, int nTx, int nTy, int ID){
        if(fPPosY+16>nTy and fPPosY<=nTy+1){
            if (fPPosX<nTx+12 and fPPosX+12>nTx+1) return true;
        }
        return false;
    }
    
    bool ColisionRight(float fPPosX, float fPPosY, int nTx, int nTy, int ID){
        if(fPPosY+16>nTy and fPPosY<nTy+16){
            if (fPPosX<nTx and fPPosX+12>=nTx-1) return true;
        }
        return false;
    }
    
    bool ColisionFall(int yVariation=0, int xVariation=0){
        for(int iy=0-TileSize; iy<VisibleTilesHigh*TileSize; iy++){
            for(int ix=0-TileSize; ix<VisibleTilesLong*TileSize; ix++){
                
                int ID=((((int)(iy+fCameraY))/TileSize)*Level_1.WidthinTiles)+((ix+fCameraX)/TileSize);
                
                if(((ix+fCameraX)/TileSize)==(int)((ix+fCameraX)/TileSize) and ((iy+fCameraY)/16)==(int)((iy+fCameraY)/ 16)){
                    switch (Level_1.Level[ID]) {
                        case 'B':
                            if(ColisionDetection(fPPosX, fPPosY, ix, iy, 0)){
                                Draw(ix, iy, FG_YELLOW);
                                return true;
                            }
                            break;
                            
                        default:
                            break;
                    }
                }
            }
        }
        
        return false;
    }
    
    bool ColisionMoveRight(int yVariation=0, int xVariation=0){
        for(int iy=0-TileSize; iy<VisibleTilesHigh*TileSize; iy++){
            for(int ix=0-TileSize; ix<VisibleTilesLong*TileSize; ix++){
                
                int ID=((((int)(iy+fCameraY))/TileSize)*Level_1.WidthinTiles)+((ix+fCameraX)/TileSize);
                
                if(((ix+fCameraX)/TileSize)==(int)((ix+fCameraX)/TileSize) and ((iy+fCameraY)/16)==(int)((iy+fCameraY)/ 16)){
                    switch (Level_1.Level[ID]) {
                        case 'B':
                            if(ColisionRight(fPPosX, fPPosY, ix, iy, 0)){
                                Draw(ix, iy, FG_GREEN);
                                return true;
                            }
                            break;
                            
                        default:
                            break;
                    }
                }
            }
        }
        
        return false;
    }
    
    void Fall(float Speed=3){
        for(int i=0; i<Speed; i++){
        if(!ColisionFall()){
            fPPosY ++;
            if(HasJumped)MarioSpriteType=1;
        }
        else if(ColisionFall()){
            MarioSpriteType=0;
            HasJumped2=false;
            HasJumped=false;
            fVelY=8;
            jumpcont=0;
        }
        }
    }
    
    bool ControlJumpSpeed(){
        jumpcont++;
        
        fVelY -= fVelY*fAccelY;
        
        if(fVelY<=0.1) fVelY=0;
        
        if(jumpcont<=10) fPPosY -= fVelY;
        
        if(HasJumped2 and jumpcont>10){
            if(GetKey(VK_SPACE).bHeld){
                fPPosY -= fVelY;
            }
        }
        
        if(GetKey(VK_SPACE).bReleased) HasJumped2=false;
        
        return true;
    }
    
    void ManageSpriteRotation(int ID){
        
        if(GetKey(VK_D).bPressed){
            bPlayerDirection=true;
        }
        else if(GetKey(VK_A).bPressed and !GetKey(VK_D).bHeld){
            bPlayerDirection=false;
        }
        else if(GetKey(VK_A).bHeld and GetKey(VK_D).bReleased){
            bPlayerDirection=false;
        }
        
        
    }
    
    void ManageGeneralRotation(bool GeneralRotation, int ID){
        if(GeneralRotation and MarioSprites[ID].HasFliped) MirrorString(MarioSprites[ID].Sprite, MarioSprites[ID].HasFliped, MarioSprites[ID].SpriteWidth, MarioSprites[ID].SpriteHeight);
        if(!GeneralRotation and !MarioSprites[ID].HasFliped) MirrorString(MarioSprites[ID].Sprite, MarioSprites[ID].HasFliped, MarioSprites[ID].SpriteWidth, MarioSprites[ID].SpriteHeight);
    }
    
    virtual bool OnUserUpdate(float fElapsedTime){
        cont ++;
        
        Fill(0, 0, ScreenWidth(), ScreenHeight(), FG_WHITE);
        
        MoveMario();
        
        DrawLevel(Level_1.Level, Level_1.WidthinTiles, Level_1.HeightinTiles);
        
        ManageSpriteRotation(MarioSpriteType);
        
        ManageGeneralRotation(bPlayerDirection, MarioSpriteType);
        
        DrawSpriteFromString(MarioSprites[MarioSpriteType].Sprite, fPPosX, fPPosY, MarioSprites[MarioSpriteType].SpriteWidth, MarioSprites[MarioSpriteType].SpriteHeight);
        
        Draw(fCameraX, fCameraY, FG_RED);
        
        Fall();
        
        return true;
    }
    
};

int main() {
    
    Game Juego;
    if(Juego.ConstructConsole(256, 240, 4, 4)){
        Juego.Start();
    }
    
}
