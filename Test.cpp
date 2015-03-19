#include "stdafx.h"
#include "RzChromaSDKTypes.h"
#include <iostream>

using namespace ChromaSDK::Keyboard;

//Global variables
HMODULE hModule = NULL;                         // Chroma SDK module handle
const COLORREF RED = RGB(255,0,0);
//IAudioMeterInformation *pMeterInfo = NULL;

#ifdef _WIN64
#define CHROMASDKDLL        _T("RzChromaSDK64.dll")
#else
#define CHROMASDKDLL        _T("RzChromaSDK.dll")
#endif

typedef RZRESULT (*INIT)(void);

//forward declarations
void        InitStuff();
void				CustomLogic();
typedef RZRESULT (*CREATEKEYBOARDCUSTOMGRIDEFFECTS)(ChromaSDK::Keyboard::CUSTOM_GRID_EFFECT_TYPE CustomEffects, RZEFFECTID *pEffectId);

void InitStuff()
{
  hModule = LoadLibrary(CHROMASDKDLL);
  if(hModule)
  {
      INIT Init = (INIT)GetProcAddress(hModule, "Init");
      if(Init)
      {
        Init();
      }
  }
}

void CustomLogic()
{
	std::cout << "Hello World!";
	CREATEKEYBOARDCUSTOMGRIDEFFECTS CreateKeyboardCustomGridEffects = (CREATEKEYBOARDCUSTOMGRIDEFFECTS)GetProcAddress(hModule, "CreateKeyboardCustomGridEffects");

	CUSTOM_GRID_EFFECT_TYPE Grid = {};

  // Presets
  Grid.Key[4][18] = RED;
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;
	Grid.Key[4][18] = RGB(r,g,b);

	for(int i = 0; i < MAX_ROW; i++)
	{
		int r = rand() % 255;
		int g = rand() % 255;
		int b = rand() % 255;


		for(int j = 0; j < MAX_COLUMN; j++)
		{
			Grid.Key[i][j] = RGB(r,g,b);
		}

	}

  try{
	  CreateKeyboardCustomGridEffects(Grid, nullptr);//No exception, keyboard is not changing either
    std::cout << "modified keyboard.";
  }catch(const std::exception &exc) {
     std::cout << exc.what();
  }catch(...){
    std::cout << "Some unknown thing went wrong dangit.";
  }
  std::cout << "Done!";
}

int _tmain(int argc, _TCHAR* argv[])
{
	InitStuff();
	CustomLogic();
	return 0;
}

