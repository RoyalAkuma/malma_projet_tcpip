#include "structure_client.h"

Client 	* client_create(char * pseudo, char * pathConfig) { 
  Client * c = malloc(sizeof(Client));
  c->client->pseudo = pseudo;
  //Construction du config !!
  return c;
}


void client_connection(char* server_name, int server_port){
	//ConnectionServeur
	printf("Connection to %s  Port:%d",server_name,server_port);
}

void client_deconnection(){
	//close(socket_descriptor);
    	exit(0);
	//send to server for broadcast to all clients
	printf("Deconnection");
}
void client_connectionRoom(char* roomName){
	printf("Connection to %s",roomName);
}
char * client_getListeRoom(){
	
}
char * client_getListeClient(){

}
char * client_getListeCommande(){

}
char * client_whoIs(char* target_name){

}
void client_chargerConfig(){

}
void client_saveConfig(){

}
