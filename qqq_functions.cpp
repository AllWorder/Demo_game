#include <SFML/Graphics.hpp>
#include <cmath>
#include "Singleton.h"
#include "GameObject.h"
#include "API.h"
#include <map>


bool checkPointInPolygonCopy( std::vector<float> point , std::vector< std::vector<float> > points_clockwise  )
{
    std::vector<float> vector;
    std::vector<std::vector<float>> T = points_clockwise;

    for(int i = 0 ; i < T.size() ; ++i)
    {
        if( i == T.size() - 1 )
        {
            float a = (T[0][0] - T[i][0])*(point[1] - T[i][1]) - (T[0][1] - T[i][1])*( point[0] - T[i][0] );
            vector.push_back(a);

        }
        else
        {   
            float a = (T[i+1][0] - T[i][0])*(point[1] - T[i][1]) - (T[i+1][1] - T[i][1])*( point[0] - T[i][0] );
            vector.push_back(a);

        }
    }
    
    int iter_plus = 0;
    int iter_minus = 0;
    for ( auto item : vector )
    {   
        if( item > 0 )
        {
            iter_plus ++ ;
            
        }
        else if ( item < 0 )
        {
            iter_minus ++;
            
        }
        
    }
    if(iter_plus == T.size())
    {
        return true;
    }
    else if (iter_minus == T.size() )
    {
        return true;
    }
    
    return false;
}

void moveToOldPosition(qqq::GameObject* object)
{
    qqq::Collider* collider = static_cast<qqq::Collider*>(object->colliders[0]);

    std::vector<float> old_position = object->old_position;
    std::vector<float> new_position = object->position;

    std::vector<float> increment = { new_position[0] - old_position[0] , new_position[1] - old_position[1]  };

    object->position[0] -= increment[0];
    object->position[1] -= increment[1];

    object->old_position[0] -= increment[0];
    object->old_position[1] -= increment[1];
    
}

std::vector<float> getAxisAngleOfCollide(std::vector<std::vector<float>> moving , std::vector<std::vector<float>> other)
{
    int quantity_of_points_moving = moving.size();
    int quantity_of_points_other = other.size(); 

    for(int j = 0 ; j < quantity_of_points_moving ; ++j)
    {
        if( checkPointInPolygonCopy( moving[j], other ) )
        {
            std::map<int,float> distances;

           for ( int i = 0 ; i < quantity_of_points_other ; ++i )
           {
               if( i == quantity_of_points_other - 1 )
               {
                   float 

                    AB = pow((other[i][0] - moving[j][0]),2) + pow((other[i][1] - moving[j][1]),2),
                    AC = pow((other[0][0] - moving[j][0]),2) + pow((other[0][1] - moving[j][1]),2),
                    r = sqrt( pow(other[i][0] - other[0][0],2) + pow(other[i][1] - other[0][1],2) );

                    float y = ( (AB - AC)/r - r )/2;

                    float x = AC - pow(y,2);

                    distances[i] = x;

               }
               else
               {
                    float 

                    AB = pow((other[i][0] - moving[j][0]),2) + pow((other[i][1] - moving[j][1]),2),
                    AC = pow((other[i+1][0] - moving[j][0]),2) + pow((other[i+1][1] - moving[j][1]),2),
                    r = sqrt( pow(other[i][0] - other[i+1][0],2) + pow(other[i][1] - other[i+1][1],2) );

                    float y = ( (AB - AC)/r - r )/2;

                    float x = AC - pow(y,2);

                    distances[i] = x;

               }
           } 



            float min = distances[0];

            for(auto item : distances)
            {
                if(item.second < min)
                {
                    min = item.second;
                }
            }

            int k = 0;

            for( auto item : distances)
            {
                if(item.second == min)
                {
                    k = item.first;
                    break;
                }
            }

            float
            sin = 0,
            cos = 0;
            
            if( k == quantity_of_points_other - 1 )
            {
                if ( other[k][0] == other[0][0])
                {
                    if (other[k][1] < other[0][1])
                    {
                        sin = 1;
                        cos = 0;
                    }
                    else 
                    {
                        sin = -1;
                        cos = 0;
                    }
                }
                else
                {
                    float p = (other[0][1] - other[k][1]) / (other[0][0] - other[k][0]);
                    
                    sin = p / (sqrt(pow(p, 2) + 1));
                    cos = 1 / (sqrt(pow(p, 2) + 1));
                }

            }
            else
            {
                if ( other[k][0] == other[k+1][0])
                {
                    if (other[k][1] < other[k+1][1])
                    {
                        sin = 1;
                        cos = 0;
                    }
                    else 
                    {
                        sin = -1;
                        cos = 0;
                    }
                }
                else
                {
                    float p = (other[k+1][1] - other[k][1]) / (other[k+1][0] - other[k][0]);
                    
                    sin = p / (sqrt(pow(p, 2) + 1));
                    cos = 1 / (sqrt(pow(p, 2) + 1));
                }

            }
            
            return {cos,-sin};

        }

    }

    return {0,0};
}


////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


void qqq::runGame(int window_width, int window_height, std::string window_name)
{
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), window_name);

    qqqP::Singleton* singleton = qqqP::Singleton::getInstance();
    sf::Event event;
    while (window.isOpen())
    {
        singleton->dt = singleton->clock.getElapsedTime().asSeconds();
        singleton->clock.restart();

        singleton->script_manager.updateAll();
        singleton->physics_manager.checkAllCollisions();
        
        
        window.clear(sf::Color(255, 255, 255));
        singleton->graphics_manager.drawAll(window);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    delete singleton;
}

qqq::GameObject* qqq::getObject(std::string name)
{
    qqqP::Singleton* singleton = qqqP::Singleton::getInstance();
    return singleton->data_storage.getObject(name);
}

float qqq::absoluteTime()
{
    qqqP::Singleton* singleton = qqqP::Singleton::getInstance();
    return singleton->clock.getElapsedTime().asSeconds();
}

float qqq::relativeTime()
{
    qqqP::Singleton* singleton = qqqP::Singleton::getInstance();
    return singleton->dt;
}

// void qqq::BallReflection::update()  // move this function to PhysicsManager or somwhere else
// {
//     float dt = qqq::relativeTime();
//     owner -> moveVdt();
// }

// void qqq::BallReflection::ifCollision(qqq::GameObject* another)
// {
//     double sin = -1;
//     double cos = 0;

//     if (this -> owner -> position[0] == another -> position[0])
//     {
//         if (this -> owner -> position[1] < another -> position[1])
//         {
//             sin = 1;
//             cos = 0;
//         }
//         else 
//         {
//             sin = -1;
//             cos = 0;
//         }
//     }
//     else {
//         double k = (another -> position[1] - this -> owner -> position[1]) / (another -> position[0] - this -> owner -> position[0]);
//         sin = k / (sqrt(pow(k, 2) + 1));
//         cos = 1 / (sqrt(pow(k, 2) + 1));
//     }

//     // зададим через матрицу перехода свзять координат в разных СО
//     float V_csi_before_1_obj = cos * this -> owner -> velocity[0] + sin * this -> owner -> velocity[1];
//     float V_eta_before_1_obj = (-1) * sin * this -> owner -> velocity[0] + cos * this -> owner -> velocity[1];

//     float V_csi_before_2_obj = cos * another -> velocity[0] + sin * another -> velocity[1];
//     float V_eta_before_2_obj = (-1) * sin * another -> velocity[0] + cos * another -> velocity[1];

//     float csi_coord_1_obj =  cos * this -> owner -> position[0] + sin * this -> owner -> position[1];
//     float eta_coord_1_obj = (-1) * sin * this -> owner -> position[0] + cos * this -> owner -> position[1];

//     float csi_coord_2_obj =  cos * another -> position[0] + sin * another -> position[1];
//     float eta_coord_2_obj = (-1) * sin * another -> position[0] + cos * another -> position[1];
//     // выразил скорости в новой СК , теперь поменяем нормальные составляющие и проверим, требуется ли в данном 
//     // рассталкивать эти обьекты

//     if (    (csi_coord_2_obj > csi_coord_1_obj and V_csi_before_2_obj <= 0 and V_csi_before_1_obj >= 0) or
//             (csi_coord_2_obj < csi_coord_1_obj and V_csi_before_2_obj >= 0 and V_csi_before_1_obj <= 0) or
//             (csi_coord_2_obj > csi_coord_1_obj and V_csi_before_1_obj - V_csi_before_2_obj > 0)       or
//             (csi_coord_2_obj < csi_coord_1_obj and V_csi_before_1_obj - V_csi_before_2_obj < 0)           )
//     {
//         float tmp = V_csi_before_1_obj;
//         V_csi_before_1_obj = V_csi_before_2_obj;
//         V_csi_before_2_obj = tmp;

//         // теперь переходим к старым координатам

//         double V_x_1_obj_after_hitting = cos * V_csi_before_1_obj - sin * V_eta_before_1_obj;
//         double V_y_1_obj_after_hitting = sin * V_csi_before_1_obj + cos * V_eta_before_1_obj;
//         double V_x_2_obj_after_hitting = cos * V_csi_before_2_obj - sin * V_eta_before_2_obj;
//         double V_y_2_obj_after_hitting = sin * V_csi_before_2_obj + cos * V_eta_before_2_obj;
        
//         this -> owner -> velocity[0] = V_x_1_obj_after_hitting;
//         this -> owner -> velocity[1] = V_y_1_obj_after_hitting;

//         another->velocity[0] = V_x_2_obj_after_hitting;
//         another->velocity[1] = V_y_2_obj_after_hitting;
//     }
// }


//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void qqq::PolygonReflection::update()
{
    float dt = qqq::relativeTime();
    owner -> moveVdt();
}

void qqq::PolygonReflection::ifCollision(qqq::GameObject* another)
{   
    if(this->owner->mass == +INFINITY)
    {
        //moveToOldPosition(owner);
    }
    else
    {
        qqq::Collider* owner_collider = static_cast<qqq::Collider*>(owner->colliders[0]);
        std::vector < std::vector <float> > new_absol_hit_coord_owner = owner_collider->getNewAbsoluteHitboxCoordinates();


        qqq::Collider* another_collider = static_cast<qqq::Collider*>(another->colliders[0]);
        std::vector < std::vector <float> > new_absol_hit_coord_other = another_collider->getNewAbsoluteHitboxCoordinates();

        ////////////////////////////////////////////////////////////////////////////////
        // теперь нужно проверить пересечение всех приращений со сторонами хитбокса для обоих обьектов  ////

        std::vector<float> angle = {0,0};

        float
        sin = 0,
        cos = 0;
        
        angle = getAxisAngleOfCollide(new_absol_hit_coord_owner,new_absol_hit_coord_other);
        if(angle == std::vector<float>{0,0})
            angle = getAxisAngleOfCollide(new_absol_hit_coord_other,new_absol_hit_coord_owner);


        sin = angle[0];
        cos = angle[1];
        ///////////////////////////////////////////////////////////////////////
        ///// сделать проверку на то что полученный вектор синусов и косинусов не равен 0 


        if( cos != 0 or sin != 0 )
        {   
            
            // ////////////////////////////////////////////////////////////////////////////////////
            // //// меняем скорости

            // //////зададим через матрицу перехода свзять координат в разных СО
            float V_csi_before_1_obj = cos * this -> owner -> old_velocity[0] + sin * this -> owner -> old_velocity[1];
            float V_eta_before_1_obj = (-1) * sin * this -> owner -> old_velocity[0] + cos * this -> owner -> old_velocity[1];

            float V_csi_before_2_obj = cos * another -> old_velocity[0] + sin * another -> old_velocity[1];
            float V_eta_before_2_obj = (-1) * sin * another -> old_velocity[0] + cos * another -> old_velocity[1];

            
            // // // выразил скорости в новой СК , теперь поменяем нормальные составляющие и проверим, требуется ли в данном 
            // // // рассталкивать эти обьекты

            
        

            float m2 = another->mass;
                
            
            if(m2 == +INFINITY)
            {
                V_csi_before_1_obj = (-1)*V_csi_before_1_obj + 2*V_csi_before_2_obj;
            }
            else
            {
                V_csi_before_1_obj = V_csi_before_2_obj ;
            }
            
            moveToOldPosition(owner);

            double V_x_1_obj_after_hitting = cos * V_csi_before_1_obj - sin * V_eta_before_1_obj;
            double V_y_1_obj_after_hitting = sin * V_csi_before_1_obj + cos * V_eta_before_1_obj;
            

            owner -> new_velocity[0] = V_x_1_obj_after_hitting;
            owner -> new_velocity[1] = V_y_1_obj_after_hitting;
        }   
    }   
}

