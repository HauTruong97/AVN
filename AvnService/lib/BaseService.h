#ifndef BaseService_H_
#define BaseService_H_

#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "BaseDef.h"
class BaseService
{
public:
    BaseService(const char* mqKey, int mqtype);
    ~BaseService();

    char*   m_buff;
    int     m_buffSize;
    pthread_t    m_thread;

    void start(bool bCreateThread);
    
    virtual void onHandleMessage(const int msgDataId, const bool status, const PROFILE profile);
    bool sender(const int target, const MESSAGE_DATA_ID id, MQ_MSG_T message);
private:
    void runMessageLooper(void *pThis);
    static void* onFncThread(void *pThis);
    MQ_MSG_T message;
    key_t key;
    long mqType;
    static int msgID;
    static int msgSize;
};

#endif