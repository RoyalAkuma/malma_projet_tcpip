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

#define connection client_connection

#define deconnection client_deconnection

#define connectionRoom client_connectionRoom

#define getListeRoom client_getListeRoom

#define getListeClient client_getListeClient

#define getListeErreur client_getListeErreur

#define whoIs client_whoIs

#define chargerConfig client_chargerConfig

#define saveConfig client_saveConfig

typedef struct Client {
	char * pseudo;
	Config config; //Configuration précédente;
	void (*connection)(char* serveur, int port);
	void (*deconnection)();
	void (*connectionRoom)(char* roomName);
	char * (*getListeRoom)();
	char * (*getListeClient)();
	char * (*getListeCommande)();
	char * (*whoIs)(char* target_name);
	void (*chargerConfig)();
	void (*saveConfig)();

	client 	* Client_new(char * pseudo, char * pathConfig) { 
	  client* c = malloc(sizeof(Client));
	  p->pseudo = pseudo;
	  //Construction du config !!

	  return c;
	}	
}Client;
 
#endif
 
