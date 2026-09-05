
#include <sys/types.h>

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//#include "mu.h"

static const char *
strcode(int si_code)
{
    switch (si_code) {
    case SI_USER:       return "sent by user";
    case SI_KERNEL:     return "sent by kernel";
    case SI_QUEUE:      return "sent by sigqueue";
    case SI_TIMER:      return "POSIX timer expired";
    case SI_MESGQ:      return "POSIX message queue state chnaged";
    case SI_ASYNCIO:    return "AIO completed";
    case SI_SIGIO:      return "Queued SIGIO";
    case SI_TKILL:      return "tkill";

    /* TODO: others: see `man sigaction` */

    default:            return "unknown";
    }
}



/* UNSAFE: this handler uses a non-async-signal-safe function (printf) */
static void
handler(int sig, siginfo_t *siginfo, void *ucontext)
{
    static int cnt = 0;
    (void)sig;
    (void)ucontext;

    cnt++;

    printf("#%d\n", cnt);
    printf("\tsi_signo: %d (%s)\n", siginfo->si_signo, strsignal(siginfo->si_signo));
    printf("\tsi_code.: %d (%s)\n", siginfo->si_code, strcode(siginfo->si_code));
    if (siginfo->si_code == SI_USER || siginfo->si_code == SI_QUEUE) {
      printf("\tsi_pid..: %d\n", siginfo->si_pid);
      printf("\tsi_uid..: %d\n", siginfo->si_uid);
    }

    return;
}


int
main(void)
{
    struct sigaction act;
    sigset_t mask;

    printf("pid: %d\n", getpid());
  
    //inizializza a zero tutta la struttura
    memset(&act, 0x00, sizeof(act));

    sigemptyset(&act.sa_mask);

    //act.sa_handler la funzione che legge solo il SIG
    act.sa_sigaction = handler;
    act.sa_flags = SA_SIGINFO;

    //gestisce la ricezione di SIGINT
    if (sigaction(SIGINT, &act, NULL) == -1){
	printf("errore %d",errno);	
	}
        //mu_die_errno(errno, "sigaction");

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);

// non so a cosa serva- while mantiene il processo attivo mentre sigprocmask ignora i segnali per 3 sec e poi li riattiva
    while (1) {
        sigprocmask(SIG_BLOCK, &mask, NULL);
        sleep(3);
        sigprocmask(SIG_UNBLOCK, &mask, NULL);
    }

    return 0;
}
