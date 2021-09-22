#include <stdafx.h>

// Thanks to SHVDN for memory patterns and structs :D

namespace Memory
{
	struct YscScriptHeader
	{
		char padding0[0x10];
		BYTE** codeBlocksOffset;

		char padding1[0x4];
		int codeLength;

		char padding2[0x4];
		int localCount;

		char padding3[0x4];
		int nativeCount;

		// padding: 0
		long* localOffset;

		char padding4[0x8];
		long* nativeOffset;

		char padding5[0x10];
		int nameHash;

		int CodePageCount()
		{
			return (codeLength + 0x3FFF) >> 14;
		}
		int GetCodePageSize(int page)
		{
			return (page < 0 || page >= CodePageCount() ? 0 : (page == CodePageCount() - 1) ? codeLength & 0x3FFF : 0x4000);
		}
		BYTE* GetCodePageAddress(int page)
		{
			return codeBlocksOffset[page];
		}
	};

	struct YscScriptTableItem
	{
		YscScriptHeader* header;

		char padding[0x4];
		int hash;

		bool IsLoaded()
		{
			return header != 0;
		}
	};

	struct YscScriptTable
	{
		YscScriptTableItem* TablePtr;

		char padding[0x10];
		DWORD32 count;

		YscScriptTableItem* FindScript(int hash)
		{
			if (!TablePtr)
			{
				return 0;
			}

			for (int i = 0; i < count; i++)
			{
				if (TablePtr[i].hash == hash)
				{
					return &TablePtr[i];
				}
			}

			return 0;
		}
	};

    void TryEnableMPCars()
    {
        static const eGameVersion gameVersion = getGameVersion();

        Handle handle = FindPattern("48 03 15 ?? ?? ?? ?? 4C 23 C2 49 8B 08");
        if (!handle.IsValid())
        {
            LOG("yscScriptTable handle invalid");
            return;
        }

		YscScriptTable* yscScriptTable = handle.At(2).Into().Get<YscScriptTable>();

		YscScriptTableItem* shopControllerItem = yscScriptTable->FindScript(0x39DA738B);
		if (!shopControllerItem )
		{
			LOG("shopControllerItem could not be found");
			return;
		}

		if (!shopControllerItem->IsLoaded())
		{
			LOG("shopControllerItem not loaded");
			return;
		}

		YscScriptHeader* shopControllerHeader = shopControllerItem->header;
		for (int i = 0; i < shopControllerHeader->CodePageCount(); i++)
		{
			int size = shopControllerHeader->GetCodePageSize(i);
			if (size > 0)
			{
				static const char* enableCarsGlobalPattern = gameVersion >= 46 ? "2D ?? ?? 00 00 2C 01 ?? ?? 56 04 00 6E 2E ?? 01 5F ?? ?? ?? ?? 04 00 6E 2E ?? 01" :
																				 "2C 01 ?? ?? 20 56 04 00 6E 2E ?? 01 5F ?? ?? ?? ?? 04 00 6E 2E ?? 01";
				static const int enableCarsGlobalOffset = gameVersion >= 46 ? 17 : 13;

				handle = FindPattern(enableCarsGlobalPattern, (DWORD64)shopControllerHeader->GetCodePageAddress(i), (DWORD64)size);
				if (handle.IsValid())
				{
					int globalIndex = handle.At(enableCarsGlobalOffset).Value<int>() & 0xFFFFFF;
					LOG("Setting global " << globalIndex << " to 1");
					*getGlobalPtr(globalIndex) = 1;
				}
			}
		}
    }
}