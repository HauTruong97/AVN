#ifndef SharememBase_H_
#define SharememBase_H_
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include "BaseDef.h"
#include <cstring>
#include <mutex>
class SharememBase
{
public:
    SharememBase();
    ~SharememBase();
    bool setSharememData(PROFILE* data);
    bool getSharememData(PROFILE (&data)[NUM_OF_ELEMENT]);
 
private:
    key_t key;
    int shmid;
    void *segment;
    PROFILE shareData[NUM_OF_ELEMENT];
    static std::mutex mutexInstance;
};

#endif