#include "Channel.h"

class WirelessNetwork;


Channel::Channel(Logger logger)
{
	//is_error_TER_ = false;
	//is_collision_ = false;
	//is_confirmation_ACK_ = false;

	time_channel_free_ = 0;
	logger_ = logger;
	logger.Info("Creating new Channel");
}

Channel::~Channel()
{
	
}

/*void Channel::setAck()
{
	is_confirmation_ACK_ = true;
}*/

/*void Channel::unsetAck()
{
	is_confirmation_ACK_ = false;
}*/

/*void Channel::setCollision()
{
	is_collision_ = true;
}*/

/*void Channel::setErrorTER()
{
	is_error_TER_ = true;
}*/

/*bool Channel::returnIsErrorTER()
{
	return is_error_TER_;
}*/

/*bool Channel::isACK()
{
	return is_confirmation_ACK_;
}*/



/*bool Channel::returnIsCollision()
{
	return is_collision_;
}*/






