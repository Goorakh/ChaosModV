#include <stdafx.h>

static bool ms_bEnabledHook = false;
static float ms_fOverrideFOV = 0;

void(*_OG_CamRenderFunc)(__int64* dest, __int64* src);
void _HK_CamRenderFunc(__int64* dest, __int64* src)
{
	_OG_CamRenderFunc(dest, src);

	if (ms_bEnabledHook)
	{
		//LOG("0: " << *(float*)(dest + 0x70));
		*(float*)(dest + 0x70) = 10.f;
		//LOG("1: " << *(float*)(dest + 0x70));
	}

	//if (ms_bEnabledHook)
	//{
	//	LOG("0");
	//	LOG(*(float*)(p1 + 0x54));
	//	*(float*)(p1 + 0x54) = ms_fOverrideFOV;
	//	LOG("1");
	//	LOG(*(float*)(p1 + 0x54));
	//}
}

static bool OnHook()
{
	LOG("_0");
	Handle handle = Memory::FindPattern("48 89 5c 24 08 57 48 83 ec 20 8b 42 40 f3 0f 10 4a 48 f3 0f 10 42 44 89 41 40 48 8b fa 41 b0 01 f3 0f 11 41 44 f3 0f 11 49 48 8b 42 4c 48 83 c2 10");
	if (!handle.IsValid())
	{
		return false;
	}

	LOG("_1");
	Memory::AddHook(handle.Get<void>(), _HK_CamRenderFunc, &_OG_CamRenderFunc);

	LOG("_2");
	return true;
}

static RegisterHook registerHook(OnHook, "CamRenderFunc");

namespace Hooks
{
	void SetForceRenderFieldOfView(float fFov)
	{
		ms_bEnabledHook = true;
		ms_fOverrideFOV = fFov;
	}
}