#include "BaseService.h"

int BaseService::msgID = 0;
int BaseService::msgSize = 0;

BaseService::BaseService(const char* mqKey, int mqtype)
{
    m_buff = nullptr;
    m_buffSize = 0;
    m_thread = 0;
    memset(&message, 0x00, sizeof(message));
    key = ftok(mqKey, MQ_PROJID);
    msgID = msgget(key, 0666 | IPC_CREAT);
    printf("msgID is %d\n", msgID);
    mqType = mqtype;
}

BaseService::~BaseService()
{
    printf("BaseService destroyed!\n");
    msgctl(msgID, IPC_RMID, NULL);
}

void BaseService::start(bool bCreateThread)
{
    if (bCreateThread == true)
    {
        int err = -1;
        err = pthread_create(&m_thread, nullptr, onFncThread, (void*)this);
        if (err != 0)
        {
            printf("\ncan't create thread :[%s]", strerror(err));
        }
        else
        {
            printf("\n Thread created successfully\n");
        }
        pthread_detach(m_thread);
    }
    else
    {
        runMessageLooper((void*)this);
    }
}

void BaseService::runMessageLooper(void *pThis)
{
    printf("\n Start message queue tid:%d \n", gettid());
    while (true)
    {
        printf("waiting message queue %d\n", (int)mqType);
        msgSize = msgrcv(msgID, &message, sizeof(message)-(int)sizeof(long), mqType, 0);
        if(msgSize >= 0)
        {
            printf("data received: %d sizeof data %d\n", message.msgDataId, msgSize);
            ((BaseService*)pThis)->onHandleMessage(message.msgDataId, message.status, message.profileData);
        }
        else
        {
            printf("Receive mq no message\n");
            usleep(500);
        }
    }
}
void* BaseService::onFncThread(void *pThis)
{
    if (pThis)
    {
        printf("\n onFncThread tid:%d \n", gettid());
        ((BaseService*)pThis)->runMessageLooper(pThis);
    }
    else
    {
        printf("\n onFncThread pThis null");
    }
    return 0;
}


bool BaseService::sender(const int target, const MESSAGE_DATA_ID id, MQ_MSG_T data)
{
    data.mesg_type = target;
    data.msgDataId = id;
    printf("sending mq msgID: %d\n",msgID);
    if(msgsnd(msgID, &data, sizeof(data)-sizeof(long), 0) >= 0)
    {
        printf("sending successed!\n");
        return true;
    }
    else
    {
        printf("sending failed!\n");
        return false;
    }
}

void BaseService::onHandleMessage(const int msgDataId, const bool status, const PROFILE profile)
{
    printf("msgDataId: %d \n", msgDataId);
}
