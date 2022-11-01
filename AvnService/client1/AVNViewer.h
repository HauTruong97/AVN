#ifndef AVNViewer_H_
#define AVNViewer_H_
#include "../lib/BaseService.h"
#include "../lib/SharememBase.h"
class AVNViewer : public BaseService, public SharememBase
{
private:
    /* data */
public:
    AVNViewer();
    ~AVNViewer();
    PROFILE data[20];
    void viewerRequest();
    void onHandleMessage(const int msgDataId, const bool status, const PROFILE profile);
};

#endif
