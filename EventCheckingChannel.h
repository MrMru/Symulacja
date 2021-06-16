#ifndef EVENT_CHECKING_CHANNEL_
#define EVENT_CHECKING_CHANNEL_
#include "BaseStation.h"
#include "Event.h"
#include "Logger.h"
#include "Package.h"
#include "WirelessNetwork.h"


class EventCheckingChannel : public Event
{
private:
	Package* package_;
	BaseStation* base_station_;
	Logger logger_;
	WirelessNetwork* network_;
	EventList* event_list_;
public:
	EventCheckingChannel(Logger logger, size_t time, Package* package, WirelessNetwork* network, BaseStation* base_station, EventList* event_list);
	void Execute() override;
	~EventCheckingChannel();

};

#endif
