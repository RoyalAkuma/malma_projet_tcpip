#ifndef STRUCUTRE_SERVER
#define STRUCTURE_SERVER

#include <stdlib.h>
#include <stdio.h>
#include <linux/types.h> 	/* pour les sockets */
#include <sys/socket.h>
#include <netdb.h> 		/* pour hostent, servent */
#include <string.h> 		/* pour bcopy, ... */  
#define TAILLE_MAX_NOM 256

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
typedef struct hostent hostent;
typedef struct servent servent;

typedef struct Room{
	char[] room_name;
	ClientInformation ** liste_client;
}Room;

typedef struct Erreur{
	int error_code;
	char[] error_name;
}Erreur

typedef struct Admin {
	ClientInformation client
	Room** room;
}

typedef struct Commande{

}Commande;


typedef struct ClientInformation{
	char[] pseudo;
	int 	socket_descriptor,		/* descripteur de socket */
		nouv_socket_descriptor, 	/* [nouveau] descripteur de socket */
		longueur_adresse_courante; 	/* longueur d'adresse courante d'un client */
    	sockaddr_in 	adresse_locale, 		/* structure d'adresse locale*/
			adresse_client_courant; 	/* adresse client courant */
	hostent* ptr_hote; 			/* les infos recuperees sur la machine hote */
	servent* ptr_service; 			/* les infos recuperees sur le service de la machine */
	char machine[TAILLE_MAX_NOM+1];
};

typedef struct Server{
	char[] name_server;
	int port_server;
	
	Erreur ** liste_erreur;
	Admin ** liste_admin;
	
}Server;

#endif

