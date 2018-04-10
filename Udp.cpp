#include "Udp.h"
#include "config.h"

/**********CONSTRUCTORS************/

Udp::Udp() {
	this->src_port = 0;
	this->dst_port = 0;
	this->length = 0;
	this->checksum = 0;
}

Udp::Udp(int data[]) {
	this->src_port = ((data[0] << 8) || data[1]);
	this->dst_port = ((data[2] << 8) || data[3]);
	this->length = ((data[4] << 8) || data[5]);
	this->checksum = ((data[6] << 8) || data[7]);
}

Udp::Udp(uint16_t src, uint16_t dst, uint16_t len) {
	this->src_port = src;
	this->dst_port = dst;
	this->length = len;
}

/*************GETTERS & SETTERS***************/

uint16_t Udp::get_src_port() {
	return this->src_port;
}
void Udp::set_src_port(uint16_t src) {
	this->src_port = src;
}

uint16_t Udp::get_dst_port() {
	return this->dst_port;
}
void Udp::set_dst_port(uint16_t dst) {
	this->dst_port = dst;
}

uint16_t Udp::get_length() {
	return this->length;
}
void Udp::set_length(uint16_t len) {
	this->length = len;
}

uint16_t Udp::get_checksum() {
	return this->checksum;
}
void Udp::set_checksum() {
	this->checksum = 0;
}