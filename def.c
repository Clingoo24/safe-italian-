#include "prot.h"

void menu(void){

	FILE *fp;
	int scelta = -1;
	int cassaforte_aperta = 0;
	int creazione_cassaforte = 0;
	int stato = 0;
	int denaro_presente = 0;
	int esistente = 0;
	
	int combinazione;
	int somma_denaro = 0;
	
	
	while(scelta != 0){
	
		printf("scegli:\n");
		printf("1. crea nuova cassaforte (eventuale cassaforte già esistente sarà distrutta)\n");
		printf("2. apri cassaforte\n");
		printf("3. visualizza lo stato della cassaforte\n");
		printf("4. visualizza ammontare\n");
		printf("5. deposita somma\n");
		printf("6. preleva somma\n");
		printf("7. chiudi cassaforte\n");
		printf("0. esci (eventuali modifiche a cassaforte aperta andranno perse)\n\n");

		if ((scanf("%d",&scelta) != 1) || (scelta < 0) || (scelta > 7))	gest_err(DATI);
		
		if (scelta == 1){
		
			if (esistente == 1){
			
				fclose(fp);
				
				printf("\nEliminazione cassaforte precedente.\n\n");
				if (remove("data.bin") == 0){
				
					printf("Eliminazione riuscita.\n\n");
					
				} else printf("Eliminazione non riuscita!\n\n");
				
				esistente = 0;
			}
		
			fp = apertura(scrittura_up);
			esistente = 1;
		
			rewind(fp);
		
			printf("\nscegli la combinazione: ");
			
			clear_buffer();
			if (scanf("%d",&combinazione) != 1) gest_err(DATI);
			
			if (fwrite(&combinazione, sizeof(int), 1, fp) != 1) gest_err(DATI);
			
			if (fwrite(&somma_denaro, sizeof(int), 1, fp) != 1) gest_err(DATI);
			
			printf("\n");
			
			creazione_cassaforte = 1;
			
			rewind(fp);
		}
		
		if (scelta == 2 && creazione_cassaforte == 1){
		
			int pin;
			int conf;
			
			rewind(fp);
		
			printf("\nInserisci combinazione: ");
			
			clear_buffer();
			if (scanf("%d",&pin) != 1) gest_err(DATI);
			
			if (fread(&conf, sizeof(int), 1, fp) != 1) gest_err(DATI);
			
			if (conf == pin){
			
				cassaforte_aperta = 1;
				printf("\nCassaforte aperta!\n\n");
				
			} else printf("\nPin errato, riprovare!\n\n");
			
			rewind(fp);
		
		} else if (scelta == 2 && creazione_cassaforte == 0) printf("\nNon hai creato alcuna cazzaforte!\n\n");
		
		
		if (scelta == 3 && creazione_cassaforte == 1){
		
			if (cassaforte_aperta == 1) printf("\nLa cassaforte è aperta\n\n");
			else printf("\nLa cassaforte è chiusa\n\n");
		
		} else if (scelta == 3 && creazione_cassaforte == 0) printf("\nNon hai creato alcuna cassaforte!\n\n");;
		
		
		if (scelta == 4 && denaro_presente == 1 && cassaforte_aperta == 1 && creazione_cassaforte == 1){
		
			rewind(fp);
		
			if (fseek(fp, sizeof(int), SEEK_CUR) != 0) gest_err(POS);
			
			if (fread(&somma_denaro, sizeof(int), 1, fp) != 1) gest_err(DATI);
			
			 printf("\nDenaro disponibile: %d\n\n", somma_denaro);
			 
			 somma_denaro = 0;
			 
			 rewind(fp);
		
		} else if (scelta == 4 && denaro_presente == 0 && cassaforte_aperta == 1 && creazione_cassaforte == 1) printf("\nLa cassaforte non contiene ancora denaro!\n\n");
		
			else if (scelta == 4 && cassaforte_aperta == 0 && creazione_cassaforte == 1) printf("\nPrima devi aprire la cassaforte!\n\n");
			
				else if (scelta == 4 && creazione_cassaforte == 0) printf("\nNon hai creato alcuna cassaforte!\n\n");
		
		if (scelta == 5 && cassaforte_aperta == 1 && creazione_cassaforte == 1){
		
			int aggiunta;
			
			rewind(fp);
			
			if (fseek(fp, sizeof(int), SEEK_CUR) != 0) gest_err(POS);
			
			if (fread(&somma_denaro, sizeof(int), 1, fp) != 1) gest_err(DATI);
			
			rewind(fp);
			
			printf("\nInserisci somma di denaro da depositare: ");
			
			clear_buffer();
			if ((scanf("%d",&aggiunta) != 1) || aggiunta < 0) gest_err(DATI);
			
			somma_denaro += aggiunta;
			
			if (fseek(fp, sizeof(int), SEEK_CUR) != 0) gest_err(POS);
			
			if (fwrite(&somma_denaro, sizeof(int), 1, fp) != 1) gest_err(DATI);
			
			denaro_presente = 1;
			
			somma_denaro = 0;
			
			rewind(fp);
		
		} else if (scelta == 5 && cassaforte_aperta == 0 && creazione_cassaforte == 1) printf("\nPrima devi aprire la cassaforte!\n\n");
		
			else if (scelta == 5 && creazione_cassaforte == 0) printf("\nNon hai creato alcuna cassaforte!\n\n");
		
		if (scelta == 6 && cassaforte_aperta == 1 && creazione_cassaforte == 1){
		
			int sottratta;
			
			rewind(fp);
			
			if (fseek(fp, sizeof(int), SEEK_CUR) != 0) gest_err(POS);
			
			if (fread(&somma_denaro, sizeof(int), 1, fp) != 1) gest_err(DATI);
			
			rewind(fp);
			
			printf("\nInserisci somma di denaro da prelevare: ");
			
			clear_buffer();
			if ((scanf("%d",&sottratta) != 1) || sottratta < 0) gest_err(DATI);
			
			somma_denaro -= sottratta;
			
			if (fseek(fp, sizeof(int), SEEK_CUR) != 0) gest_err(POS);
			
			if (fwrite(&somma_denaro, sizeof(int), 1, fp) != 1) gest_err(DATI);
			
			denaro_presente = 1;
			
			somma_denaro = 0;
			
			rewind(fp);
		
		} else if (scelta == 6 && cassaforte_aperta == 0 && creazione_cassaforte == 1) printf("\nPrima devi aprire la cassaforte!\n\n");
		
			else if (scelta == 6 && creazione_cassaforte == 0) printf("\nNon hai creato alcuna cassaforte!\n\n");
		
		if (scelta == 7 && cassaforte_aperta == 1 && creazione_cassaforte == 1){
		
			printf("\nHo chiuso la cassaforte!\n\n");
			cassaforte_aperta = 0;
			
		} else if (scelta == 7 && cassaforte_aperta == 0 && creazione_cassaforte == 1) printf("\nLa cassaforte è già chiusa!\n\n");
		
			else if (scelta == 6 && creazione_cassaforte == 0) printf("\nNon hai creato alcuna cassaforte!\n\n");
	}
	
	printf("\n\nUscita in corso...\n");
	exit(-1);
}

FILE* apertura(FILE* (*tipo) (FILE *fp)){

	FILE *fp;

	fp = tipo(fp);
	
	if (fp == NULL) gest_err(AP_SCR);
	
	return fp;
}

FILE* scrittura_up(FILE *fp){

	return fopen("data.bin", "w+b");
}

void clear_buffer(void){

	char c;

	do {
		c = getchar();
	
	} while (c != '\n' && c != EOF);
}

void gest_err(int err){

	switch(err){
	
		case 0: 	printf("Errore inserimento dati, uscita...\n");
				exit(-1);
			break;
		
		case 1: 	printf("Errore allocazione, uscita...\n");
				exit(-1);
			break;
			
		case 2: 	printf("Errore apertura file in scrittura, uscita...\n");
				exit(-1);
			break;	
			
		case 3: 	printf("Errore posizionamento file, uscita...\n");
				exit(-1);
			break;	
	}
}
