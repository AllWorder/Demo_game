#include <SFML/Graphics.hpp>
#include <string>
#include "GameObject.h"
#include "Component.h"

////////////////////////////////////

void qqq::Renderer::draw(sf::RenderWindow& window)
{
    sprite.setPosition( owner->position[0], owner->position[1] );
    window.draw(sprite);
}

void qqq::Renderer::loadTexture(std::string texturename) 
{
    texture.loadFromFile(texturename);
}

std::string qqq::Renderer::getNameOfTexture()
{
    return name_of_texture;
}

void qqq::Renderer::createSprite()
{
    sprite.setTexture(texture);
}

sf::Sprite* qqq::Renderer::getSprite()
{
    return &sprite;
}

////////////////////////////////////

void qqq::Collider::setBodyPointClockwise( std::vector < float > point )
{
    relative_hitbox_coordinates.push_back( point );
}

int qqq::Collider::getQuantityOfBodyPoints()
{
    return relative_hitbox_coordinates.size();
}

std::vector<float> qqq::Collider::getPointByIndex(int index)
{
    return relative_hitbox_coordinates[index];
}

bool qqq::Collider::setHitboxRectangle(float height, float width)
{
    setBodyPointClockwise( { width*0 , height*0 } );
    setBodyPointClockwise( { width*1 , height*0 } );
    setBodyPointClockwise( { width*1 , height*1 } );
    setBodyPointClockwise( { width*0 , height*1 } );

    int quantity_of_points = getQuantityOfBodyPoints();

    std::vector <std::vector<float>> new_absolute_hitbox_coordinates;
    std::vector <std::vector<float>> relative_hitbox_coordinates = getRelativeHitboxCoordinates();

    float 
    x = owner->position[0],
    y = owner->position[1];

    for(int i = 0 ; i < quantity_of_points ; ++i)
    {
        new_absolute_hitbox_coordinates.push_back({ relative_hitbox_coordinates[i][0] + x , relative_hitbox_coordinates[i][1] + y });
    }

    setNewAbsoluteHitboxCoordinates(new_absolute_hitbox_coordinates);

    return true;
}

std::vector< std::vector<float> > qqq::Collider::getNewAbsoluteHitboxCoordinates()
{
    return new_absolute_hitbox_coordinates;
}

std::vector< std::vector<float> > qqq::Collider::getOldAbsoluteHitboxCoordinates()
{
    return old_absolute_hitbox_coordinates;
}

std::vector< std::vector<float> > qqq::Collider::getRelativeHitboxCoordinates()
{
    return relative_hitbox_coordinates;
}

void qqq::Collider::setNewAbsoluteHitboxCoordinates(std::vector< std::vector<float> > new_absolute_hitbox_coordinates)
{
    this->new_absolute_hitbox_coordinates = new_absolute_hitbox_coordinates;
}

void qqq::Collider::setOldAbsoluteHitboxCoordinates(std::vector< std::vector<float> > old_absolute_hitbox_coordinates)
{
    this->old_absolute_hitbox_coordinates = old_absolute_hitbox_coordinates;
}