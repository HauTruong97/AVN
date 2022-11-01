#include "AvnService.h"

AvnService::AvnService():BaseService(MQ_AVN_APP, MQ_TYPE_VIEWER)
{
    memset(data,0x00,sizeof(PROFILE)*20);
}

AvnService::~AvnService()
{
    printf("Destroy AvnService");
}

void AvnService::requestUpdateDataToService()
{
    MQ_MSG_T message;

      message.mesg_type = 1;
      message.status = true;
      const char* test = "sommeone";
      strncpy(message.profileData.name, test, sizeof(message.profileData.name));
      for(int i= 1;i<=5;i++)
      {
         message.msgDataId = i;
         message.profileData.profile_id = i;
         message.profileData.AsblyLevel = i;
         message.profileData.CppLevel = i;
         message.profileData.JSLevel = i;
         message.profileData.OpenGLLevel = i;
         message.profileData.QMLLevel = i;
         printf("Write Data : %d %d\n", i, (int)message.mesg_type);
         sender(MQ_TYPE_SERVICE, (MESSAGE_DATA_ID)i, message);
         usleep(2000000);
      }
}

void AvnService::onHandleMessage(const int msgDataId, const bool status, const PROFILE profile)
{
    printf("msgDataId: %d status: %d\n", msgDataId, status);
        switch (msgDataId)
        {
        case MSG_REQUEST_UPDATE_FROM_EDITOR:
        {
            printf("MSG_REQUEST_UPDATE_FROM_EDITOR profileID: %d, name: %s, asm: %d, cpp: %d,Js: %d, QML: %d, OpenGL: %d\n",
            profile.profile_id, profile.name, profile.AsblyLevel, profile.CppLevel, profile.JSLevel, profile.QMLLevel, profile.OpenGLLevel);
            break;
        }
        case MSG_NOTIFY_SHAREMEM_AVAILABLE:
        {
            printf("MSG_NOTIFY_SHAREMEM_AVAILABLE  msgDataId: %d status: %d\n", msgDataId, status);
            getSharememData(data);
            for(int i=0;i<20;i++)
            {
                printf("profileID: %d\n",data[i].profile_id);
            }
        }
        default:
            break;
        }
    }

