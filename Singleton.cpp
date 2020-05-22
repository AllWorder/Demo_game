#include "Singleton.h"

qqqP::Singleton* qqqP::Singleton::getInstance()
{
    if (!instance)
        instance = new qqqP::Singleton();
    return instance;
}

qqqP::Singleton* qqqP::Singleton::instance = nullptr;
