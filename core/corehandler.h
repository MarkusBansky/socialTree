#ifndef COREHANDLER_H
#define COREHANDLER_H
#include "../request/request.h"

class coreHandler
{
public:
    void processRequest(sRequest r);
private:
    void addCase();
    void deleteCase();
};

#endif // COREHANDLER_H
