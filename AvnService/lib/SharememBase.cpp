#include "SharememBase.h"
std::mutex SharememBase::mutexInstance;
SharememBase::SharememBase(/* args */)
{
    key = ftok(SHMEM_AVN,SHMEM_PROJID);
    shmid = shmget(key,NUM_OF_ELEMENT*sizeof(PROFILE),0666|IPC_CREAT);
    if (shmid < 0) printf("error allocation segment\n");
    segment = shmat(shmid, NULL, 0);
    if (segment == (void*)-1)
    {
        printf("share memory attach error!\n");
    }
    memset(shareData, 0x00, NUM_OF_ELEMENT*sizeof(PROFILE));
}
SharememBase::~SharememBase()
{
    // clean sharemem
    printf("SharememBase destroyed!");
    shmdt(shareData);
    shmctl(shmid,IPC_RMID,NULL);
}

bool SharememBase::setSharememData(PROFILE* data)
{
    std::lock_guard<std::mutex> lock(mutexInstance);
    memcpy(segment, data, NUM_OF_ELEMENT*sizeof(PROFILE));
    return true;
}

bool SharememBase::getSharememData(PROFILE (&data)[NUM_OF_ELEMENT])
{
    std::lock_guard<std::mutex> lock(mutexInstance);
    memcpy(data, segment, NUM_OF_ELEMENT*sizeof(PROFILE));
    return true;
}