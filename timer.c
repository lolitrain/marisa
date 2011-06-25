#include "timer.h"

static long frame_time = 0;


void timer_set_frame_time(long time)
{
	frame_time = time;
}

float timer_get_time()
{
	return frame_time/1000.0f;
}

