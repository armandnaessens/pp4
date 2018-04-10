#ifndef IP6ADDRESS_H
#define IP6ADDRESS_H

#include <stdint.h>

class Ip6Address {
public:
	int addr [8];
public:
	Ip6Address();
	Ip6Address(int addr_arr[8]);
	Ip6Address(const Ip6Address& ip6addr);
public:
	int * get_addr();
	bool operator==(const Ip6Address& ip1);
	void print();
	

};

#endif // !IP6ADDRESS_H
