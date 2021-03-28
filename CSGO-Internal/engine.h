#ifndef __ENGINE_H__
#define __ENGINE_H__

#pragma once
#include "stdafx.h"

namespace csgo
{
	class engine
	{
	public:
		class player_t;
		class glowObject_t;

		struct variable_t
		{
			struct
			{
				uint32_t csgo, client, engine;
			} modules;

			void get_data();

		} *vars;
	public:
		engine()
		{
			this->vars = new variable_t();
		}

		~engine()
		{
			delete[] this->vars;
		}

		player_t* local_player();
		player_t* get_player_by_id(uint32_t id);
		glowObject_t* get_glow_object_by_id(uint32_t id);

		uint32_t& force_attack();
		uint32_t& force_jump();

	};

	class engine::player_t
	{
	public:
		inline int& armor()
		{
			return *(int*)((uint32_t)this + hazedumper::netvars::m_ArmorValue);
		}

		inline int& health()
		{
			return *(int*)((uint32_t)this + hazedumper::netvars::m_iHealth);
		}

		inline int& team()
		{
			return *(int*)((uint32_t)this + hazedumper::netvars::m_iTeamNum);
		}

		inline int& state()
		{
			return *(int*)((uint32_t)this + hazedumper::netvars::m_iState);
		}

		inline int& glow_index()
		{
			return *(int*)((uint32_t)this + hazedumper::netvars::m_iGlowIndex);
		}

		inline float& flash_duration()
		{
			return *(float*)((uint32_t)this + hazedumper::netvars::m_flFlashDuration);
		}

		inline bool& dormant()
		{
			return *(bool*)((uint32_t)this + hazedumper::signatures::m_bDormant);
		}

		inline int& crosshair_id()
		{
			return *(int*)((uint32_t)this + hazedumper::netvars::m_iCrosshairId);
		}

		inline int& flags()
		{
			return *(int*)((uint32_t)this + hazedumper::netvars::m_fFlags);
		}
	};

	class engine::glowObject_t
	{
	public:
		void* pEntity;
		float r, g, b, a;
		char __unknown00[8];
		float BloomAmount;
		char __unknown01[4];
		bool RenderWhenOccluded;
		bool RenderWhenUnoccluded;
		bool FullBloomRender;
		char __unknown02;
		int FullBloomStencilTestValue;
		char __unknown03[4];
		int SplitScreenSlot;
		int NextFreeSlot;
	};
}



#endif // !__ENGINE_H__
