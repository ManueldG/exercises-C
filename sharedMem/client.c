#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

struct AreaCondivisa {
    int status;
    int utenti;
    int collegati;
    char messaggio[100];
};

int main() {
    const char *path = "/data/data/com.termux/files/usr/tmp/condiviso.dat";
    
    // 1. Apre il file esistente
    int fd = open(path, O_RDWR);
    if (fd == -1) {
        perror("[B] Errore nell'apertura del file (forse A non è ancora partito?)");
        return 1;
    }

    // 2. Mappa in RAM
    struct AreaCondivisa *shm = mmap(NULL, sizeof(struct AreaCondivisa),PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);


    // 3. SEGNALA LA PRESENZA A B
    printf("[B] Connesso alla memoria. Avviso il Processo A...\n");
    shm->collegati++; // Questo sbloccherà il "while" nel Processo A
/*
    munmap(shm, sizeof(struct AreaCondivisa));
usleep(100000);
    fd = open(path, O_RDWR);
    if (fd == -1) {
        perror("[B] Errore nell'apertura del file (forse A non è ancora partito?)");
        return 1;
    
    }
    shm = mmap(NULL, sizeof(struct AreaCondivisa),PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
//    shm->pronto = 1; // Questo sbloccherà il "while" nel Processo A
    // 4. Aspetta che A inserisca i dati veri e propri (flag = 2)
*/
    printf("[B] In attesa dei dati dal Processo A...\n");
    while (shm->status != 1) {
        usleep(1000);
    }

    // 5. Legge il messaggio
    printf("[B] Dati letti con successo: %s\n", shm->messaggio);

    while (shm->status != 1) {
        usleep(1000);
    }
    shm->status = 2;
    printf("\ninvio messaggio\n");
    snprintf(shm->messaggio,sizeof(struct AreaCondivisa),"risposta da processo [B]");    
    shm->status = 1;
    munmap(shm, sizeof(struct AreaCondivisa));
    return 0;
}
