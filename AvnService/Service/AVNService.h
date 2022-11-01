#ifndef AVNService_H_
#define AVNService_H_

#include "../lib/BaseService.h"
#include "../lib/SharememBase.h"
class AVNService : public BaseService, public SharememBase
{
public:
    AVNService();
    ~AVNService();
    void onHandleMessage(const int msgDataId, const bool status, const PROFILE profile);
    void notifySharememAvailable();
    void loadData();
};

#endif
