#ifndef __GRAPHICS_MANAGER__
#define __GRAPHICS_MANAGER__

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Component.h"
#include "API.h"

class qqqP::GraphicsManager {
    public:
        void drawAll(sf::RenderWindow& window);
        bool addRenderer(qqq::Component* new_renderer);
        bool removeRenderer(qqq::Component* removing_renderer);
    private:
        std::vector<qqq::RendererBase*> renderers;
};

#endif