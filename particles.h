#ifndef __PATICLES__
#define __PATICLES__

#include <SFML/Graphics.hpp>
#include <random>
#include "GameObject.h"
#include "API.h"

class qqqP::ParticleCircle: public qqq::RendererBase
{
public:
    float r;
    sf::Color color;

    void draw(sf::RenderWindow& window);
};

class qqqP::ParticleSquare: public qqq::RendererBase
{
public:
    float size;
    sf::Color color;

    void draw(sf::RenderWindow& window);
};

class qqqP::ParticleDirectMotion: public qqq::Script
{
public:
    float resistance=0;

    void setParameters(float vx, float vy, float r);

    void update();
};

class qqq::ParticleSource: public qqq::Script
{
public:
    std::string type;
    float frequency;
    float v;
    float life_time;
    float resistsnce;
    std::vector<int> source_size;
    float direction;
    float direction_variation;

    sf::Color color;
    float size;
    std::string texture_name; // bydlocode

    static int quantity_of_particles;

    void setParameters(float frequency, float v, float life_time, float direction = -1, float resistsnce = 0, std::vector<int> source_size = {5,5}, float direction_variation = 10);
    void setCircle(float size, int R, int G, int B);
    void setSquare(float size, int R, int G, int B);
    void setPicture(std::string texture_name);
    void update();

private:
    float timer;
    void setRenderer(qqq::GameObject *particle);
};

#endif