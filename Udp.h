#ifndef UDP_H
#define UDP_H

#include <stdint.h>


class Udp
{
public:
	uint16_t src_port, dst_port, length, checksum;
	
public:
	Udp();
	Udp(int data[]);
	Udp(uint16_t src, uint16_t dst, uint16_t len);

public:
	uint16_t get_src_port();
	void set_src_port(uint16_t);

	uint16_t get_dst_port();
	void set_dst_port(uint16_t);

	uint16_t get_length();
	void set_length(uint16_t);

	uint16_t get_checksum();
	void set_checksum();


};



#endif // !UDP_H
