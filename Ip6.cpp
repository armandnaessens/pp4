#include "Ip6.h"
#include "config.h"

/****************CONSTRUCTORS**********************/
Ip6::Ip6() {
	this->version = 6;
	this->traffic_class = 0;
	this->flow_label = 1;
	this->hoplim = 64;
}

Ip6::Ip6(Ip6Address src_addr, Ip6Address dst_addr, int length) {
	this->src = src_addr;
	this->dst = dst_addr;
}

Ip6::Ip6(data) {
	this->version = ((data[0] & 0xF0) >> 4);
	this->traffic_class = (((data[0] & 0xF) << 4) || ((data[1] & 0xF0) >> 4));
	this->flow_label = (((data[1] & 0xF) << 16) || (data[2] << 8) || data[3] );
	this->pl = (data[4] << 8 || data[5]);
	this->nexth = data[6];
	this->hoplim = data[7];

	this->src = new Ip6Address((uint8_t*)(data + 8));
	this->dst = new Ip6Address((uint8_t*)(data + 24));
}

/***********GETTERS & SETTERS*************/
uint8_t Ip6::get_version() {
	return this->version;
}
void Ip6::set_version(uint8_t version) {
	this->version = version;
}

uint32_t Ip6::get_fl() {
	return this->flow_label;
}
void Ip6::set_fl(uint32_t fl) {
	this->flow_label = fl;
}

uint8_t Ip6::get_tc() {
	return this->traffic_class;
}
void Ip6::set_tc(uint8_t tc) {
	this->traffic_class = tc;
}

uint16_t Ip6::get_pl() {
	return this->pl;
}
void Ip6::set_pl(uint16_t pl) {
	this->pl = pl;
}

uint8_t Ip6::get_nexth() {
	return this->nexth;
}
void Ip6::set_nexth(uint8_t nexth) {
	this->nexth = nexth;
}

uint8_t Ip6::get_hoplim() {
	return this->hoplim;
}
void Ip6::set_hoplim(uint8_t hoplim) {
	this->hoplim = hoplim;
}