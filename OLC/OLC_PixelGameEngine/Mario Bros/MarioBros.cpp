//
//  main.cpp
//  MarioBros 1.2
//
//  Created by Santiago Vera on 28/08/20.
//  Copyright © 2020 Mistic_Lion. All rights reserved.
//

#include <iostream>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#define OLC_PGE_GAMEPAD
#include "olcPGEX_Gamepad.h"

using namespace std;

class Game : public olc::PixelGameEngine {

private:
    float cont = 0;
    int cont2 = 0;
    int jumpcont = 0;
    int animcont = 0;
    float AnimVel = 15;

    int TileSize = 16;

    int VisibleTilesLong = 16;
    int VisibleTilesHigh = 12;

    float fPPosX = 10;
    float fPPosY = (240 - TileSize * 2) - 105;
    float fTilePPosX = 0;
    float fTilePPosY = 0;
    float fLastTilePPosX = fTilePPosX;
    float fLastTilePPosY = fTilePPosY;
    float fVelX = 0;
    float fVelY = 0;
    float fAccelX = 0.9;
    float fAccelY = 0.03;
    float NewVel = 0;
    float MaxSideSpeed = 10;
    float MaxJumpSpeed = 2;

    bool HasJumped = false;
    bool HasLeftGround = false;
    bool HasTouchedCeiling = false;
    bool PlayerIsOnGround = false;

    float fCameraX = 0;
    float fCameraY = 5;

    float fOffSetX = 0;
    float fOffSetY = 0;

    bool bPlayerDirection = true;

    int MarioSpriteType = 0;

    //Controller Variables
    bool RightDPad = false;
    bool LeftDPad = false;

    bool StickRight = false;
    bool StickLeft = false;

    bool ButtonAHeld = false;
    bool ButtonATouch = false;
    bool ButtonAReleased = false;
    bool ButtonBHeld = false;
    bool ButtonBTouch = false;
    bool ButtonBReleased = false;

    bool ButtonX = false;
    bool ButtonY = false;

    //End of Controller Variables

    wstring TestSprite;

    struct PlayerSpriteObject {
        bool HasFliped = false;
        wstring Sprite;
        int SpriteWidth;
        int SpriteHeight;
    };

    vector<PlayerSpriteObject> MarioSprites;

    struct LevelObj {
        wstring Level;
        int WidthinTiles = 16;
        int HeightinTiles = 8;
    };

    LevelObj Level_1;

    struct BlockObj {
        wstring BlockSprite;
        float SpriteWidth = 0;
        float SpriteHeight = 0;
    };

    vector<BlockObj> BlockSprites;


public:

    Game() {

    }

    ~Game() {

    }

    olc::GamePad* gamepad = nullptr;

    void DrawSpriteFromString(wstring Sprite, int xPos, int yPos, int SpriteWidth = 12, int SpriteHeight = 16) {

        for (int y = 0; y < SpriteHeight; y++) {
            for (int x = 0; x < SpriteWidth; x++) {
                int i = (y * SpriteWidth) + x;

                switch (Sprite[i]) {
                case '.':
                    break;

                case 'r':
                    Draw(x + xPos, y + yPos, olc::RED);
                    break;

                case 'b':
                    Draw(x + xPos, y + yPos, olc::BLUE);
                    break;

                case 'c':
                    Draw(x + xPos, y + yPos, olc::CYAN);
                    break;

                case 'g':
                    Draw(x + xPos, y + yPos, olc::GREEN);
                    break;

                case 'w':
                    Draw(x + xPos, y + yPos, olc::WHITE);
                    break;

                case 'm':
                    Draw(x + xPos, y + yPos, olc::MAGENTA);
                    break;

                case 'p':
                    Draw(x + xPos, y + yPos, olc::BLACK);
                    break;

                case 'q':
                    Draw(x + xPos, y + yPos, olc::GREY);
                    break;

                case 'y':
                    Draw(x + xPos, y + yPos, olc::YELLOW);
                    break;

                case 'R':
                    Draw(x + xPos, y + yPos, olc::DARK_RED);
                    break;

                case 'B':
                    Draw(x + xPos, y + yPos, olc::DARK_BLUE);
                    break;


                case 'C':
                    Draw(x + xPos, y + yPos, olc::DARK_CYAN);
                    break;

                case 'G':
                    Draw(x + xPos, y + yPos, olc::DARK_GREEN);
                    break;

                case 'M':
                    Draw(x + xPos, y + yPos, olc::DARK_MAGENTA);
                    break;

                case 'Y':
                    Draw(x + xPos, y + yPos, olc::DARK_YELLOW);
                    break;

                default:
                    break;
                }

            }
        }
    }

    void DrawLevel(wstring Level, int WidthinTiles, int HeightinTiles, float OffSetX = 0, float OffSetY = 0) {
        int TileX, TileY = 0;

        fLastTilePPosX = fTilePPosX;
        fLastTilePPosY = fTilePPosY;

        MoveMario();


        //cout << fTilePPosX + 1 << endl;

        //cout << fTilePosX << " " << fTilePosY << endl;
        for (int iy = 0; iy < Level_1.HeightinTiles; iy++) {
            for (int ix = 0; ix < Level_1.WidthinTiles; ix++) {

                int ID = ((iy * WidthinTiles) + (ix));

                ResolveCamera();

                TileX = (ix * TileSize) - int(OffSetX * TileSize);
                TileY = (iy * TileSize) - int(OffSetY * TileSize);

                fPPosX = (fTilePPosX * TileSize) - (fCameraX * TileSize);
                fPPosY = (fTilePPosY * TileSize) - (fCameraY * TileSize);

                if (ID< Level_1.Level.size() and ix<int(VisibleTilesLong + 1 +(OffSetX)) and 
                    ix>int((OffSetX)-2)) {
                    switch (Level_1.Level[ID]) {
                    case 'B':
                        //if (trunc(fTilePPosX + 1) == ix and ) cout << "Colision" << endl;
                        DoColisions(ix, iy);

                        DrawSpriteFromString(BlockSprites[0].BlockSprite, TileX, TileY, 16, 16);
                        //Draw({TileX, TileY}, olc::YELLOW);
                        //FillRect({TileX, TileY}, { TileSize, TileSize }, olc::RED);
                        break;

                    default:
                        break;
                    }
                }
            }
        }

        //cout << fTilePPosX << " " << fCameraX << " " << fPPosX << endl;

        AnimateRunning(AnimVel);

        //FillRect({ int(fPPosX), int(fPPosY) }, { TileSize, TileSize }, olc::GREEN);

        if (MarioSpriteType == 0) DrawSpriteFromString(MarioSprites[MarioSpriteType].Sprite, 2 + fPPosX, fPPosY,
            MarioSprites[MarioSpriteType].SpriteWidth, MarioSprites[MarioSpriteType].SpriteHeight);
        else if (MarioSpriteType > 0) DrawSpriteFromString(MarioSprites[MarioSpriteType].Sprite, fPPosX, fPPosY,
            MarioSprites[MarioSpriteType].SpriteWidth, MarioSprites[MarioSpriteType].SpriteHeight);
    }

    bool MirrorString(wstring& Sprite, bool& HasFliped, int SpriteWidth = 12, int SpriteHeight = 16) {
        for (int y = 0; y < SpriteHeight; y++) {
            for (int x = 0; x < SpriteWidth / 2; x++) {
                int i = (y * SpriteWidth) + x;
                int i2 = (y * SpriteWidth) + (SpriteWidth - x - 1);

                char Char1 = Sprite[i];
                char Char2 = Sprite[i2];

                Sprite[i] = Char2;
                Sprite[i2] = Char1;

            }
        }

        if (HasFliped)HasFliped = false;
        else if (!HasFliped) HasFliped = true;

        return true;
    }

    virtual bool OnUserCreate() {
        olc::GamePad::init();

        //Level Objects

        Level_1.Level += L"...................................................................................................";
        Level_1.Level += L"...................................................................................................";
        Level_1.Level += L"...................................................................................................";
        Level_1.Level += L"...................................................................................................";
        Level_1.Level += L"...................................................................................................";
        Level_1.Level += L"..............BB...................................................................................";
        Level_1.Level += L"...................................................................................................";
        Level_1.Level += L"...................................................................................................";
        Level_1.Level += L"...................................................................................................";
        Level_1.Level += L"..............BB...................................................................................";
        Level_1.Level += L"...................................................................................................";
        Level_1.Level += L"..........................................BBB.....BBB.........BBB...........B......................";
        Level_1.Level += L".......................B.............BBB................BB............BBB..............BBB....B..B.";
        Level_1.Level += L".........BB....................BB................B................................B...........B..B.";
        Level_1.Level += L"..............................................................................................B..B.";
        Level_1.Level += L".........................B....................................................................B..B.";
        Level_1.Level += L"B....B.BBBBBB......B.....B....................................................................B..B.";
        Level_1.Level += L"B....B.............B.....B....................................................................B..B.";
        Level_1.Level += L"B....B.............B.....B....................................................................B..BB";
        Level_1.Level += L"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB";
        Level_1.WidthinTiles = 99;
        Level_1.HeightinTiles = 20;

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
        BlockSprites.push_back({ TestSprite, 16, 16 });
        TestSprite.clear();

        //Player Objects

        TestSprite += L"...rrrrr....";
        TestSprite += L"...rrrrr....";
        TestSprite += L"..rrrrrrrrr.";
        TestSprite += L"..pppYYpY...";
        TestSprite += L".pYpYYYpYYY.";
        TestSprite += L".pYppYYYpYYY";
        TestSprite += L".ppYYYYpppp.";
        TestSprite += L"...YYYYYYY..";
        TestSprite += L"..rrbrrbrr..";
        TestSprite += L".rrrbrrbrrr.";
        TestSprite += L"rrrrbbbbrrrr";
        TestSprite += L"YYrbybbybrYY";
        TestSprite += L"YYYbbbbbbYYY";
        TestSprite += L"YYbbbbbbbbYY";
        TestSprite += L"..bbb..bbb..";
        TestSprite += L".qqq....qqq.";
        TestSprite += L"qqqq....qqqq";
        MarioSprites.push_back({ false, TestSprite, 12, 17 });
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
        MarioSprites.push_back({ false, TestSprite, 17, 16 });
        TestSprite.clear();

        TestSprite += L".....rrrrr.....";
        TestSprite += L".....rrrrr.....";
        TestSprite += L"....rrrrrrrrr..";
        TestSprite += L"....pppYYpY....";
        TestSprite += L"...pYpYYYpYYY..";
        TestSprite += L"...pYppYYYpYYY.";
        TestSprite += L"...ppYYYYpppp..";
        TestSprite += L".....YYYYYYY...";
        TestSprite += L"..rrrrbbrr.....";
        TestSprite += L"YYrrrrbbbrrrYYY";
        TestSprite += L"YYY.rrbybbrrrYY";
        TestSprite += L"YY..bbbbbbb..q.";
        TestSprite += L"...bbbbbbbbbqq.";
        TestSprite += L"..bbbbbbbbbbqq.";
        TestSprite += L".qqbbb...bbbqq.";
        TestSprite += L".qqq...........";
        TestSprite += L"..qqq..........";
        MarioSprites.push_back({ false, TestSprite, 15, 17 });
        TestSprite.clear();

        TestSprite += L".....rrrrr.....";
        TestSprite += L".....rrrrr.....";
        TestSprite += L"....rrrrrrrrr..";
        TestSprite += L"....pppYYpY....";
        TestSprite += L"...pYpYYYpYYY..";
        TestSprite += L"...pYppYYYpYYY.";
        TestSprite += L"...ppYYYYpppp..";
        TestSprite += L".....YYYYYYY...";
        TestSprite += L"....rrrrbr.Y...";
        TestSprite += L"...YrrrrrrYYY..";
        TestSprite += L"..YYbrrrrrYY...";
        TestSprite += L"..qqbbbbbbb....";
        TestSprite += L"..qbbbbbbbb....";
        TestSprite += L".qqbbb.bbb.....";
        TestSprite += L".q....qqq......";
        TestSprite += L"......qqqq.....";
        MarioSprites.push_back({ false, TestSprite, 15, 16 });
        TestSprite.clear();

        TestSprite += L".....rrrrr.....";
        TestSprite += L".....rrrrr.....";
        TestSprite += L"....rrrrrrrrr..";
        TestSprite += L"....pppYYpY....";
        TestSprite += L"...pYpYYYpYYY..";
        TestSprite += L"...pYppYYYpYYY.";
        TestSprite += L"...ppYYYYpppp..";
        TestSprite += L".....YYYYYYY...";
        TestSprite += L"....rrbrrr.....";
        TestSprite += L"...rrrrbbrr....";
        TestSprite += L"...rrrbbybbY...";
        TestSprite += L"...rrrrbbbbb...";
        TestSprite += L"...brrYYYbbb...";
        TestSprite += L"....brYYbbb....";
        TestSprite += L".....bbbqqq....";
        TestSprite += L".....qqqqqqq...";
        TestSprite += L".....qqqq......";
        MarioSprites.push_back({ false, TestSprite, 15, 17 });
        TestSprite.clear();

        return true;
    }

    bool MoveSide(float &XSpeed, float &YSpeed, float &MaxXSpeed) {
        float Accel = 3;
        //cout << XSpeed << endl;
        if (GetKey(olc::D).bHeld or RightDPad or StickRight) {
            XSpeed += Accel * GetElapsedTime();
            if (XSpeed >= MaxXSpeed * GetElapsedTime() * 10) XSpeed = MaxXSpeed * GetElapsedTime() * 10;
        }

        else if (GetKey(olc::A).bHeld or LeftDPad or StickLeft) {
            XSpeed += -Accel * GetElapsedTime();
            if (XSpeed <= -MaxXSpeed * GetElapsedTime() * 10) XSpeed = -MaxXSpeed * GetElapsedTime() * 10;
        }
        else {
            XSpeed -= Accel * GetElapsedTime() * XSpeed * 0.5;
            if (XSpeed < 0.1 and XSpeed > -0.1) XSpeed = 0;
        }

        if (PlayerIsOnGround) XSpeed -= Accel * GetElapsedTime() * XSpeed * 1;

        float LimitSpeed = 0.7;
        if (XSpeed >= LimitSpeed or XSpeed <= -LimitSpeed) MaxJumpSpeed = 2.1;
        else if (XSpeed > -LimitSpeed and XSpeed < LimitSpeed) MaxJumpSpeed = 1.9;

        /*if (GetKey(olc::W).bHeld) {
            YSpeed = -1;
        }

        else if (GetKey(olc::S).bHeld) {
            YSpeed = 1;
        }*/
        //else YSpeed = 0;

        fTilePPosX += (XSpeed * GetElapsedTime() * 10);
        fTilePPosY += (YSpeed * GetElapsedTime() * 10);

        return true;
    }

    void AnimateRunning(int AnimVel = 15) {
        if (fVelX != 0 and !HasLeftGround) {
            cont++;
            if (animcont < 3 and cont > (AnimVel/(GetElapsedTime()*100))) {
                cont = 0;
                animcont++;

                switch (animcont) {
                case 1:
                    MarioSpriteType = 2;
                    break;
                case 2:
                    MarioSpriteType = 3;
                    break;
                case 3:
                    MarioSpriteType = 4;
                    break;
                }
            }
            if (animcont >= 3) animcont = 0;
        }
    }

    void MoveCamera(float XSpeed = 1, float YSpeed = 1) {
        if (GetKey(olc::RIGHT).bHeld) {
            fCameraX -= (XSpeed * GetElapsedTime() * 10);
        }

        else if (GetKey(olc::LEFT).bHeld) {
            fCameraX += (XSpeed * GetElapsedTime() * 10);
        }

        if (GetKey(olc::UP).bHeld) {
            fCameraY += (YSpeed * GetElapsedTime() * 10);
        }

        else if (GetKey(olc::DOWN).bHeld) {
            fCameraY -= (YSpeed * GetElapsedTime() * 10);
        }

    }

    void ResolveCamera(float XSpeed = 1) {
        fCameraX = fTilePPosX - 7;
        fCameraY = fTilePPosY - 5;

        if (fCameraX <= 0) fCameraX = 0;
        else if (fCameraX + VisibleTilesLong >= Level_1.WidthinTiles) fCameraX = Level_1.WidthinTiles - VisibleTilesLong;

        if (fCameraY <= 0) fCameraY = 0;
        else if (fCameraY + VisibleTilesHigh >= Level_1.HeightinTiles) fCameraY = Level_1.HeightinTiles - VisibleTilesHigh;
    }

    void MoveMario(float XSpeed = 2, float YSpeed = 8) {
        //cout << NewVel;
        if (GetKey(olc::SPACE).bPressed or ButtonATouch or ButtonBTouch) {
            if (!HasJumped and !HasLeftGround) {
                NewVel = -MaxJumpSpeed;
                fAccelY = 0.1 * GetElapsedTime() * 50;
                HasJumped = true;
                HasLeftGround = true;

                ButtonATouch = false;
                ButtonBTouch = false;
            }
        }
        if (GetKey(olc::SPACE).bHeld or ButtonAHeld or ButtonBHeld) {
            if (HasJumped and !HasTouchedCeiling) {
                fAccelY = 0.1 * GetElapsedTime() * 50;
                NewVel += fAccelY;
                if (NewVel > -0.1) {
                    NewVel = 0;
                    HasJumped = false;
                }
                fVelY = NewVel;
            }
        }
        if (GetKey(olc::SPACE).bReleased or ButtonAReleased or ButtonBReleased) {
            HasJumped = false;
            NewVel = 0;

            ButtonAReleased = false;
            ButtonBReleased = false;
        }
        if (!HasLeftGround) {
            if (fVelX == 0)MarioSpriteType = 0;
            HasTouchedCeiling = false;
        }
        else if (HasLeftGround) MarioSpriteType = 1;

        if (HasTouchedCeiling) {
            NewVel = 0;
        }

        if (GetKey(olc::SHIFT).bHeld or ButtonX or ButtonY) {
            MaxSideSpeed = 60;
            AnimVel = 5;
        }
        else{
            MaxSideSpeed = 30;
            AnimVel = 15;
        }

        MoveSide(fVelX, fVelY, MaxSideSpeed);
    }

    //ColisionDetection(fPPosX, fPPosY, MarioSprites[MarioSpriteType].SpriteWidth, MarioSprites[MarioSpriteType].SpriteHeight
    //, TileX, TileY, TileSize, TileSize)

    void DoColisions( int ix, int iy) {
        bool MovesRight = false;
        bool MovesLeft = false;

        if (fVelX < 0) {
            MovesLeft = true;
            if (trunc(fTilePPosX - 0.1) == ix and trunc(fLastTilePPosY) == iy) {
                fTilePPosX = ix + 1;
                fVelX = 0;
            }
            else if (trunc(fTilePPosX - 0.1) == ix and trunc(fLastTilePPosY + 1 - 0.1f) == iy) {
                fTilePPosX = ix + 1;
                fVelX = 0;
            }
        }
        if (fVelX > 0) {
            MovesRight = true;
            if (trunc(fTilePPosX + 1) == ix and trunc(fLastTilePPosY) == iy) {
                fTilePPosX = trunc(fTilePPosX);
                fVelX = 0;
            }
            else if (trunc(fTilePPosX + 1) == ix and trunc(fLastTilePPosY + 1 - 0.1f) == iy) {
                fTilePPosX = trunc(fTilePPosX);
                fVelX = 0;
            }
        }

        if (fVelY > 0) {
            if (trunc(fTilePPosX + 1 - 0.05) == ix and trunc(fTilePPosY + 1) == iy) {
                fTilePPosY = iy - 1;
                fVelY = 0;
                HasLeftGround = false;
                PlayerIsOnGround = true;
            }
            else if (trunc(fTilePPosX) == ix and trunc(fTilePPosY + 1) == iy) {
                fTilePPosY = iy - 1;
                fVelY = 0;
                HasLeftGround = false;
                PlayerIsOnGround = true;
            }
            else {
                HasLeftGround = true;
                PlayerIsOnGround = false;
            }
        }
        if (fVelY < 0 and !MovesRight and !MovesLeft) {
            if (trunc(fTilePPosX + 0.01) == ix and trunc(fTilePPosY) == iy) {
                fTilePPosY = iy + 1;
                HasTouchedCeiling = true;
            }
            else if (trunc(fTilePPosX + 1 - 0.05) == ix and trunc(fTilePPosY) == iy) {
                fTilePPosY = iy + 1;
                fVelY = 0;
                HasTouchedCeiling = true;
            }
        }
        else if (fVelY < 0 and fVelX > 0) {
            if (trunc(fTilePPosX) == ix and trunc(fTilePPosY) == iy) {
                fTilePPosY = iy + 1;
                HasTouchedCeiling = true;
            }
            else if (trunc(fTilePPosX + 1 - 0.2) == ix and trunc(fTilePPosY) == iy) {
                fTilePPosY = iy + 1;
                fVelY = 0;
                HasTouchedCeiling = true;
            }
        }
        else if (fVelY < 0 and fVelX < 0) {
            if (trunc(fTilePPosX + 0.2) == ix and trunc(fTilePPosY) == iy) {
                fTilePPosY = iy + 1;
                HasTouchedCeiling = true;
            }
            else if (trunc(fTilePPosX + 1) == ix and trunc(fTilePPosY) == iy) {
                fTilePPosY = iy + 1;
                fVelY = 0;
                HasTouchedCeiling = true;
            }
        }

        if (fTilePPosX <= 0) fTilePPosX = 0;
        else if (fTilePPosX + 1 >= Level_1.WidthinTiles) fTilePPosX = Level_1.WidthinTiles - 1;

        if (fTilePPosY <= 0) fTilePPosY = 0;
    }


    void Fall(float &Speed) {
        Speed += 0.5;
        if (Speed >= 1.5) Speed = 1.5;

        fVelY = Speed;
    }


    void ManageSpriteRotation(int ID) {

        if (GetKey(olc::D).bPressed) {
            bPlayerDirection = true;
        }
        else if (GetKey(olc::A).bPressed and !GetKey(olc::D).bHeld) {
            bPlayerDirection = false;
        }
        else if (GetKey(olc::A).bHeld and GetKey(olc::D).bReleased) {
            bPlayerDirection = false;
        }

        if (RightDPad) {
            bPlayerDirection = true;
        }
        else if (LeftDPad) {
            bPlayerDirection = false;
        }

        if (StickRight) {
            bPlayerDirection = true;
        }
        else if (StickLeft) {
            bPlayerDirection = false;
        }


    }

    void ManageGeneralRotation(bool GeneralRotation, int ID) {
        if (GeneralRotation and MarioSprites[ID].HasFliped) MirrorString(MarioSprites[ID].Sprite, MarioSprites[ID].HasFliped, MarioSprites[ID].SpriteWidth, MarioSprites[ID].SpriteHeight);
        if (!GeneralRotation and !MarioSprites[ID].HasFliped) MirrorString(MarioSprites[ID].Sprite, MarioSprites[ID].HasFliped, MarioSprites[ID].SpriteWidth, MarioSprites[ID].SpriteHeight);
    }

    void ManageControllers() {

        if (gamepad->getButton(olc::GPButtons::DPAD_R).bHeld) RightDPad = true;
        else if (gamepad->getButton(olc::GPButtons::DPAD_R).bReleased) RightDPad = false;

        if (gamepad->getButton(olc::GPButtons::DPAD_L).bHeld) LeftDPad = true;
        else if (gamepad->getButton(olc::GPButtons::DPAD_L).bReleased) LeftDPad = false;

        if (gamepad->getAxis(olc::GPAxes::LX) > 0.2) {
            StickRight = true;
            StickLeft = false;
        }
        else if (gamepad->getAxis(olc::GPAxes::LX) < -0.2) {
            StickRight = false;
            StickLeft = true;
        }
        else {
            StickRight = false;
            StickLeft = false;
        }

        if (!gamepad->getButton(olc::GPButtons::FACE_L).bHeld) {
            if (gamepad->getButton(olc::GPButtons::FACE_D).bPressed) ButtonATouch = true;
            else if (!gamepad->getButton(olc::GPButtons::FACE_D).bPressed) ButtonATouch = false;
            if (gamepad->getButton(olc::GPButtons::FACE_D).bHeld) ButtonAHeld = true;
            else if (gamepad->getButton(olc::GPButtons::FACE_D).bReleased) {
                ButtonAHeld = false;
                ButtonAReleased = true;
            }
        }

        if (!gamepad->getButton(olc::GPButtons::FACE_D).bHeld) {
            if (gamepad->getButton(olc::GPButtons::FACE_L).bPressed) ButtonBTouch = true;
            else if (!gamepad->getButton(olc::GPButtons::FACE_L).bPressed) ButtonBTouch = false;
            if (gamepad->getButton(olc::GPButtons::FACE_L).bHeld) ButtonBHeld = true;
            else if (gamepad->getButton(olc::GPButtons::FACE_L).bReleased) {
                ButtonBHeld = false;
                ButtonBReleased = true;
            }
        }

        if (gamepad->getButton(olc::GPButtons::FACE_U).bHeld) ButtonX = true;
        else if (gamepad->getButton(olc::GPButtons::FACE_U).bReleased) ButtonX = false;

        if (gamepad->getButton(olc::GPButtons::FACE_R).bHeld) ButtonY = true;
        else if (gamepad->getButton(olc::GPButtons::FACE_R).bReleased) ButtonY = false;
    }

    virtual bool OnUserUpdate(float fElapsedTime) {

        //cout << cont << " - " << animcont << endl;

        Clear(olc::WHITE);

        DrawLevel(Level_1.Level, Level_1.WidthinTiles, Level_1.HeightinTiles, fCameraX, fCameraY);

        Fall(fVelY);

        ManageSpriteRotation(MarioSpriteType);

        ManageGeneralRotation(bPlayerDirection, MarioSpriteType);

        if (gamepad == nullptr || !gamepad->stillConnected) {

            gamepad = olc::GamePad::selectWithButton(olc::GPButtons::SELECT);
            //DrawString(10, 10, "Press select button!", olc::BLACK);

            return true;
        }

        ManageControllers();

        return true;
    }

};

int main() {

    Game Juego;
    if (Juego.Construct(256, 192, 4, 4, false, true)) {
        Juego.Start();
    }

}
