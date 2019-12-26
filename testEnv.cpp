#include <iostream>
#include "windows.h"
#include <ctime>
#include <cstdlib>
#include <conio.h>

using namespace std;

const int wth = 25, hth = 25; //wth - x    hth - y

enum Direction {STOP = 0, UP, DOWN, LEFT, RIGHT};

struct Player{
	int X;
	int Y;
	Direction dir;
};

bool gameOver;
int fX, fY;
Player P;
int score;

int tail, tlX[wth], tlY[hth];

void arr_push(int push, int arr[], int arr_size){
	for(int i=arr_size; i>=0; i--){
		arr[i+1]=arr[i];}
	arr[0]=push;
}

void Setup(){
	gameOver=false;
	score=0;
	P.X=wth/2;
	P.Y=hth/2;
	
	srand(time(NULL));
	fX=rand()%wth;
	fY=rand()%hth;
}

void Draw(){
	bool wasTailPrinted;
	system("cls");
	for(int i=0; i<wth+2; i++)cout<<"#";
	cout<<endl;
	
	for(int y=0; y<hth; y++){
		cout<<"#";
		for(int x=0; x<wth; x++){
			if(P.X == x && P.Y ==y )cout<<"O";
			else if(fX == x && fY == y)cout<<"F";
			else { 
			wasTailPrinted=false;
			for(int i=0; i<=tail; i++){
				if(tlX[i]==x && tlY[i]==y){
					cout<<"o";
					wasTailPrinted=true;
				}
			}
			if(wasTailPrinted==false)cout<<" ";	
			}
		}
		cout<<"#"<<endl;
	}
	
	for(int i=0; i<wth+2; i++)cout<<"#";
	cout<<endl<<"Score "<<score;
	
	}



void Input(){
	if(_kbhit()){
	
		switch(getch()){
			case 119: 
				P.dir=UP;break;
			case 97:
				P.dir=LEFT;break;
			case 100:
				P.dir=RIGHT;break;
			case 115:
				P.dir=DOWN;break;
		}
	
	}
}

void Logic(){
	
	//tail logic
	arr_push(P.X, tlX, wth);
	arr_push(P.Y, tlY, hth);
	
	int oldFX, oldFY; //old fruit coord	
	//movement
	if(P.dir==UP)P.Y--;
	else if(P.dir==DOWN)P.Y++;
	else if(P.dir==LEFT)P.X--;
	else if(P.dir==RIGHT)P.X++;
	//wrapping
	if(P.X>wth)P.X-=wth+1;
	if(P.X<0)P.X+=wth;
	if(P.Y>hth)P.Y-=hth+1;
	if(P.Y<0)P.Y+=hth;
	//collision
	if(P.X == fX && P.Y == fY){
		score++;
		tail++;
		//spawning a new fruit
		oldFX=fX; oldFY=fY;
		srand(time(NULL));
		while(fX==oldFX || fY==oldFY){
			fX=rand()%wth;
			fY=rand()%hth;
		}			
	}
	//colision with tail
	for(int i=1; i<tail; i++){
		if(tlX[i]==P.X && tlY[i]==P.Y)gameOver=true;
	}
	
}

int main() {
	
	Setup();
    
    while(gameOver!=true){
    	
		Draw();
    	Input();
    	Logic();
    
    	//Sleep(100);
	}
	
	system("cls");
	cout<<"przejebales lol";
	
	return 0;
}
