#ifndef __COMPONENT__
#define __COMPONENT__

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "API.h"

class qqq::Component
{
public:
    std::string name;
    qqq::GameObject* owner;
};

/////////////////////////////////////////////////

class qqq::RendererBase: public qqq::Component
{
public:
    virtual void draw(sf::RenderWindow& window) {}
};

class qqq::Renderer: public qqq::RendererBase
{
public:
    void draw(sf::RenderWindow& window);
    void loadTexture(std::string texturename);
    std::string getNameOfTexture();
    void createSprite();
    sf::Sprite* getSprite();

private:
    std::string name_of_texture;
    sf::Texture texture;
    sf::Sprite sprite;
};

/////////////////////////////////////////////////

class qqq::Script: public qqq::Component
{
public:
    virtual void update() {}
    virtual void ifCollision(qqq::GameObject* another) {}
};

/////////////////////////////////////////////////

class qqq::Collider: public qqq::Component
{   
    public:
        
        void setBodyPointClockwise( std::vector < float > point );
        int getQuantityOfBodyPoints();
        std::vector < float > getPointByIndex(int index);
        bool setHitboxRectangle(float height , float width);
        std::vector< std::vector<float> > getNewAbsoluteHitboxCoordinates();
        std::vector< std::vector<float> > getOldAbsoluteHitboxCoordinates();
        std::vector< std::vector<float> > getRelativeHitboxCoordinates();
        void setOldAbsoluteHitboxCoordinates(std::vector< std::vector<float> > old_absolute_hitbox_coordinates);
        void setNewAbsoluteHitboxCoordinates(std::vector< std::vector<float> > new_absolute_hitbox_coordinates);
        

    private:
        std::vector< std::vector<float> > relative_hitbox_coordinates;
        std::vector< std::vector<float> > old_absolute_hitbox_coordinates;
        std::vector< std::vector<float> > new_absolute_hitbox_coordinates;
};

#endif