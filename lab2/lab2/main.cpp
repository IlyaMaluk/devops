#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include "Aztec.h"

// Объявление функции создания сервера HTTP из вашего кода.
int CreateHTTPserver();

void sigchldHandler(int s)
{
    printf("Caught signal SIGCHLD\n");

    pid_t pid;
    int status;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        if (WIFEXITED(status)) printf("\nChild process terminated");
    }
}

void sigintHandler(int s)
{
    printf("Caught signal %d. Starting graceful exit procedure\n", s);

    pid_t pid;
    int status;
    while ((pid = waitpid(-1, &status, 0)) > 0)
    {
        if (WIFEXITED(status)) printf("\nChild process terminated");
    }

    if (pid == -1) printf("\nAll child processes terminated");

    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[])
{
    signal(SIGCHLD, sigchldHandler);
    signal(SIGINT, sigintHandler);

    Aztec aztec;

    aztec.AddString("The first string");
    aztec.AddString("The second string");

    aztec.ShowText();

    // Запуск HTTP-сервера
    CreateHTTPserver();

    return 0;
}
