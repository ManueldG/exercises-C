#include <stdio.h>

// 1. DEFINIZIONE DELLA LISTA (Tipo, Nome, Valore di Reset)
#define LISTA_CONFIG \
    X(int, temperatura, 20)  \
    X(int, pressione, 100)   \
    X(float, tensione, 5.5f)

// 2. GENERAZIONE AUTOMATICA DELLA STRUCT
struct Configurazione {
#define X(tipo, nome, reset) tipo nome;
    LISTA_CONFIG
#undef X
};

// 3. FUNZIONE PER AZZERARE I MEMBRI ai valori di default
void resetConfig(struct Configurazione *c) {
#define X(tipo, nome, reset) c->nome = reset;
    LISTA_CONFIG
#undef X
}

// 4. FUNZIONE PER STAMPARE TUTTI I MEMBRI
void stampaConfig(struct Configurazione c) {
    printf("--- STATO CONFIGURAZIONE ---\n");
#define X(tipo, nome, reset) \
    if (__builtin_types_compatible_p(tipo, int)) printf("%s: %d\n", #nome, c.nome); \
    else if (__builtin_types_compatible_p(tipo, float)) printf("%s: %.2f\n", #nome, c.nome);
    
    LISTA_CONFIG
#undef X
    printf("----------------------------\n\n");
}

int main() {
    struct Configurazione miaConfig;

    // Inizializza/Azzera la struct automaticamente
    resetConfig(&miaConfig);
    stampaConfig(miaConfig);

    // Modifica manuale di un campo specifico (come una struct normale)
    miaConfig.temperatura = 35;
    miaConfig.tensione = 4.8f;

    printf("Dopo la modifica manuale:\n");
    stampaConfig(miaConfig);

    return 0;
}

