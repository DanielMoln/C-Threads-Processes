#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

extern void processes();
extern void threads();
extern void getValueFromThread();
extern void passUniqueValueToThread();
extern void forkExample();

int main()
{
    // processes();
    // passUniqueValueToThread();
    forkExample();
    return 0;
}