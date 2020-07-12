//
//  main.cpp
//  Tetris
//
//  Created by Santiago Vera on 07/07/20.
//  Copyright © 2020 Mistic_Lion. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
#include "olcConsoleGameEngineSDL.h"
using namespace std;

class Juego : public olcConsoleGameEngine{
private:
    
    int long score;
    
    int Speed=60;
    
    int FieldWidth=60;
    int FieldHeight=100;
    int cont=0;
    int cont_2=0;
    int cont_3=0;
    int cont_4=0;
    int FramesToGoDown=0;
    
    int Tetromino_Type=rand()%7;
    int long UserTetrominoArraySize=0;
    int long MeshTetrominoArraySize=0;
    int long MeshIndex=0;
    
    int const static Block_Size=4;
    
    struct Coord{
        float x,y;
    };
    
    struct Cubes{
        vector <Coord> Arr;
        short Colour;
    };
    
    int Next_Type=5;
    
    vector <Cubes> Tetromino;
    vector <Cubes> Tetromino_Mesh;
    vector <Cubes> Next_Tetromino;
    
    
    float Pos_X=ScreenWidth()-8;
    float Pos_Y=28;
    
    float User_Flag=0;
    float User_Y=0;
    
public:
    Juego(){}
    ~Juego(){}
    
    void DrawField(){
        int BorderField_OOB_X = ((ScreenWidth()-FieldWidth)/2)-2;
        int BorderField_OOB_Y = ((ScreenHeight()-FieldHeight)/2)-2;
        
        int x1=BorderField_OOB_X;
        int y1=BorderField_OOB_Y;
        int x2=BorderField_OOB_X+Block_Size;
        int y2=BorderField_OOB_Y+FieldHeight;
        int x3=x2;
        int y3=y2-Block_Size;
        int x4=x2+FieldWidth-Block_Size;
        int y4=y2;
        int x5=x4-Block_Size;
        int y5=y1;
        int x6=x4;
        int y6=y4;
        
        Fill(x1,y1,x2,y2,PIXEL_SOLID,FG_WHITE);
        Fill(x3,y3,x4,y4,PIXEL_SOLID,FG_WHITE);
        Fill(x5,y5,x6,y6,PIXEL_SOLID,FG_WHITE);
    }
    
    void Rotate_Tetromino(){
        int ID[8];
        if(GetKey(VK_SPACE).bPressed and Tetromino_Type!=4 and Tetromino_Type!=1){
            
                    for(int i=0; i<UserTetrominoArraySize; i++){
                        int x=(Tetromino[Tetromino_Type].Arr[i].x/4);
                        int y=(Tetromino[Tetromino_Type].Arr[i].y/4);
                        
                        ID[i]=3-y+(4*x);
                        
                        y=(ID[i]/4);
                        x=ID[i]-(4*y);
                        
                        x=x*4;
                        y=y*4;
                        
                        Tetromino[Tetromino_Type].Arr[i].x=x;
                        Tetromino[Tetromino_Type].Arr[i].y=y;
                        }
        
        }
        else if (GetKey(VK_SPACE).bPressed and Tetromino_Type==1){
            
            if(cont_2==0){
                for(int i=0; i<UserTetrominoArraySize; i++){
                    int x=(Tetromino[Tetromino_Type].Arr[i].x/4);
                    int y=(Tetromino[Tetromino_Type].Arr[i].y/4);
                    ID[i]=3-y+(4*x);
                    
                    y=(ID[i]/4);
                    x=ID[i]-(4*y);
                    
                    Tetromino[Tetromino_Type].Arr[i].x=x*4;
                    Tetromino[Tetromino_Type].Arr[i].y=y*4;
                }
                cont_2=1;
            }
            else if(cont_2==1){
                for(int i=0; i<Tetromino[Tetromino_Type].Arr.size(); i++){
                    int x=(Tetromino[Tetromino_Type].Arr[i].x/4);
                    int y=(Tetromino[Tetromino_Type].Arr[i].y/4);
                    
                    ID[i]=12+y-(x*4);
                    
                    y=(ID[i]/4);
                    x=ID[i]-(4*y);
                    
                    Tetromino[Tetromino_Type].Arr[i].x=x*4;
                    Tetromino[Tetromino_Type].Arr[i].y=y*4;
                }
                cont_2=0;
            }
        }
    }
    
    bool DoesPieceFit(){
        for (int i=0; i<UserTetrominoArraySize; i++){
            if((Tetromino[Tetromino_Type].Arr[i].x+Pos_X)>=(((((ScreenWidth()-FieldWidth)/2)-2)+Block_Size)+FieldWidth-(2*Block_Size))-Block_Size)return false;
        }
        
        return true;
    }
    
    bool DoesPieceFit2(){
        for (int i=0; i<UserTetrominoArraySize; i++){
            if((Tetromino[Tetromino_Type].Arr[i].x+Pos_X)<=(((ScreenWidth()-FieldWidth)/2)-2)+Block_Size) return false;
        }
        return true;
    }
    
    bool DoesPieceFit3(){
        for (int i=0; i<UserTetrominoArraySize; i++){
            if((Tetromino[Tetromino_Type].Arr[i].y+Pos_Y)>=((((ScreenHeight()-FieldHeight)/2)-2)+FieldHeight)-(2*Block_Size)) return false;
        }
        return true;
    }
    
    bool DoesPieceFitDown(){
        for (int i=0; i<UserTetrominoArraySize;i++){
            for (int j=0; j<=MeshIndex;j++){
                MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
                for(int k=0; k<MeshTetrominoArraySize; k++){
                    if(Tetromino[Tetromino_Type].Arr[i].y+Pos_Y+4<Tetromino_Mesh[j].Arr[k].y+4 and Tetromino[Tetromino_Type].Arr[i].y+Pos_Y+8>Tetromino_Mesh[j].Arr[k].y){
                        if(Tetromino[Tetromino_Type].Arr[i].x+Pos_X<Tetromino_Mesh[j].Arr[k].x+4 and Tetromino[Tetromino_Type].Arr[i].x+Pos_X+4>Tetromino_Mesh[j].Arr[k].x) return false;
                    }
                }
            }
        }
        return true;
    }
    
    bool DoesPieceFitRight(){
        for (int i=0; i<UserTetrominoArraySize;i++){
            for (int j=0; j<=MeshIndex;j++){
                MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
                for(int k=0; k<MeshTetrominoArraySize; k++){
                    if(Tetromino[Tetromino_Type].Arr[i].y+Pos_Y<Tetromino_Mesh[j].Arr[k].y+4 and Tetromino[Tetromino_Type].Arr[i].y+Pos_Y+4>Tetromino_Mesh[j].Arr[k].y){
                        if(Tetromino[Tetromino_Type].Arr[i].x+Pos_X+4<Tetromino_Mesh[j].Arr[k].x+4 and Tetromino[Tetromino_Type].Arr[i].x+Pos_X+8>Tetromino_Mesh[j].Arr[k].x) return false;
                    }
                }
            }
        }
        return true;
    }
    
    bool DoesPieceFitLeft(){
        for (int i=0; i<UserTetrominoArraySize;i++){
            for (int j=0; j<=MeshIndex;j++){
                MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
                for(int k=0; k<MeshTetrominoArraySize; k++){
                    if(Tetromino[Tetromino_Type].Arr[i].y+Pos_Y<Tetromino_Mesh[j].Arr[k].y+4 and Tetromino[Tetromino_Type].Arr[i].y+Pos_Y+4>Tetromino_Mesh[j].Arr[k].y){
                        if(Tetromino[Tetromino_Type].Arr[i].x+Pos_X-4<Tetromino_Mesh[j].Arr[k].x+4 and Tetromino[Tetromino_Type].Arr[i].x+Pos_X>Tetromino_Mesh[j].Arr[k].x) return false;
                    }
                }
            }
        }
        return true;
    }
    
    bool NextRotationDoesFit(){
        int ID[8];
        
        if(Tetromino_Type!=4 and Tetromino_Type!=1){
        for(int i=0; i<UserTetrominoArraySize; i++){
            int x=(Tetromino[Tetromino_Type].Arr[i].x/4);
            int y=(Tetromino[Tetromino_Type].Arr[i].y/4);
            
            ID[i]=3-y+(4*x);
            
            y=(ID[i]/4);
            x=ID[i]-(4*y);
            
            x=x*4;
            y=y*4;
            
            if((x+Pos_X)>(((((ScreenWidth()-FieldWidth)/2)-2)+Block_Size)+FieldWidth-(3*Block_Size)) or (x+Pos_X-1<(((ScreenWidth()-FieldWidth)/2)-2)) or (y+Pos_Y>((((ScreenHeight()-FieldHeight)/2)-2)+FieldHeight)-(2*Block_Size))) return false;
            
            for (int j=0; j<=MeshIndex;j++){
                MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
                for(int k=0; k<MeshTetrominoArraySize; k++){
                    if(y+Pos_Y+1<=Tetromino_Mesh[j].Arr[k].y+4 and y+Pos_Y+3>=Tetromino_Mesh[j].Arr[k].y){
                        if(x+Pos_X+1<=Tetromino_Mesh[j].Arr[k].x+4 and x+Pos_X+3>=Tetromino_Mesh[j].Arr[k].x)
                            return false;
                    }
                }
            }
        }
        }
        else if (Tetromino_Type==1){
            
            if(cont_2==0){
                for(int i=0; i<UserTetrominoArraySize; i++){
                    int x=(Tetromino[Tetromino_Type].Arr[i].x/4);
                    int y=(Tetromino[Tetromino_Type].Arr[i].y/4);
                    
                    ID[i]=3-y+(4*x);
                    
                    y=(ID[i]/4);
                    x=ID[i]-(4*y);
                    
                    x=x*4;
                    y=y*4;
                    
                    if((x+Pos_X)>(((((ScreenWidth()-FieldWidth)/2)-2)+Block_Size)+FieldWidth-(3*Block_Size)) or (x+Pos_X-1<(((ScreenWidth()-FieldWidth)/2)-2)) or (y+Pos_Y>((((ScreenHeight()-FieldHeight)/2)-2)+FieldHeight)-(2*Block_Size)))
                        return false;
                    
                    for (int j=0; j<=MeshIndex;j++){
                        MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
                        for(int k=0; k<MeshTetrominoArraySize; k++){
                            if(y+Pos_Y+1<=Tetromino_Mesh[j].Arr[k].y+4 and y+Pos_Y+3>=Tetromino_Mesh[j].Arr[k].y){
                                if(x+Pos_X+1<=Tetromino_Mesh[j].Arr[k].x+4 and x+Pos_X+3>=Tetromino_Mesh[j].Arr[k].x)return false;
                            }
                        }
                    }
                }
            }
            else if(cont_2==1){
                for(int i=0; i<Tetromino[Tetromino_Type].Arr.size(); i++){
                    int x=(Tetromino[Tetromino_Type].Arr[i].x/4);
                    int y=(Tetromino[Tetromino_Type].Arr[i].y/4);
                    
                    ID[i]=12+y-(x*4);
                    
                    y=(ID[i]/4);
                    x=ID[i]-(4*y);
                    
                    x=x*4;
                    y=y*4;
                    
                    if((x+Pos_X)>(((((ScreenWidth()-FieldWidth)/2)-2)+Block_Size)+FieldWidth-(3*Block_Size)) or (x+Pos_X-1<(((ScreenWidth()-FieldWidth)/2)-2)) or (y+Pos_Y>((((ScreenHeight()-FieldHeight)/2)-2)+FieldHeight)-(2*Block_Size))) return false;
                    
                    for (int j=0; j<=MeshIndex;j++){
                        MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
                        for(int k=0; k<MeshTetrominoArraySize; k++){
                            if(y+Pos_Y+1<=Tetromino_Mesh[j].Arr[k].y+4 and y+Pos_Y+3>=Tetromino_Mesh[j].Arr[k].y){
                                if(x+Pos_X+1<=Tetromino_Mesh[j].Arr[k].x+4 and x+Pos_X+3>=Tetromino_Mesh[j].Arr[k].x) return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }
    
    void MoveTetromino(){
        
        if(GetKey(VK_RIGHT).bPressed and DoesPieceFit() and DoesPieceFitRight()){
            Pos_X=Pos_X+4;
        }
        
        else if(GetKey(VK_RIGHT).bHeld and DoesPieceFit() and DoesPieceFitRight()){
            User_Flag=User_Flag+0.1;
            
            if(User_Flag>=1){
                Pos_X=Pos_X+4;
                User_Flag=0;
            }
        }
        
        if(GetKey(VK_LEFT).bPressed and DoesPieceFit2() and DoesPieceFitLeft()){
            Pos_X=Pos_X-4;
        }
        
        else if(GetKey(VK_LEFT).bHeld and DoesPieceFit2() and DoesPieceFitLeft()){
            User_Flag=User_Flag+0.1;
            
            if(User_Flag>=1){
                Pos_X=Pos_X-4;
                User_Flag=0;
            }
        }
        
        if(GetKey(VK_DOWN).bPressed and DoesPieceFit3() and DoesPieceFitDown()){
            Pos_Y=Pos_Y+4;
        }
        
        else if(GetKey(VK_DOWN).bHeld and DoesPieceFit3() and DoesPieceFitDown()){
            User_Flag=User_Flag+0.1;
            
            if(User_Flag>=1){
                Pos_Y=Pos_Y+4;
                User_Flag=0;
            }
        }
    }
    
    
    void MeshTetrominos(){
            if (!DoesPieceFit3() or !DoesPieceFitDown()){
                cont_3++;
                
                if(cont_3>120){
                Tetromino_Mesh.push_back({});
                for(int j=0; j< Tetromino[Tetromino_Type].Arr.size(); j++){
                    MeshIndex=Tetromino_Mesh.size()-1;
                    
                    float x=(Tetromino[Tetromino_Type].Arr[j].x+Pos_X);
                    float y=(Tetromino[Tetromino_Type].Arr[j].y+Pos_Y);
                    Tetromino_Mesh[MeshIndex].Arr.push_back({x, y});
                    Tetromino_Mesh[MeshIndex].Colour=Tetromino[Tetromino_Type].Colour;
                }
                    
                Pos_X=ScreenWidth()/2;
                Pos_Y=28;
                Tetromino_Type=Next_Type;
                    
                Next_Type=rand()%7;
                    
                    if(!CheackToEraseCompleteLine()) cout << "";
                    
                cont_3=0;
                    
                    if(GameOver()){
                        
                        cout << "Score= " << score << endl;
                        
                        Tetromino_Mesh.clear();
                        Tetromino.clear();
                        cont=0;
                        Speed=60;
                        score=0;
                    }
                }
            }
                
            }
    
    void DrawTetromino(){
        if(cont<1){
            Tetromino.push_back({});
            Tetromino.push_back({});
            Tetromino.push_back({});
            Tetromino.push_back({});
            Tetromino.push_back({});
            Tetromino.push_back({});
            Tetromino.push_back({});
            
            
            
            Tetromino[0].Arr.push_back({8, 0});
            Tetromino[0].Arr.push_back({8, 4});
            Tetromino[0].Arr.push_back({12, 4});
            Tetromino[0].Arr.push_back({8, 8});
            Tetromino[0].Colour=FG_MAGENTA;
            
            Tetromino[1].Arr.push_back({0, 0});
            Tetromino[1].Arr.push_back({4, 0});
            Tetromino[1].Arr.push_back({8, 0});
            Tetromino[1].Arr.push_back({12, 0});
            Tetromino[1].Colour=FG_BLUE;
            
            Tetromino[2].Arr.push_back({0,0});
            Tetromino[2].Arr.push_back({4,0});
            Tetromino[2].Arr.push_back({8,0});
            Tetromino[2].Arr.push_back({0,4});
            Tetromino[2].Colour=FG_DARK_BLUE;
            
            Tetromino[3].Arr.push_back({4, 4});
            Tetromino[3].Arr.push_back({8, 4});
            Tetromino[3].Arr.push_back({12, 4});
            Tetromino[3].Arr.push_back({12, 0});
            Tetromino[3].Colour=FG_CYAN;
            
            Tetromino[4].Arr.push_back({8, 0});
            Tetromino[4].Arr.push_back({8, 4});
            Tetromino[4].Arr.push_back({12, 0});
            Tetromino[4].Arr.push_back({12, 4});
            Tetromino[4].Colour=FG_YELLOW;
            
            Tetromino[5].Arr.push_back({4, 4});
            Tetromino[5].Arr.push_back({8, 4});
            Tetromino[5].Arr.push_back({8, 0});
            Tetromino[5].Arr.push_back({12, 0});
            Tetromino[5].Colour=FG_GREEN;
            
            Tetromino[6].Arr.push_back({4, 0});
            Tetromino[6].Arr.push_back({8, 0});
            Tetromino[6].Arr.push_back({8, 4});
            Tetromino[6].Arr.push_back({12, 4});
            Tetromino[6].Colour=FG_RED;
            
            
            //----------------------------------
            
            
            Next_Tetromino.push_back({});
            Next_Tetromino.push_back({});
            Next_Tetromino.push_back({});
            Next_Tetromino.push_back({});
            Next_Tetromino.push_back({});
            Next_Tetromino.push_back({});
            Next_Tetromino.push_back({});
            
            
            
            Next_Tetromino[0].Arr.push_back({8, 0});
            Next_Tetromino[0].Arr.push_back({8, 4});
            Next_Tetromino[0].Arr.push_back({12, 4});
            Next_Tetromino[0].Arr.push_back({8, 8});
            Next_Tetromino[0].Colour=FG_MAGENTA;
            
            Next_Tetromino[1].Arr.push_back({0, 0});
            Next_Tetromino[1].Arr.push_back({4, 0});
            Next_Tetromino[1].Arr.push_back({8, 0});
            Next_Tetromino[1].Arr.push_back({12, 0});
            Next_Tetromino[1].Colour=FG_BLUE;
            
            Next_Tetromino[2].Arr.push_back({0,0});
            Next_Tetromino[2].Arr.push_back({4,0});
            Next_Tetromino[2].Arr.push_back({8,0});
            Next_Tetromino[2].Arr.push_back({0,4});
            Next_Tetromino[2].Colour=FG_DARK_BLUE;
            
            Next_Tetromino[3].Arr.push_back({4, 4});
            Next_Tetromino[3].Arr.push_back({8, 4});
            Next_Tetromino[3].Arr.push_back({12, 4});
            Next_Tetromino[3].Arr.push_back({12, 0});
            Next_Tetromino[3].Colour=FG_CYAN;
            
            Next_Tetromino[4].Arr.push_back({8, 0});
            Next_Tetromino[4].Arr.push_back({8, 4});
            Next_Tetromino[4].Arr.push_back({12, 0});
            Next_Tetromino[4].Arr.push_back({12, 4});
            Next_Tetromino[4].Colour=FG_YELLOW;
            
            Next_Tetromino[5].Arr.push_back({4, 4});
            Next_Tetromino[5].Arr.push_back({8, 4});
            Next_Tetromino[5].Arr.push_back({8, 0});
            Next_Tetromino[5].Arr.push_back({12, 0});
            Next_Tetromino[5].Colour=FG_GREEN;
            
            Next_Tetromino[6].Arr.push_back({4, 0});
            Next_Tetromino[6].Arr.push_back({8, 0});
            Next_Tetromino[6].Arr.push_back({8, 4});
            Next_Tetromino[6].Arr.push_back({12, 4});
            Next_Tetromino[6].Colour=FG_RED;
        }
        
            for(int j=0;j<Tetromino[Tetromino_Type].Arr.size();j++){
                int x=Tetromino[Tetromino_Type].Arr[j].x+Pos_X;
                int y=Tetromino[Tetromino_Type].Arr[j].y+Pos_Y;
                int x1=x+Block_Size;
                int y1=y+Block_Size;
                short Colour=Tetromino[Tetromino_Type].Colour;
                
                Fill(x,y,x1,y1, PIXEL_SOLID, Colour);
            }
        
        for(int i=0; i<Tetromino_Mesh.size(); i++){
            for(int j=0;j<Tetromino_Mesh[i].Arr.size();j++){
                int x=Tetromino_Mesh[i].Arr[j].x;
                int y=Tetromino_Mesh[i].Arr[j].y;
                int x1=x+Block_Size;
                int y1=y+Block_Size;
                short Colour=Tetromino_Mesh[i].Colour;
                
                Fill(x,y,x1,y1, PIXEL_SOLID, Colour);
            }
        }
        
            for(int j=0;j<Next_Tetromino[Next_Type].Arr.size();j++){
                int x=Next_Tetromino[Next_Type].Arr[j].x+112;
                int y=Next_Tetromino[Next_Type].Arr[j].y+30;
                int x1=x+Block_Size;
                int y1=y+Block_Size;
                short Colour=Next_Tetromino[Next_Type].Colour;
                
                Fill(x,y,x1,y1, PIXEL_SOLID, Colour);
            }
        
    }
    
    bool CheackToEraseCompleteLine(){
        int multiplication=0;
        int cont=0;
        for(int h=28; h<=((((ScreenHeight()-FieldHeight)/2)-2)+FieldHeight)-(2*Block_Size); h=h+4){
            cont=0;
            
            for(int a=(((ScreenWidth()-FieldWidth)/2)-2); a<=(((((ScreenWidth()-FieldWidth)/2)-2)+Block_Size)+FieldWidth-(3*Block_Size)); a=a+4){
                
                for (int j=0; j<=MeshIndex;j++){
                    MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
                    for(int k=0; k<MeshTetrominoArraySize; k++){
                        
                        if(a==Tetromino_Mesh[j].Arr[k].x and h==Tetromino_Mesh[j].Arr[k].y){
                            cont++;
                        }
                    }
                }
            }
            if(cont>=13){
                multiplication++;
                for (int j=0; j<=MeshIndex;j++){
                    score=score+(10*multiplication);
                    
                    MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
                    for(int k=0; k<MeshTetrominoArraySize; k++){
                        float y = Tetromino_Mesh[j].Arr[k].y;
                        y=y+Block_Size;
                        if(Tetromino_Mesh[j].Arr[k].y<h) Tetromino_Mesh[j].Arr[k].y=y;
                        else if(Tetromino_Mesh[j].Arr[k].y==h) Tetromino_Mesh[j].Arr[k].y=((((ScreenHeight()-FieldHeight)/2)-2)+FieldHeight)-Block_Size;
                    }
                }
            }
        }
        return false;
    }
    
    bool GameOver(){
        for (int j=0; j<=MeshIndex;j++){
            MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
            for(int k=0; k<MeshTetrominoArraySize; k++){
                if(Tetromino_Mesh[j].Arr[k].y<=32) return true;
            }
        }
        
        
        return false;
    }
    
    void GainSpeed(){
        switch(score){
            case 5:
                Speed=50;
                break;
                
            case 10:
                Speed=40;
                break;
                
            case 20:
                Speed=20;
                break;
            
            case 30:
                Speed=15;
                break;
                
            case 40:
                Speed=10;
                break;
        }
    }
    
    
    virtual bool OnUserCreate(){
        
        return true;
    }
    
    virtual bool OnUserUpdate(float fElapsedTime){
        
        Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);
        
        if(cont_4>Speed and DoesPieceFitDown() and DoesPieceFit3()){
            Pos_Y=Pos_Y+4;
            cont_4=0;
        }
        
        if(NextRotationDoesFit()){
        Rotate_Tetromino();
        }
        
        MoveTetromino();
        
        MeshTetrominos();
        
        NextRotationDoesFit();
        
        DrawTetromino();
        
        DrawField();
        
        GainSpeed();
        
    
        UserTetrominoArraySize = Tetromino[Tetromino_Type].Arr.size();
        MeshIndex=Tetromino_Mesh.size()-1;
        
        score =Tetromino_Mesh.size();
        
        cont++;
        cont_4++;
        return true;
    }
    
};


int main() {
    
    Juego Demo;
    
    if(Demo.ConstructConsole(160, 160, 4, 4)){
        Demo.Start();
    }
    
    else cout << "Construct Failed";
}
