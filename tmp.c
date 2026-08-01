#include <stdio.h>
#include <unistd.h>
#include <termios.h>

void disabilita_buffer_terminale(struct termios *vecchio) {
    struct termios nuovo;
    tcgetattr(STDIN_FILENO, vecchio); // Salva la configurazione attuale
    nuovo = *vecchio;
    nuovo.c_lflag &= ~(ICANON ); // Disabilita modalità canonica ed eco dei tasti
    tcsetattr(STDIN_FILENO, TCSANOW, &nuovo); // Applica subito
}

void ripristina_terminale(struct termios *vecchio) {
    tcsetattr(STDIN_FILENO, TCSANOW, vecchio); // Ripristina la vecchia configurazione
}

int main() {
    struct termios vecchio_terminale;
    disabilita_buffer_terminale(&vecchio_terminale);

    printf("Premi un tasto qualsiasi (Uscita con 'q'):\n");

    char ch;
    // Funziona allo stesso modo sostituendo read() con: ch = getchar();
    while (read(STDIN_FILENO, &ch, 1) > 0 && ch != 'q') {
        printf("Tasto rilevato istantaneamente: '%c'\n", ch);
    }
/*
    ripristina_terminale(&vecchio_terminale);
    */
    return 0;
}

