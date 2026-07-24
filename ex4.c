#include <stdio.h>

// 1. GENERAZIONE DELLA STRUCT
struct Persona {
#define X(tipo, nome) tipo nome;
#include "ex4.h"
#undef X
};

// 2. GENERAZIONE AUTOMATICA DELL'ENUM
// Creerà: ID_eta = 0, ID_altezza = 1, ID_id = 2, NUM_CAMPI = 3
enum CampiPersona {
#define X(tipo, nome) ID_##nome,
#include "ex4.h"
#undef X
    NUM_CAMPI // Identifica automaticamente quanti campi ci sono nella struct
};

// 3. ARRAY DI STRINGHE COORDINATO (Usa la stringificazione #nome)
const char* NOMI_CAMPI[] = {
#define X(tipo, nome) #nome,
#include "ex4.h"
#undef X
};

int main() {
    // Possiamo usare NUM_CAMPI per sapere quanti elementi stampare nel ciclo
    printf("La struct ha %d campi disponibili.\n\n", NUM_CAMPI);

    // Possiamo usare le costanti dell'enum per accedere ai nomi testuali
    printf("Il campo con ID %d si chiama: %s\n", ID_altezza, NOMI_CAMPI[ID_altezza]);

    printf("Il campo con ID %d si chiama: %s\n", ID_eta, NOMI_CAMPI[ID_eta]);

    printf("Il campo con ID %d si chiama: %s\n", ID_id, NOMI_CAMPI[ID_id]);

    return 0;
    printf("Il campo con ID %d si chiama: %s\n", ID_eta, NOMI_CAMPI[ID_eta]);
    printf("Il campo con ID %d si chiama: %s\n", ID_eta, NOMI_CAMPI[ID_eta]);
}

