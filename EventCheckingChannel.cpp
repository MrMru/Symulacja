#include "EventCheckingChannel.h"
#include "EventTransmission.h"


EventCheckingChannel::EventCheckingChannel(Logger logger, size_t time, Package* package, WirelessNetwork* network, BaseStation* base_station, EventList* event_list): Event(time, network)
{
	execution_time_ = time;
	logger_ = logger;
	package_ = package;
	network_ = network;
	base_station_ = base_station;
	event_list_ = event_list;
	logger_.Debug("Next CheckingChannel in : " + std::to_string(execution_time_) + " BS : " + std::to_string(base_station->returnBaseStationID()));
}


EventCheckingChannel::~EventCheckingChannel()
{
}

void EventCheckingChannel::Execute()
{
	logger_.Debug("Base Station : " + std::to_string(base_station_->base_station_id_) + " is checking channel");
	
		if (network_->base_stations_.at(base_station_->returnBaseStationID())->returnSizeOfBuffer() != 0) //packages in BS's buffer_
		{
			if (network_->return_is_channel_free()) //channel is free		
			{
				if (execution_time_ % 10 == 0) {


					network_->EventStartTransmission(logger_, execution_time_, package_, network_, base_station_);
					event_list_->push(new EventTransmission(logger_, execution_time_, package_, network_, base_station_, event_list_));

				}
				
				else
				{
					
					event_list_->push(new EventCheckingChannel(logger_, execution_time_+1, package_, network_, base_station_, event_list_));
				
				}
			}
			else //channel isn't free
			{
				
				event_list_->push(new EventCheckingChannel(logger_, execution_time_ +1, package_, network_, base_station_, event_list_));
			}
		}
		else
		{
			event_list_->push(new EventCheckingChannel(logger_, execution_time_ +1, package_, network_, base_station_, event_list_));
		}
		
	}
	

	


