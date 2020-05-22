#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include <string>
#include <vector>
#include <iostream>
#include "Component.h"
#include "default_scripts.h"
#include "Singleton.h"
#include "DataStorage.h"
#include "API.h"

class qqq::GameObject
{
public:
    std::vector <float> position = {0,0};
    std::vector <float> old_position = {0,0};
    std::vector <float> new_velocity = {0,0};
    std::vector <float> old_velocity = {0,0};
    float mass = 1;


    bool dynamic = false;
    std::string id_in_data_storage;
    std::vector <qqq::Component*> scripts;
    std::vector <qqq::Component*> colliders; /////////////////////////

    ~GameObject()
    {
        for (qqq::Component* component : components)
        {
            std::cout << "    " << component->name << std::endl;
            delete component;
            std::cout << "    deleted" << std::endl;
        }
    }

    template <typename T>
    bool addComponent()
    {
        try
        {
            T* new_component = new T;
            new_component->name = typeid(T).name();
            components.push_back(new_component);
            components[components.size() - 1]->owner = this;
            qqqP::Singleton* singleton = qqqP::Singleton::getInstance();
            
            if (std::is_base_of<qqq::RendererBase, T>())
            {
                singleton->graphics_manager.addRenderer(new_component);
            }
            else if (std::is_base_of<qqq::Script, T>())
            {
                singleton->script_manager.addScript(new_component);
                scripts.push_back(new_component);
            }
            else if ( typeid(T).name() == typeid(qqq::Collider).name() )
            {
                singleton->physics_manager.addCollider(new_component);
                colliders.push_back(new_component);
            }

            return true;
        }
        catch(...)
        {
            return false;
        }
    }

    template <typename T>
    T* getComponent()
    {
	    std::string name = typeid(T).name();

        for (qqq::Component* comp: components)
        {
            if (comp->name == name)
                return static_cast<T*>(comp);
        }
        return nullptr;
    }

    template <typename T>
    bool deleteComponent()
    {
        qqqP::Singleton* singleton = qqqP::Singleton::getInstance();

        if (typeid(T).name() == typeid(qqq::Renderer).name())  
        {
            singleton->graphics_manager.removeRenderer(getComponent<T>());
        }
        else if ( typeid(T).name() == typeid(qqq::Collider).name() )
        {
            singleton->physics_manager.removeCollider(getComponent<T>());
        }
        else if (std::is_base_of<qqq::Script, T>())
        {
            singleton->script_manager.removeScript(getComponent<T>());
        }

        std::string name = typeid(T).name();

        for (int i = 0; i < components.size(); i++)
        {
            if (components[i]->name == name)
            {
                std::cout << "deleteComponent: " << components.size() << std::endl;
                delete components[i];
                components.erase(components.begin() + i);
                std::cout << "deleteComponent: " << components.size() << ")" << std::endl;
                return true;
            }
        }
        return false;
    }

    void record(std::string id)
    {
        qqqP::Singleton* singleton = qqqP::Singleton::getInstance();
        singleton->data_storage.addObject(id, this );
    }

    void moveVdt()
    {
        float dt = qqq::relativeTime();
        old_position = position;
        position[0] += new_velocity[0] * dt;
        position[1] += new_velocity[1] * dt;
    }

private:
    
    std::vector<qqq::Component*> components;   
    
};

#endif