#ifndef EVENT_TRANSMISSION_
#define EVENT_TRANSMISSION_
#include "Event.h"
#include "Logger.h"
#include "Package.h"
#include "WirelessNetwork.h"

class EventTransmission : public Event
{
private:
	Logger logger_;
	Package* package_;
	WirelessNetwork* network_;
	EventList* event_list_;
	BaseStation*base_station_;
	
	
public:
	EventTransmission(Logger logger, size_t time, Package* package, WirelessNetwork* network, BaseStation* base_station,EventList* event_list);
	void Execute() override;
	~EventTransmission();

};

#endif
