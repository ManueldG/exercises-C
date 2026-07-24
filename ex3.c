#include <stdio.h>

// 1. GENERAZIONE DELLA STRUCT
struct Persona {
#define X(tipo, nome) tipo nome;
#include "ex3.def"
#undef X
};

// 2. FUNZIONE DI STAMPA AUTOMATICA
void stampaPersona(struct Persona p) {
#define X(tipo, nome) \
    if (__builtin_types_compatible_p(tipo, int)) printf("%s: %d\n", #nome, p.nome); \
    else if (__builtin_types_compatible_p(tipo, float)) printf("%s: %.2f\n", #nome, p.nome);
#include "ex3.def"
#undef X
}

int main() {
    struct Persona utente = {25, 1.75f, 99};

    stampaPersona(utente);
    
    return 0;
}

