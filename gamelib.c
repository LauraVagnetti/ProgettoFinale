#include "gamelib.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

static Zona *prima_zona = NULL;
static Zona *ultima_zona = NULL;

static Giocatore *giocatore[numeroGiocatori];

char sceltaMappa;
//inserisci un item(zona) nella lista
void ins_zona(int sceltaMenuZona)
{
	if(prima_zona ==NULL) //creazione prima zona
	{
		prima_zona = (Zona *)malloc(sizeof(Zona));
		prima_zona -> nome_zona = sceltaMenuZona;
		prima_zona -> oggetto = randomOggetti(sceltaMenuZona);
		prima_zona -> zona_successiva = NULL;
		ultima_zona = prima_zona;
	}
	else
	{
		ultima_zona ->zona_successiva = (Zona *)malloc(sizeof(Zona));
		ultima_zona = ultima_zona ->zona_successiva;
		ultima_zona->nome_zona = sceltaMenuZona;
		ultima_zona-> oggetto = randomOggetti(sceltaMenuZona);
		ultima_zona-> zona_successiva = NULL;
	}
}

//stampa la lista(mappa)
void stampaMappa()
{
	Zona *temp = prima_zona;
	int countZone = 1;
	
	while(temp != NULL)
	{
		printf("\n-----------------\n");
		printf("%d, %s\n", countZone, assoc_nome_zone[temp->nome_zona]);
		printf("%s\n", assoc_nome_oggetti[temp->oggetto]);
		printf("------------------\n");
		temp = temp->zona_successiva;
		countZone++;
	}
	
	if(prima_zona == NULL)
	{
		printf("\n-------Mappa Vuota-------\a\n");
	}
}

//menù  per la gestione della mappa
void gest_mappa()
{
	int sceltaMenuMappa;
	int sceltaMenuZona;
	char sceltaEliminazioneMappa = ' ';

	do
	{
		printf("\n --Crea Mappa--\n");
		printf("\n1) Inserisci zona\n2) Cancella zona\n3) Stampa mappa\n4) Eliminazione mappa\n5) Chiudi mappa\n");
		scanf("%d", &sceltaMenuMappa);
		switch(sceltaMenuMappa)
		{
			case 1:
				if(flagMappaCreata == 0)
				{
					do
					{
						printf("\nScegli:\n1) Cucina\n2) Soggiorno\n3) Rimessa\n4) Strada\n 5) Lungo lago\n6) Fine inserimento ^-^\n");
						scanf("%d", &sceltaMenuZona);
						sceltaMenuZona--;
						if(sceltaMenuZona >= 0 && sceltaMenuZona <= 4)
						{
							ins_zona(sceltaMenuZona);
							//printf("%d", sceltaMenuZona);
						}		
						else if(sceltaMenuZona == 5)
						{
							break;
						}
						else
						{
							printf("\n------ Sbagliato (>-<) ------\a\n");
							sceltaMenuZona = -1;
						}
					}
					
					while(sceltaMenuZona != 5);
				}
				
				else
				{
					printf("\n Mappa già creata, non puoi inserire zone (^-^)''\a\n");
				}
				break;

			case 2:
				if(flagMappaCreata == 0)
				{
					rimuoviElemento();
				}
				else
				{
					printf("\n Mappa già creata, non puoi eliminare zone (°v°)\a\n");
				}
				break;

			case 3:
				stampaMappa();
				break;

			case 4:
				do
				{
					printf("\n Ne sei sicuro?(S/N)\n");
					scanf("%s", &sceltaEliminazioneMappa);
					switch(sceltaEliminazioneMappa)
					{
						case 'S':
						case 's':
							elimina_mappa();
							flagMappaCreata = 0;
							break;
						
						case 'N':
						case 'n':
							break;
		
						default:
							sceltaEliminazioneMappa = 'e';
							break;
					}
				}
				while(sceltaEliminazioneMappa == 'e');
				break;

		      case 5:
				switch(controlloInsMappa())
				{
					case 1:
						flagMappaCreata = 1; //flag responsabile della creazione completa della lista(mappa)
						ins_zona(5); //inserisci il campo UscitaCampeggio alla fine dell'insermento di tutti gli elementi(zone)
						countZone();

						printf("\n PERFECT! Mappa chiusa (*-*)\n");
						break;
				
					case -1:
						printf("\n Devi aggiungere più zone (<_<)\n");
						sceltaMenuMappa = -1;
						break;

					case -2: 
						printf("\n Mappa Vuota (T_T) non hai inserito nulla\a\n");
						break;		
					case -3:
						//non permette l inserimento di uscita cammpeggio quando è già presente
						break;		
				}
				break;
			
			default:
				printf("\nScelta errata!\n"); 
				break;
			}
		}
		while(sceltaMenuMappa !=5);
		sleep(3); //rimane printato per 3 secondi, se no col systemclear cancella le printf
		system("clear");
}
				

//rimuovere ultimo elemento lista (mappa)
void rimuoviElemento()
{
	if(prima_zona == ultima_zona)
	{
		free(prima_zona);
		prima_zona = NULL;
		ultima_zona = NULL;
		if(prima_zona == NULL)
		{
			printf("La mappa non ha zone da eliminare!\n");
		}
	}
	else
	{
		Zona *temp = prima_zona;
		while(temp != NULL)
		{
			if(temp->zona_successiva == ultima_zona)
			{
				free(ultima_zona);
				temp->zona_successiva = NULL;
				ultima_zona=temp;
				break;
			}
			
			temp= temp-> zona_successiva;
		}
	}
}

//inizializza la funzione di sistema rand()
void inizializzazioneRand()
{
	time_t t;
	srand((unsigned) time(&t));
}

//estrarre casualmente un oggetto attinendosi alle probabilità della matrice probabilita_ogg_zona

int randomOggetti(int indexZona)
{
	int randNum = (rand() % 1000);
	int count = 0;
	int i = -1;
	do 
	{
		i++;
		count = count + probabilita_ogg_zona[indexZona][i];
	}
	while(count < randNum);
	return i;
}

//controllo parametri lista(mappa)
int controlloInsMappa()
{

	if(prima_zona == NULL) //controllo se nella lista ci sta aleno un elemento(zona)
	{
		return -2;
	}
	if(countZone() < 8) //controllo se il numero di elementi (zone) siano almeno 8
	{
		return -1;
	}
	else if(ultima_zona -> nome_zona == 5)
	{
		return -3;
	}
	else //se tutti i controlli sono andati a buon fine
	{
		return 1;
	}
}

//elimina intera lista (mappa)
void elimina_mappa()
{
	//eliminazione e deallocazione delle liste dati
	while(prima_zona != NULL)
	{
		Zona *temp = prima_zona;
		prima_zona = prima_zona -> zona_successiva;
		free(temp);
	}
	
	prima_zona = NULL;
	ultima_zona = NULL;
	flagMappaCreata = 0;
}

//conta elementi (zone) all interno della lista(mappa)
int countZone()
{
	Zona *temp = prima_zona;
	int countZone = 0;
	while(temp !=NULL)
	{
		countZone++;
		temp -> numZona = countZone;
		temp = temp-> zona_successiva;
	}
	return countZone;
} 


//GIOCA

//pulizia zaino 
void inizZaino(Giocatore *giocatore)
{
	for(int i = 0; i < sizeof(giocatore -> zaino)/4; i++)
	{
		giocatore -> zaino[i] = 0;
	}
}

//Funzione che randomizza chi inizia il turno
/*int randomGiocatore()
{
	return rand() % numeroGiocatori;
}

//
void ordine_giocatori(numeroGiocatori, *i_array)
{
}*/

//Funzione che inizializza il gioco
void inizGioco(int numGiocatori)
{
	for(int i =0; i < numeroGiocatori; i++)
	{
		giocatore[i] = (Giocatore *)malloc(sizeof(Giocatore));
		giocatore[i] -> indexGiocatore = i;
		giocatore[i] -> stato = 0; //vivo
		giocatore[i] -> posizioneGiocatore = prima_zona;
		giocatore[i] -> vittoria = 0;
		inizZaino(giocatore[i]);
	}

	strcpy(giocatore[0] -> nome_giocatore, "Giacomo");
	strcpy(giocatore[1] -> nome_giocatore, "Marzia");
	giocatore[0] -> zaino[2] = 1;
	giocatore[1] -> zaino[5] = 2;
}

//Funzione che controll il gioco principale 
void gioca()
{
	int player = 0;
	int sceltaOpzioniGioco = 0;
	char sceltaUscitaGioco = ' ';
	int turno = 0; //quando giocano entrambi
	int countFase = 0;//singola mossa di un giocatore

	do
	{
		if(giocatore[0] ->  stato != 2 && giocatore[1] -> stato != 2)
		{
			if(flagRipTurn == 0)
			{
				if(countFase == 0)
				{
					player = rand() % numeroGiocatori;
					countFase ++;
				}
				else
				{
					player = switch_giocatore(player);
					countFase = 0;
				}
				if(countFase == 1)
				{
					turno ++;   //per contare il turno a cui stanno
				}
			}
			else
			{
				flagRipTurn --; //flagripturno si incrementa per tipo quando guardi lo zaino se no perdi il turno. poi però te lo ridecrementa per portarlo alla situazione iniziale
			}
		}
		else if(giocatore[0] -> stato != 2 || giocatore[1] -> stato != 2)
		{
			if(flagRipTurn == 0)
			{
				if(giocatore[0] -> stato ==2)
				{
					player = 1;
				}
				else
				{
					player = 0;
				}
				turno++;
			}
			else
			{
				flagRipTurn--;
			}
		}
	

	printf("\nZona attuale: %s\nZona %d di %d\n", assoc_nome_zone[giocatore[player] -> posizioneGiocatore -> nome_zona], giocatore[player] -> posizioneGiocatore -> numZona, countZone());
	printf("Turno: %d, %s\n", turno, giocatore[player] ->  nome_giocatore);
	printf("Stato: %s\n", assoc_stato[giocatore[player] -> stato]);
	printf("\nSeleziona un'azione da fare:\n1) Cerca oggetto\n2) Prendi oggetto\n3) Avanza alla zona successiva\n4) Cura\n5) Usa Adrenalina\n6) Visualizza zaino\n7) Esci dal gioco\n");
	scanf("%d", &sceltaOpzioniGioco);

	do
	{
		
		switch(sceltaOpzioniGioco)
		{
			case 1:
				if(giocatore[player] -> posizioneGiocatore -> oggetto != -1)
				{
					printf("\nGurdandoti attorno hai trovato %s\n", assoc_nome_oggetti[mostra_oggetto(giocatore[player] -> posizioneGiocatore)]);
				sceltaOpzioniGioco = 7;
				}
				else
				{
					printf("\nPurtroppo non hai trovato nulla...\n");
				}
				sceltaOpzioniGioco = 0;
				break;
			case 2:
				if(prendi_oggetto(giocatore[player] -> posizioneGiocatore, giocatore[player]) == 0)
				{
					printf("\nNessun oggetto presente in zona\n");
					flagRipTurn = 1;
				}
				else
				{
					prendi_oggetto(giocatore[player] -> posizioneGiocatore, giocatore[player]);
				}
				sceltaOpzioniGioco = 7; //deve uscire dal ciclo interno. metto 7 ogni volta
				break;
				
			case 3:
				if((giocatore[player] -> posizioneGiocatore) -> nome_zona != 5)
				{
					avanza(giocatore[player]);
					printf("\nSei arrivato a %s\n", assoc_nome_zone[giocatore[player]-> posizioneGiocatore -> nome_zona]);
				sceltaOpzioniGioco = 7;
				}
				else
				{
					printf("Ce l'hai quasi fatta!!!\n");
					sceltaOpzioniGioco = 7;
					giocatore[player] -> vittoria = 1;
				}
				break;

			case 4:
				switch(cura(giocatore[player]))
				{
					case 0: 
						cura(giocatore[player]);
						printf("\nTi sei curato per fortuna >_>\n");
						break;
					case -1:
						printf("\nNon serve che ti curi haha\n");
						flagRipTurn++;
						break;
					case -3:
						printf("\nNon hai strumenti di cura\n");
						flagRipTurn++;			
						break;
				}
				sceltaOpzioniGioco= 7;
				break;
		
			case 5:
				if(usa_adrenalina(giocatore[player]) == 1)
				{
					flagRipTurn = 2; //fa due mosse invece che una
					printf("\nHai usato Adrenalina\n");
				}
				else
				{
					printf("\nNon hai Adrenalina\n");
					flagRipTurn++;
				}

			case 6:
				visualizza_zaino(giocatore[player]);
				flagRipTurn++;
				sceltaOpzioniGioco = 0;
				break;
			case 7:
				printf("\nSicuro di voler continuare? S/N\n");
				scanf("%s", &sceltaUscitaGioco);
				switch(sceltaUscitaGioco)
				{
					case 'S':
					case 's':
							deallocazioneDati();
							elimina_mappa();
							sceltaOpzioniGioco = 9;
							break;
					case 'N':
					case 'n':
							sceltaOpzioniGioco = 0;
							flagRipTurn++;
							break;
					default:
							printf("**Errore**\n");
							flagRipTurn++;
							sceltaOpzioniGioco = 0;
							break;
				}
				break;
			default:
				printf("**Errore**\n");
				flagRipTurn++;
				sceltaOpzioniGioco = 0;
				break;
			}
		}
	while(sceltaOpzioniGioco < 7  && sceltaOpzioniGioco >= 1 );


	if(sceltaOpzioniGioco == 9)
	{
		break;
	}
	else
	{
		if(flagRipTurn == 0)
		{
			if(benzinaUsata == 0)
			{
				if(prob_gieson(giocatore[player], giocatore[switch_giocatore(player)], giocatore[player] -> posizioneGiocatore)== 1)
				{
					gieson(giocatore[player]);
					if(giocatore[player] -> stato == 2)
					{
						printf("\n%s viene ucciso da Gieson\n", giocatore[player] -> nome_giocatore);
					}
					else if(giocatore[player] -> vittoria == 1)
					{
						printf("%s è riuscito a sopravvivere\n", giocatore[player] -> nome_giocatore);
						giocatore[player] -> stato = 2;
					}
				}
			}
			else
			{
				if(giocatore[player] -> vittoria == 1)
				{
					printf("\n%s è riuscito a sopravvivere\n", giocatore[player] -> nome_giocatore);
					giocatore[player] -> stato = 2;
				}
				benzinaUsata--;
			}
			sceltaOpzioniGioco = 0;
		}
	}



	if(giocatore[0] -> vittoria == 1 && giocatore[1] -> vittoria == 1)
	{
		printf("\nHai vinto!!!\n");
		deallocazioneDati();
		elimina_mappa();
		sceltaOpzioniGioco = 9;
	}

	else if(giocatore[0] -> vittoria == 1 && giocatore[1] -> vittoria == 0)
	{
		printf("\nHai vinto!!!\n");
		deallocazioneDati();
		elimina_mappa();
		sceltaOpzioniGioco = 9;
	}
	else if(giocatore[0] -> vittoria == 0 && giocatore[1] -> vittoria == 1)
	{
		printf("\nHai vinto!!!\n");
		deallocazioneDati();
		elimina_mappa();
		sceltaOpzioniGioco = 9;
	}
	else if(giocatore[0]-> stato == 2 && giocatore[1] ->stato == 2)
	{
		printf("\nEntrambi i giocatori sono morti\n");
		deallocazioneDati();
		elimina_mappa();
		sceltaOpzioniGioco = 9;
	}
}
while(sceltaOpzioniGioco != 9);
}


//Funzione che mostra oggetto
int mostra_oggetto(Zona *posizioneGiocatore)
{
	return posizioneGiocatore -> oggetto;
}

//Funzione che prende l oggetto
int prendi_oggetto(Zona *posizioneGiocatore, Giocatore *giocatore)
{
	if(posizioneGiocatore -> oggetto != -1)
	{
		giocatore -> zaino[posizioneGiocatore -> oggetto]++;
		printf("\nHai preso %s\n", assoc_nome_oggetti[posizioneGiocatore -> oggetto]);
		posizioneGiocatore -> oggetto = -1;
		return 1;
	}
	else
	{
		return 0;
	}
}


//Funzione che visualizza lo zaino
void visualizza_zaino(Giocatore *giocatore)
{
	printf("Zaino di %s\n", giocatore -> nome_giocatore);
	for(int i = 0;  i < sizeof(giocatore -> zaino) / 4; i++)
	{
		printf("|%s x %d|\n", assoc_nome_oggetti[i], giocatore -> zaino[i]);
	}
}

void avanza(Giocatore *giocatore)
{
	giocatore -> posizioneGiocatore = (giocatore -> posizioneGiocatore) -> zona_successiva;
}

int cura(Giocatore *giocatore)
{
	switch(giocatore -> stato)
	{
		case 0:
			return -1;
		case 1:
			if(giocatore ->zaino[1] != 0) //si cura una volta ammesso abbia le bende
			{
				giocatore -> stato = 0;
				giocatore -> zaino [1] --;
				return 0;
			}
			else  //non ci sone bende
			{
				return -3;
			}
	}
}

void deallocazioneDati()
{
	for(int i = 0; i < numeroGiocatori; i++)
	{
		free(giocatore[i]);
		giocatore[i] = NULL;
	}
}


int usa_adrenalina(Giocatore *giocatore)
{
	if(giocatore -> zaino[5] != 0)
	{
		giocatore -> zaino[5]--;
		return 1;
	}
	else
	{			
		return 0;
	}
}


int switch_giocatore(int giocatore)
{
	switch(giocatore)
	{
		case 0:
			giocatore = 1;
			break;
		case 1:
			giocatore = 0;
			break;
	}
	return giocatore;
}

int prob_gieson(Giocatore *giocatore_1, Giocatore *giocatore_2, Zona *posizioneGiocatore)
{
	int p_gieson = 0;
	p_gieson = rand() %1000;
	if(posizioneGiocatore -> nome_zona != 5)
	{
		if(giocatore_1 -> stato != 2 && giocatore_2 -> stato != 2)
		{
			if(p_gieson <= 300)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			if(p_gieson <= 500)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		if(p_gieson <= 750)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

int gieson(Giocatore *giocatore)
{
	printf("\nAppare Gieson\n");
	if(giocatore -> zaino[2] != 0 || giocatore -> zaino[3] != 0 || giocatore -> zaino[4] != 0)
	{
		int opzioniGieson = 0;
		do
		{
			printf("\nScegli un'azione da fare:\n1) Usa Coltello\n2) Usa Pistola\n3) Usa Benzina\n");
		visualizza_zaino(giocatore);
		scanf("%d", &opzioniGieson);

	
		switch(opzioniGieson)
		{		
			case 1:
				if(giocatore -> zaino[2] != 0)
				{
					giocatore -> stato++;
					giocatore -> zaino[2]--;
					printf("\nUsi il coltello ma hai riportato danni dallo scontro\n");
				}
				else
				{
					printf("\nNon hai il coltello\n");
					opzioniGieson = -1;
				}break;
			case 2:
				if(giocatore-> zaino[3] != 0)
				{
					giocatore -> zaino[3]--;
					printf("\nUsi la pistola contro Gieson e riesci a fuggire\n");
				}
				else
				{
					printf("\nNon hai la pistola\n");
					opzioniGieson = -1;
				}break;
			case 3:
				if(giocatore -> zaino[4] != 0)
				{
					giocatore -> zaino[4]--;
					printf("\nUsi la benzina\n");
				}
				else
				{
					printf("\nNon hai la benzina\n");
					opzioniGieson = -1;
				}
				benzinaUsata = 4; //porto la benzina usata a 4 e non appare gieson per 4 mosse
				break;
			default:
				opzioniGieson = -1;
				break;
		}
	}
	while(opzioniGieson < 1 || opzioniGieson > 3);
}
else
{
	printf("\nNon hai nessun oggetto per difenderti...\n");
	giocatore -> stato = 2;
}
}

						
