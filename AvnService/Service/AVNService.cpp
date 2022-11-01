#include "../lib/BaseService.h"
#include "AVNService.h"
#include <jsoncpp/json/json.h>
#include "json.hpp"
#include <fstream>
#include <iostream>
#include<json/writer.h>
#include "json/json.h"
using namespace std;

AVNService::AVNService()
: BaseService(MQ_AVN_APP, MQ_TYPE_SERVICE)
{
    loadData();
}

AVNService::~AVNService()
{

}

void AVNService::notifySharememAvailable()
{
    printf("notifySharememAvailable\n");
    // sender();
    MQ_MSG_T message;
    memset(&message, 0x00, sizeof(message));
    sender(MQ_TYPE_VIEWER, MSG_NOTIFY_SHAREMEM_AVAILABLE,message);
}

void AVNService::loadData()
{
    ifstream fJson("data.json");
    stringstream buffer;
    buffer << fJson.rdbuf();
    auto json = nlohmann::json::parse(buffer.str());

    cout << "\nNumber of questions: " << json["1"]["profile_id"] << "\n";
    cout << "\nNumber of questions: " << json["2"] << "\n";
    // for (auto employee : json["employees"])
    // {
    //     cout << "Answer: " << employee["name"] << "\n";
    //     cout << "Answer: " << employee["average"] << "\n";
    // }

    // json["1"] = "12";
    // std::fstream file("data.json");
    // file << json;
}

void AVNService::onHandleMessage(const int msgDataId, const bool status, const PROFILE profile)
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
    case MSG_GET_DATA_ONE_ROW:
    {
        printf("MSG_GET_DATA_ONE_ROW msgDataId: %d status: %d\n", msgDataId, status);
        
        PROFILE data[20];
        memset(data, 0x00, sizeof(PROFILE)*20);
        for(int i=0;i<20;i++)
        {
            data[i].profile_id = i;
        }
        setSharememData(data);
        notifySharememAvailable();
    }
    default:
        break;
    }
}