#include "StdAfx.h"
#include "LoginTimeTick.h"
#include "LoginService.h"

LoginTimeTick::LoginTimeTick(void)
{
}

LoginTimeTick::~LoginTimeTick(void)
{
}

bool LoginTimeTick::run()
{
	CODE_PF_BEGIN();
	LoginService::getSingleton().HandleCommand();
	Timer::run();
	CODE_PF_END("LoginTimeTick����ʱ��");

	Sleep(1);

	return true;
}