#ifndef __CSGO_HAX_H__
#define __CSGO_HAX_H__

#pragma once
#include "stdafx.h"
#include "engine.h"

class csgohax
{
public:
	static uint32_t __stdcall main(void*);
	static uint32_t __stdcall prepare();
	static uint32_t __stdcall hack();
private:
	static csgo::engine game;
};



#endif // !__CSGO_HAX_H__
