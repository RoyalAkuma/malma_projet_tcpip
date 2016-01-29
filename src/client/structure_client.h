#ifndef STRUCUTRE_CLIENT
#define STRUCTURE_CLIENT
#include <stdlib.h>
#include <stdio.h>
#include <linux/types.h> 	/* pour les sockets */
#include <sys/socket.h>
#include <netdb.h> 		/* pour hostent, servent */
#include <string.h> 

typedef struct Config{ 
	char* last_server;
	int last_port_serve;
	char* last_room;
}Config;

typedef struct Client {
	char * pseudo;
	Config config; //Configuration précédente;	
}Client;

Client 	* client_create(char * pseudo, char * pathConfig);
void sendMessage(char * message);
void client_connection(char* serveur, int port);
void client_deconnection();
void client_connectionRoom(char* roomName);
char * client_getListeRoom();
char * client_getListeClient();
char * client_getListeCommande();
char * client_whoIs(char* target_name);
void client_chargerConfig();
void client_saveConfig();
 
#endif
 
