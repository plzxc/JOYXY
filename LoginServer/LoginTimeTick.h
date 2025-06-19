#pragma once
#include <Timer.h>
#include <Singleton.h>

class LoginTimeTick : public Timer, public Singleton<LoginTimeTick>
{
public:
	LoginTimeTick(void);
	virtual ~LoginTimeTick(void);

	virtual bool run();
};
