#include <SFML/Graphics.hpp>
#include <random>
#include "GameObject.h"




class UpdateColliderObject: public qqq::Script
{   
    public:

        void update()
        {   ////////////////////////////////////////
            qqq::Collider* collider = static_cast<qqq::Collider*>(owner->colliders[0]);
            int quantity_of_points = collider->getQuantityOfBodyPoints();

            std::vector <std::vector<float>> new_absolute_hitbox_coordinates;
            std::vector <std::vector<float>> relative_hitbox_coordinates = collider->getRelativeHitboxCoordinates();

            float 
            x = owner->position[0],
            y = owner->position[1];

            for(int i = 0 ; i < quantity_of_points ; ++i)
            {
                new_absolute_hitbox_coordinates.push_back({ relative_hitbox_coordinates[i][0] + x , relative_hitbox_coordinates[i][1] + y });
            }

            collider->setNewAbsoluteHitboxCoordinates(new_absolute_hitbox_coordinates);
            /////////////////////////////////////////
            std::vector <std::vector<float>> old_absolute_hitbox_coordinates;

            
            x = owner->old_position[0],
            y = owner->old_position[1];

            for(int i = 0 ; i < quantity_of_points ; ++i)
            {
                old_absolute_hitbox_coordinates.push_back({ relative_hitbox_coordinates[i][0] + x , relative_hitbox_coordinates[i][1] + y });
            }

            collider->setOldAbsoluteHitboxCoordinates(old_absolute_hitbox_coordinates);
        }


};

class Resistance: public qqq::Script
{
public:
    void update()
    {   
        
        float dt = sqrt(2);//qqq::relativeTime();

        float resistance_of_field = 0.2;

        for ( int i = 0 ; i < 2 ; ++i)
        {
            if( owner->new_velocity[i] > 0 and owner->new_velocity[i] - resistance_of_field > 0  )
            {
                owner->new_velocity[i] -= resistance_of_field;
            }
            else if( owner->new_velocity[i] < 0 and owner->new_velocity[i] + resistance_of_field < 0 )
            {
                owner->new_velocity[i] += resistance_of_field;
            }
            else
            {
                owner->new_velocity[i] = 0;
            }
        }
    }
};

class Controller: public qqq::Script
{
public:
    float a = 500;

    void update()
    {
        float dt = qqq::relativeTime();
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            owner -> new_velocity[0] += a*dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            owner -> new_velocity[0] -= a*dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            owner -> new_velocity[1] += a*dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            owner -> new_velocity[1] -= a*dt;
        }

        // у игровых обьектов менять можно только скорость!!!!!!!!!!!!!!!!!!!!!!!!!!1
        // не менять координаты самому это делается специальная функция
    }
};

class Health: public qqq::Script
{
public:
    int health = 3;
    int BRS = 0;
    int tick = 0;

    void update()
    {
        tick += 1;

        if(tick % 500 == 0)
        {
            printf("BRS: %d\n", BRS);
            printf("Lives: %d\n", health);
        }

        if (health <= 0)
        {
            printf("YOU LOSE\n\n\n");
        }

        if (BRS >= 30)
        {
            printf("YOU WIN\n\n\n");
        }
    }
};

class GoodPlateBehavior: public qqq::Script
{
    void ifCollision(qqq::GameObject* another)
    {   
        if ((another->id_in_data_storage == "player"))
        {
            another->getComponent<Health>()->BRS += 1;
            this->owner->position[0] = 5000;
            this->owner->getComponent<qqq::PolygonReflection>()->update();
        }

        if ((another->id_in_data_storage == "wall1"))
        {
            this->owner->position[0] = 5000;
            this->owner->getComponent<qqq::PolygonReflection>()->update();
        }
    }
};

class BadPlateBehavior: public qqq::Script
{
    void ifCollision(qqq::GameObject* another)
    {   
        if ((another->id_in_data_storage == "player"))
        {
            another->getComponent<Health>()->health -= 1;
            
            this->owner->position[0] = 5000;
            this->owner->getComponent<qqq::PolygonReflection>()->update();
        }

        if ((another->id_in_data_storage == "wall1"))
        {
            this->owner->position[0] = 5000;
            this->owner->getComponent<qqq::PolygonReflection>()->update();
        }

    }
};

class PlateSpawner: public qqq::Script
{
    int enemy_number = 0;
    int tick = 0;

    void update()
    {
        tick += 1;

        if( tick % 250 == 0)
        {
            int role_number = rand() % 2;
            
            qqq::GameObject* Enemy = new qqq::GameObject;
            Enemy->dynamic = true;

            Enemy->addComponent<qqq::Renderer>();
            if(role_number == 0)
            {
                Enemy->getComponent<qqq::Renderer>()->loadTexture("BRS.png");
                Enemy->addComponent<GoodPlateBehavior>();
            }
            else
            {
                Enemy->getComponent<qqq::Renderer>()->loadTexture("Ivanova.png");
                Enemy->addComponent<BadPlateBehavior>();
            }
            
            
            Enemy->getComponent<qqq::Renderer>()->createSprite();

            Enemy->addComponent<qqq::Collider>();
            Enemy->getComponent<qqq::Collider>()->setHitboxRectangle(80,200);
            Enemy->addComponent<qqq::PolygonReflection>();

            Enemy->position[0] = 1300;
            Enemy->position[1] = 1 + rand() % 720 - 90;
            Enemy->new_velocity[0] = -150;



            Enemy->addComponent<UpdateColliderObject>();
            Enemy->record("enemy_" + std::to_string(enemy_number++));




        }
    }
};

int main()
{
    //BACKGROUND:

    qqq::GameObject backGround;
    backGround.addComponent<qqq::Renderer>();
    backGround.getComponent<qqq::Renderer>()->loadTexture("background.jpg");
    backGround.getComponent<qqq::Renderer>()->createSprite();
    backGround.position[0] = 0;
    backGround.position[1] = 0;

    //PLAYER:
    qqq::GameObject player;
    player.addComponent<qqq::Renderer>();
    player.getComponent<qqq::Renderer>()->loadTexture("player.png");
    player.getComponent<qqq::Renderer>()->createSprite();
    player.addComponent<qqq::Collider>();
    player.getComponent<qqq::Collider>()->setHitboxRectangle(50,50);
    player.addComponent<qqq::PolygonReflection>();
    player.addComponent<Resistance>();
    player.addComponent<Health>();

    player.position[0] = 50;
    player.position[1] = 50;

    player.addComponent<Controller>();
    player.addComponent<UpdateColliderObject>();

    player.record("player");
    
    //SPAWNER
    qqq::GameObject plate_spawner;
    plate_spawner.addComponent<PlateSpawner>();
    plate_spawner.record("plate_spawner");

    //WALLS:
   
    qqq::GameObject Wall1;
    Wall1.addComponent<qqq::Collider>();
    Wall1.addComponent<qqq::Renderer>();
    Wall1.getComponent<qqq::Collider>()->setHitboxRectangle(720, 10);
    Wall1.addComponent<qqq::PolygonReflection>();
    Wall1.position[0] = -10;
    Wall1.position[1] = 0;
    Wall1.mass = +INFINITY;
    Wall1.addComponent<UpdateColliderObject>();
    Wall1.record("wall1");

    qqq::GameObject Wall2;
    Wall2.addComponent<qqq::Collider>();
    Wall2.addComponent<qqq::Renderer>();
    Wall2.getComponent<qqq::Collider>()->setHitboxRectangle(10, 1200);
    Wall2.addComponent<qqq::PolygonReflection>();
    Wall2.position[0] = 0;
    Wall2.position[1] = -10;
    Wall2.mass = +INFINITY;
    Wall2.addComponent<UpdateColliderObject>();
    Wall2.record("wall2");

    qqq::GameObject Wall3;
    Wall3.addComponent<qqq::Collider>();
    Wall3.addComponent<qqq::Renderer>();
    Wall3.getComponent<qqq::Collider>()->setHitboxRectangle(10, 1200);
    Wall3.addComponent<qqq::PolygonReflection>();
    Wall3.position[0] = 0;
    Wall3.position[1] = 720;
    Wall3.mass = +INFINITY;
    Wall3.addComponent<UpdateColliderObject>();
    Wall3.record("wall3");


    //GAME:
    qqq::runGame(1200, 720, "30 BRS");

    return 0;
}

// g++ demo_game.cpp Component.cpp DataStorage.cpp PhysicsManager.cpp GraphicsManager.cpp ScriptManager.cpp Singleton.cpp qqq_functions.cpp particles.cpp -o demo_game -lsfml-graphics -lsfml-window -lsfml-system
// ./demo_game