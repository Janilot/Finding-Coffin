/******************************************************************************/
/*!
\file            Level2.cpp
\project name    Finding Coffin
\author          Wonjae Jung - Particle, Generated Map, Collision, 
                               Background, Cheat key, Color change
				 Seungeun Ji - FMOD Sound, Score, Score image screen
				 Jiwon Jung  - Jump physics, Score text, 

\par             GAM150
\brief

This is file contains the code for collision, player control, game level state
and score

All content © 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Level2.h"
#include "Data.h"
#include "Actions.h"

#define FINDING_COFFIN 45000

/*The max time to be in this state*/
const float FONT_SPACING    = 20.f;
const int   ARRAY_SIZE      = 20;
const int   MAX_COLORS      = 5;  //!<MAX COLORS
const int   RED             = 0;  //!<RED COLORS
const int   YELLOW          = 1;  //!<YELLOW COLORS
const int   BLUE            = 2;  //!<BLUE COLORS
const int   GREEN           = 3;  //!<GREEN COLORS
const int   WHITE           = 4;  //!<GREEN COLORS
float       ClearValue      = 0;
bool        forClear        = false;
bool        CHEAT           = false;
float       m_minTrailVel   = 0;
float       m_maxTrailVel   = 100;
float       m_minTrailScale = 0.25;
float       m_maxTrailScale = 1;
float       m_scaleFactor   = 1;
float       m_minExpVel     = 20;
float       m_maxExpVel     = 200;
float       m_minExpScale   = 2;
float       m_maxExpScale   = 4;
float xVALUE;

unsigned  g_colors[MAX_COLORS] = { 0xFF0000FF, 0xFF00FFFF, 0xFFFFFF00, 0xFF00FF00, 0xFFFFFFFF }; //!< colors 
/*File*/
void LoadFile(const char* fileName)
{
		FILE* pFile = 0;
		fopen_s(&pFile, fileName, "rt");
		WEDEBUG_ASSERT(pFile != 0, "Can't open the file!!!");
		fscanf_s(pFile, "%d", &data.BoxID);
		fscanf_s(pFile, "%d", &data.num);

		for (int i = 0; i <= data.num; ++i)
		{
				fscanf_s(pFile, "%f", &data.box[i].pos.x);
				fscanf_s(pFile, "%f", &data.box[i].pos.y);

				data.box[i].scale.x = 20;
				data.box[i].scale.y = 15;
				std::cout << std::endl;
				//spike
				if (data.box[i].pos.y == 0)
				{
						data.spike[i].pos.x   = data.box[i].pos.x;
						data.spike[i].pos.y   = data.box[i].pos.y;
				}
		}
		fclose(pFile);
}//end LoadFile
/******************************************************************************/
/*!
Call my Objectproperties
*/
/******************************************************************************/
void DrawBox(int num)
{
		if (num == 1)
				LoadFile("ObjectProperties1.txt");

		if (num == 2)
				LoadFile("ObjectProperties2.txt");

		if (num == 3)
				LoadFile("ObjectProperties3.txt");

		if (num == 4)
			    LoadFile("ObjectProperties4.txt");

		if (num == 5)
				LoadFile("ObjectProperties5.txt");

		if (num == 6)
				LoadFile("ObjectProperties6.txt");

		if (num == 7)
		  	    LoadFile("ObjectProperties7.txt");
	
		if (num == 8)
				LoadFile("ObjectProperties8.txt");

		if (num == 9)
				LoadFile("ObjectProperties9.txt");

		if (num == 10)
				LoadFile("ObjectProperties10.txt");
	
		if (num == 11)
				LoadFile("ObjectProperties11.txt");
	
		for (int i = 0; i < data.num; ++i)
		{
				data.box[i].pos.x += data.Human.pos.x + Infront;
		}
}//end DrawBox

#define WE_ANI_TIMER .1f
/******************************************************************************/
/*!
Load my textures
*/
/******************************************************************************/
void Level2Load(void)
{
		/*Load my textures used for this state*/
		data.PlayerTexture  = WEGraphics::LoadTexture("Textures\\mainChar.tga");
		data.PlayerTexture2 = WEGraphics::LoadTexture("Textures\\bluechar.tga");
		data.PlayerTexture3 = WEGraphics::LoadTexture("Textures\\redchar.tga");
		data.PlayerTexture4 = WEGraphics::LoadTexture("Textures\\yellowchar.tga");
		data.PlayerTexture5 = WEGraphics::LoadTexture("Textures\\Y_Redchar.tga");
		data.PlayerTexture6 = WEGraphics::LoadTexture("Textures\\MUchar.tga");

		data.SlideTexture  = WEGraphics::LoadTexture("Textures\\s_mainchar.tga");
		data.SlideTexture2 = WEGraphics::LoadTexture("Textures\\s_bluechar.tga");
		data.SlideTexture3 = WEGraphics::LoadTexture("Textures\\s_redchar.tga");
		data.SlideTexture4 = WEGraphics::LoadTexture("Textures\\s_yellowchar.tga");
		data.SlideTexture5 = WEGraphics::LoadTexture("Textures\\s_Y_Redchar.tga");

		data.BGTexture     = WEGraphics::LoadTexture("Textures\\BG.tga");
		data.BGGTexture    = WEGraphics::LoadTexture("Textures\\BBG.tga");
		data.BoxTexture    = WEGraphics::LoadTexture("Textures\\Object.tga");
		data.SpikeTexture  = WEGraphics::LoadTexture("Textures\\spike.tga");
		data.CoffinTexture = WEGraphics::LoadTexture("Textures\\coffin.tga");

		//For score texture
		data.ScoreTex1000  = WEGraphics::LoadTexture("Textures\\1000.tga");
		data.ScoreTex5000  = WEGraphics::LoadTexture("Textures\\5000.tga");
		data.ScoreTex10000 = WEGraphics::LoadTexture("Textures\\10000.tga");

		data.zero = WEGraphics::LoadTexture("Textures\\0.tga");
		data.one = WEGraphics::LoadTexture("Textures\\1.tga");
		data.two = WEGraphics::LoadTexture("Textures\\2.tga");
		data.three = WEGraphics::LoadTexture("Textures\\3.tga");
		data.four = WEGraphics::LoadTexture("Textures\\4.tga");
		data.five = WEGraphics::LoadTexture("Textures\\5.tga");
		data.six = WEGraphics::LoadTexture("Textures\\6.tga");
		data.seven = WEGraphics::LoadTexture("Textures\\7.tga");
		data.eight = WEGraphics::LoadTexture("Textures\\8.tga");
		data.nine = WEGraphics::LoadTexture("Textures\\9.tga");
		data.SCORE = WEGraphics::LoadTexture("Textures\\score.tga");

		//For Particle
		data.starTexture = WEGraphics::LoadTexture("Textures//Star.tga");

		WEGraphics::SetToOrtho();
}
/******************************************************************************/
/*!
Initialize data
*/
/******************************************************************************/
void Level2Init(void)
{
	data.x = 10000000;
		//For Particle Init
		for (int i = 0; i < 1000; ++i)
		{
				data.particles[i].pos.x = -200;
				data.particles[i].pos.y = -200;
				data.particles[i].vel.x = 0;
				data.particles[i].vel.y = 0;
				data.particles[i].color = 0;

				data.particles2[i].pos.x = 200;
				data.particles2[i].pos.y = 200;
				data.particles2[i].vel.x = 0;
				data.particles2[i].vel.y = 0;
				data.particles2[i].color = 0;
		}
	

		//For Particle scale Init
		for (int i = 0; i < 1000; ++i)
		{
			data.particles [i].scale = 0;
			data.particles2[i].scale = 0;

		}
		WERandom::Seed((int)time(0));

		LoadFile("ObjectProperties0.txt");

		data.screenWidth  = (float)WEApplication::GetWidth();
		data.screenHeight = (float)WEApplication::GetHeight();

		//Human position init
		data.Human.pos.x   = -50;
		data.Human.pos.y   = 13;
		data.Human.scale.x = 30;
		data.Human.scale.y = 40;
		data.Human.vel.x   = 100;
		data.Human.vel.y   = 50;

		//Slide Human position init
		data.s_Human.pos.x   = -40;
		data.s_Human.pos.y   = -50;
		data.s_Human.scale.x = 35;
		data.s_Human.scale.y = 30;
		data.s_Human.vel.x   = 50;
		data.s_Human.vel.y   = 50;

		/*bacground init*/
		data.background[0].pos.x    = 0;
		data.background[0].pos.y    = 63;
		data.background[0].scale.x  = 400;
		data.background[0].scale.y  = 200;
		data.background2[0].pos.x   = 0;
		data.background2[0].pos.y   = 95;
		data.background2[0].scale.x = 3000;
		data.background2[0].scale.y = 200;


		//Switch
		data.Switch = FALSE;
		data.DJSwitch = FALSE;
		data.SlideSwitch = FALSE;

		data.Jtime = 0;
		data.Ftime = 0;
		data.Dtime = 0;
		data.Stime = 0;
		data.FinalScore = 0;
		data.dvNUM = 0;

		/*Set time*/
		data.textcoord = 0.0f;
		data.totalTime = 0.0f;

		/*Set Camera*/
		data.cameraZ = 90.f;
		data.cameraX = 0.f;
		data.cameraY = 63.f;
		data.cameraRot = 0.0f;
		/*Set the background color*/
		WEGraphics::SetBackgroundColor(0, 0, 0);

		///////////////////////////////////////////FMOD
		Common_Init(&f_data.extradriverdata);

		f_data.result = FMOD::System_Create(&f_data.system);
		ERRCHECK(f_data.result);

		f_data.result = f_data.system->getVersion(&f_data.version);
		ERRCHECK(f_data.result);

		if (f_data.version < FMOD_VERSION)
		{
			Common_Fatal("FMOD lib version %08x doesn't match header version %08x", f_data.version, FMOD_VERSION);
		}

		f_data.result = f_data.system->init(32, FMOD_INIT_NORMAL, f_data.extradriverdata);
		ERRCHECK(f_data.result);

		f_data.result = f_data.system->createSound(Common_MediaPath("Jump.wav"), FMOD_DEFAULT, 0, &f_data.sound1);
		ERRCHECK(f_data.result);

		/* drumloop.wav has embedded loop points which automatically makes looping turn on, */
		f_data.result = f_data.sound1->setMode(FMOD_LOOP_OFF);
		/* so turn it off here.  We could have also just put FMOD_LOOP_OFF in the above CreateSound call. */
		ERRCHECK(f_data.result);

		f_data.result = f_data.system->createSound(Common_MediaPath("Crash.wav"), FMOD_DEFAULT, 0, &f_data.sound2);
		ERRCHECK(f_data.result);

		/* drumloop.wav has embedded loop points which automatically makes looping turn on, */
		f_data.result = f_data.sound2->setMode(FMOD_LOOP_OFF);
		/* so turn it off here.  We could have also just put FMOD_LOOP_OFF in the above CreateSound call. */
		ERRCHECK(f_data.result);

		f_data.result = f_data.system->createSound(Common_MediaPath("slide.2"), FMOD_DEFAULT, 0, &f_data.sound3);
		ERRCHECK(f_data.result);

		/* drumloop.wav has embedded loop points which automatically makes looping turn on, */
		f_data.result = f_data.sound3->setMode(FMOD_LOOP_OFF);
		/* so turn it off here.  We could have also just put FMOD_LOOP_OFF in the above CreateSound call. */
		ERRCHECK(f_data.result);

		f_data.result = f_data.system->createSound(Common_MediaPath("score.wav"), FMOD_DEFAULT, 0, &f_data.sound4);
		ERRCHECK(f_data.result);

		/* drumloop.wav has embedded loop points which automatically makes looping turn on, */
		f_data.result = f_data.sound4->setMode(FMOD_LOOP_OFF);
		/* so turn it off here.  We could have also just put FMOD_LOOP_OFF in the above CreateSound call. */
		ERRCHECK(f_data.result);

		//////stream//////
		f_data.result = f_data.system->createSound(Common_MediaPath("Bee.mp3"), FMOD_LOOP_NORMAL | FMOD_2D, 0, &f_data.background);
		ERRCHECK(f_data.result);

		f_data.result = f_data.background->getNumSubSounds(&f_data.numsubsounds);
		ERRCHECK(f_data.result);

		if (f_data.numsubsounds)
		{
			f_data.background->getSubSound(0, &f_data.sound_to_play);
			ERRCHECK(f_data.result);
		}
		else
		{
			f_data.sound_to_play = f_data.background;
		}

		/*
		Play the sound.
		*/
		f_data.result = f_data.system->playSound(f_data.sound_to_play, 0, false, &f_data.channel);
		ERRCHECK(f_data.result);

		/*Reset the timer for this state*/
		data.timerCount  = 0.f;


}
/******************************************************************************/
/*!
Update game and draw objects
*/
/******************************************************************************/
void Level2Update(float dt)
{
	 /*Trail particle*/
	for (int i = 0; i < 1000; ++i)
	{
			//If scale of particle is 0
			if (data.particles[i].scale == 0)
			{
					float vel = WERandom::GetFloat(m_minTrailVel, m_maxTrailVel);
					//Get rotation of emitter using atan2
					float rotation = atan2(data.Human.vel.y, data.Human.vel.x);

					//Rotate that value by PI
					rotation += WEMath::PI;
					//Add a random rotation between + or PI/4
					rotation += WERandom::
							GetFloat(-WEMath::PI*0.25f, WEMath::PI*0.25f);

					//Use rotation to calculate velocity x and y
					data.particles[i].vel.x = cosf(rotation);
					data.particles[i].vel.y = sinf(rotation);

					data.particles[i].vel.Normalize();
					data.particles[i].vel *= vel;

					//Set particle position to emitter position.
					data.particles[i].pos.x = data.Human.pos.x + 3;
					data.particles[i].pos.y = data.Human.pos.y - 13;
					//Scale velocity random float between min/max TrailVel.
					data.particles[i].scale
							= WERandom::GetFloat(m_minTrailScale, m_maxTrailScale);

			}
			//Update particle position based on velocity and dt
			data.particles[i].pos += data.particles[i].vel*dt;
			//pEmitter->pParitcles[i].pos += pEmitter->vel*dt;

			//Update particle scale based on scaleFactor and dt
			data.particles[i].scale -= m_scaleFactor*dt;
			//Clamp particle scale to 0 and maxTrailScale
			data.particles[i].scale = WEMath::Clamp(data.particles[i].scale, 0, m_maxTrailScale);
	}

	/******Exp****/
	for (int i = 0; i < 200; ++i)
	{
		if (score > 1000 && score < 1050
			|| score > 5000 && score < 5200
			|| score > 10000 && score < 10300
			|| score > 15000 && score < 15300)
		{
			data.particles2[i].pos.x = data.Human.pos.x;
			data.particles2[i].pos.y = data.Human.pos.y;

			float vel = WERandom::GetFloat(m_minExpVel, m_maxExpVel) * 70;
			//Get rotation of emitter using atan2
			float rotation = WERandom::GetFloat(WEMath::PI * 2 / 3, WEMath::PI * 1 / 3);

			//Use rotation to calculate velocity x and y
			data.particles2[i].vel.x = cosf(rotation);
			data.particles2[i].vel.y = sinf(rotation);

			//data.particles2[i].vel.Normalize();
			data.particles2[i].vel *= vel;

			//Set particle position to emitter position.
			data.particles2[i].pos.x = data.Human.pos.x + 3;
			data.particles2[i].pos.y = -25;
			//Scale velocity random float between min/max TrailVel.

			data.particles2[i].scale
				= WERandom::GetFloat(m_minExpScale, m_maxExpScale);

			//Update particle position based on velocity and dt
			data.particles2[i].pos += data.particles2[i].vel*dt;

			//Update particle scale based on scaleFactor and dt
			data.particles2[i].scale -= m_scaleFactor*dt;
			//Clamp particle scale to 0 and maxTrailScale
			data.particles2[i].scale = WEMath::Clamp(data.particles2[i].scale, 0, m_maxExpScale);
		}
		else
		{
			data.particles2[i].scale = 0;
		}
	}

	/****************** Random Object ******************/
	if (score < 35000)
	{
			for (int i = 1; i < 150; i++)
			{

					if (data.Human.pos.x > 900 * i && data.Human.pos.x < (900 * i) + 4)
					{
							if (score > 1000 && score < 5000)
							{
									int random = WERandom::GetInt(2, 5);
									DrawBox(random);
							}
							else if (score >5000 && score < 10000)
							{
									int random = WERandom::GetInt(4, 6);
									DrawBox(random);
							}
							else if (score >10000 && score < 15000)
							{
									int random = WERandom::GetInt(5, 8);
									DrawBox(random);
							}
							else if (score > 15000)
							{
									int random = WERandom::GetInt(6, 11);
									DrawBox(random);
							}
							else
							{
									int random = WERandom::GetInt(0, 3);
									DrawBox(random);
							}
					}
			}
	}

/*********************************************************/
		WEMtx44 transform;
		data.totalTime += dt;

		/*if press ESC key, quit game*/
		if (WEInput::IsTriggered(WE_ESCAPE))
				WEStateManager::Quit();

		if (data.totalTime > WE_ANI_TIMER)
		{
				data.totalTime = 0.0f;
				data.textcoord += .25f;
				WEMath::Wrap(data.textcoord, 0.0f, 1.0f);
		}

		WEGraphics::StartDraw();

		/*Update the camera since it could have moved*/
		WEGraphics::SetCamera(data.cameraX, data.cameraY, data.cameraZ,
				data.cameraRot);

		WEGraphics::SetToPerspective();
		//Draw the particle*************************************************************************
		WEGraphics::SetTexture(data.starTexture);
	
		for (int i = 0; i < 1000; ++i)
		{
				if (score > 1000 && score < 5000)
				{
						WEGraphics::SetTextureColor(g_colors[BLUE]);
				}
				else if (score >5000 && score < 10000)
				{
						WEGraphics::SetTextureColor(g_colors[RED]);
				}
				else if (score >10000 && score < 15000)
				{
						WEGraphics::SetTextureColor(g_colors[YELLOW]);
				}
				else if (score > 15000)
				{
						int COLOR;
						COLOR = WERandom::GetInt(-1, 4);
						WEGraphics::SetTextureColor(g_colors[COLOR]);
				}
				else
				{
						WEGraphics::SetTextureColor(g_colors[WHITE]);
				}
				WEMtx44::MakeTransform(transform,
						data.particles[i].scale,
						data.particles[i].scale,
						0.f,
						data.particles[i].pos.x,
						data.particles[i].pos.y,
						1.f);

				WEGraphics::Draw(transform);
		}
		//Draw the particle*************************************************************************
		WEGraphics::SetTexture(data.starTexture);

		for (int i = 0; i < 1000; ++i)
		{
			int COLOR;
			if (score > 1000 && score < 5000)
			{
				COLOR = WERandom::GetInt(YELLOW, GREEN);
				WEGraphics::SetTextureColor(g_colors[COLOR]);
			}
			else if (score >5000 && score < 10000)
			{
				COLOR = WERandom::GetInt(-1, BLUE);
				if (COLOR!=1)
				WEGraphics::SetTextureColor(g_colors[COLOR]);
			}
			else if (score >10000 && score < 15000)
			{
				COLOR = WERandom::GetInt(-1, YELLOW);
				WEGraphics::SetTextureColor(g_colors[COLOR]);
			}
			else if (score > 15000)
			{
				COLOR = WERandom::GetInt(-1, WHITE);
				WEGraphics::SetTextureColor(g_colors[COLOR]);
			}
			else
			{
				WEGraphics::SetTextureColor(g_colors[WHITE]);
			}
			
			WEMtx44::MakeTransform(transform,
				data.particles2[i].scale,
				data.particles2[i].scale,
				0.f,
				data.particles2[i].pos.x,
				data.particles2[i].pos.y,
				1.f);

			WEGraphics::Draw(transform);
		}
		/*Drawing Background Terrain to the whole level*/

		/*Draw BackGround 1*/

		for (float i = 0; i < 100000; i += 338.0f)
		{
				WEGraphics::SetTexture(data.BGTexture);//Background
				WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);

				/*Draw an object with a transform and apply a color*/
				WEGraphics::SetTextureColor(0xFFFFFFFF);
				WEMtx44::MakeTransform(transform,
						data.background[0].scale.x,
						data.background[0].scale.y,
						0.0f,
						data.background[0].pos.x + i,
						data.background[0].pos.y,
						0.0f);
				WEGraphics::Draw(transform);
		}

		/*******************BackGround*************************/
		for (int i = 0; i < 100000; i+=338)
		{
				WEGraphics::SetTexture(data.BGGTexture);//Background
				WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
				/*Draw an object with a transform and apply a color*/
				WEGraphics::SetTextureColor(0xFFFFFFFF);
				WEMtx44::MakeTransform(transform,
						data.background2[0].scale.x,
						data.background2[0].scale.y,
						0.0f,
						data.background2[0].pos.x + i,
						data.background2[0].pos.y,
						0.0f);
				WEGraphics::Draw(transform);
		}
		data.background2[0].pos.x += 2;

		int Player = data.PlayerTexture;
		if (score > 1000)
				Player = data.PlayerTexture2;
		
		if (score > 5000)
				Player = data.PlayerTexture3;
		
		if (score > 10000)
				Player = data.PlayerTexture4;
		
		if (score > 15000)
				Player = data.PlayerTexture5;
		
		if (score > 35000)
				Player = data.PlayerTexture6;

		/*set player to the game*/
		WEGraphics::SetTexture(Player);
		WEGraphics::SetTextureCoords(.25f, 1.0f, 0.0f, data.textcoord, 0.0f);
		WEMtx44::MakeTransform(transform,
				data.Human.scale.x,
				data.Human.scale.y,
				0.0f,
				data.Human.pos.x,
				data.Human.pos.y,
				1.0);
/*************************************  Moving   *************************************************/
		data.Human.pos.x += data.Human.vel.x * dt * 2;
		data.cameraX = data.Human.pos.x + 90;

/*************************************  Collision(death condition)   *************************************************/
	if (CHEAT != true)
	{
		for (int i = 0; i < data.num; ++i)
		{
				Object& Human = data.Human;
				Box& box = data.box[i];

				if (box.pos.y == 0)
				{
					if (Human.pos.x > box.pos.x - 15 && Human.pos.x < box.pos.x + 10
							&& Human.pos.y< box.pos.y + 23 && Human.pos.y> box.pos.y)
					{
							Human.vel.x = 0;
							data.Dtime += dt;
							forClear = true;
					}
				}
				else if (box.pos.y != 0)
				{
					if (Human.pos.x > box.pos.x - 20 && Human.pos.x < box.pos.x + 15
							&& Human.pos.y< box.pos.y + 23 && Human.pos.y> box.pos.y)
					{
							Human.vel.x = 0;
							data.Dtime += dt;
							forClear = true;
					}
				}
				// makes player to slide through
				if (Human.pos.x > box.pos.x - 20 && Human.pos.x < box.pos.x + 15
						&& Human.pos.y < box.pos.y && !(WEInput::IsPressed(WE_ARROW_DOWN) || WEInput::IsPressed(WE_MOUSE_RIGHT)))
				{
						Human.vel.x = 0;
						data.Dtime += dt;
						forClear = true;
				}
			}
	}//end cheat
		/*Ending position*/
		if (score > FINDING_COFFIN)
		{
				WEStateManager::Quit();
		}

		/*cheat key*/
		if (WEInput::IsTriggered(WE_1))
				data.Human.vel.x = 0;
		
		if (WEInput::IsTriggered(WE_2))
				data.Human.vel.x = 100;
		
		if (WEInput::IsTriggered(WE_3))
				data.Human.vel.x += 50;
		
		if (WEInput::IsTriggered(WE_4))
				data.Human.vel.x -= 50;
		
		if (WEInput::IsTriggered(WE_5))
				CHEAT = true;
		
		if (WEInput::IsTriggered(WE_6))
				CHEAT = false;
		
		if (WEInput::IsTriggered(WE_7))
			 data.Human.pos.x += 10000;
		
		if (WEInput::IsTriggered(WE_8))
				score += 10000;
		
		///////////////////////////////////////////////////Code for fixing the crash sound :) By Quesik
		if (forClear == true && ClearValue == 0)
			ClearValue = dt;

		if (ClearValue == dt && forClear == true)
			f_data.result = f_data.system->playSound(f_data.sound2, 0, false, &f_data.channel);

		if (ClearValue > 0)
		{
			ClearValue += dt;
		}
		///////////////////////////////////////////////////////////////
		// after 2sec, go back to first
		if (data.Dtime > 0 && ClearValue > 0.4f)
		{
			f_data.result = f_data.background->release();
			ERRCHECK(f_data.result);
		  data.Dtime = 0;
			ClearValue = 0;
			forClear = false;
		  WEStateManager::SetNextState(DS_END);
		}
		
///////////////////////////////////////////////////////////////////Player Control
		/*Sliding*/
		if (WEInput::IsPressed(WE_ARROW_DOWN) || WEInput::IsPressed(WE_MOUSE_RIGHT)) //Should ask
		{
			data.SlideSwitch = TRUE;
			++data.Stime;
		}
		//sound
		if (data.Stime == 1)
		{
			f_data.result = f_data.system->playSound(f_data.sound3, 0, false, &f_data.channel);
		}
		if (data.SlideSwitch == TRUE)
		{
			data.s_Human.pos.x = data.Human.pos.x;
			data.s_Human.pos.y = data.Human.pos.y - 10;

			//color change
			int s_Player = data.SlideTexture;

			if (score > 1000)
				s_Player = data.SlideTexture2; //blue

			if (score > 5000)
				s_Player = data.SlideTexture3; //red

			if (score > 10000)
				s_Player = data.SlideTexture4; //yellow

			if (score > 15000)
				s_Player = data.SlideTexture5; //rain bow

			//draw slide character
			WEGraphics::SetTexture(s_Player);
			WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
			WEMtx44::MakeTransform(transform,
				data.s_Human.scale.x,
				data.s_Human.scale.y,
				0.0f,
				data.s_Human.pos.x,
				data.s_Human.pos.y,
				1.0);

			if (!(WEInput::IsPressed(WE_ARROW_DOWN) || WEInput::IsPressed(WE_MOUSE_RIGHT)))
			{
				data.SlideSwitch = FALSE;
				data.Stime = 0;
			}
		}
		/**************************JUMP*************************************/
		if ((WEInput::IsTriggered(WE_SPACE) || WEInput::IsTriggered(WE_ARROW_UP) 
			|| WEInput::IsTriggered(WE_MOUSE_LEFT))
			&& data.Ftime == 0 && !WEInput::IsPressed(WE_ARROW_DOWN)
			&& !WEInput::IsPressed(WE_MOUSE_RIGHT)) 
		{ //blocking down arrow key is for preventing errors
				data.Switch   = TRUE;
				data.DJSwitch = TRUE;
				//sound
				f_data.result = f_data.system->playSound(f_data.sound1, 0, false, &f_data.channel);
		}

		if (data.Switch == TRUE)
		{
				data.Jtime += dt;
				data.Human.pos.y += 8.6f * data.Human.vel.y * dt;
				data.Human.vel.y *= .90f;
				if (data.Jtime > MAX_JUMP)
				{
						data.Switch = FALSE;
						data.Jtime = 0;
				}
		}
		/********Prevent double jumping***********/
		if (data.DJSwitch == TRUE)
		{
				data.Ftime += dt;
				if (data.Switch == FALSE)
					data.Human.vel.y *= 1.1f;
				if (data.Ftime > MAX_FALL)
				{
						data.DJSwitch = FALSE;
						data.Ftime = 0;
						data.Human.vel.y = 50;
				}
		}
		/***************serves gravity role*********************/
		if (data.Human.pos.y > 13)
		{
			data.Human.pos.y -= 4.3f * data.Human.vel.y * dt;

		  for (int i = 0; i < data.num; i++)
			{
				Object& Human = data.Human;
				Box& box = data.box[i];
				if (Human.pos.x > box.pos.x - 20 && Human.pos.x < box.pos.x + 15 
						&& Human.pos.y < box.pos.y + 23 && box.pos.y != 0)
				{
					Human.pos.y = box.pos.y + 23;
				}
			}
		}
		WEGraphics::Draw(transform);
		/*Box*/
		
		for (int i = 0; i < data.num; i++)
		{
				/*Spike*/
				if (data.box[i].pos.y == 0)
				{
						WEGraphics::SetTexture(data.SpikeTexture);
						WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
						WEMtx44::MakeTransform(transform,
								data.box[i].scale.x,
								data.box[i].scale.y,
								0.0f,
								data.box[i].pos.x,
								data.box[i].pos.y,
								1.0);
						WEGraphics::Draw(transform);
				}
				else
				{
						WEGraphics::SetTexture(data.BoxTexture);
						WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
						WEMtx44::MakeTransform(transform,
								data.box[i].scale.x,
								data.box[i].scale.y,
								0.0f,
								data.box[i].pos.x,
								data.box[i].pos.y,
								1.0);
						WEGraphics::Draw(transform);
				}
		}
		
		score = data.timerCount * data.Human.pos.x / 90; //calculate score
		data.timerCount += dt;
		/////////////////////////////////////////////////////////////////////////score image implementation
        //sound for when reaching score;
		if (score >= 1000 && score <= 1009)
		{
			//sound
			f_data.result = f_data.system->playSound(f_data.sound4, 0, false, &f_data.channel);
		}
		//score when 1000
		if (score > 1000 && score < 1150)
		{
			WEGraphics::SetTexture(data.ScoreTex1000);
			/*Set position scale and rotation of what I want to draw*/
			WEMtx44::MakeTransform(transform,
				100,
				50,
				0.0f,
				data.Human.pos.x+50,
				100.f,
				0.0);
			WEGraphics::Draw(transform);
		}
		//sound when score 5000
		if (score >= 5000 && score <= 5020)
		{
			//sound
			f_data.result = f_data.system->playSound(f_data.sound4, 0, false, &f_data.channel);
		}
		//score when 5000
		if (score > 5000 && score < 5200)
		{
			WEGraphics::SetTexture(data.ScoreTex5000);
			/*Set position scale and rotation of what I want to draw*/
			WEMtx44::MakeTransform(transform,
				100,
				50,
				0.0f,
				data.Human.pos.x + 50,
				100.f,
				0.0);
			WEGraphics::Draw(transform);
		}
		//sound when score 10000
		if (score >= 10000 && score <= 10080)
		{
			//sound
			f_data.result = f_data.system->playSound(f_data.sound4, 0, false, &f_data.channel);
		}
		//score when 5000
		if (score > 10000 && score < 10300)
		{
			WEGraphics::SetTexture(data.ScoreTex10000);
			/*Set position scale and rotation of what I want to draw*/
			WEMtx44::MakeTransform(transform,
				100,
				50,
				0.0f,
				data.Human.pos.x + 50,
				100.f,
				0.0);
			WEGraphics::Draw(transform);
		}
		/*****************score: **************************/
		WEGraphics::SetTexture(data.SCORE);
		WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);

		/*Draw an object with a transform and apply a color*/
		WEGraphics::SetTextureColor(0xFFFFFFFF);
		WEMtx44::MakeTransform(transform,
			40,
			20,
			0.0f,
			data.Human.pos.x - 57,
			146.f,
			0.0f);
		WEGraphics::Draw(transform);

		/********************Score : ********************/
		data.dvNUM = (int)score;        //temp value of score
		xVALUE = data.Human.pos.x - 17; // x position of first digit
		while (data.dvNUM != 0)         // when there is digit value for print in screen
		{
			if ((data.dvNUM % 10) == 0)
			
				WEGraphics::SetTexture(data.zero);
			
		  if ((data.dvNUM % 10) == 1)
				WEGraphics::SetTexture(data.one);
			
			if ((data.dvNUM % 10) == 2)
				WEGraphics::SetTexture(data.two);
		
			if ((data.dvNUM % 10) == 3)
				WEGraphics::SetTexture(data.three);
			
			if ((data.dvNUM % 10) == 4)
					WEGraphics::SetTexture(data.four);
				
			if ((data.dvNUM % 10) == 5)
				WEGraphics::SetTexture(data.five);

			if ((data.dvNUM % 10) == 6)
				WEGraphics::SetTexture(data.six);

			if ((data.dvNUM % 10) == 7)
				WEGraphics::SetTexture(data.seven);

			if ((data.dvNUM % 10) == 8)
				WEGraphics::SetTexture(data.eight);
				
			if ((data.dvNUM % 10) == 9)
				WEGraphics::SetTexture(data.nine);
			
			WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);

			/*Draw an object with a transform and apply a color*/
			WEGraphics::SetTextureColor(0xFFFFFFFF);
			WEMtx44::MakeTransform(transform,
					10,
					20,
					0.0f,
					xVALUE,
					146.f,
					0.0f);
			WEGraphics::Draw(transform);
			data.dvNUM /= 10; // increase digit of temp score value
			xVALUE -= 4;      // move x position for next digit of score
		}//while

		/********************** FINDING COFFIN ****************************/
		
		if (score > 38500 && score<= 38550)
		{
			 data.x = data.Human.pos.x + 200;
		}
		WEGraphics::SetTexture(data.CoffinTexture);
		WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);

		/*Draw an object with a transform and apply a color*/
		WEGraphics::SetTextureColor(0xFFFFFFFF);
		WEMtx44::MakeTransform(transform,
				50,
				100,
				0.0f,
				data.x,
				40,
				1.0f);
			WEGraphics::Draw(transform);
			//If player find coffin, change to credit screen
			if (data.x < data.Human.pos.x)
			{
				CreditAction();
			}
		
		WEGraphics::EndDraw();
}
/******************************************************************************/
/*!
Nothing to do here
*/
/******************************************************************************/
void Level2Shutdown(void)
{
	f_data.result = f_data.system->close();
	ERRCHECK(f_data.result);
	f_data.result = f_data.system->release();
	ERRCHECK(f_data.result);
}
/******************************************************************************/
/*!
Unload my textures
*/
/******************************************************************************/
void Level2Unload(void)
{
		WEGraphics::UnloadTexture(data.PlayerTexture );
		WEGraphics::UnloadTexture(data.PlayerTexture2);
		WEGraphics::UnloadTexture(data.PlayerTexture3);
		WEGraphics::UnloadTexture(data.PlayerTexture4);
		WEGraphics::UnloadTexture(data.PlayerTexture5);
		WEGraphics::UnloadTexture(data.PlayerTexture6);
		WEGraphics::UnloadTexture(data.SlideTexture  );
		WEGraphics::UnloadTexture(data.SlideTexture2 );
		WEGraphics::UnloadTexture(data.SlideTexture3 );
		WEGraphics::UnloadTexture(data.SlideTexture4 );
		WEGraphics::UnloadTexture(data.SlideTexture5 );
		WEGraphics::UnloadTexture(data.BGTexture     );
		WEGraphics::UnloadTexture(data.BGGTexture    );
		WEGraphics::UnloadTexture(data.BoxTexture    );
		WEGraphics::UnloadTexture(data.SpikeTexture  );
		WEGraphics::UnloadTexture(data.ScoreTex1000  );
		WEGraphics::UnloadTexture(data.ScoreTex5000  );
		WEGraphics::UnloadTexture(data.ScoreTex10000 );
		WEGraphics::UnloadTexture(data.starTexture   );
		WEGraphics::UnloadTexture(data.CoffinTexture );

		WEGraphics::UnloadTexture(data.zero          );
		WEGraphics::UnloadTexture(data.one           );
		WEGraphics::UnloadTexture(data.two           );
		WEGraphics::UnloadTexture(data.three         );
		WEGraphics::UnloadTexture(data.four          );
		WEGraphics::UnloadTexture(data.five          );
		WEGraphics::UnloadTexture(data.six           );
		WEGraphics::UnloadTexture(data.seven         );
		WEGraphics::UnloadTexture(data.eight         );
		WEGraphics::UnloadTexture(data.nine          );
		WEGraphics::UnloadTexture(data.SCORE         );
}