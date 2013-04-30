#ifndef COMMON_H
#define COMMON_H

#include <string>

//define the process names for BlockMember class
#define TRANSPORT_RECEIVER "transport_receiver"
#define TRANSPORT_SENDER "transport_sender"
#define APP "app"
#define CLUSTER "cluster"
#define UNICAST_ID 0

#ifdef BOOST
#define ID std::string
#define ExternalRef std::string
#define BROADCAST_ID "255.255.255.255"
#define LOCAL_BROADCAST_ID "255.255.255.254"

#elif defined ODEMX
#define ID int
#define ExternalRef odemx::ProtocolStack*
#define BROADCAST_ID 255
#define LOCAL_BROADCAST_ID 254

#else
#define ID int
#define ExternalRef RTDS_QueueId
#define BROADCAST_ID 255
#define LOCAL_BROADCAST_ID 254
#endif
//rekrutierung durch den clusterhead
typedef struct recruit_s{
	ID head;
} recruit_t; 

//antwort eines followers
typedef struct recruitResp_s{
	ID head;
	ID follower;
	//int hopCount;
} recruitResp_t;

//poll anfrage eines clusterheads
typedef struct poll_s{
	ID head;
} poll_t;

//poll antwort mit anzahl der follower
typedef struct pollResp_s{
	ID head;
	ID follower;
	int countFollower;
} pollResp_t;

//ernennung eines neuen cluster heads
typedef struct promote_s{
	//unicast an neuen head
	ID head;
	ID follower; //nur zum check
} promote_t;

//weitergabe eines clusterheads an den nächsten
typedef struct abdicate_s{
	ID head;
	ID newHead;
} abdicate_t;

typedef struct ping_s{

	int i;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & i;
	}
} ping_t;


typedef struct pong_s{

	int i;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & i;
	}
} pong_t;

typedef struct payload_s{
	ping_t ping;
	pong_t pong;
	recruit_t recruit;
	recruitResp_t recruitResp;
	poll_t poll;
	pollResp_t pollResp;
	promote_t promote;
	abdicate_t abdicate;
} payload_t;

#endif
