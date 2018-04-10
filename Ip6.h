#ifndef IP6_H
#define IP6_H

#include <stdint.h>
#include "Ip6Address.h"

class Ip6 {
public:
	uint8_t version;
	uint32_t flow_label;
	uint8_t traffic_class;
	uint16_t pl;
	uint8_t nexth;
	uint8_t hoplim;
	//Ip6Address src;
	//Ip6Address dst;
public:
	Ip6();
	Ip6(int data[]);
	Ip6(Ip6Address src_addr, Ip6Address dst_addr, int length);
	~Ip6();
public:
	uint8_t get_version();
	void set_version(uint8_t version);

	uint32_t get_fl();
	void set_fl(uint32_t fl);

	uint8_t get_tc();
	void set_tc(uint8_t tc);

	uint16_t get_pl();
	void set_pl(uint16_t pl);

	uint8_t get_nexth();
	void set_nexth(uint8_t nh);

	uint8_t get_hoplim();
	void set_hoplim(uint8_t hoplim);

	//nog get en set van src en dst


};

#endif // !IP6_H
