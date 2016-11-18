#include <SDL2/SDL_net.h>
#include <stdio.h>
#include "Point.h"

#define Server_error(msg) \
	do { \
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, __func__, msg, NULL); \
		abort(); \
	} while(0)

enum Server_Message
{
	SERVER_DEAD,
	SERVER_WAITING,
	SERVER_POSITION,
	SERVER_SHOOTING,
	SERVER_STARTING,
};

struct Server_Packet
{
	Uint8 type;
	Point data;
};

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		if(argc && argv[0])
			printf("Usage: %s [PORT]\n", argv[0]);
		else
			puts("Usage: ./server [PORT]");
		return 1;
	}

	if(SDL_Init(0))
		Server_error(SDL_GetError());
	if(SDLNet_Init())
		Server_error(SDLNet_GetError());

	IPaddress address;
	TCPsocket server_socket;
	TCPsocket players[2] = {0};
	SDLNet_SocketSet socket_set;
	Uint16 port = atoi(argv[1]);
	struct Server_Packet packet;
	int game_running = 0;

	if(SDLNet_ResolveHost(&address, NULL, port))
		Server_error(SDLNet_GetError());

	server_socket = SDLNet_TCP_Open(&address);
	if(!server_socket)
		Server_error(SDLNet_GetError());
	
	if(!(socket_set = SDLNet_AllocSocketSet(3)))
		Server_error(SDLNet_GetError());
	
	SDLNet_TCP_AddSocket(socket_set, server_socket);
	printf("Listening on port %i...\n", port);
	while(1)
	{
		int ready = SDLNet_CheckSockets(socket_set, 0);
		if(ready == -1)
			Server_error(SDLNet_GetError());

		if(!game_running && SDLNet_SocketReady(server_socket))
		{
			if(!players[0])
			{
				players[0] = SDLNet_TCP_Accept(server_socket);
				packet.type = SERVER_WAITING;
				int result = SDLNet_TCP_Send(players[0], &packet, sizeof(packet));
				if(result < (int)sizeof(packet))
				{
					SDLNet_TCP_Close(players[0]);
					players[0] = NULL;
				}
				else
					puts("Player (1/2) connected");
			}
			else if(!players[1])
			{  
				players[1] = SDLNet_TCP_Accept(server_socket);
				packet.type = SERVER_WAITING;
				int result = SDLNet_TCP_Send(players[1], &packet, sizeof(packet));
				if(result < (int)sizeof(packet))
				{
					SDLNet_TCP_Close(players[1]);
					players[1] = NULL;
				}
				else
					puts("Player (2/2) connected");
			}

			if(players[0] && players[1])
			{
				packet.type = SERVER_STARTING;
				int result_1 = SDLNet_TCP_Send(players[0], &packet, sizeof(packet));
				int result_2 = SDLNet_TCP_Send(players[1], &packet, sizeof(packet));
				if(result_1 < (int)sizeof(packet))
				{
					SDLNet_TCP_Close(players[0]);
					players[0] = NULL;
					puts("Something went wrong");
				}
				else if(result_2 < (int)sizeof(packet))
				{
					SDLNet_TCP_Close(players[1]);
					players[1] = NULL;
					puts("2: Something went wrong");
				}
				else
				{
					SDLNet_TCP_DelSocket(socket_set, players[0]);
					SDLNet_TCP_DelSocket(socket_set, players[1]);

					SDLNet_TCP_AddSocket(socket_set, players[0]);
					SDLNet_TCP_AddSocket(socket_set, players[1]);
					puts("Game is starting...");

					game_running = 1;
				}
			}
		}
		else if(game_running)
		{
			for(int i = 0; i < 2; i++)
			{
				if(SDLNet_SocketReady(players[i]))
				{
					int result = SDLNet_TCP_Recv(players[i], &packet, sizeof(packet));
					if(result < (int)sizeof(packet))
					{
						SDLNet_TCP_DelSocket(socket_set, players[i]);
						SDLNet_TCP_Close(players[i]);

						players[i] = NULL;
						puts(SDLNet_GetError());
						packet.type = SERVER_WAITING;
						SDLNet_TCP_Send(players[!i], &packet, sizeof(packet));
						game_running = 0;

						puts("Player lost connection");
						break;
					}

					switch(packet.type)
					{
					case SERVER_STARTING:
						packet.type = SERVER_WAITING;
						SDLNet_TCP_Send(players[!i], &packet, sizeof(packet));
						game_running = 0;
						puts("Player quit");
						break;
					case SERVER_DEAD:
					case SERVER_POSITION:
					case SERVER_SHOOTING:
						SDLNet_TCP_Send(players[!i], &packet, sizeof(packet));
						break;
					default:
						puts("Recieved corrupted data");
					}
				}
			}
		}
	//	SDL_Delay(1);
	}

	SDLNet_Quit();
	SDL_Quit();
}
