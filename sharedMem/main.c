#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <strings.h>

/*
si potrebbe richiedere il n di utenti
se si collegano n utenti fare unlink
del file
per gestire l'accesso creare una coda
di modifiche o una coda di richieste
d'accesso

o semplicemente
 0 in collegamento utenti == collegati per passare a 1 
 1 pronto
 2 occupato faccio la modifica e torno a 1 aggiungerei un timeout
 3 richiesta colleganento i client si scollegano e si rifa la procedura di collegamento

la struct 
int collegati
int utenti il server scrive gli utenti i client quando si collegano utenti-- quando arriva a 0 si fa unlink
int status
in caso di errore?
*/

struct AreaCondivisa {
    int status;
    int utenti;
    int collegati;
    char messaggio[100];
};

const char *path = "/data/data/com.termux/files/usr/tmp/condiviso.dat";

struct AreaCondivisa * connect(struct AreaCondivisa *oldadd){

    // 1. Crea e imposta la dimensione del file
    int fd = open(path, O_RDWR | O_CREAT, 0666);
    ftruncate(fd, sizeof(struct AreaCondivisa));
    // 2. Mappa in RAM
    struct AreaCondivisa *shm = mmap(oldadd, sizeof(struct AreaCondivisa), 

                                     PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd); // Il file descriptor non serve più

    return shm;
}

int main() {

    char *oldstr;   

    struct AreaCondivisa *shm = NULL;
    shm = connect(shm);

    // 3. Inizializza il flag di handshake
    shm->status = 0; //in collegamento
    shm->utenti = 2;
    shm->collegati = 1;
    printf("[A] In attesa che il Processo B si colleghi...\n");

    // 4. LOOP DI ATTESA (Spin-lock): aspetta che B scriva 1
    while (shm->utenti != shm->collegati) {
        usleep(100000); // Aspetta 100 millisecondi per non sovraccaricare la CPU
    }

    // 5. ORA PUOI FARE UNLINK IN SICUREZZA!
    printf("[A] Processo B rilevato! Eseguo unlink del file.\n");
    unlink(path);
/*    
    fd = open(path, O_RDWR | O_CREAT, 0666);
    ftruncate(fd, sizeof(struct AreaCondivisa));
    munmap(shm, sizeof(struct AreaCondivisa));
    struct AreaCondivisa *tmp = mmap(shm, sizeof(struct AreaCondivisa),
                                     PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    printf("\n %lu %lu \n ",shm,tmp);
    tmp = shm;
*/

    shm->status = 2;

    // Da qui in poi la memoria è invisibile sul disco ma attiva in RAM
    printf("[A] Scrivo i dati in RAM...\n");
    snprintf(shm->messaggio, sizeof(shm->messaggio), "Ciao da Processo A (in RAM anonima)!");

    strcpy(oldstr,shm->messaggio);    
    // Cambia il flag per dire a B che i dati sono pronti da leggere

    shm->status = 1; 


    while( ( shm->status != 1 ) || (strcmp(oldstr,shm->messaggio) == 0) ){

       usleep(1000);

    }

    printf("\n[B]:%s \n",shm->messaggio);    

    /*
       ricevo il segnale usr1 status 3 viene
       letto dai client che decrementano collegatie
       si scollegano fino a 0 incremento utenti faccio una copia di shm e scollego
      shm ripeto la procedura
       open mmap passo il vecchio indirizzo truncate status 0 attendo utenti == collegati status 1
       
    */

    munmap(shm, sizeof(struct AreaCondivisa));
    return 0;
}

