#include "Event.h"


Event::Event(size_t time, WirelessNetwork* network) 
{
	execution_time_ = time;
	network_ = network;
}
Event::~Event()
{
	
}

double Event::get_execution_time()
{
	return execution_time_;
}

