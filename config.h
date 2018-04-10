#ifndef CONFIG_H
#define CONFIG_H

#define UDP_PROTO		17

#define LL_HLEN			0
#define UDP_HLEN		8
#define IP6_HLEN		40

#define H_LEN			(LL_HLEN + UDP_HLEN + IP6_HLEN)

#endif