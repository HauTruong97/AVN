
#ifndef BaseDef_H_
#define BaseDef_H_
// #include <process.h>
#define MQ_MSG_SIZE             1024*4
#define MQ_AVN_APP  "           avnservice"
#define MQ_PROJID               65
#define MQ_TYPE_SERVICE         1
#define MQ_TYPE_VIEWER          2
#define MQ_TYPE_EDITOR          3

#define SHMEM_BUFFER_SIZE       1024*10
#define NUM_OF_ELEMENT          20
#define SHMEM_AVN               "sharemem"
#define SHMEM_PROJID            65

typedef struct
{
    int profile_id;
    char name[50];
    int AsblyLevel;
    int CppLevel;
    int JSLevel;
    int QMLLevel;
    int OpenGLLevel;
    double average;
}PROFILE;
typedef struct
{
    long mesg_type;
    int msgDataId;
    bool status;
    PROFILE profileData;
} MQ_MSG_T;


enum MESSAGE_DATA_ID
{
    MSG_REQUEST_UPDATE_FROM_EDITOR = 0,
    MSG_UPDATE_DATA_TO_VIEWER,
    MSG_NOTIFY_SHAREMEM_AVAILABLE,
    MSG_GET_DATA_ONE_ROW
};
#endif