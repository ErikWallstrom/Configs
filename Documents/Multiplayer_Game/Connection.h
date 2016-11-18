#ifndef CONNECTION_H
#define CONNECTION_H

#include <SDL2/SDL_net.h>
#include "Vec.h"

typedef struct Connection Connection;
struct Connection
{
	SDLNet_SocketSet socket_set;
	TCPsocket socket;
	IPaddress address;
	Vec(char) ip;
	Uint16 port;
};

struct Connection* Connection_ctor(struct Connection* self, char* ip, Uint16 port);
int Connection_incoming_data(struct Connection* self);
void Connection_send(struct Connection* self, void* data, size_t data_len);
void Connection_recieve(struct Connection* self, void* buffer, size_t buffer_size);
void Connection_dtor(struct Connection* self);

#endif
