#ifndef PACKAGE_H_
#define PACKAGE_H_
#include "Logger.h"


class Package
{
private:
	int package_id_; //ID of a package
	size_t cgpk_; //time of package generation
	size_t ctp_; //time of package transmission - CTPk
	size_t time_of_start_transmission_ = 0; //time of leaving the buffer_
	size_t time_of_end_transmission_ = 0; //time of leaving the system
	int retransmission_counter_; //retransmission counter, max 10 (zmienione na 5, w celu zwiekszenia liczby odrzuconych pakietow)
	double crp_; //time of waiting for retransmission
	double R_; //variable needed to calculate crp_ time
	int actual_base_station; //ID of package's BS
	bool is_collision_; //TRUE - there was a collision, FALSE - there was no collision
	bool is_confirmation_ACK_; //TRUE - ACK confirmation sent, FALSE - ACK confirmation not sent
	bool is_end_; //TRUE - package sent, FALSE - package not sent
	bool is_rejected_; //TRUE - package rejected, FALSE - is not rejected
	bool to_statistics_; //TRUE - pakiet liczony w statystykach, FALSE - pakiet nie brany pod uwage w statystykach
	
	

public:
	Package(int package_id, int base_station_id, Logger logger, size_t cgpk, size_t ctpk);
	~Package();
	int return_packade_id(); //returns package_id_
	void increaseRetransmissionCounter(); //increases retransmission_counter_
	int returnRetransmissionCounter(); //returns retransmission_counter_
	int returnCTP(); //returns ctp_
	bool returnIsCollision(); //TRUE - collision, FALSE - no collision
	void setCollision(); //sets id_collision_ = TRUE
	void unsetCollision(); //sets id_collision_ = FALSE
	void setAck(); //sets is_confirmation_ACK_ = TRUE
	void unsetAck(); //sets is_confirmation_ACK_ = FALSE
	bool isACK();//TRUE - ACK, FALSE - no ACK
	void setR(size_t R);//sets R_ = R
	void setCRP(size_t CRP);//sets crp_ = CRP
	size_t returnCRP(); //returns crp_
	size_t returnCGPk(); //returns cgpk_
	void setIsEnd();//sets is_end_ = TRUE
	bool returnIsEnd();//returns is_end_
	int returnActualBSid();
	void setTimeOfStartTransmission(size_t time);
	size_t returnTimeOfStartTransmission();
	void setTimeOfEndTransmission(size_t time);
	size_t returnTimeOfEndTransmission();
	void setIsRejected(bool is_rejected);
	bool returnIsRejected();
	void setToStatistics(bool to_statistics);
	bool returnToStatistics();

};



#endif 
