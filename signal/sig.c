#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>

// 1. QUESTA È LA TUA FUNZIONE CONFIGURATA (Il Signal Handler)
//void gestore_sigusr1(int num_segnale, siginfo_t *info, void *context) {
void gestore_sigusr1(int num_segnale) {

        printf("\n[Client] Ricevuto SIG n %d \n", num_segnale);
        //ricevuto USR1 scrivo nell'area condivisa utenti + 1 e status 0 (da definire i vari codici) 
       /*
		0 collegamento il file è presente e aspetta che tutti si collegano utenti attesi == utenti collegati
		1 normale tutti hanno l'indirizzo del'area e il file é cancellato
		2 l'area é occupata il client scrive e ritorna a 1 lo status
		3 riavvio: i client si scollegano utenti-- quando utenti =0 tutti scollegati aspettano il server che crea il file per ricollegarsi il server si scollega ricrea il file lo mappa controlla gli utenti se sono tutti ricancello il file e status 1
	*/ 
}

int main() {

    // Stampa il PID del client (servirà al server per chiamarlo)
    printf("Client attivo. Il mio PID è: %d\n", getpid());

    // 2. CONFIGURAZIONE DEL SEGNALE TRAMITE SIGACTION
    struct sigaction sa;
    sa.sa_handler = gestore_sigusr1; // Collega la tua funzione custom
    sigemptyset(&sa.sa_mask);        // Non bloccare altri segnali mentre esegui questa funzione
//    sa.sa_flags = SA_RESTART | SA_SIGINFO;        // Riavvia automaticamente le chiamate di sistema interrotte
    sa.sa_flags = SA_SIGINFO;        // Riavvia automaticamente le chiamate di sistema interrotte

    // Applica la configurazione a SIGUSR1
    if (sigaction(SIGUSR2, &sa, NULL) == -1) {
        perror("Errore sigaction");
        return EXIT_FAILURE;
    }
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Errore sigaction");
        return EXIT_FAILURE;
    }

    printf("In attesa di segnali dal server... (Fermami con Ctrl+C)\n");

    while(1) {
        pause(); // Sospende il processo fino all'arrivo di UN QUALSIASI segnale
    }

    return EXIT_SUCCESS;

}
