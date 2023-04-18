/******************************************************************************/
/*!
\file            Data.h
\project name    Finding Coffin
\author          Jiwon Jung, Wonjae Jung, Seungeun Ji
\par             GAM150
\brief

This is file contains most of data sound, count, texture and switchs

All content © 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdio>

#include "GameTypes.h"
#include "DemoStates.h"

#include "WEInput.h"
#include "WEStateManager.h"
#include "WEGraphics.h"
#include "WEMtx44.h"
#include "WEApplication.h"
#include "WEIntersection.h"
#include "WERandom.h"
#include "WEDebugTools.h"
#include "WEMath.h"
#include "WEVec2.h"

//////////////FMOD
#include "fmod.hpp"
#include "common.h"

/////////////////Menu
#include "Menu.h"

#define NumofBackground 100
#define Start_position 0
#define Ending_position 100000
#define heightofbox 14
#define floor 0
#define Infront 200

extern float score;

namespace
{
const float BOX_HEIGHT = 64.f;
const float BOX_WIDTH = 64.f;
const float MAX_JUMP = 0.16f;
const float MAX_FALL = 0.304f;

struct InitData
{
		
	Object Human;
	Object s_Human;
	Box box[2000];
	Box spike[100];
	Background background[NumofBackground];
	Background background2[NumofBackground];

	Particle123 particles [1000];
	Particle123 particles2[1000];

	//texture of main character
	int PlayerTexture;
	int PlayerTexture2;
	int PlayerTexture3;
	int PlayerTexture4;
	int PlayerTexture5;
	int PlayerTexture6;

	int SlideTexture;
	int SlideTexture2;
	int SlideTexture3;
	int SlideTexture4;
	int SlideTexture5;
	int SlideTexture6;

	//other textures for game
	int BGTexture;
	int BGGTexture;
	int BoxTexture;
	int SpikeTexture;
	int CoffinTexture;

	//score number texture
	int zero;
	int one;
	int two;
	int three;
	int four;
	int five;
	int six;
	int seven;
	int eight;
	int nine;
	int SCORE;

	//temp value of score to print out score
	int dvNUM;

	int ScoreTex1000;
	int ScoreTex5000;
	int ScoreTex10000;

	/*For Particle*/
	int      starTexture;

	int num;
	float x;
	int BoxID;
	float FinalScore;
		


	float textcoord;
	float totalTime;

	float Jtime; //Jumping Time
	float Ftime;
	float Dtime;
	float Stime; //Sliding Time

	bool Switch;
	bool DJSwitch;//switch for preventing double jump
	bool SlideSwitch;

	float screenWidth;
	float screenHeight;
	float cameraZ;
	float cameraX;
	float cameraY;
	float cameraRot;


	float timerCount;
};

InitData data;

typedef void(*Action)(void);

struct Button
{
	WEVec2 pos;
	WEVec2 scale;
	Action action;
};


struct SoundData
{
	FMOD::System     *system;
	FMOD::Sound      *sound1, *sound2, *sound3, *sound4, *background, *sound_to_play;
	FMOD::Channel    *channel = 0;
	FMOD_RESULT       result;
	unsigned int      version;
	void             *extradriverdata = 0;
	int               numsubsounds;
};
SoundData f_data;

	
float count()
{
	float num = 0;

	return num;
}

}//end unnamed namespace

#endif