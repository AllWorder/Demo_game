#include "PhysicsManager.h"
#include "GameObject.h"
#include <cmath>

bool checkPointInPolygon( std::vector<float> point , std::vector< std::vector<float> > points_clockwise  )
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

float getMaxElement(const std::vector < float > vector)
{
    float max = vector[0];

    for(auto element : vector){

        if( element >= max )
        {
            max = element;
        }

    }
    return max;
}

float getMinElement(const std::vector < float > vector)
{
    float min = vector[0];

    for(auto element : vector){

        if( element <= min )
        {
            min = element;
        }

    }
    return min;
}

bool checkOneObject( std::vector < std::vector < float > > absolute_points_coordinates_of_first_obj_clockwise , int quantity_of_points_first , std::vector < std::vector < float > > absolute_points_coordinates_of_second_obj_clockwise , int quantity_of_points_second )
{
    for ( int i = 0 ; i < quantity_of_points_first ; ++i ){

        bool tg_inf = false;
        float cos = 0;
        float sin = 1;

        if( i == quantity_of_points_first - 1 )
        {   
            float x1 = absolute_points_coordinates_of_first_obj_clockwise[i][0];
            float y1 = absolute_points_coordinates_of_first_obj_clockwise[i][1];

            float x2 = absolute_points_coordinates_of_first_obj_clockwise[0][0];
            float y2 = absolute_points_coordinates_of_first_obj_clockwise[0][1];

            if ( x1 == x2 )
            {
                tg_inf = true;
            }
            else
            {
                float tg = ( y1 - y2 ) / (x1 - x2);

                cos = sqrt( 1/( 1 + tg*tg ) );
                sin = tg*cos;
            }
        }   
        else
        {
            float x1 = absolute_points_coordinates_of_first_obj_clockwise[i][0];
            float y1 = absolute_points_coordinates_of_first_obj_clockwise[i][1];

            float x2 = absolute_points_coordinates_of_first_obj_clockwise[i+1][0];
            float y2 = absolute_points_coordinates_of_first_obj_clockwise[i+1][1];

            if ( x1 == x2 )
            {
                tg_inf = true;
            }
            else
            {
                float tg = ( y1 - y2 ) / (x1 - x2);

                cos = sqrt( 1/( 1 + tg*tg ) );
                sin = tg*cos;
            }
        }


        std::vector < float > points_proection_on_new_axis_for_first_obj;
        std::vector < float > points_proection_on_new_axis_for_second_obj;

        for ( int i = 0 ; i < quantity_of_points_first ; ++i){
            points_proection_on_new_axis_for_first_obj.push_back( -absolute_points_coordinates_of_first_obj_clockwise[i][0]*sin + absolute_points_coordinates_of_first_obj_clockwise[i][1]*cos );
        }

        for ( int i = 0 ; i < quantity_of_points_second ; ++i){
            points_proection_on_new_axis_for_second_obj.push_back( -absolute_points_coordinates_of_second_obj_clockwise[i][0]*sin + absolute_points_coordinates_of_second_obj_clockwise[i][1]*cos );
        }

        float max1 = getMaxElement(points_proection_on_new_axis_for_first_obj);
        float min1 = getMinElement(points_proection_on_new_axis_for_first_obj);

        float max2 = getMaxElement(points_proection_on_new_axis_for_second_obj);
        float min2 = getMinElement(points_proection_on_new_axis_for_second_obj);

        if ( max1 < min2 or max2 < min1)
        {
            return false;
        }
    }

    return true;
}
////////////////////////////////////////////////////////////
//////////////// ADDING AND DELETING OBJECTS ///////////////
////////////////////////////////////////////////////////////

bool qqqP::PhysicsManager::addCollider(qqq::Component* new_collider){

    try
    {
        collider_objects.push_back(static_cast<qqq::Collider*>(new_collider));
        return true;
    }
    catch(...)
    { 
        return false;
    }
}

bool qqqP::PhysicsManager::removeCollider(qqq::Component* removing_collider){

    for(int i = 0 ; i < collider_objects.size() ; i++){

        if(collider_objects[i] == removing_collider)
        {
            collider_objects.erase(collider_objects.begin() + i );
            return true;
        }

        return false;
    }
}
////////////////////////////////////////////////////////////
///////////////// GETTING OBJECTS //////////////////////////
////////////////////////////////////////////////////////////

std::vector < qqq::Collider* > qqqP::PhysicsManager::getAll()
{
    std::vector < qqq::Collider* > output_colliders;

    for( auto obj : collider_objects)
    {
        output_colliders.push_back(obj);
    }

    return output_colliders;
}
////////////////////////////////////////////////////////////
////////////////// COLLISION OF OBJECTS ////////////////////
////////////////////////////////////////////////////////////

bool qqqP::PhysicsManager::checkForCollide( qqq::Collider* first , qqq::Collider* second )
{   
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////

    int quantity_points_firts = first->getQuantityOfBodyPoints();
    int quantity_points_second = second->getQuantityOfBodyPoints();

    std::vector<std::vector<float>> first_hitbox = first->getNewAbsoluteHitboxCoordinates();
    std::vector<std::vector<float>> second_hitbox = second->getNewAbsoluteHitboxCoordinates();

    for( int i = 0 ; i < quantity_points_firts ; ++i)
    {
        if( checkPointInPolygon(first_hitbox[i], second_hitbox) )
        {
            return true;
        }
    }

    for( int i = 0 ; i < quantity_points_second ; ++i)
    {
        if( checkPointInPolygon(second_hitbox[i], first_hitbox) )
        {
            return true;
        }
    }

    return false;


    // std::vector < std::vector < float > > absolute_points_coordinates_of_first_obj_clockwise;
    // std::vector < std::vector < float > > absolute_points_coordinates_of_second_obj_clockwise;

    // int quantity_of_points_first = first ->  getQuantityOfBodyPoints();
    // int quantity_of_points_second = second -> getQuantityOfBodyPoints();

    // float x_coordinate_of_first = first -> owner -> position[0];
    // float y_coordinate_of_first = first -> owner -> position[1];

    // float x_coordinate_of_second = second -> owner -> position[0];
    // float y_coordinate_of_second = second -> owner -> position[1];

    // for ( int i = 0 ; i < quantity_of_points_first ; ++i)
    // {
    //     float x_coordinate_of_point = first -> getPointByIndex(i)[0];
    //     float y_coordinate_of_point = first -> getPointByIndex(i)[1];

    //     absolute_points_coordinates_of_first_obj_clockwise.push_back( { x_coordinate_of_first + x_coordinate_of_point , y_coordinate_of_first + y_coordinate_of_point } );
    // }

    // for ( int i = 0 ; i < quantity_of_points_second ; ++i)
    // {
    //     float x_coordinate_of_point = second -> getPointByIndex(i)[0];
    //     float y_coordinate_of_point = second -> getPointByIndex(i)[1];

    //     absolute_points_coordinates_of_second_obj_clockwise.push_back( { x_coordinate_of_second + x_coordinate_of_point , y_coordinate_of_second + y_coordinate_of_point } );
    // }

    // //////////////////////////////////////////////////////////////////////////////////////////////////
    // //////////////////////////////////////////////////////////////////////////////////////////////////
    // //////////////////////////////////////////////////////////////////////////////////////////////////

    // bool this_objects_collided = true;

    // this_objects_collided = checkOneObject( absolute_points_coordinates_of_first_obj_clockwise,quantity_of_points_first , absolute_points_coordinates_of_second_obj_clockwise,quantity_of_points_second);

    // this_objects_collided = checkOneObject( absolute_points_coordinates_of_second_obj_clockwise,quantity_of_points_second , absolute_points_coordinates_of_first_obj_clockwise,quantity_of_points_first);

    // return this_objects_collided;
}

void qqqP::PhysicsManager::checkAllCollisions()
{   
    for (int i = 0; i < collider_objects.size(); i++)
    {
        for (int j = 0; j < collider_objects.size(); j++)
        {
            if (i > j)
            {
                if(checkForCollide(collider_objects[i], collider_objects[j]))
                {   
                    collider_objects[i]->owner->old_velocity = collider_objects[i]->owner->new_velocity;
                    collider_objects[j]->owner->old_velocity = collider_objects[j]->owner->new_velocity;

                    std::cout << "enemy has old velocity = "<<collider_objects[i]->owner->old_velocity[1]<<std::endl;
                    std::cout << "player has old velocity = "<<collider_objects[j]->owner->old_velocity[1]<<std::endl;
                    

                    for (qqq::Component* script : collider_objects[j]->owner->scripts)       
                    {
                        static_cast<qqq::Script*>(script)->ifCollision(collider_objects[i]->owner);
                    }

                    for (qqq::Component* script : collider_objects[i]->owner->scripts)       
                    {
                        static_cast<qqq::Script*>(script)->ifCollision(collider_objects[j]->owner);
                    }

                    
                    std::cout << "enemy has new velocity = "<<collider_objects[i]->owner->new_velocity[1]<<std::endl;
                    std::cout << "player has new velocity = "<<collider_objects[j]->owner->new_velocity[1]<<std::endl;
                    
                    std::cout << collider_objects[i]->owner->id_in_data_storage <<"have equal velocities?"<<(bool)(collider_objects[i]->owner->old_velocity==collider_objects[i]->owner->new_velocity)<<std::endl;
                    std::cout << collider_objects[j]->owner->id_in_data_storage<<" have equal velocities?"<<(bool)(collider_objects[j]->owner->old_velocity==collider_objects[j]->owner->new_velocity)<<std::endl;
                    
                    
                    
                    
                }
            }
        }
    }
}



