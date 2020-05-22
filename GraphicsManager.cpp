#include <SFML/Graphics.hpp>
#include <iostream>
#include "GraphicsManager.h"
#include "GameObject.h"


void qqqP::GraphicsManager::drawAll(sf::RenderWindow& window){

    for (qqq::RendererBase* renderer: renderers){
        renderer->draw(window);

        ////////////////////////////////////////////
        //////////FOR COLLIION DEVELOP//////////////
        /////////DRAWING HITBOX ANIMATION///////////
        ////////////////////////////////////////////
        if(renderer -> owner -> getComponent<qqq::Collider>())
        {      
            qqq::Collider* collider = renderer -> owner -> getComponent<qqq::Collider>();
            sf::VertexArray lines;
            float x = 0.0f, y = 0.0f;
            for( int i = 0 ; i < collider -> getQuantityOfBodyPoints() ; ++i)
            {   
                x = collider -> getPointByIndex(i)[0] + renderer ->owner -> position[0];
                y =  collider -> getPointByIndex(i)[1] + renderer ->owner -> position[1];
                lines.append( sf::Vertex( sf::Vector2f (x,y) , sf::Color::Black , sf::Vector2f (0.0f,0.0f) ) ) ;   
            }

            lines.setPrimitiveType ( sf::LinesStrip );
            lines.append( lines[0] ) ;
            window.draw(lines);
        }
        ////////////////////////////////////////////
        ////////////////////////////////////////////
        ////////////////////////////////////////////
    }

    window.display();
}

bool qqqP::GraphicsManager::addRenderer(qqq::Component* new_renderer)
{
    try
    {
        renderers.push_back(static_cast<qqq::RendererBase*>(new_renderer));
        return true;
    }
    catch(...)
    {
        return false;
    }
}

bool qqqP::GraphicsManager::removeRenderer(qqq::Component* removing_renderer)
{
    for (int i = 0; i < renderers.size(); i++)
    {
        if (renderers[i] == removing_renderer)
        {
            renderers.erase(renderers.begin() + i);
            return true;
        }
    }
    return false;
}