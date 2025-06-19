#pragma once
#include <Timer.h>
#include <Singleton.h>

class GuildMarkTimeTick : public Timer, public Singleton<GuildMarkTimeTick>
{
public:
	GuildMarkTimeTick(void);
	virtual ~GuildMarkTimeTick(void);

	virtual bool run();
};
