#ifndef PACKET_H
#define PACKET_H

#include "Ip6.h"
#include "Udp.h"
#include <stdint.h>



class Packet
{

public:
	uint16_t headroom;
	uint32_t data_len;
	int* data;
	uint8_t priority;
	int* next;


public:
	Packet(int bytes[], int length);
	Packet(uint16_t headroom, int bytes[], int length);
	Packet(Packet& p);
	~Packet();
	operator(os, p);
	bool operator==(const Packet& p);
public:
	uint8_t * get_ip6_header();
	void set_ip6_header(Ip6* iph, int* header_ptr);
	
	uint8_t* get_udp_header();
	void set_udp_header(Udp* udph, int* header_ptr);

	uint8_t* get_next();
	void set_next(Packet* p);

	uint8_t get_priority();
	void set_priority(uint8_t prio);

	int* get_data();
	void set_head();

	uint32_t get_data_length();
	uint32_t get_length();
};


#endif // !PACKET_H
