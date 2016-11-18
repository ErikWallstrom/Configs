#include "Connection.h"
#include <assert.h>

#define Connection_error(msg) \
	do { \
		printf("%i\n", __LINE__); \
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, __func__, msg, NULL); \
		abort(); \
	} while(0)

struct Connection* Connection_ctor(struct Connection* self, char* ip, Uint16 port)
{
	assert(self);
	assert(ip);
	assert(port);

	if(SDLNet_ResolveHost(&self->address, ip, port))
		Connection_error(SDLNet_GetError());

	self->socket_set = SDLNet_AllocSocketSet(1);
	if(!self->socket_set)
		Connection_error(SDLNet_GetError());

	self->socket = SDLNet_TCP_Open(&self->address);
	if(!self->socket)
		Connection_error(SDLNet_GetError());

	SDLNet_TCP_AddSocket(self->socket_set, self->socket);

	self->port = port;
	Vec_ctor(&self->ip, 1, 0);
	Vec_set(&self->ip, ip, strlen(ip) + 1);
	return self;
}

int Connection_incoming_data(struct Connection* self)
{
	assert(self);
	int ready = SDLNet_CheckSockets(self->socket_set, 0);
	if(ready == -1)
		Connection_error(SDLNet_GetError());
	return (ready && SDLNet_SocketReady(self->socket));
}

void Connection_send(struct Connection* self, void* data, size_t data_len)
{
	assert(self);
	assert(data);
	assert(data_len);
	
	int result = SDLNet_TCP_Send(
			self->socket, 
			data, 
			data_len);
	if(result < (int)data_len)
		Connection_error(SDLNet_GetError());
}

void Connection_recieve(struct Connection* self, void* buffer, size_t buffer_size)
{
	assert(self);
	assert(buffer);
	assert(buffer_size);

	int result = SDLNet_TCP_Recv(
			self->socket, 
			buffer,
			buffer_size);
	if(result < (int)buffer_size)
		Connection_error(SDLNet_GetError());
}

void Connection_dtor(struct Connection* self)
{
	assert(self);
	puts("Bluad");
	SDLNet_TCP_Close(self->socket);
	SDLNet_FreeSocketSet(self->socket_set);
	Vec_dtor(&self->ip);
	self->socket_set = NULL;
	self->socket = NULL;
}
