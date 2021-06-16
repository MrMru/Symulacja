#ifndef CHANNEL_H_
#define CHANNEL_H_
#include <queue>

#include "Package.h"


class Channel
{
private:

	Logger logger_;
	//bool is_error_TER_; //TRUE - there was a TER error, FALSE - there was no TER error
	//bool is_collision_; //TRUE - there was a collision, FALSE - there was no collision
	//bool is_confirmation_ACK_; //TRUE - ACK confirmation sent, FALSE - ACK confirmation not 
	double time_channel_free_; //time the channel is free

public:
	Channel(Logger logger);
	~Channel();
	//void setAck(); //ustawia is_confirmation_ACK_ na TRUE
	//void unsetAck(); //ustawia is_confirmation_ACK_ na FALSE
	//void setCollision(); //ustawia is_collision_ na true
	//void setErrorTER(); // ustawia is_error_TER_ na true
	//bool returnIsCollision();
	//bool returnIsErrorTER();
	//bool isACK();
	
	
	
	

	

	
	
	
};

#endif 