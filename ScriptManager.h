#ifndef __SCRIPT_MANAGER__
#define __SCRIPT_MANAGER__

#include "API.h"

class qqqP::ScriptManager
{
public:
    void updateAll();
    bool addScript(qqq::Component* new_script);
    bool removeScript(qqq::Component* removing_script);

private:
    std::vector<qqq::Script*> scripts;
};

#endif