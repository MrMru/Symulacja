#include "EventTransmission.h"

#include "EventSendACK.h"


EventTransmission::EventTransmission(Logger logger, size_t time, Package* package, WirelessNetwork* network, BaseStation* base_station, EventList* event_list):Event(time, network)
{
	logger_ = logger;
	package_ = package;
	network_ = network;
	base_station_ = base_station;
	execution_time_ = time;
	event_list_ = event_list;
	
}


EventTransmission::~EventTransmission()
{

}

void EventTransmission::Execute()
{
	//collision
	if (network_->returnChannelQueue().size() > 0 && network_->return_is_channel_free()) //packages in channel and is_channel_free_ = true
	{
		network_->set_is_channel_free(false);
	}
	
	package_ = network_->returnPackageInChannel();

	if (network_->is_next_package_in_channel())
	{
		package_->setCollision();
	}else
	{
		package_->unsetCollision();
	}
	
	logger_.Debug("Event Transmission. Transmitting package ID " + std::to_string(package_->return_packade_id()) + " from Base Station : " + std::to_string(base_station_->returnBaseStationID()));
	
	//ACK confirmation
	if(!package_->returnIsCollision()) //no collision
	{
		if(!network_->return_is_error_TER()) //no error TER
		{
			package_->setAck();
			event_list_->push(new EventSendACK(logger_, execution_time_ + package_->returnCTP() + 10, package_, network_, base_station_, event_list_));
			
		}
		else //error TER
		{
			package_->unsetAck();
			event_list_->push(new EventSendACK(logger_, execution_time_ + package_->returnCTP() + 10, package_, network_, base_station_, event_list_));
		}
	}
	else //collision
	{
		package_->unsetAck();
		event_list_->push(new EventSendACK(logger_, execution_time_ + package_->returnCTP() + 10, package_, network_, base_station_, event_list_));
	}

	
	
}

