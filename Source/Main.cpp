/******************************************************************************/
/*!
\file            Main.cpp
\project name    Finding Coffin
\author          Seungeun Ji
\par             GAM150
\brief

This is file contains the main function to make a basic window. 

All content © 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "WEMemory.h"
/* These are necessary includes to do any memory leak detection ***************/
/*This should always  be the first code in your file*/

/******************************************************************************/

#include <windows.h> /*WinMain*/ 

/*Include the engine functions*/
#include "WEApplication.h"
#include "WEStateManager.h"
#include "WEState.h"
#include "WEGameData.h"

/*My GameStates*/
#include "SplashState.h"
#include "Level2.h"
#include "Menu.h"
#include "Howto.h"
#include "Howto2.h"
//#include "Credit.h"
#include "Credit2.h"
#include "Ending.h"

#include "WEDebugTools.h"


/******************************************************************************/
/*!
The user must add states to their game After initializing the Application, and 
before updating the Application.

\attention
To make switching states easier, I add the states in the order they are listed
in the DemoStates enum.
*/
/******************************************************************************/
void DemoAddStates(void)
{
	WEState state;
	int stateID;

	/*A make sure to add my state in the order they are in
	my DemoStates enum*/

	/*Add my SplashState*/
	
	state.Load     = SplashStateLoad;
	state.Init     = SplashStateInit;
	state.Update   = SplashStateUpdate;
	state.Shutdown = SplashStateShutdown;
	state.Unload   = SplashStateUnload;

	stateID = WEStateManager::AddState(state);
  WEStateManager::SetStartState(stateID);

	state.Load     = MenuLoad;
	state.Init     = MenuInit;
	state.Update   = MenuUpdate;
	state.Shutdown = MenuShutdown;
	state.Unload   = MenuUnload;

	WEStateManager::AddState(state);


	state.Load     = Level2Load;
	state.Init     = Level2Init;
	state.Update   = Level2Update;
	state.Shutdown = Level2Shutdown;
	state.Unload   = Level2Unload;

	 WEStateManager::AddState(state);

	state.Load     = HowtoLoad;
	state.Init     = HowtoInit;
	state.Update   = HowtoUpdate;
	state.Shutdown = HowtoShutdown;
	state.Unload   = HowtoUnload;


	 WEStateManager::AddState(state);

	 state.Load     = Howto2Load;
	 state.Init     = Howto2Init;
	 state.Update   = Howto2Update;
	 state.Shutdown = Howto2Shutdown;
	 state.Unload   = Howto2Unload;

	 WEStateManager::AddState(state);

	 state.Load     =  CreditLoad;
	 state.Init     =  CreditInit;
	 state.Update   =  CreditUpdate;
	 state.Shutdown =  CreditShutdown;
	 state.Unload   =  CreditUnload;

	 WEStateManager::AddState(state);


	 state.Load     = EndLoad;
	 state.Init     = EndInit;
	 state.Update   = EndUpdate;
	 state.Shutdown = EndShutdown;
	 state.Unload   = EndUnload;


	 WEStateManager::AddState(state);
	
}

/******************************************************************************/
/*!

\brief
The main function for a windowed program.

\param instance 
An identifier for the process.  This is used for various windows things.

\param prev
This is not used anymore, we can ignore it.

\param comamndLine
A string that is comes from the typed command line.  In games we usually don't
care.

\param show 
A variable stating if the window is visible, we always want it visible.

\return
An Error code.  Just return 0;
*/
/******************************************************************************/
#pragma warning(suppress: 28251)
int WINAPI WinMain(HINSTANCE instance,
                   HINSTANCE /*prev*/, 
                   LPSTR /*commandLine*/, 
                   int /*show*/)
{


  /*Declare my InitStruct*/
  WEInitData initStruct;
  /*Create my game data initial values*/
  WEGameData gameData = { 0 };

  /*Set up my InitStruct*/
  initStruct.instance   = instance;
  initStruct.width      = 1280;
  initStruct.height     = 720;
  initStruct.title      = "EdgeOftheCliff";
  initStruct.fps        = 60;
  initStruct.fullScreen = false;

  /*Information about your specific gamedata */
  initStruct.pGData       = &gameData;
  initStruct.gameDataSize = sizeof(WEGameData);

  /*Pass InitStruct to Function.  This function must be called first!!!*/
  WEApplication::Init(initStruct);
  /*Function to add all of my game states*/
  DemoAddStates();
  /*Start running the game*/
  WEApplication::Update();
  /*This function must be called after the window has closed!!!*/

  WEApplication::Shutdown();
  
  //int* p = new int;
  //p = 0;

  return 0;
}

