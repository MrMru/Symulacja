#ifndef EVENT_GENERATE_PACKET_
#define EVENT_GENERATE_PACKET_

#include "Event.h"
#include "BaseStation.h"
#include "Logger.h"
#include "WirelessNetwork.h"

class EventGeneratePackage : public Event
{
private:
	BaseStation* base_station_;
	Logger logger_;
	WirelessNetwork* network_;
	Package* package_;
	EventList* event_list_;
	int generate_package_max_time = 10;
	
public:
	EventGeneratePackage(Logger logger, size_t start_time, BaseStation* base_station,  WirelessNetwork* network, EventList* event_list);
	void Execute() override;

};

#endif
