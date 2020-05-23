#include <SFML/Graphics.hpp>
#include <random>
#include "GameObject.h"
#include "API.h"
#include "particles.h"


void qqqP::ParticleCircle::draw(sf::RenderWindow& window)
{
    sf::CircleShape circle(r);
    circle.setFillColor(color);
    circle.setPosition(owner->position[0], owner->position[1]);
    window.draw(circle);
}

void qqqP::ParticleSquare::draw(sf::RenderWindow& window)
{
    sf::RectangleShape square(sf::Vector2f(size, size));
    square.setFillColor(color);
    square.setPosition(owner->position[0], owner->position[1]);
    window.draw(square);
}

class qqqP::Telomere: public qqq::Script
{
public:
    float telomere;

    void update()
    {
        telomere -= qqq::relativeTime();
        if (telomere <= 0)
        {
            owner->kostylDestructor();
        }
    }
};

void qqqP::ParticleDirectMotion::setParameters(float vx, float vy, float r)
{
    owner->new_velocity[0] = vx;
    owner->new_velocity[1] = vy;
    resistance = r;
}

void qqqP::ParticleDirectMotion::update()
{
    owner->moveVdt();

    float dt = qqq::relativeTime();
    owner->new_velocity[0] -= resistance * owner->new_velocity[0] * dt;
    owner->new_velocity[1] -= resistance * owner->new_velocity[1] * dt;
}

void qqq::ParticleSource::setParameters(float frequency, float v, float life_time, float direction, float resistsnce, std::vector<int> source_size, float direction_variation)
{
    this->frequency = frequency;
    this->v = v;
    this->life_time = life_time;
    this->direction = (direction == -1 ? -1 : - direction * M_PI / 180);
    this->resistsnce = resistsnce;
    this->source_size = source_size;
    this->direction_variation = direction_variation * M_PI / 180;

    timer = 1/frequency;
}

void qqq::ParticleSource::setCircle(float size, int R, int G, int B)
{
    this->type = "circle";
    this->size = size;
    this->color = sf::Color(R, G, B);
}

void qqq::ParticleSource::setSquare(float size, int R, int G, int B)
{
    this->type = "square";
    this->size = size;
    this->color = sf::Color(R, G, B);
}

void qqq::ParticleSource::setPicture(std::string texture_name)
{
    this->type = "picture";
    this->texture_name = texture_name;
}

void qqq::ParticleSource::update()
{
    timer -= qqq::relativeTime();
    if(timer <= 0)
    {
        timer = 1/frequency;

        qqq::GameObject *particle = new qqq::GameObject;

        particle->addComponent<qqqP::Telomere>();
        particle->getComponent<qqqP::Telomere>()->telomere = life_time;


        particle->addComponent<qqqP::ParticleDirectMotion>();
        float phi = (direction == -1 ? (random()%100)/100.0 * (2*M_PI) :
            direction + ((random()%200)/100.0 - 1) * direction_variation);

        float vx = v*cos(phi);
        float vy = v*sin(phi);
        particle->getComponent<qqqP::ParticleDirectMotion>()->setParameters(vx, vy, resistsnce);
        

        setRenderer(particle);

        particle->position[0] = owner->position[0] + (random()%(2*source_size[0]) - source_size[0]);
        particle->position[1] = owner->position[1] + (random()%(2*source_size[1]) - source_size[1]);

        particle->record("particle_" + std::to_string(quantity_of_particles++));
    }
}

void qqq::ParticleSource::setRenderer(qqq::GameObject *particle)
{
    if (type == "circle")
    {
        particle->addComponent<qqqP::ParticleCircle>();
        particle->getComponent<qqqP::ParticleCircle>()->color = color;
        particle->getComponent<qqqP::ParticleCircle>()->r = size;
    }

    else if (type == "square")
    {
        particle->addComponent<qqqP::ParticleSquare>();
        particle->getComponent<qqqP::ParticleSquare>()->color = color;
        particle->getComponent<qqqP::ParticleSquare>()->size = size;
    }

    else if (type == "picture")
    {
        particle->addComponent<qqq::Renderer>();
        particle->getComponent<qqq::Renderer>()->loadTexture(texture_name);
        particle->getComponent<qqq::Renderer>()->createSprite();
    }
}

int qqq::ParticleSource::quantity_of_particles = 0;