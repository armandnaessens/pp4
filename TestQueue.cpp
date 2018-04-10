int queue_test() {
	uint32_t length = 32;
	uint8_t data[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };

	cout << "Creating ip header... ";
	uint8_t src_addr[16] = { 0x20, 0x01, 0x06, 0xA8, 0x1D, 0x80, 0x20, 0x21, 0x02, 0x30, 0x48, 0xFF, 0xFE, 0x5A, 0x3E, 0xE4 };
	uint8_t dst_addr[16] = { 0x20, 0x01, 0x06, 0xA8, 0x1D, 0x80, 0x20, 0x21, 0x50, 0x74, 0xF2, 0xFF, 0xFE, 0xB1, 0xA8, 0x7F };
	// for comparison
	Ip6Address *dest = new Ip6Address(dst_addr);

	Ip6 iph;
	iph.set_src(src_addr);
	iph.set_dst(dst_addr);
	iph.set_pl( (UDP_HLEN + length) );

	if (iph.get_dst()->operator==(*dest)) {
		cout << "ip header created successfully!" << endl;
	}
	else {
		cout << "failed to create header" << endl;
		return 0;
	}

	// create udp header for Session Initiation Protocol (RFC 3261)
	cout << "Creating udp header... ";
	uint16_t sip_src = 5060;
	uint16_t sip_dst = 5061;

	Udp udp_sip;
	udp_sip.set_src_port(sip_src);
	udp_sip.set_dst_port(sip_dst);
	udp_sip.set_length((length + UDP_HLEN));

	if ((udp_sip.get_src_port() == sip_src) && (udp_sip.get_dst_port() == sip_dst)) {
		cout << "udp header created successfully!" << endl;
	}
	else {
		cout << "failed to create packet" << endl;
		return 0;
	}

	cout << "Creating packet... ";
	Packet p(H_LEN, data, length);
	if (p.get_data_length() == 32) {
		cout << "packet created successfully!" << endl;
	}
	else {
		cout << "failed to create packet" << endl;
		return 0;
	}

	p.set_udp_header(&udp_sip, (uint8_t*)(p.get_head() + IP6_HLEN));
	p.set_ip6_header(&iph, (uint8_t*)(p.get_head()));

	cout << "Packet contents: " << endl;
	cout << p << endl;

	PriorityQueue priority_queue;

	cout << "Adding packet to queue... ";
	priority_queue.enqueue(&p, 1);
	if (priority_queue.get_head() == &p) {
		cout << "packet successfully added to the queue!" << endl;
	}
	else {
		cout << "failed to add packet to queue" << endl;
		return 0;
	}

	cout << endl;

	// copy packet
	cout << "Copying packet... ";
	Packet p1 = p;
	if (p == p1) {
		cout << "packet copied successfully!" << endl;
	}
	else {
		cout << "failed to copy packet" << endl;
		return 0;
	}

	cout << "Packet contents: " << endl;
	cout << p1 << endl;

	cout << "Adding packet to queue... ";
	priority_queue.enqueue(&p1, 3);
	if (priority_queue.get_at(0) == &p1) {
		cout << "packet successfully added to the queue!" << endl;
	}
	else {
		cout << "failed to add packet to queue" << endl;
		return 0;
	}

	Packet p2 = p;
	priority_queue.enqueue(&p2, 2);

	Packet p3 = p;
	priority_queue.enqueue(&p3, 4);

	Packet p4 = p;
	priority_queue.enqueue(&p4, 2);

	cout << endl;

	priority_queue.list();
	cout << endl;

	// create a queue for low priority traffic
	// such as SMTP
	Queue queue;

	length = 16;
	uint8_t smtp_data[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

	cout << "Creating packet... ";
	Packet s((H_LEN), smtp_data, length);
	if (s.get_data_length() == 16) {
		cout << "packet created successfully!" << endl;
	}
	else {
		cout << "failed to create packet" << endl;
		return 0;
	}

	uint16_t smtp_port = 25;

	Udp udp_smtp(smtp_port, smtp_port, (length + UDP_HLEN));
	s.set_udp_header(&udp_smtp, (uint8_t*)(s.get_head() + IP6_HLEN));

	uint8_t dst2[16] = { 0x20, 0x01, 0x06, 0xA8, 0x1D, 0x80, 0x20, 0x21, 0x74, 0x34, 0x44, 0xFF, 0xFE, 0xB1, 0xAA, 0x2E };
	Ip6 iph2(src_addr, dst2, (length + UDP_HLEN));

	s.set_ip6_header(&iph2, (uint8_t*)(s.get_head()));

	cout << "Packet contents: " << endl;
	cout << s << endl;

	cout << "Adding packet to queue... ";
	queue.enqueue(&s);
	if (queue.get_head() == &s) {
		cout << "packet successfully added to the queue!" << endl;
	}
	else {
		cout << "failed to add packet to queue" << endl;
		return 0;
	}

	cout << endl;

	uint8_t smtp_data2[25] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
	Packet s2((H_LEN), smtp_data2, 25);
	s2.set_ip6_header(&iph, (uint8_t*)(s2.get_head()));
	queue.enqueue(&s2);

	uint8_t smtp_data1[5] = { 0, 1, 2, 3, 4 };
	Packet s1((H_LEN), smtp_data1, 5);
	s1.set_ip6_header(&iph, (uint8_t*)(s1.get_head()));
	queue.enqueue(&s1);

	queue.list();
	cout << endl;

	queue.reschedule();

	queue.list();
	cout << endl;

	return 1;
}

int main(int argc, const char* argv[]) {
	if (queue_test() == 0) {
		cout << "Queue test failed" << endl;
	}
	else {
		cout << endl << "Queue test succeeded" << endl;
	}

	cout << endl << "Press any key to exit...";
	_getch();

	return 0;
}