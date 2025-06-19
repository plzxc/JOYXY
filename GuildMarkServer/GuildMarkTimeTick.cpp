#include "StdAfx.h"
#include "GuildMarkTimeTick.h"
#include "GuildMarkService.h"

GuildMarkTimeTick::GuildMarkTimeTick(void)
{
}

GuildMarkTimeTick::~GuildMarkTimeTick(void)
{
}

bool GuildMarkTimeTick::run()
{
	GuildMarkService::getSingleton().HandleCommand();

	Timer::run();	

	sleep(10);
	return true;
}