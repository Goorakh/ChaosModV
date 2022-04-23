#pragma once

#include "Memory.h"
#include "Handle.h"
#include "stdafx.h"

namespace Memory
{
    void SetTimescaleLimitsDisabled(bool bDisable)
    {
        struct PatchInfo
        {
            std::string m_szPattern;
            int m_iOffset;

            PatchInfo(std::string szPattern, int iOffset)
            {
                m_szPattern = szPattern;
                m_iOffset = iOffset;
            }
        };
        
        static const int c_iNumPatches = 3;
        static PatchInfo patches[c_iNumPatches] =
        {
            PatchInfo("F3 0F 59 CB F3 0F 58 CB 0F 2F 0D A4 6C 0F 01 73 ?? 0F 57 C9 EB ??", 15),
            PatchInfo("F3 0F 58 CA 0F 2F CD 73 ?? 0F 28 CD EB ??", 7),
            PatchInfo("0F 2F 35 63 61 82 01 76 ?? F3 0F 10 35 59 61 82 01 EB ??", 7)
        };

        static const int c_iNumPatchBytes = 2;
        struct PatchBytes
        {
            BYTE m_ucOrigInstructions[c_iNumPatchBytes];
            BYTE** m_pucTargetBytes;
            
            PatchBytes()
            {
            }

            PatchBytes(BYTE* pucTargets[c_iNumPatchBytes])
            {
                m_pucTargetBytes = pucTargets;
                
                for (int i = 0; i < c_iNumPatchBytes; i++)
                {
                    m_ucOrigInstructions[i] = *pucTargets[i];
                }
            }
        };

        static PatchBytes patchBytes[c_iNumPatches] = {};
        static bool c_bDidInit = false;
        if (!c_bDidInit)
        {
            for (int i = 0; i < c_iNumPatches; i++)
            {
                Handle handle = FindPattern(patches[i].m_szPattern);
                if (handle.IsValid())
                {
                    handle = handle.At(patches[i].m_iOffset);

                    BYTE* pucPatchTargets[c_iNumPatchBytes] = {};

                    pucPatchTargets[0] = handle.Get<BYTE>();

                    handle = handle.At(1);
                    handle = handle.At(handle.Value<BYTE>()).At(1);
                    pucPatchTargets[1] = handle.At(3).Get<BYTE>();

                    patchBytes[i] = PatchBytes(pucPatchTargets);
                }
            }

            c_bDidInit = true;
        }

        for (int i = 0; i < c_iNumPatches; i++)
        {
            for (int j = 0; j < c_iNumPatchBytes; j++)
            {
                if (patchBytes[i].m_pucTargetBytes[j])
                {
                    *patchBytes[i].m_pucTargetBytes[j] = bDisable ? _INSTR_JMP : patchBytes[i].m_ucOrigInstructions[j];
                }
            }
        }
    }

    inline void SetTimeScale(float fTimeScale)
    {
        static float* pfTimescaleAddr = nullptr;
        if (!pfTimescaleAddr)
        {
            Handle handle = FindPattern("0F 2E 09 74 40 F3 0F 10 05 ?? ?? ?? ??");
            if (!handle.IsValid())
            {
                return;
            }

            handle = handle.At(8).Into();
            if (!handle.IsValid())
            {
                return;
            }

            pfTimescaleAddr = handle.At(-8).Get<float>();
        }

        pfTimescaleAddr[1] = fTimeScale;
        pfTimescaleAddr[3] = fTimeScale;
        //pfTimescaleAddr[4] = fTimeScale;
        //pfTimescaleAddr[5] = fTimeScale;

        //for (int i = 0; i < 6; i++)
        //{
        //    pfTimescaleAddr[i] = fTimeScale;
        //}
    }
}