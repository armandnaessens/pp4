#include "Packet.h"
#include "config.h"
#include <stdio.h>
#include <string>

uint8_t* Packet::get_ip6_header() {
	return ((uint8_t*)(data + LL_HLEN));
}

void Packet::set_ip6_header(Ip6* iph,int* header_ptr) {
	uint8_t header[8] = { 
		(iph->get_version() << 4) | ((iph->get_tc() & 0xF0) >> 4),
		(iph->get_tc() & 0x0F) | ((iph->get_fl() & 0xF0000) >> 16),
		((iph->get_fl() & 0xFF00) >> 8),
		(iph->get_fl() & 0xFF), ((iph->get_pl() & 0xFF00) >> 8), 
		(iph->get_pl() & 0xFF), iph->get_nexth(), iph->get_hoplim()
	};

	memcpy((uint8_t*)(header_ptr), header, 8);
	memcpy((uint8_t*)(header_ptr + 8), iph->get_src(), 16);
	memcpy((uint8_t*)(header_ptr + 24), iph->get_dst(), 16);
}

uint8_t* Packet::get_udp_header() {
	return ((uint8_t*) (data + (LL_HLEN + IP6_HLEN)));
}

void Packet::set_udp_header(Udp* udph, int* header_ptr) {
	uint8_t header[8] = { 
		((udph->get_src_port() & 0xFF00) >> 8), (udph->get_src_port() & 0xFF),
		((udph->get_dst_port() & 0xFF00) >> 8), (udph->get_dst_port() & 0xFF), 
		((udph->get_length() & 0xFF00) >> 8), (udph->get_length() & 0xFF),
		((udph->get_checksum() & 0xFF00) >> 8), (udph->get_checksum() & 0xFF),
	};

	memcpy((uint8_t*) (header_ptr), header, 8);
}

operator(os, p) {
	int i = 0;

	for (i = 0; i < p.get_length(); i++) {
		os << (int)(p.get_head()[i]) << " ";
	}

	return os;
}