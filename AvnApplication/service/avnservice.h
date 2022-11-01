#ifndef AVNSERVICE_H
#define AVNSERVICE_H
#include "../AvnService/lib/BaseService.h"
#include "../AvnService/lib/SharememBase.h"

class AvnService: public BaseService, public SharememBase
{
public:
    AvnService();
    ~AvnService();
    PROFILE data[20];
    void requestUpdateDataToService();
    void onHandleMessage(const int msgDataId, const bool status, const PROFILE profile);
};

#endif // AVNSERVICE_H
