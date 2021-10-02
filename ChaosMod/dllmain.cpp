#include <stdafx.h>
#include "Util/AudioVolumeController.h"

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		__try
		{
			Memory::Init();
		}
		__except (CrashHandler(GetExceptionInformation()))
		{

		}

		scriptRegister(hInstance, Main::Run);

		keyboardHandlerRegister(Main::OnKeyboardInput);

		break;
	case DLL_PROCESS_DETACH:
		Memory::Uninit();

		scriptUnregister(hInstance);

		keyboardHandlerUnregister(Main::OnKeyboardInput);

		if (GetConsoleWindow())
		{
			g_ConsoleOut.close();

			FreeConsole();
		}

		// If the game is exited while a volume override is active, the override will persist to the next time the game is started
		AudioVolumeController::ResetOverrideVolume();

		break;
	}

	return TRUE;
}