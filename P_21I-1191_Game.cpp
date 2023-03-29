//============================================================================
// Name        : game.cpp
// Author      : FAST CS Department
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game...
//============================================================================


//Name: Fatima Bilal
//Roll number: 21I-1191
//Final Project
#ifndef RushHour_CPP_
#define RushHour_CPP_
#include <Windows.h>
#include "util.h"
#include <iostream>
#include<mmsystem.h>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
#include<fstream>  //file handling
#include<sstream>   //for coversion of int to string for displaying it
using namespace std;
#pragma comment(lib, "Winmm.lib")

void MenuDisplay();
void game1();
void game();
int level=1;
int GAME=0;
int high_scores[10];
int score_player = 0;
int score_bot = 0;
string NAME[10];
string NAME2[10];
Combat_Game g;
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}
int player_mode_2=0;
void Settings()     //settings screen
{
	glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
		1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT);
	DrawRectangle(0, 0, 1060, 1050, colors[BLUE]);
	DrawString(400, 770, "Select a player type: select lower case alphabet", colors[WHITE]);
	DrawString(400, 650, "t-tank ", colors[WHITE]);
	DrawString(400, 600, "h-helicopter ", colors[WHITE]);
	DrawString(400, 550, "p-fighter plane ", colors[WHITE]);
	glutDisplayFunc(MenuDisplay);
	glutSwapBuffers();
}

int xI = 400, yI = 400;   //player
int XI = 400, YI = 400;    //player cannon

int xII = 1000, yII = 500;   //bot
int XII = 1000, YII = 500;    //bot cannon

int xIII = 1000, yIII = 500;   //PLAYER 2
int XIV = 1000, YIV = 500;    //CANNON OF PLAYER 2
int random = 0;
void rand_spawn()    //for random spawn points
{
	random = rand() % 100;

}
//functions to draw players, bots and cannons
//tanks
void drawBot() {
	DrawSquare(xII+random, yII, 20, colors[BLACK]);   //bot in 1 player game
	drawcircle(xII-5+random, yII-5, 5, colors[RED]);
	drawcircle(xII +10+random, yII-5, 5, colors[RED]);
	glutPostRedisplay();
}

void drawTank() {
	DrawSquare(xI+random, yI, 20, colors[RED]);      //player in 1 player game
	drawcircle(xI - 5+random, yI - 5, 5, colors[BLACK]);
	drawcircle(xI + 10+random, yI - 5, 5, colors[BLACK]);
	glutPostRedisplay();

}
void drawTANK() {
	DrawSquare(xIII+random, yIII, 20, colors[BLUE]);       //player in 2 player game
	drawcircle(xIII + random - 5, yIII - 5, 5, colors[BLACK]);
	drawcircle(xIII + random + 10, yIII - 5, 5, colors[BLACK]);
	glutPostRedisplay();
}

//helicopters

void drawBot1() {
	DrawSquare(xII+10 + random, yII, 20, colors[BLUE]);        //bot in one player game
	DrawSquare(xII + random, yII, 15, colors[YELLOW]);
	glutPostRedisplay();
}

void drawTank1() {                                   //player in one player game
	DrawSquare(xI + 10 + random, yI, 20, colors[RED]);
	DrawSquare(xI + random, yI, 10, colors[YELLOW]);
	glutPostRedisplay();

}
void drawTANK1() {                                    //player in two player game
	DrawSquare(xIII + 10 + random, yIII, 20, colors[BLUE]);
	DrawSquare(xIII + random, yIII, 15, colors[YELLOW]);
	glutPostRedisplay();
}


//fighter planes
void drawBot2() {
	DrawSquare(xII + 10 + random, yII, 20, colors[YELLOW]);       //bot in one player game
	DrawSquare(xII+random, yII + 10, 15, colors[GREEN]);
	DrawSquare(xII + random, yII -10, 15, colors[GREEN]);
	glutPostRedisplay();
}
void drawTANK2() {                                    //fighter plane player
	DrawSquare(xIII + 10+random , yIII, 20, colors[YELLOW]);
	DrawSquare(xIII, yIII + 10, 15, colors[GREEN]);
	DrawSquare(xIII, yIII - 10, 15, colors[GREEN]);
	glutPostRedisplay();
}
void drawTank2() {                                //fighter plane player
	DrawSquare(xI + 10 + random, yI, 20, colors[RED]);
	DrawSquare(xI + random, yI + 10, 15, colors[BLUE]);
	DrawSquare(xI + random, yI - 10, 15, colors[BLUE]);
	glutPostRedisplay();

}

//cannons
void drawCannon() {

	drawcircle(XI+random, YI, 10, colors[RED]);     //cannon for player in 1 player game
	glutPostRedisplay();
}

void DRAWCANNON() {                                 //cannon for bot in one player game
	drawcircle(XII+random, YII, 10, colors[BLACK]);
	glutPostRedisplay();

}
void DRAWCANNONIV() {
	drawcircle(XIV+random, YIV, 10, colors[BLACK]);   //cannon for player in 2 player game
	glutPostRedisplay();

}
void lose()     //losing screen
{
	static int i = 1;
	for (i = i; i > 0; i--)
	{
		score_bot=score_bot + 10;     //10 Points for losing level
	}
	sounds s;
	s.play_LOSE_sound();
	high_scores[GAME] = score_bot;
	glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
		1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	DrawString(300, 750, "\nYou lose\n", colors[BLUE]);
	DrawString(300, 700, "\nCOMBAT GAME ATARI \n", colors[BLUE]);
	DrawString(300, 650, "\nGame End \n", colors[BLUE]);
	DrawString(300, 600, "\nPress 0 to enter the game again \n", colors[BLUE]);
	level = 1;
	glutSwapBuffers();
}
void win()     //winning screen
{
	static int i = 1;
	for (i = i; i > 0; i--)
	{
		score_player = score_player + 10;     //10 Points for winning level
	}
	sounds s;
	s.play_WIN_sound();
	high_scores[GAME] = score_player;
	glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
		1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	DrawString(300, 750, "\nCOMBAT GAME ATARI \n", colors[BLUE]);
	DrawString(300, 700, "\nYou Win\n", colors[BLUE]);
	DrawString(300, 650, "\nGame End \n", colors[BLUE]);
	level = 2;
	DrawString(300, 600, "\nPress 0 to rematch again \n", colors[BLUE]);
	glutSwapBuffers();
}

void score_check() //SCORE IS CHECKED AFTER EVERY SOME TIME TO ADD TO THE TOTAL POINTS OF THE PLAYER OR BOT
{
	if ((((YII >= yI) && (YII<=yI+15)) && ((XII >= xI)&&(XII<=xI+15))))
	{
		++score_bot;
		g.b->set_score(score_bot);
		score_player--;
		g.P->set_score(score_player);
		score_player = g.P->get_score();
		sounds s;
		s.play_collision_sound();

		if (score_bot >= 15)
		{
			glutDisplayFunc(lose);
		}
		if (score_player >= 15)
		{
			glutDisplayFunc(win);
		}
	}
	if (((YI >= yII)&&(YI<=yII+15) ) && ((XI >= xII)&&(XI <= xII+15)))
	{
		++score_player;
		g.P->set_score(score_player);
		--score_bot;
		g.b->set_score(score_bot);
		score_player = g.P->get_score();
		sounds s;
		s.play_collision_sound();

		if (score_bot >= 15)
		{
			glutDisplayFunc(lose);

		}
		if (score_player >= 15)
		{
			glutDisplayFunc(win);

		}
	}
	if (((yII >= yI)&& (yII <= yI+15 )) && ((xII>=xI)&&(xII <= xI+15)))
	{
		--score_player;
		g.P->set_score(score_player);
		--score_bot;
		g.b->set_score(score_bot);
		score_player = g.P->get_score();

		sounds s;
		s.play_collision_sound();  //collision sound added

		if (score_bot >=15)
		{
			glutDisplayFunc(lose);

		}
		if (score_player >= 15)
		{
			glutDisplayFunc(win);

		}
	}
}

void score_check1() //SCORE IS CHECKED AFTER EVERY SOME TIME TO ADD TO THE TOTAL POINTS OF THE PLAYER 1 OR PLAYER 2
{
	if ((((YIV >= yI) && (YIV <= yI + 15)) && ((XIV >= xI) && (XIV <= xI + 15))))
	{
		++score_bot;
		g.b->set_score(score_bot);
		score_player--;
		g.P->set_score(score_player);
		score_player = g.P->get_score();

		sounds s;
		s.play_collision_sound();

		if (score_bot >= 15)
		{
			glutDisplayFunc(lose);
		}
		if (score_player >= 15)
		{
			glutDisplayFunc(win);
		}
	}
	if (((YI >= yIII) && (YI <= yIII + 15)) && ((XI >= xIII) && (XI <= xIII + 15)))
	{
		++score_player;
		g.P->set_score(score_player);
		g.b->score = --score_bot;
		score_player = g.P->get_score();

		sounds s;
		s.play_collision_sound();

		if (score_bot >= 15)
		{
			glutDisplayFunc(lose);

		}
		if (score_player >= 15)
		{
			glutDisplayFunc(win);

		}
	}
	if (((yIII >= yI) && (yIII <= yI + 15)) && ((xIII >= xI) && (xIII <= xI + 15)))
	{
		--score_player;
		g.P->set_score(score_player);
		--score_bot;
		g.b->set_score(score_bot);
		score_player = g.P->get_score();

		sounds s;
		s.play_collision_sound();

		if (score_bot >= 15)
		{
			glutDisplayFunc(lose);

		}
		if (score_player >= 15)
		{
			glutDisplayFunc(win);

		}
	}
}
bool flag = true;
bool moves= true;
void moveCar()
{
	if (level == 2)
	{
		//BOT MOVEMENT
		if (xII > 10  && flag) {

			for (int i = 0; i <= 12; i++)
			{

				if ((yII >= 200 && yII <= 300) || (yII >= 600 && yII <= 700))
				{

					if ((xII == 200) || (xII == 650))
					{
						moves = false;
					}
				}
				else
				{

					continue;
				}
			}
			if (moves == true)
			{

				xII -= 10;
				XII -= 15;

			}
			else if (moves == false)
			{
				if ((yII >= 200 && yII <= 300))
				{

					yII += 120;
					xII -= 10;

					XII -= 10;
					YII += 120;
				}
				if ((yII >= 600 && yII <= 700))
				{

					yII -= 120;
					xII -= 10;

					XII -= 10;
					YII -= 120;
				}
				moves = true;
			}



			if (xII < 100)
			{

				flag = false;
			}


		}
		else if (xII < 1010 && (yII<800 && yII>50) && !flag) {

			for (int i = 0; i <= 12; i++)
			{

				if ((yII >= 200 && yII <= 300) || (yII >= 600 && yII <= 700))
				{

					if ((xII == 200) || (xII == 650))
					{
						moves = false;
					}
				}
				else
				{
					continue;
				}
			}
			if (moves == true)
			{

				xII += 10;
				XII += 15;

			}
			else if (moves == false)
			{
				if ((yII >= 200 && yII <= 300))
				{

					yII += 120;
					xII += 10;

					XII += 15;
					YII += 120;
				}
				if ((yII >= 600 && yII <= 700))
				{

					yII -= 120;
					xII += 10;

					XII += 15;
					YII -= 120;
				}
				moves = true;
			}

			if (xII > 900)
			{

				flag = true;
			}

		}


		//PLAYER Cannon MOVEMENT
		if (XI > 10 && flag) {

			for (int i = 0; i <= 12; i++)
			{

				if ((YI >= 200 && YI <= 300) || (YI >= 600 && YI <= 700))
				{

					if ((XI == 200) || (XI == 650))
					{
						moves = false;
					}
				}
				else
				{

					continue;
				}
			}
			if (moves == true)
			{
				XI -= 10;

			}
			else if (moves == false)
			{
				if ((YI >= 200 && YI <= 300))
				{



					XI -= 15;
					YI += 120;
				}
				if ((YI >= 600 && YI <= 700))
				{



					XI -= 15;
					YI -= 120;
				}
				moves = true;
			}



			if (XI < 100)
			{

				flag = false;
			}


		}
		else if (XI < 1010 && !flag) {

			for (int i = 0; i <= 12; i++)
			{

				if ((YI >= 200 && YI <= 300) || (YI >= 600 && YI <= 700))
				{

					if ((XI == 200) || (XI == 650))
					{
						moves = false;
					}
				}
				else
				{
					continue;
				}
			}
			if (moves == true)
			{

				XI += 10;
			}
			else if (moves == false)
			{
				if ((YI >= 200 && YI <= 300))
				{


					XI += 15;
					YI += 120;
				}
				if ((YI >= 600 && YI <= 700))
				{



					XI += 15;
					YI -= 120;
				}
				moves = true;
			}

			if (XI > 900)
			{

				flag = true;
			}

		}

		//Player movement
		if (xI > 10 )
		{
			for (int i = 0; i <= 12; i++)
			{

				if ((yI >= 200 && yI <= 300) || (yI >= 600 && yI <= 700))
				{

					if ((xI == 200) || (xI == 650))
					{
						moves = false;
					}
				}
				else
				{

					continue;
				}
			}
			 if (moves == false)
			{
				if ((yI >= 200 && yI <= 300))
				{
					yI += 120;
				}
				if ((yI >= 600 && yI <= 700))
				{
					yI -= 120;
				}
				moves = true;
			}






		}
		else if (xI < 1010) {

			for (int i = 0; i <= 12; i++)
			{

				if ((yI >= 200 && yI <= 300) || (yI >= 600 && yI <= 700))
				{

					if ((xI == 200) || (xI == 650))
					{
						moves = false;
					}
				}
				else
				{
					continue;
				}
			}
			if (moves == false)
			{
				if ((yI >= 200 && yI <= 300))
				{
					yI += 120;
				}
				if ((yI >= 600 && yI <= 700))
				{
					yI -= 120;
				}
				moves = true;
			}



		}
		score_check();
		//
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////
	if (level == 1)
	{
		//BOT MOVEMENT
		if (xII > 10 && (yII > 50 && yII<800) && flag) {

			for (int i = 0; i <= 12; i++)
			{

				if ((xII >= 200 && xII <= 300) || (xII >= 600 && xII <= 700))
				{

					if ((yII == 200) || (yII == 650))
					{
						moves = false;
					}
				}
				else
				{

					continue;
				}
			}
			if (moves == true)
			{

				xII -= 10;
				XII -= 15;


			}
			else if (moves == false)
			{
				if (yII == 200 )
				{

					xII -= 10;
					yII -= 30;

					XII -= 15;
					YII -= 30;
				}
				if ( yII == 650)
				{

					yII -= 30;
					xII -= 10;

					XII -= 15;
					YII -= 30;
				}
				moves = true;
			}



			if (xII < 100)
			{

				flag = false;
			}


		}
		else if (xII < 1010 && (yII<800 && yII>50) && !flag) {

			for (int i = 0; i <= 12; i++)
			{
				if ((xII >= 200 && xII <= 300) || (xII >= 600 && xII <= 700))
				{
					if ((yII == 200) || (yII == 650))
					{
						moves = false;
					}
				}
				else
				{
					continue;
				}
			}
			if (moves == true)
			{

				xII += 10;
				XII += 15;

			}
			else if (moves == false)
			{
				if (yII == 200 )
				{

					yII += 30;
					xII += 10;

					XII += 15;
					YII += 15;
				}
				if (yII == 650)
				{

					yII -= 30;
					xII += 10;

					XII += 15;
					YII += 30;
				}
				moves = true;
			}

			if (xII > 900)
			{

				flag = true;
			}

		}
		//player cannon movement

		if (XI > 10  && flag) {

			for (int i = 0; i <= 12; i++)
			{

				if ((XI >= 200 && XI <= 300) || (XI >= 600 && XI <= 700))
				{

					if ((YI == 200) || (YI == 650))
					{
						moves = false;
					}
				}
				else
				{

					continue;
				}
			}
			if (moves == true)
			{

				XI -= 10;

			}
			else if (moves == false)
			{
				if (YI == 200)
				{

					XI -= 10;
					YI -= 120;


				}
				if (YI == 650)
				{

					YI -= 120;
					XI -= 10;


				}
				moves = true;
			}



			if (XI < 100)
			{

				flag = false;
			}


		}
		else if (XI < 1010 && !flag) {

			for (int i = 0; i <= 12; i++)
			{
				if ((XI >= 200 && XI <= 300) || (XI >= 600 && XI <= 700))
				{
					if ((YI == 200) || (YI == 650))
					{
						moves = false;
					}
				}
				else
				{
					continue;
				}
			}
			if (moves == true)
			{
				XI += 15;
			}
			else if (moves == false)
			{
				if (YI == 200)
				{

					YI += 120;
					XI += 10;

				}
				if (YI == 650)
				{

					YI -= 120;
					XI += 10;
				}
				moves = true;
			}

			if (XI > 900)
			{

				flag = true;
			}

		}
		//players move

		if (xI > 10 && flag) {

			for (int i = 0; i <= 12; i++)
			{

				if ((xI >= 200 && xI <= 300) || (xI >= 600 && xI <= 700))
				{

					if ((yI == 200) || (yI == 650))
					{
						moves = false;
					}
				}
				else
				{

					continue;
				}
			}
			if (moves == false)
			{
				if (yI == 200)
				{
					yI += 50;
				}
				if (yI == 650)
				{


					yI -= 50;


				}
				moves = true;
			}
		}
		else if (xI < 1010 && !flag) {

			for (int i = 0; i <= 12; i++)
			{
				if ((xI >= 200 && xI <= 300) || (xI >= 600 && xI <= 700))
				{
					if ((yI == 200) || (yI == 650))
					{
						moves = false;
					}
				}
				else
				{
					continue;
				}
			}
			if (moves == false)
			{
				if (yI == 200)
				{
					yI += 50;

				}
				if (yI == 650)
				{
					yI -= 50;
				}
				moves = true;
			}

		}
		score_check();
	}
}


void moveCar1()
{
	if (level == 1)
	{

		//PLAYER 1 cannon
		if (XI > 10 && flag) {

			for (int i = 0; i <= 12; i++)
			{

				if ((YI >= 200 && YI <= 300) || (YI >= 600 && YI <= 700))
				{

					if ((XI == 200) || (XI == 650))
					{
						moves = false;
					}
				}
				else
				{

					continue;
				}
			}
			if (moves == true)
			{
				XI -= 10;

			}
			else if (moves == false)
			{
				if ((YI >= 200 && YI <= 300))
				{



					XI -= 15;
					YI += 120;
				}
				if ((YI >= 600 && YI <= 700))
				{



					XI -= 15;
					YI -= 120;
				}
				moves = true;
			}



			if (XI < 100)
			{

				flag = false;
			}

		}
		else if (XI < 1010 && !flag) {

			for (int i = 0; i <= 12; i++)
			{

				if ((YI >= 200 && YI <= 300) || (YI >= 600 && YI <= 700))
				{

					if ((XI == 200) || (XI == 650))
					{
						moves = false;
					}
				}
				else
				{
					continue;
				}
			}
			if (moves == true)
			{

				XI += 10;
			}
			else if (moves == false)
			{
				if ((YI >= 200 && YI <= 300))
				{


					XI += 15;
					YI += 120;
				}
				if ((YI >= 600 && YI <= 700))
				{



					XI += 15;
					YI -= 120;
				}
				moves = true;
			}

			if (XI > 900)
			{

				flag = true;
			}

		}


		//player 1

		if (xI > 10 && flag) {

			for (int i = 0; i <= 12; i++)
			{

				if ((xI >= 200 && xI <= 300) || (xI >= 600 && xI <= 700))
				{

					if ((yI == 200) || (yI == 650))
					{
						moves = false;
					}
				}
				else
				{

					continue;
				}
			}
			if (moves == false)
			{
				if (yI == 200)
				{
					yI += 50;
				}
				if (yI == 650)
				{


					yI -= 50;


				}
				moves = true;
			}
		}
		else if (xI < 1010 && !flag) {

			for (int i = 0; i <= 12; i++)
			{
				if ((xI >= 200 && xI <= 300) || (xI >= 600 && xI <= 700))
				{
					if ((yI == 200) || (yI == 650))
					{
						moves = false;
					}
				}
				else
				{
					continue;
				}
			}
			if (moves == false)
			{
				if (yI == 200)
				{
					yI += 50;

				}
				if (yI == 650)
				{
					yI -= 50;
				}
				moves = true;
			}

		}

		//player 2

		if (xIII > 10 && flag) {

			for (int i = 0; i <= 12; i++)
			{

				if ((xIII >= 200 && xIII <= 300) || (xIII >= 600 && xIII <= 700))
				{

					if ((yIII == 200) || (yIII == 650))
					{
						moves = false;
					}
				}
				else
				{

					continue;
				}
			}
			if (moves == false)
			{
				if (yIII == 200)
				{
					yIII += 50;
				}
				if (yIII == 650)
				{


					yIII -= 50;


				}
				moves = true;
			}
		}
		else if (xIII< 1010 && !flag) {

			for (int i = 0; i <= 12; i++)
			{
				if ((xIII >= 200 && xIII <= 300) || (xIII >= 600 && xIII <= 700))
				{
					if ((yIII == 200) || (yIII == 650))
					{
						moves = false;
					}
				}
				else
				{
					continue;
				}
			}
			if (moves == false)
			{
				if (yIII == 200)
				{
					yIII += 50;

				}
				if (yIII == 650)
				{
					yIII -= 50;
				}
				moves = true;
			}

		}
		//PLAYER 2 cannon
		if (XIV > 10 && flag) {

			for (int i = 0; i <= 12; i++)
			{

				if ((YIV >= 200 && YIV <= 300) || (YIV >= 600 && YIV <= 700))
				{

					if ((XIV == 200) || (XIV == 650))
					{
						moves = false;
					}
				}
				else
				{

					continue;
				}
			}
			if (moves == true)
			{
				XIV -= 10;

			}
			else if (moves == false)
			{
				if ((YIV >= 200 && YIV <= 300))
				{



					XIV -= 15;
					YIV += 120;
				}
				if ((YIV >= 600 && YIV <= 700))
				{



					XIV -= 15;
					YIV -= 120;
				}
				moves = true;
			}



			if (XIV < 100)
			{

				flag = false;
			}

		}
		else if (XIV < 1010 && !flag) {

			for (int i = 0; i <= 12; i++)
			{

				if ((YIV >= 200 && YIV <= 300) || (YIV >= 600 && YIV <= 700))
				{

					if ((XIV == 200) || (XIV == 650))
					{
						moves = false;
					}
				}
				else
				{
					continue;
				}
			}
			if (moves == true)
			{

				XIV += 10;
			}
			else if (moves == false)
			{
				if ((YIV >= 200 && YIV <= 300))
				{


					XIV += 15;
					YIV += 120;
				}
				if ((YIV >= 600 && YIV <= 700))
				{



					XIV += 15;
					YIV -= 120;
				}
				moves = true;
			}

			if (XIV > 900)
			{

				flag = true;
			}
			score_check1();
		}

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////
	if (level == 2)
	{

		//player movement

		//PLAYER 1 cannon
		if (XI > 10 && flag) {

			for (int i = 0; i <= 12; i++)
			{

				if ((XI >= 200 && XI <= 300) || (XI >= 600 && XI <= 700))
				{

					if ((YI == 200) || (YI == 650))
					{
						moves = false;
					}
				}
				else
				{

					continue;
				}
			}
			if (moves == true)
			{

				XI -= 10;

			}
			else if (moves == false)
			{
				if (YI == 200)
				{

					XI -= 10;
					YI -= 120;


				}
				if (YI == 650)
				{

					YI -= 120;
					XI -= 10;


				}
				moves = true;
			}



			if (XI < 100)
			{

				flag = false;
			}

		}
		else if (XI < 1010 && !flag) {

			for (int i = 0; i <= 12; i++)
			{
				if ((XI >= 200 && XI <= 300) || (XI >= 600 && XI <= 700))
				{
					if ((YI == 200) || (YI == 650))
					{
						moves = false;
					}
				}
				else
				{
					continue;
				}
			}
			if (moves == true)
			{
				XI += 15;
			}
			else if (moves == false)
			{
				if (YI == 200)
				{

					YI += 120;
					XI += 10;

				}
				if (YI == 650)
				{

					YI -= 120;
					XI += 10;
				}
				moves = true;
			}

			if (XI > 900)
			{

				flag = true;
			}
		}

		//player 1

		if (xI > 10)
		{
			for (int i = 0; i <= 12; i++)
			{

				if ((yI >= 200 && yI <= 300) || (yI >= 600 && yI <= 700))
				{

					if ((xI == 200) || (xI == 650))
					{
						moves = false;
					}
				}
				else
				{

					continue;
				}
			}
			if (moves == false)
			{
				if ((yI >= 200 && yI <= 300))
				{
					yI += 120;
				}
				if ((yI >= 600 && yI <= 700))
				{
					yI -= 120;
				}
				moves = true;
			}
		}
		else if (xI < 1010) {

			for (int i = 0; i <= 12; i++)
			{

				if ((yI >= 200 && yI <= 300) || (yI >= 600 && yI <= 700))
				{

					if ((xI == 200) || (xI == 650))
					{
						moves = false;
					}
				}
				else
				{
					continue;
				}
			}
			if (moves == false)
			{
				if ((yI >= 200 && yI <= 300))
				{
					yI += 120;
				}
				if ((yI >= 600 && yI <= 700))
				{
					yI -= 120;
				}
				moves = true;
			}
		}

		//PLAYER 2

		if (xIII > 10)
		{
			for (int i = 0; i <= 12; i++)
			{

				if ((yIII >= 200 && yIII <= 300) || (yIII >= 600 && yIII <= 700))
				{

					if ((xIII == 200) || (xIII == 650))
					{
						moves = false;
					}
				}
				else
				{

					continue;
				}
			}
			if (moves == false)
			{
				if ((yIII >= 200 && yIII <= 300))
				{
					yIII += 120;
				}
				if ((yIII >= 600 && yIII <= 700))
				{
					yIII -= 120;
				}
				moves = true;
			}
		}
		else if (xIII < 1010) {

			for (int i = 0; i <= 12; i++)
			{

				if ((yIII >= 200 && yIII <= 300) || (yIII >= 600 && yIII <= 700))
				{

					if ((xIII == 200) || (xIII == 650))
					{
						moves = false;
					}
				}
				else
				{
					continue;
				}
			}
			if (moves == false)
			{
				if ((yIII >= 200 && yIII <= 300))
				{
					yIII += 120;
				}
				if ((yIII >= 600 && yIII <= 700))
				{
					yIII -= 120;
				}
				moves = true;
			}
		}

		//PLAYER 2 CANNON

		if (XIV > 10 && flag)
		{

			for (int i = 0; i <= 12; i++)
			{

				if ((XIV >= 200 && XIV <= 300) || (XIV >= 600 && XIV <= 700))
				{

					if ((YIV == 200) || (YIV == 650))
					{
						moves = false;
					}
				}
				else
				{

					continue;
				}
			}
			if (moves == true)
			{

				XIV -= 10;

			}
			else if (moves == false)
			{
				if (YIV == 200)
				{

					XIV -= 10;
					YIV -= 120;


				}
				if (YIV == 650)
				{

					YIV -= 120;
					XIV -= 10;


				}
				moves = true;
			}



			if (XIV < 100)
			{

				flag = false;
			}

		}
		else if (XIV < 1010 && !flag) {

			for (int i = 0; i <= 12; i++)
			{
				if ((XIV >= 200 && XIV <= 300) || (XIV >= 600 && XIV <= 700))
				{
					if ((YIV == 200) || (YIV == 650))
					{
						moves = false;
					}
				}
				else
				{
					continue;
				}
			}
			if (moves == true)
			{
				XIV += 15;
			}
			else if (moves == false)
			{
				if (YIV == 200)
				{

					YIV += 120;
					XIV += 10;

				}
				if (YIV == 650)
				{

					YIV -= 120;
					XIV += 10;
				}
				moves = true;
			}

			if (XIV > 900)
			{

				flag = true;
			}
		}

		score_check1();
	}

}
/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {         //timer added for one player  mode bot

	glutTimerFunc(100, Timer, 0);
	glutPostRedisplay();
	// implement your functionality here
	moveCar();
	// once again we tell the library to call our Timer function after next 1000/FPS

}
void Timer1(int m) {        //timer added for two player mode cannons

	glutTimerFunc(100, Timer1, 0);
	glutPostRedisplay();
	// implement your functionality here
	moveCar1();
	// once again we tell the library to call our Timer function after next 1000/FPS

}
//void crediting()
//{
//	glClearColor(0, 0, 0, 0);
//	glClear(GL_COLOR_BUFFER_BIT);
//	DrawString(100, 700, "Credits", colors[WHITE]);
//	glutSwapBuffers();
//}
void highscores()      //high scores screen
{
	PlaySound(TEXT("happy.wav"), NULL, SND_ASYNC);
	glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
		1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT);
	DrawRectangle(0, 0, 1060, 1050, colors[BLUE]);
	DrawString(450, 800, "Highscores", colors[WHITE]);
	DrawString(300, 100, "Press 0 to return to menu", colors[WHITE]);
	fstream file;
	file.open("scoresPlayer.txt");
	if (file.is_open())
	{
		for (int i = 0; i < GAME; i++)
		{
			file << high_scores[i] << endl;
		}
		file.close();
	}
	fstream File;
	string s;
	int i=700 , j=0;
	File.open("scoresPlayer.txt");

	DrawString(100, 750, "NAME:  ", colors[WHITE]);
	while (getline(File, s))
	{
		DrawString(200, i, NAME[j], colors[WHITE]);
		DrawString(300, i, s, colors[WHITE]);
		i=i -50;
		j++;
	}
	File.close();
	glutSwapBuffers();
}
void playersmode()     //function for selecting the player mode 1 or 2
{
	glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
		1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT);
	DrawRectangle(0, 0, 1060, 1050, colors[BLUE]);
	DrawString(400, 650, "Players modes ", colors[WHITE]);
	DrawString(400, 550, "Press 1 for single PLayer mode", colors[WHITE]);
	DrawString(400, 500, "Press 2 for double Player mode", colors[WHITE]);
	glutSwapBuffers();
}
void get_name()       //one player mode
{
	rand_spawn();
	cout << "\nNAME: ";
	cin >> NAME[GAME];
	glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
		1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT);
	DrawRectangle(0, 0, 1060, 1050, colors[BLUE]);

	g.l->set_level( level);
    level = g.l->get_level();
	glutDisplayFunc(game);
	glutTimerFunc(1000.0, Timer, 0);
	glutSwapBuffers();
}
void get_name1()     //two player mode
{
	rand_spawn();
	cout << "\nNAME player1: ";
	cin >> NAME[GAME];
	cout << "\nNAME player2: ";
	cin >> NAME[GAME];
	glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
		1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT);
	DrawRectangle(0, 0, 1060, 1050, colors[BLUE]);
	g.l->set_level(level );
	level = g.l->get_level();
	glutDisplayFunc(game1);
	glutTimerFunc(1000.0, Timer1, 0);
	glutSwapBuffers();
}
void name()    //one player
{
	glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
		1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT);
	DrawRectangle(0, 0, 1060, 1050, colors[BLUE]);
	DrawString(300, 750, "Enter your name", colors[WHITE]);
	glutDisplayFunc(get_name);
	glutSwapBuffers();
}
void name1()       //two player
{

	glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
		1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT);
	DrawRectangle(0, 0, 1060, 1050, colors[BLUE]);
	DrawString(300, 750, "Enter your name", colors[WHITE]);
	glutDisplayFunc(get_name1);
	DrawString(300, 700, NAME[GAME], colors[BLUE]);
	glutSwapBuffers();
}

int player_shape = 1;
void game()      //one player mode
{
	if (level == 1)
	{
		glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
			1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		glClear(GL_COLOR_BUFFER_BIT); //Update the colors



		Hurdles h;
		h.display_design(g , player_mode_2);
		h.set_level(level);     //inheritence applied
		h.display_hurdle();
		if (player_shape == 1)
		{
			drawBot();
			drawTank();
			drawCannon();
			DRAWCANNON();
		}
		else if (player_shape == 2)
		{
			drawBot1();
			drawTank1();
			drawCannon();
			DRAWCANNON();
		}
		else if (player_shape == 3)
		{
			drawBot2();
			drawTank2();
			drawCannon();
			DRAWCANNON();
		}

		glutSwapBuffers(); // do not modify this line..
	}
	if (level == 2)
	{
		glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
			1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		glClear(GL_COLOR_BUFFER_BIT); //Update the colors





		Hurdles h;
		h.display_design(g , player_mode_2);
		h.set_level(level);                 //inheritence applied   //The type of hurdles are added on the screen according to the
											//level number generated. So, the hurdles class inherits the level number from the level_of_match class
		h.display_hurdle();

		if (player_shape == 1)          //bot and player is added according to the player type selected
		{
			drawBot();
			drawTank();
			drawCannon();
			DRAWCANNON();
		}
		else if (player_shape == 2)
		{
			drawBot1();
			drawTank1();
			drawCannon();
			DRAWCANNON();
		}
		else if (player_shape == 3)
		{
			drawBot2();
			drawTank2();
			drawCannon();
			DRAWCANNON();
		}
		glutSwapBuffers(); // do not modify this line..
	}


}
void game1()        //two player mode
{
	if (level == 1)       //level 2
	{
		glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
			1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		glClear(GL_COLOR_BUFFER_BIT); //Update the colors


		Hurdles H;
		H.display_design(g , player_mode_2);
		H.set_level(level);		  //inheritence applied   //The type of hurdles are added on the screen according to the
								  //level number generated. So, the hurdles class inherits the level number from the level_of_match class
		H.display_hurdle();

		if (player_shape == 1)
		{

			drawTank();
			drawTANK();
			drawCannon();
			DRAWCANNONIV();
		}
		else if (player_shape == 2)
		{

			drawTank1();
			drawTANK1();
			drawCannon();
			DRAWCANNONIV();
		}
		else if (player_shape == 3)
		{

			drawTank2();
			drawTANK2();
			drawCannon();
			DRAWCANNONIV();
		}
		glutSwapBuffers(); // do not modify this line..
	}
	if (level == 2)      //level 1
	{
			glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
				1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
			glClear(GL_COLOR_BUFFER_BIT);     //Update the colors



			Hurdles h;
			h.display_design(g , player_mode_2);
			h.set_level(level);			  //inheritence applied   //The type of hurdles are added on the screen according to the
											//level number generated. So, the hurdles class inherits the level number from the level_of_match class
			h.display_hurdle();

			if (player_shape == 1)
			{

				drawTank();
				drawTANK();
				drawCannon();
				DRAWCANNONIV();
			}
			else if (player_shape == 2)
			{

				drawTank1();
				drawTANK1();
				drawCannon();
				DRAWCANNONIV();
			}
			else if (player_shape == 3)
			{

				drawTank2();
				drawTANK2();
				drawCannon();
				DRAWCANNONIV();
			}
			glutSwapBuffers(); // do not modify this line.

	}
}
void MenuDisplay()        //menu display function
{
	PlaySound(TEXT("happy.wav"), NULL, SND_ASYNC);
	glClearColor(1/*Red Component*/, 1,	//148.1/255/*Green Component*/,
		1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT );
	DrawRectangle(0, 0, 1060,1050, colors[BLUE]);
	DrawString(500, 750, "MENU", colors[WHITE]);
	DrawString(400, 650, "H-Highscores", colors[WHITE]);
	DrawString(400, 550, "S-Settings", colors[WHITE]);
	DrawString(400, 450, "P-Players modes ", colors[WHITE]);
	DrawString(400, 350, "Press the option key to select it", colors[WHITE]);
	glutSwapBuffers();

}
void MenuDisplay1()         //menu displayed after the esc key is pressed
{
	PlaySound(TEXT("happy.wav"), NULL, SND_ASYNC);
	Player *pla=new Player;
	pla->set_score(score_player);
	pla->player_progress();       //player progress

}



/*
 * Main Canvas drawing function.
 * */

void Display(){

		MenuDisplay(); //CALLING MENU DISPLAY
}


/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		xI -= 10;    //x coordinate for player
		XI =xI;      //for player cannon

		xII += 8;        //for bot
		XII = xII;        //for bot cannon
	}
	else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/)
	{
		xI += 10;
		XI = xI;

		xII -= 8;
		XII =xII;
	}
	else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		yI += 10;
		YI = yI;

		yII +=6;
		YII = yII;
	}

	else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		yI -= 10;
		YI = yI;

		yII -=6;
		YII = yII;
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		glutDisplayFunc(MenuDisplay1);
	}

	else if (key == 't' ) //Key for selecting tank
	{
		player_shape = 1;

	}
	else if (key == 'h') //Key for selecting helicopter
	{
		player_shape = 2;
	}
	else if (key == 'p') //Key for selecting plane
	{
		player_shape = 3;
	}
	else if ( key == 'H')  //highscores
	{

		glutDisplayFunc(highscores);
	}
	else if (key == 'P')      //mode
	{
		glutDisplayFunc(playersmode);
	}
	else if (key == 'S' )  //settings
	{
		glutDisplayFunc(Settings);

	}
	else if (key == 'k' || key == 'K')   //continue to menu
	{
		glutDisplayFunc(MenuDisplay);

	}

	else if (key == '1')
	{
		score_bot = 0;
		score_player = 0;
		glClear(GL_COLOR_BUFFER_BIT);
		glutDisplayFunc(name);
		glutSwapBuffers();
	}
	else if (key == '2')
	{
		score_bot = 0;
		score_player = 0;
		player_mode_2++;
		if (player_mode_2 == 2)
		{
			level = 2;
			glClear(GL_COLOR_BUFFER_BIT);
			glutDisplayFunc(name1);
			glutSwapBuffers();
		}
		if (player_mode_2 == 1)
		{
			level = 1;
			glClear(GL_COLOR_BUFFER_BIT);
			glutDisplayFunc(name1);
			glutSwapBuffers();
		}

	}
	else if (key == '0')      //start
	{
		GAME++;
		score_player = 0;
		score_bot = 0;
		bool menu=true;
		if (menu == true)
		{
			glutDisplayFunc(Display);
			menu = false;
		}
	}
	else if (key == 's')
	{
		g.c->small_cannon_count++;
	}
	else if (key == 'm')
	{
		g.c->medium_cannon_count++;
	}
	else if (key == 'l')
	{
		g.c->large_cannon_count++;
	}
	//FCVB

	else if (key == 'F' || key == 'f') //control keys for the player 2
	{
		yIII +=6;
		YIV = yIII;
	}
	else if (key == 'C' || key == 'c')
	{
		xIII -= 8;
		XIV = xIII;
	}

	else if (key == 'V' || key == 'v')
	{
		yIII -= 6;
		YIV = yIII;
	}
	else if (key == 'B' || key == 'b')
	{
		xIII += 8;
		XIV = xIII;
	}

	glutPostRedisplay();
}





/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			cout<<"Right Button Pressed"<<endl;

	}
	glutPostRedisplay();
}

/*
 * our gateway main function
 * */

int main(int argc, char*argv[]) {
	int width = 1060, glut_sub_sub_menu = 0, height = 850; // i have set my window size to be 800 x 600

	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // we will be using color display mode
	glutInitWindowPosition(50, 100); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window

	glutCreateWindow("Menu game By fatima"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks


	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse
	Combat_Game c;
	c.set_match_num(1);
	c.Combat_Game_set();



		// now handle the control to library and it will call our registered functions when
		// it deems necessary...
		glutMainLoop();



}
#endif /* RushHour_CPP_ */
