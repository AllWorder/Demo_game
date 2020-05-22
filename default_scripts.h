#include "Component.h"
#include "API.h"

class qqq::BallReflection: public qqq::Script
{
public:
    void update();  // move this function to PhysicsManager or somewhere else
    void ifCollision(qqq::GameObject* another);
};



/////////////////////////////////////////////
class qqq::PolygonReflection: public qqq::Script
{
public:
    void update();  // move this function to PhysicsManager or somewhere else
    void ifCollision(qqq::GameObject* another);
};

///////////////////////////////////////////////