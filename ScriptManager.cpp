#include "GameObject.h"
#include "ScriptManager.h"

void qqqP::ScriptManager::updateAll()
{
    for (int i = 0; i < scripts.size(); i++)
    {
        qqq::Script* script = scripts[i];
        script->update();
    }
}

bool qqqP::ScriptManager::addScript(qqq::Component* new_script)
{
    try
    {
        scripts.push_back(static_cast<qqq::Script*>(new_script));
        new_script->manager = 's';
        return true;
    }
    catch(...)
    {
        return false;
    }
}

bool qqqP::ScriptManager::removeScript(qqq::Component* removing_script)
{
    for (int i = 0; i < scripts.size(); i++)
    {
        if (scripts[i] == removing_script)
        {
            scripts.erase(scripts.begin() + i);
            return true;
        }
    }
    return false;
}