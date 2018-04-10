#include <iostream>
#include "Ip6Address.h"
#include "config.h"

using namespace std;

/*********CONSTRUCTORS***********/
Ip6Address::Ip6Address() {
	memset(this->addr, 0, 8);
}
Ip6Address::Ip6Address(int addr_arr[8]) {
	memcpy(this->addr, addr_arr, sizeof(this->addr));
}
Ip6Address::Ip6Address(const Ip6Address& ip6addr) {
	*this->addr = *ip6addr.addr;
}

/***********NEST*************/
int * Ip6Address::get_addr() {
	return this->addr;
}

bool Ip6Address::operator== (const Ip6Address& ip1) {
	return strcmp((char*)this->addr, (char*)ip1.addr);
}

void print() {
	//hier moet nog iets komen
}