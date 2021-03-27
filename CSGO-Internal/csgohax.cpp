#include "csgohax.h"

csgohax::variable_t csgohax::vars;

uint32_t __stdcall csgohax::main(void*)
{
	while (!prepare()) Sleep(1000);
	char buffer[128];
	sprintf_s(buffer, "%X", vars.client);
	MessageBoxA(0, buffer, 0, 0);
	for (;; Sleep(10)) hack();
	return uint32_t();
}

uint32_t __stdcall csgohax::prepare()
{
	if (!vars.client) vars.client = (uint32_t)GetModuleHandleA("client.dll");
	return vars.client;
}

uint32_t __stdcall csgohax::hack()
{
	uint32_t localPlayer = *(uint32_t*)(vars.client + hazedumper::signatures::dwLocalPlayer);
	if (!localPlayer) return 0;
	uint32_t glowManager = *(uint32_t*)(vars.client + hazedumper::signatures::dwGlowObjectManager);
	if (!glowManager) return 0;

	// no flash
	*(float*)(localPlayer + hazedumper::netvars::m_flFlashDuration) = 0.0f;

	// glow esp
	for (size_t i = 0; i < 32; i++)
	{
		uint32_t target = *(uint32_t*)(vars.client + hazedumper::signatures::dwEntityList + 0x10 * i);

		if (!target) continue;

		bool glowDormant = *(bool*)(target + hazedumper::signatures::m_bDormant);
		int	glowIndex = *(int*)(target + hazedumper::netvars::m_iGlowIndex);
		int teamID = *(int*)(target + hazedumper::netvars::m_iTeamNum);

		if (glowDormant || !teamID) continue;

		if (*(int*)(localPlayer + hazedumper::netvars::m_iTeamNum) == teamID)
		{
			// allies
			*(float*)(glowManager + glowIndex * 0x38 + 0x04) = 100.0f / 255.0f;
			*(float*)(glowManager + glowIndex * 0x38 + 0x08) = 240.0f / 255.0f;
			*(float*)(glowManager + glowIndex * 0x38 + 0x0C) = 120.0f / 255.0f;
			*(float*)(glowManager + glowIndex * 0x38 + 0x10) = 255.0f / 255.0f;
		}
		else
		{
			// enemies
			*(float*)(glowManager + glowIndex * 0x38 + 0x04) = 230.0f / 255.0f;
			*(float*)(glowManager + glowIndex * 0x38 + 0x08) = 70.0f / 255.0f;
			*(float*)(glowManager + glowIndex * 0x38 + 0x0C) = 70.0f / 255.0f;
			*(float*)(glowManager + glowIndex * 0x38 + 0x10) = 255.0f / 255.0f;
		}

		*(uint32_t*)(glowManager + glowIndex * 0x38 + 0x24) = 1;
	}


	return uint32_t();
}
