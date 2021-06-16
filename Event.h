#ifndef EVENT_H_
#define EVENT_H_

#include <functional>
#include <queue>
#include<vector>
class WirelessNetwork;

class Event
{
public:

	typedef std::priority_queue<Event*, std::vector<Event*>, std::function<bool(Event*, Event*)>> EventList;
	Event(size_t time, WirelessNetwork* network);
	~Event();
	
	virtual void Execute() = 0;
	double get_execution_time();
	
protected:
	size_t execution_time_;
	WirelessNetwork* network_ = nullptr;
	
};

#endif

