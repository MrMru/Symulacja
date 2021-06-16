#ifndef EVENT_SEND_ACK_
#define EVENT_SEND_ACK_
#include "BaseStation.h"
#include "Event.h"
#include "Package.h"


class EventSendACK : public Event
{
private:
	Package* package_;
	BaseStation* base_station_;
	WirelessNetwork* network_;
	Logger logger_;
	EventList* event_list_;
	
public:
	EventSendACK(Logger logger, size_t start_time, Package* package, WirelessNetwork* network, BaseStation* base_station, EventList* event_list);
	void Execute() override;
	~EventSendACK();
};

#endif
