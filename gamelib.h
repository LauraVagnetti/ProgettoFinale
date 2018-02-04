#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define numeroGiocatori 2

int flagMappaCreata = 0;
int flagRipTurn = 0;
int benzinaUsata = 0;


typedef enum {vivo, ferito, morto} Stato_Giocatore;
typedef enum {cucina, soggiorno, rimessa, strada, lungo_lago, uscita_campeggio} Tipo_Zona;
typedef enum {cianfrusaglia, bende, coltello, pistola, benzina, adrenalina} Tipo_Oggetto;

const static int probabilita_ogg_zona[6][6] =
{
	{300, 200, 400, 0, 0, 100},
	{200, 100, 100, 300, 0, 300},
	{200, 100, 300, 0, 300, 100},
	{800, 0, 100, 0, 100, 0},
	{700, 0, 100, 0, 200, 0},
	{900, 0, 100, 0, 0, 0}
};

char assoc_nome_oggetti[6][20] =
{
	{"Cianfrusaglia"},
	{"Bende"},
	{"Coltello"},
	{"Pistola"},
	{"Benzina"},
	{"Adrenalina"}
};


char assoc_nome_zone[6][20] =
{
	{"Cucina"},
	{"Soggiorno"},
	{"Rimessa"},
	{"Strada"},
	{"Lungo Lago"},
	{"Uscita Campeggio"}
};

char assoc_stato[3][20] =
{
	{"Vivo"},
	{"Ferito"},
	{"Morto"}
};

typedef struct s_zona
{
	Tipo_Zona nome_zona;
	Tipo_Oggetto oggetto;
	int numZona;
	struct s_zona *zona_successiva;
}Zona;


typedef struct
{
	int indexGiocatore;
	char nome_giocatore[30];
	Zona *posizioneGiocatore;
	Stato_Giocatore stato;
	int vittoria;
	int zaino[6];
}Giocatore;

//dichiarazione delle funzioni Gestione Mappa
void ins_zona(int);
void gest_mappa();
void crea_mappa();
void elimina_mappa();
int randomOggetti(int);
void inizializzazioneRand();
void stampaMappa();
void rimuoviElemento(); //é cancella zona, lo scrivo così Gian(accanto a me) è più contento.
int controlloInsMappa();
int countZone();

//dichiarazione della funzione gioca
void inizZaino(Giocatore*);
void inizGioco(int);
void gioca();
int mostra_oggetto(Zona*);
int prendi_oggetto(Zona*, Giocatore*);
void visualizza_zaino(Giocatore*);
void deallocazioneDati();
int usa_adrenalina(Giocatore*);
void avanza(Giocatore*);
int cura(Giocatore*);
int switch_giocatore(int);
int prob_gieson(Giocatore*, Giocatore*, Zona*);
int gieson(Giocatore*);

	

