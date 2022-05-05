#pragma once

#define _NODISCARD [[nodiscard]]

#define _INSTR_NOP 0x90
#define _INSTR_RET 0xC3
#define _INSTR_DEC 0x48

// Evaluates to 0 at g_MetaInfo.m_fChaosMultiplier = 1, evaluates to x at g_MetaInfo.m_fChaosMultiplier = infinity
#define approach_rt(x, rate) (((x) * (1.f - (1.f / ((MetaModifiers::m_fChaosMultiplier * (rate)) - ((rate) - 1.f))))))

// Evaluates to 0 at g_MetaInfo.m_fChaosMultiplier = 1, evaluates to x at g_MetaInfo.m_fChaosMultiplier = infinity
#define approach(x) approach_rt(x, 1.f)