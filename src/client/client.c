//-----------------------------------------------------------
//Client a lancer apres le serveur avec la commande :
//client <adresse-serveur> <message-a-transmettre>
//------------------------------------------------------------//
#include <stdlib.h>
#include <stdio.h>
#include <linux/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <ncurses.h>
#include <panel.h>
#include <menu.h>
#include <form.h>
#include "client.h"
#include "structure_client.h"
#include <time.h>
typedef struct sockaddr 	sockaddr;
typedef struct sockaddr_in 	sockaddr_in;
typedef struct hostent 		hostent;
typedef struct servent 		servent;




#define NFIELDS 20
typedef struct messages_liste{
    int max;    
    int used;
}messages_liste;

int main()
{   

    int NLINES,NCOLS,rows,cols,m_rows,m_cols;
    /* Initialize curses */
    initscr();
    getmaxyx(stdscr,NLINES,NCOLS);

    WINDOW *my_wins[2];
    FIELD *m_fields[20];
    FIELD *field[2];
    FORM  *my_form;
    FORM *m_form;
    
    messages_liste * liste_m =  malloc((1) * sizeof(messages_liste));
    liste_m->max = 19;
    liste_m->used = 0;

    int ch;

    
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    /* Initialize all the colors */
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);


    
    /* Initialize the fields */
    field[0] = new_field(1, NCOLS/5*4-20, 1, 1, 0, 0);
    int i=0;
    for(i = 0; i < NFIELDS; ++i){
        m_fields[i] = new_field(1, NCOLS/5*4, 1+i, 1, 2, 2);
        //set_field_buffer(m_fields[i], 0, "This is a static Field");
        //set_field_buffer(m_fields[i], 0, "totototototo");
        //set_field_back(m_fields[i], A_UNDERLINE);
        field_opts_off(m_fields[i], O_AUTOSKIP);
        field_opts_off(m_fields[i], O_STATIC); /* Don't go to next field when this */
                          /* Field is filled up         */
    }

    /* Set field options */
    set_field_back(field[0], A_UNDERLINE);
    field_opts_off(field[0], O_AUTOSKIP); /* Don't go to next field when this */
                          /* Field is filled up         */
    
    
    /* Create the form and post it */
    my_form = new_form(field);
    scale_form(my_form, &rows, &cols);
    my_wins[1] = newwin(NLINES/3, NCOLS, NLINES/3*2, 0);
    keypad(my_wins[1], TRUE);
    /* Set main window and sub window */
    set_form_win(my_form, my_wins[1]);
    set_form_sub(my_form, derwin(my_wins[1], rows, cols, 2, 2));
    box(my_wins[1], 0, 0);
    print_in_middle(my_wins[1], 0, 0, cols, "JUST WRITE HERE ", COLOR_PAIR(1));
    post_form(my_form);    
    wrefresh(my_wins[1]);
    refresh();


    m_form = new_form(m_fields);
    /* Calculate the area required for the form */
    scale_form(m_form, &m_rows, &m_cols);
    /* Create the window to be associated with the form */
    my_wins[0] = newwin(NLINES/3*2, NCOLS, 0, 0);
    keypad(my_wins[0], TRUE);
    set_form_win(m_form, my_wins[0]);
    set_form_sub(m_form, derwin(my_wins[0], m_rows+2, m_cols+2, 2, 2));
    /* Print a border around the main window and print a title */
    box(my_wins[0], 0, 0);    
    print_in_middle(my_wins[0], 0, 0, m_cols, "MESSAGES[IN/OUT] HERE ", COLOR_PAIR(2));
    post_form(m_form);
    wrefresh(my_wins[0]);

    mvprintw(LINES - 2, 2, "[USE IN FULL SCREEN] Type your message and press ENTER to send your command or message");
    refresh();
    //top = my_panels[1];

    char * dest = malloc(20 * sizeof(char)) ;
    char * message = malloc(NCOLS/5*4 * sizeof(char));
    char * tmp_message = malloc(NCOLS/5*4 * sizeof(char));
    while((ch = wgetch(my_wins[1])) != KEY_ENTER)
    {   
        check_message_field(m_form,m_fields,liste_m,liste_m->used,NCOLS/5*4);
        switch(ch)
        {   
            case KEY_LEFT:
                form_driver(my_form,REQ_PREV_CHAR);
                break;

            case KEY_RIGHT:
                form_driver(my_form,REQ_NEXT_CHAR);
                break;
            case KEY_DC:
                form_driver(my_form,REQ_DEL_CHAR);
                break;
            case '\n':
            case 0x127:
            case KEY_ENTER:
                
                //SEND MY MESSAGE HERE !!
                //form_driver(m_form,REQ_INS_MODE);
                if (form_driver(my_form, REQ_VALIDATION) == E_OK) {
                    char * myTime = getMyTime();
                    dest = concat("[",concat(myTime,"]"));
                    message = concat(dest,field_buffer(field[0],0));       
                    int error = sendMessage(message);
                    if(error == 0){
                        if(liste_m->used == liste_m->max-2){
                            for(i=1;i<liste_m->max-1;i++){
                                mvprintw(i,4,"time");
                                if (form_driver(m_form, REQ_VALIDATION) == E_OK) {
                                    tmp_message = field_buffer(m_fields[i],0);
                                    set_field_buffer(m_fields[i-1], 0, tmp_message);
                                    set_field_buffer(m_fields[i], 0, "");
                                }            
                            }
                            liste_m->used-=1;
                        }else{
                            set_field_buffer(m_fields[liste_m->used], 0, message );
                            form_driver(my_form,REQ_DEL_LINE);
                            liste_m->used++;
                        }
                        
                    }else{
                        set_field_buffer(m_fields[liste_m->used], 0, "A NETWORK PROBLEM APPEARED" );
                        liste_m->used++;
                    }
                    //form_driver(m_form,ch);
                        
                    //set_field_userptr(field[0],0);
                    //form_driver(my_form,REQ_PREV_FIELD);
                }
                
                refresh();

                break;
            case KEY_BACKSPACE:
                form_driver(my_form,REQ_PREV_CHAR);
                form_driver(my_form,REQ_DEL_CHAR);
                break;
            default:
                /* If this is a normal character, it gets */
                /* Printed     
                           */
                set_field_buffer(m_fields[0], 0, field_buffer(field[0],1) );
                form_driver(my_form, ch);
                break;
            

        }
        wrefresh(my_wins[0]);
        //refresh(my_wins[1]);
        refresh();
    }

    /* Un post form and free the memory */
    unpost_form(my_form);
    unpost_form(m_form);
    free_form(my_form);
    free_form(m_form);
    free_field(field[0]);
    free_field(field[1]); 
    for(i=0;i<NFIELDS;++i){
        free_field(m_fields[i]);
    }
    endwin();
    return 0;
}

char * getMyTime(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char * myTime = malloc(20 * sizeof(char));// = concat(hour,concat(":",concat(min,concat(":",sec))));
    sprintf (myTime, "%dH:%dM:%dS", tm.tm_hour, tm.tm_min, tm.tm_sec);    
    return myTime;
}

char * concat(char * dest,char* src){
    char *buffer = malloc (strlen (dest) + strlen (src));
    if (buffer == NULL) {
        // Out of memory.
        return "";
    } else {
        strcpy (buffer, dest);
        strcat (buffer, src);
        return buffer;
        // Do something with buffer.
    }
    
}

/* Show the window with a border and a label */
void win_show(WINDOW *win, char *label, int label_color)
{   int startx, starty, height, width;
    getbegyx(win, starty, startx);
    getmaxyx(win, height, width);
    box(win, 0, 0);
    mvwaddch(win, 2, 0, ACS_LTEE); 
    mvwhline(win, 2, 1, ACS_HLINE, width - 2); 
    mvwaddch(win, 2, width - 1, ACS_RTEE); 
    print_in_middle(win, 1, 0, width, label, COLOR_PAIR(label_color));
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{   int length, x, y;
    float temp;

    if(win == NULL)
        win = stdscr;
    getyx(win, y, x);
    if(startx != 0)
        x = startx;
    if(starty != 0)
        y = starty;
    if(width == 0)
        width = 80;

    length = strlen(string);
    temp = (width - length)/ 2;
    x = startx + (int)temp;
    wattron(win, color);
    mvwprintw(win, y, x, "%s", string);
    wattroff(win, color);
    refresh();
}

void check_message_field(FORM * my_form,FIELD * field,messages_liste * liste,int using,int msg){
    if(liste->max-2 == using){
        char * message = malloc(msg * sizeof(char));
        // LOCK ALL FIELDS TO ACQUIRE DATA 
        int i= 1;
        for(i;i<liste->max;i++){
            if (form_driver(my_form, REQ_VALIDATION) == E_OK) {
                message = field_buffer(&field[i],0);
                set_field_buffer(&field[i-1], 0, message );
            }            
        }
        message = field_buffer(&field[i],0);
        set_field_buffer(&field[i+1], 0, message );
        liste->used = using-1;

    }else{
        //NOTHING TO DO
    }
}
 /*

int main(int argc, char **argv) {
    


   
    int 	socket_descriptor, 	// descripteur de socket //
		longueur; 		// longueur d'un buffer utilisé //
    sockaddr_in adresse_locale; 	// adresse de socket local //
    hostent *	ptr_host; 		// info sur une machine hote //
    servent *	ptr_service; 		// info sur service //
    char 	buffer[256];
    char *	prog; 			// nom du programme //
    char *	host; 			// nom de la machine distante //
    char *	mesg; 			// message envoyé //
     


    if (argc != 3) {
	perror("usage : client <adresse-serveur> <message-a-transmettre>");
	exit(1);
    }

	
    prog = argv[0];
    host = argv[1];
    mesg = argv[2];
    
    printf("nom de l'executable : %s \n", prog);
    printf("adresse du serveur  : %s \n", host);
    printf("message envoye      : %s \n", mesg);
    
    if ((ptr_host = gethostbyname(host)) == NULL) {
	perror("erreur : impossible de trouver le serveur a partir de son adresse.");
	exit(1);
    }
    
    // copie caractere par caractere des infos de ptr_host vers adresse_locale //
    bcopy((char*)ptr_host->h_addr, (char*)&adresse_locale.sin_addr, ptr_host->h_length);
    adresse_locale.sin_family = AF_INET; // ou ptr_host->h_addrtype; //
    
    // 2 facons de definir le service que l'on va utiliser a distance //
    // (commenter l'une ou l'autre des solutions) //
    
    //-----------------------------------------------------------//
    // SOLUTION 1 : utiliser un service existant, par ex. "irc" //
    //
    if ((ptr_service = getservbyname("irc","tcp")) == NULL) {
	perror("erreur : impossible de recuperer le numero de port du service desire.");
	exit(1);
    }
    adresse_locale.sin_port = htons(ptr_service->s_port);
    
    //-----------------------------------------------------------//
    
    //-----------------------------------------------------------//
    // SOLUTION 2 : utiliser un nouveau numero de port //
    adresse_locale.sin_port = htons(5000);
    //-----------------------------------------------------------//
    
    printf("numero de port pour la connexion au serveur : %d \n", ntohs(adresse_locale.sin_port));
    
    // creation de la socket //
    if ((socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
	perror("erreur : impossible de creer la socket de connexion avec le serveur.");
	exit(1);
    }
    
    // tentative de connexion au serveur dont les infos sont dans adresse_locale //
    if ((connect(socket_descriptor, (sockaddr*)(&adresse_locale), sizeof(adresse_locale))) < 0) {
	perror("erreur : impossible de se connecter au serveur.");
	exit(1);
    }
    
    printf("connexion etablie avec le serveur. \n");
    
    printf("envoi d'un message au serveur. \n");
      
    // envoi du message vers le serveur //
    if ((write(socket_descriptor, mesg, strlen(mesg))) < 0) {
	perror("erreur : impossible d'ecrire le message destine au serveur.");
	exit(1);
    }
    
    // mise en attente du prgramme pour simuler un delai de transmission //
    sleep(3);
     
    printf("message envoye au serveur. \n");
                
    // lecture de la reponse en provenance du serveur //
    while((longueur = read(socket_descriptor, buffer, sizeof(buffer))) > 0) {
	printf("reponse du serveur : \n");
	write(1,buffer,longueur);
    }
    
    printf("\nfin de la reception.\n");
    
    close(socket_descriptor);
    
    printf("connexion avec le serveur fermee, fin du programme.\n");
    
    exit(0);

    
    
}

*/
