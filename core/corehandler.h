#ifndef COREHANDLER_H
#define COREHANDLER_H
#include "../request/request.h"

class coreHandler
{
public:
    coreHandler();

    void processRequest(sRequest r);
};

#endif // COREHANDLER_H
