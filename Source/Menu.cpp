/******************************************************************************/
/*!
\file            Menu.cpp
\project name    Finding Coffin
\author          Wonjae Jung - Menu buttons and images
			     Seungeun Ji - Sound effect
				 Jiwon Jung  - Usable to Keyboard
\par             GAM150
\brief

This is file for menu state

All content © 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Menu.h"
#include "Data.h"
#include "Actions.h"


#define WE_ANI_TIMER .1f
namespace
{
		const int BUTTON_WIDTH = 64;
		const int BUTTON_HEIGHT = 16;
		const int BUTTON_COUNT = 4;
		int buttonCtrl = 1;
		struct Menudata
		{
				float  screenWidth;
				float  screenHeight;

				bool isShowCursor;

				int MenuTexture;
				int StartTexture;
				int HowtoTexture;
				int CreditTexture;
				int ExitTexture;
				int SelectionTexture;

				WEVec2 topLeft;
				WEVec2 botRight;
				Button buttons[BUTTON_COUNT];
		};
		Menudata mdata;
}
/******************************************************************************/
/*!
Load my textures
*/
/******************************************************************************/
void MenuLoad(void)
{
	/*Load my textures used for this state*/
	
	mdata.MenuTexture   = WEGraphics::LoadTexture("Textures\\moMENU.tga");
	mdata.StartTexture  = WEGraphics::LoadTexture("Textures\\start box.tga");
	mdata.HowtoTexture  = WEGraphics::LoadTexture("Textures\\how to box.tga");
	mdata.CreditTexture = WEGraphics::LoadTexture("Textures\\create box.tga");
	mdata.ExitTexture   = WEGraphics::LoadTexture("Textures\\exit box.tga");
	mdata.SelectionTexture = WEGraphics::LoadTexture("Textures\\Selection.tga");

	WEGraphics::SetToOrtho();
}
/******************************************************************************/
/*!
Initialize data
*/
/******************************************************************************/
void MenuInit(void)
{

	mdata.screenWidth = (float)WEApplication::GetWidth();
	mdata.screenHeight = (float)WEApplication::GetHeight();

	WEGraphics::GetWorldTopLeft(mdata.topLeft);
	WEGraphics::GetWorldBotRight(mdata.botRight);

	/**/
	data.textcoord = 0.0f;
	data.totalTime = 0.0f;
	
	/*Set Camera*/
	data.cameraZ = 90.f;
	data.cameraX = 0.f;
	data.cameraY = 0.f;
	data.cameraRot = 0.0f;

	/*Set the background color*/
	WEGraphics::SetBackgroundColor(0, 0, 0);

	///start Button
	mdata.buttons[0].pos.x = 0;
	mdata.buttons[0].pos.y = 0;
	mdata.buttons[0].scale.x = BUTTON_WIDTH;
	mdata.buttons[0].scale.y = BUTTON_HEIGHT;
	mdata.buttons[0].action = StartAction;



	////Howto Button
	mdata.buttons[1].pos.x = 0;
	mdata.buttons[1].pos.y = mdata.buttons[0].pos.y - 25;
	mdata.buttons[1].scale.x = BUTTON_WIDTH;
	mdata.buttons[1].scale.y = BUTTON_HEIGHT;
	mdata.buttons[1].action = HowtoAction;


	////Creidt Button
	mdata.buttons[3].pos.x = 0;
	mdata.buttons[3].pos.y = mdata.buttons[1].pos.y - 25;
	mdata.buttons[3].scale.x = BUTTON_WIDTH;
	mdata.buttons[3].scale.y = BUTTON_HEIGHT;
	mdata.buttons[3].action = CreditAction;

	////Stop Button
	mdata.buttons[2].pos.x = 0;
	mdata.buttons[2].pos.y = mdata.buttons[3].pos.y - 25;
	mdata.buttons[2].scale.x = BUTTON_WIDTH;
	mdata.buttons[2].scale.y = BUTTON_HEIGHT;
	mdata.buttons[2].action = QuitAction;

	////Curr




	/////////////////////////////////////////FMOD
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

	f_data.result = f_data.system->createSound(Common_MediaPath("change.wav"), FMOD_DEFAULT, 0, &f_data.sound4);
	ERRCHECK(f_data.result);

	/* drumloop.wav has embedded loop points which automatically makes looping turn on, */
	f_data.result = f_data.sound4->setMode(FMOD_LOOP_OFF);
	/* so turn it off here.  We could have also just put FMOD_LOOP_OFF in the above CreateSound call. */
	ERRCHECK(f_data.result);

	//////stream//////
	f_data.result = f_data.system->createSound(Common_MediaPath("Opening.mp3"), FMOD_LOOP_NORMAL | FMOD_2D, 0, &f_data.background);
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

}

/******************************************************************************/
/*!
Update game and draw objects
*/
/******************************************************************************/
void MenuUpdate(float dt)
{
	
	WEMtx44 transform;


	//Check Input ****************************************
	if (WEInput::IsTriggered(WE_MOUSE_LEFT))
	{
			WEVec2 click;
			WEInput::GetMouse(click);
			WEGraphics::ConvertScreenToWorld(click.x, click.y);

			for (int i = 0; i < BUTTON_COUNT; ++i)
			{
					if (WEIntersection::PointRect(click, mdata.buttons[i].pos,
							mdata.buttons[i].scale.x, mdata.buttons[i].scale.y))
					{

							mdata.buttons[i].action();
							f_data.result = f_data.background->release();
							ERRCHECK(f_data.result);
					}
			}

	}
	/*********************************************************/
	data.totalTime += dt;

	/*if press space, quit game*/
	if (WEInput::IsTriggered(WE_ESCAPE))
		WEStateManager::Quit();

	WEGraphics::StartDraw();

	/*Update the camera since it could have moved*/
	WEGraphics::SetCamera(data.cameraX, data.cameraY, data.cameraZ,
		data.cameraRot);

	WEGraphics::SetToPerspective();

	/*Drawing Background Terrain to the whole level*/

	/*Draw BackGround 1*/

	
		WEGraphics::SetTexture(mdata.MenuTexture);
		WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);


		/*Draw an object with a transform and apply a color*/
		WEGraphics::SetTextureColor(0xFFFFFFFF);
		WEMtx44::MakeTransform(transform,
			300,
			150,
			0.0f,
			0,
			0,
			0.0f);
		WEGraphics::Draw(transform);
		/*************************Draw Start********************************************/
		WEGraphics::SetTexture(mdata.StartTexture);
		WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);


		/*Draw an object with a transform and apply a color*/
		WEGraphics::SetTextureColor(0xFFFFFFFF);
		//WEGraphics::SetToOrtho()


		WEMtx44::MakeTransform(transform,
			mdata.buttons[0].scale.x,
			mdata.buttons[0].scale.y,
			0.0f,
			mdata.buttons[0].pos.x,
			mdata.buttons[0].pos.y,
			0.0f);
		WEGraphics::Draw(transform);
	/*************************Draw Howto box********************************************/
		WEGraphics::SetTexture(mdata.HowtoTexture);
		WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);


		/*Draw an object with a transform and apply a color*/
		WEGraphics::SetTextureColor(0xFFFFFFFF);
		//WEGraphics::SetToOrtho()


		WEMtx44::MakeTransform(transform,
			mdata.buttons[1].scale.x,
			mdata.buttons[1].scale.y,
			0.0f,
			mdata.buttons[1].pos.x,
			mdata.buttons[1].pos.y,
			0.0f);
		WEGraphics::Draw(transform);
	/*************************Draw Exit box********************************************/
		WEGraphics::SetTexture(mdata.ExitTexture);
		WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);


		/*Draw an object with a transform and apply a color*/
		WEGraphics::SetTextureColor(0xFFFFFFFF);
		//WEGraphics::SetToOrtho()


		WEMtx44::MakeTransform(transform,
			mdata.buttons[2].scale.x,
			mdata.buttons[2].scale.y,
			0.0f,
			mdata.buttons[2].pos.x,
			mdata.buttons[2].pos.y,
			0.0f);
		WEGraphics::Draw(transform);
		/*************************Draw Exit box********************************************/
		WEGraphics::SetTexture(mdata.CreditTexture);
		WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);

		/*Draw an object with a transform and apply a color*/
		WEGraphics::SetTextureColor(0xFFFFFFFF);
		//WEGraphics::SetToOrtho()


		WEMtx44::MakeTransform(transform,
				mdata.buttons[3].scale.x,
				mdata.buttons[3].scale.y,
				0.0f,
				mdata.buttons[3].pos.x,
				mdata.buttons[3].pos.y,
				0.0f);
		WEGraphics::Draw(transform);
		/*************************Draw Current box*******************************/

		/*************************Keyboard Movement*******************/
		//change position of selection texture by pressing up arrow key
		if (WEInput::IsTriggered(WE_ARROW_UP))
		{
			//if selection texture is already on top
			if (buttonCtrl == 1)
				;
			else
			{
				f_data.result = f_data.system->playSound(f_data.sound4, 0, false, &f_data.channel);
				--buttonCtrl;
			}
		}
		//change position of selection texture by pression down arrow key
		else if (WEInput::IsTriggered(WE_ARROW_DOWN))
		{
			//if selection texture is already on bottom
			if (buttonCtrl == 4)
				;
			else
			{
				f_data.result = f_data.system->playSound(f_data.sound4, 0, false, &f_data.channel);
				++buttonCtrl;
			}
		}
		/**************Start Button*******************/
		if (buttonCtrl == 1)
		{

			WEGraphics::SetTexture(mdata.SelectionTexture);
			WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);


			/*Draw an object with a transform and apply a color*/
			WEGraphics::SetTextureColor(0xFFFFFFFF);
			//WEGraphics::SetToOrtho()


			WEMtx44::MakeTransform(transform,
				mdata.buttons[0].scale.x+12,
				mdata.buttons[0].scale.y+10,
				0.0f,
				mdata.buttons[0].pos.x,
				mdata.buttons[0].pos.y,
				0.0f);
			WEGraphics::Draw(transform);

			if (WEInput::IsTriggered(WE_RETURN))
				StartAction();
		}
		/*************How to Button*****************/
		else if (buttonCtrl == 2)
		{

			WEGraphics::SetTexture(mdata.SelectionTexture);
			WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);


			/*Draw an object with a transform and apply a color*/
			WEGraphics::SetTextureColor(0xFFFFFFFF);
			//WEGraphics::SetToOrtho()


			WEMtx44::MakeTransform(transform,
				mdata.buttons[1].scale.x+12,
				mdata.buttons[1].scale.y+10,
				0.0f,
				mdata.buttons[1].pos.x,
				mdata.buttons[1].pos.y,
				0.0f);
			WEGraphics::Draw(transform);

			if (WEInput::IsTriggered(WE_RETURN))
				HowtoAction();
		}
		/*************Exit Button****************/
		else if (buttonCtrl == 4)
		{

			WEGraphics::SetTexture(mdata.SelectionTexture);
			WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);


			/*Draw an object with a transform and apply a color*/
			WEGraphics::SetTextureColor(0xFFFFFFFF);
			//WEGraphics::SetToOrtho()


			WEMtx44::MakeTransform(transform,
				mdata.buttons[2].scale.x+12,
				mdata.buttons[2].scale.y+10,
				0.0f,
				mdata.buttons[2].pos.x,
				mdata.buttons[2].pos.y,
				0.0f);
			WEGraphics::Draw(transform);
			if (WEInput::IsTriggered(WE_RETURN))
				WEStateManager::Quit();
		}
		else if (buttonCtrl == 3)
		{
			WEGraphics::SetTexture(mdata.SelectionTexture);
			WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);


			/*Draw an object with a transform and apply a color*/
			WEGraphics::SetTextureColor(0xFFFFFFFF);
			//WEGraphics::SetToOrtho()


			WEMtx44::MakeTransform(transform,
					mdata.buttons[3].scale.x + 12,
					mdata.buttons[3].scale.y + 10,
					0.0f,
					mdata.buttons[3].pos.x,
					mdata.buttons[3].pos.y,
					0.0f);
			WEGraphics::Draw(transform);


			if (WEInput::IsTriggered(WE_RETURN))
				CreditAction();
		}

	WEGraphics::EndDraw();
}
/******************************************************************************/
/*!
Nothing to do here
*/
/******************************************************************************/
void MenuShutdown(void)
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
void MenuUnload(void)
{
	WEGraphics::UnloadTexture(mdata.MenuTexture);
	WEGraphics::UnloadTexture(mdata.StartTexture);
	WEGraphics::UnloadTexture(mdata.HowtoTexture);
	WEGraphics::UnloadTexture(mdata.CreditTexture);
	WEGraphics::UnloadTexture(mdata.ExitTexture);
	WEGraphics::UnloadTexture(mdata.SelectionTexture);
}
