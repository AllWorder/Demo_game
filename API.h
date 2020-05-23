#ifndef __QQQ_API__
#define __QQQ_API__

namespace qqq
{
    class GameObject;
    
    class Component;
        // components
        class RendererBase;
            class Renderer;
        class Collider;
        class Script;
            // scripts
            class BallReflection;
            class PolygonReflection;
            class ParticleSource;


    void runGame(int window_width, int window_height, std::string window_name);
    qqq::GameObject* getObject(std::string name);
    float absoluteTime();
    float relativeTime();
}


//  PRIVATE FUNCTIONS

namespace qqqP
{
    class DataStorage;
    class Singleton;
    class GraphicsManager;
    class ScriptManager;
    class PhysicsManager;

    class ParticleCircle;
    class ParticleSquare;
    class ParticleDirectMotion;
    class Telomere;
}

#endif