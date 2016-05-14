#include "main.h"
#include <stdio.h>

int inspection(queue_osnova * q){
    int i;
    for(i = 0; i < 3; i++){
        if(0 != queue_value(q, MAX_SIZE - i))
            break;
    }
    if(i != 3)
        return 0;
    return 1;
}
void reaction(){
    printf("\n---\nStill sunny\n---\n");
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
