#include <stdio.h>
#include "gamelib.c"

//nel main metto solo la stampa del menu iniziale e i richiami alle tre scelte del giocatore

int main()
{
	char sceltaMenuStart;
	inizializzazioneRand();

	do
	{
		printf("\n --! Welcome !--\n");
		printf("\n1) Gestione mappa\n2) Gioca\n3) Termina gioco\n");
		scanf("%s", &sceltaMenuStart);
		
		switch(sceltaMenuStart)
		{
			case '1':
				system("clear");
				gest_mappa();
				break;

			case '2':
				if(flagMappaCreata == 1)
				{
					system("clear");
					inizGioco(numeroGiocatori);
					gioca();
					break;
				}
				else
				{
					printf("Crea prima la mappa!!\n");
					sceltaMenuStart = ' ';
				}

			case '3':
	
				exit(1);
				break;

			default:
				printf("\nScelta non valida!!!\n");
				sceltaMenuStart = ' ';
				break;
		}
	}while(sceltaMenuStart != '3');

}	
