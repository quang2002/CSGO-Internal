#ifndef __CSGO_HAX_H__
#define __CSGO_HAX_H__

#pragma once
#include "stdafx.h"

class csgohax
{
public:
	static uint32_t __stdcall main(void*);
	static uint32_t __stdcall prepare();
	static uint32_t __stdcall hack();
private:
	static struct variable_t
	{
		uint32_t client;
	} vars;
};



#endif // !__CSGO_HAX_H__
