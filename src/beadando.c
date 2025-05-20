#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h> 
#include <sys/time.h>

struct Jatekos
{
    int szektor15;
    int szektor16;
    int szektor17;
    int szektor18;
    int szektor19;
    int szektor20;
    int szektor21;
    int bezartSzektorok;
    int elertPontok;
};

int csovezetek1[2];
int csovezetek2[2];

sem_t* szemafor_jatekos1_start;
sem_t* szemafor_jatekos1_done;

sem_t* szemafor_jatekos2_start;
sem_t* szemafor_jatekos2_done;

void Jatekos1Koszones()
{
    printf("\nArpi becsatlakozott a jatekba :)!\n");
}

void Jatekos2Koszones()
{
    printf("\nBela becsatlakozott a jatekba :)!\n");
}

void Jatekos1Jatek()
{
    // Arpi
    szemafor_jatekos1_start = sem_open("/jatekos1_start", O_CREAT, 0600, 0);
    szemafor_jatekos1_done = sem_open("/jatekos1_done", O_CREAT, 0600, 0);

    close(csovezetek1[0]);
    signal(SIGUSR1, Jatekos1Koszones);

    while (1)
    {
        sem_wait(szemafor_jatekos1_start);

        struct timeval tv;
        gettimeofday(&tv, NULL);
        srand(tv.tv_usec ^ getpid());

        sleep(1);
        int dobottSzektor = rand() % 8 + 13;
        sleep(1);
        int szorzo = rand() % 3 + 1;
        sleep(1);

        write(csovezetek1[1], &dobottSzektor, sizeof(int));
        write(csovezetek1[1], &szorzo, sizeof(int));

        sem_post(szemafor_jatekos1_done);
    }
}

void Jatekos2Jatek()
{
    // Bela
    szemafor_jatekos2_start = sem_open("/jatekos2_start", O_CREAT, 0600, 0);
    szemafor_jatekos2_done = sem_open("/jatekos2_done", O_CREAT, 0600, 0);

    close(csovezetek2[0]);
    signal(SIGUSR1, Jatekos2Koszones);

    while (1)
    {
        sem_wait(szemafor_jatekos2_start);

        struct timeval tv;
        gettimeofday(&tv, NULL);
        srand(tv.tv_usec ^ getpid());

        sleep(1);
        int dobottSzektor = rand() % 8 + 13;
        sleep(1);
        int szorzo = rand() % 3 + 1;
        sleep(1);

        write(csovezetek2[1], &dobottSzektor, sizeof(int));
        write(csovezetek2[1], &szorzo, sizeof(int));

        sem_post(szemafor_jatekos2_done);
    }
}

void JatekosDobas(struct Jatekos * aktivJatekos, struct Jatekos * masikJatekos, int dobottSzektor, int dobottSzorzo)
{
    int adhatoPontok = 0;

    if (dobottSzektor >= 15 && dobottSzektor <= 20)
    {
        adhatoPontok += dobottSzektor * dobottSzorzo;
    }

    if (dobottSzektor >= 13 && dobottSzektor <= 14)
    {
        adhatoPontok = 0;
    }
    
    if (dobottSzektor == 21)
    {
        if (dobottSzorzo >= 1 && dobottSzorzo <= 2)
        {
            adhatoPontok += 25;
        }
        
        if (dobottSzorzo == 3)
        {
            adhatoPontok += 50;
        }
    }

    switch (dobottSzektor)
    {
        case 15:
            if (aktivJatekos->szektor15 < 3)
            {
                aktivJatekos->szektor15 += 1;
                aktivJatekos->elertPontok += adhatoPontok;

                if (aktivJatekos->szektor15 >= 3)
                {
                    aktivJatekos->bezartSzektorok++;
                }
            }
            // Ha a masik meg nem zarta le a szektort, de az adott jatekos mar igen
            else if (aktivJatekos->szektor15 >= 3 && masikJatekos->szektor15 < 3)
            {
                aktivJatekos->elertPontok += adhatoPontok;
            }
            break;
        case 16:
            if (aktivJatekos->szektor16 < 3)
            {
                aktivJatekos->szektor16 += 1;
                aktivJatekos->elertPontok += adhatoPontok;

                if (aktivJatekos->szektor16 >= 3)
                {
                    aktivJatekos->bezartSzektorok++;
                }
            }
            // Ha a masik meg nem zarta le a szektort
            else if (aktivJatekos->szektor16 >= 3 && masikJatekos->szektor16 < 3)
            {
                aktivJatekos->elertPontok += adhatoPontok;
            }
            break;
        case 17:
            if (aktivJatekos->szektor17 < 3)
            {
                aktivJatekos->szektor17 += 1;
                aktivJatekos->elertPontok += adhatoPontok;

                if (aktivJatekos->szektor17 >= 3)
                {
                    aktivJatekos->bezartSzektorok++;
                }
            }
            // Ha a masik meg nem zarta le a szektort
            else if (aktivJatekos->szektor17 >= 3 && masikJatekos->szektor17 < 3)
            {
                aktivJatekos->elertPontok += adhatoPontok;
            }
            break;
        case 18:
            if (aktivJatekos->szektor18 < 3)
            {
                aktivJatekos->szektor18 += 1;
                aktivJatekos->elertPontok += adhatoPontok;

                if (aktivJatekos->szektor18 >= 3)
                {
                    aktivJatekos->bezartSzektorok++;
                }
            }
            // Ha a masik meg nem zarta le a szektort
            else if (aktivJatekos->szektor18 >= 3 && masikJatekos->szektor18 < 3)
            {
                aktivJatekos->elertPontok += adhatoPontok;
            }
            break;
        case 19:
            if (aktivJatekos->szektor19 < 3)
            {
                aktivJatekos->szektor19 += 1;
                aktivJatekos->elertPontok += adhatoPontok;

                if (aktivJatekos->szektor19 >= 3)
                {
                    aktivJatekos->bezartSzektorok++;
                }
            }
            // Ha a masik meg nem zarta le a szektort
            else if (aktivJatekos->szektor19 >= 3 && masikJatekos->szektor19 < 3)
            {
                aktivJatekos->elertPontok += adhatoPontok;
            }
            break;
        case 20:
            if (aktivJatekos->szektor20 < 3)
            {
                aktivJatekos->szektor20 += 1;
                aktivJatekos->elertPontok += adhatoPontok;

                if (aktivJatekos->szektor20 >= 3)
                {
                    aktivJatekos->bezartSzektorok++;
                }
            }
            // Ha a masik meg nem zarta le a szektort
            else if (aktivJatekos->szektor20 >= 3 && masikJatekos->szektor20 < 3)
            {
                aktivJatekos->elertPontok += adhatoPontok;
            }
            break;
        case 21:
            if (aktivJatekos->szektor21 < 3)
            {
                aktivJatekos->szektor21 += 1;
                aktivJatekos->elertPontok += adhatoPontok;

                if (aktivJatekos->szektor21 >= 3)
                {
                    aktivJatekos->bezartSzektorok++;
                }
            }
            // Ha a masik meg nem zarta le a szektort
            else if (aktivJatekos->szektor21 >= 3 && masikJatekos->szektor21 < 3)
            {
                aktivJatekos->elertPontok += adhatoPontok;
            }
            break;
        
        default:
            break;
    }
}

int main()
{
    puts("\n");
    puts("Krikett jatek!");
    puts("\n");

    setvbuf(stdout, NULL, _IONBF, 0);

    szemafor_jatekos1_start = sem_open("/jatekos1_start", O_CREAT, 0600, 0);
    szemafor_jatekos1_done = sem_open("/jatekos1_done", O_CREAT, 0600, 0);

    szemafor_jatekos2_start = sem_open("/jatekos2_start", O_CREAT, 0600, 0);
    szemafor_jatekos2_done = sem_open("/jatekos2_done", O_CREAT, 0600, 0);

    pipe(csovezetek1);
    pipe(csovezetek2);

    int jatekos1PID = fork();
    if (jatekos1PID == 0) {
        Jatekos1Jatek();
        return 0;
    }

    int jatekos2PID = fork();
    if (jatekos2PID == 0) {
        Jatekos2Jatek();
        return 0;
    }

    sleep(2);

    kill(jatekos1PID, SIGUSR1);
    kill(jatekos2PID, SIGUSR1);

    close(csovezetek1[1]);
    close(csovezetek2[1]);

    sleep(2);

    struct Jatekos Arpi;
    struct Jatekos Bela;

    Arpi.szektor15 = 0;
    Arpi.szektor16 = 0;
    Arpi.szektor17 = 0;
    Arpi.szektor18 = 0;
    Arpi.szektor19 = 0;
    Arpi.szektor20 = 0;
    Arpi.szektor21 = 0;
    Arpi.bezartSzektorok = 0;
    Arpi.elertPontok = 0;
    
    Bela.szektor15 = 0;
    Bela.szektor16 = 0;
    Bela.szektor17 = 0;
    Bela.szektor18 = 0;
    Bela.szektor19 = 0;
    Bela.szektor20 = 0;
    Bela.szektor21 = 0;
    Bela.bezartSzektorok = 0;
    Bela.elertPontok = 0;

    for (int i = 0; i < 20; i++)
    {
        printf("\nKör: %d\n", i + 1);

        sem_post(szemafor_jatekos1_start);
        sem_post(szemafor_jatekos2_start);

        sem_wait(szemafor_jatekos1_done);
        sem_wait(szemafor_jatekos2_done);

        int arpiSzektor;
        int arpiSzorzo;
        int belaSzektor;
        int belaSzorzo;

        read(csovezetek1[0], &arpiSzektor, sizeof(int));
        read(csovezetek1[0], &arpiSzorzo, sizeof(int));

        read(csovezetek2[0], &belaSzektor, sizeof(int));
        read(csovezetek2[0], &belaSzorzo, sizeof(int));

        JatekosDobas(&Arpi, &Bela, arpiSzektor, arpiSzorzo);
        JatekosDobas(&Bela, &Arpi, belaSzektor, belaSzorzo);

        printf("Arpi dobott szektora %d, Arpi altal kapott szorzo: (%d)\nBela dobott szektora %d Bela altal kapott szorzo: (%d)\n",
            arpiSzektor, arpiSzorzo,
            belaSzektor, belaSzorzo);

        if (Arpi.bezartSzektorok == 7 ||
            Bela.bezartSzektorok == 7)
		{
			break;
		}
    }

    printf("\nA jatek veget ert!\n");
    printf("Arpi elert pontjai: %d\n", Arpi.elertPontok);
    printf("Arpi lezart szektorjai: %d\n", Arpi.bezartSzektorok);
    printf("\n");
    printf("Bela elert pontjai: %d\n", Bela.elertPontok);
    printf("Bela lezart szektorjai: %d\n", Bela.bezartSzektorok);
    printf("\n");

    if (Arpi.elertPontok > Bela.elertPontok)
    {
        printf("Nyertes: Arpi!\n");
    }
    else
    {
        printf("Nyertes: Bela!\n");
    }

    printf("\n");

    kill(jatekos1PID, SIGTERM);
	kill(jatekos2PID, SIGTERM);
    
    wait(NULL);
    wait(NULL);

    sem_close(szemafor_jatekos1_start);
    sem_close(szemafor_jatekos1_done);
    sem_close(szemafor_jatekos2_start);
    sem_close(szemafor_jatekos2_done);

    sem_unlink("/jatekos1_start");
    sem_unlink("/jatekos1_done");
    sem_unlink("/jatekos2_start");
    sem_unlink("/jatekos2_done");

    return 0;
}