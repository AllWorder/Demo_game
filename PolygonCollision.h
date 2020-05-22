#include <SFML/Graphics.hpp>
#include <cmath>
#include "Singleton.h"
#include "GameObject.h"

#include "Vector3f.h"




// bool areCrossing(Vector3f first_point_hitbox,Vector3f  second_point_hitbox,Vector3f old_point_hitbox ,Vector3f new_point_hitbox , std::vector<std::vector<float>>& angle_and_coordinates  )
// {   
//     Vector3f

//     v11 = first_point_hitbox,
//     v12 = second_point_hitbox,

//     v21 = old_point_hitbox,
//     v22 = new_point_hitbox;

//     Vector3f cut1 = v12 - v11;
//     Vector3f cut2 = v22 - v21;

//     Vector3f 

//     prod1 = cross(cut1 , v21 - v11 ),
//     prod2 = cross(cut1 , v22 - v11 );

//     if( prod1[2]*prod2[2] > 0  or (prod1[2] == 0) or (prod2[2] == 0))
//     {
//         return false;
//     }

//     prod1 = cross(cut2 , (v11-v21));
//     prod2 = cross(cut2 , (v12-v21));

//     if( prod1[2]*prod2[2] > 0  or (prod1[2] == 0) or (prod2[2] == 0))
//     {
//         return false;
//     }  

//     float 

//     x_coor_point = new_point_hitbox[0],
//     y_coor_point = new_point_hitbox[1];

//     Vector3f crossing;

//     crossing[0] = v11[0] + cut1[0]*fabs(prod1[2])/fabs(prod2[2]-prod1[2]);
//     crossing[1] = v11[1] + cut1[1]*fabs(prod1[2])/fabs(prod2[2]-prod1[2]);

//     float sin = -1;
//     float cos = 0;


//     if (x_coor_point == crossing[0])
//     {
//         if (y_coor_point < crossing[1])
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
//         float k = (crossing[1] - y_coor_point) / (crossing[0] - x_coor_point);
//         sin = k / (sqrt(pow(k, 2) + 1));
//         cos = 1 / (sqrt(pow(k, 2) + 1));
//     }

//     angle_and_coordinates[0][0] = sin;
//     angle_and_coordinates[0][1] = cos;

//     angle_and_coordinates[1] = {old_point_hitbox[0],old_point_hitbox[1]};
//     angle_and_coordinates[2] = {crossing[0],crossing[1]};

//     return true;
// }

// std::vector<std::vector<float>> findCollisionOneObj(std::vector < std::vector <float> > absol_hit_coord_1 , std::vector < std::vector <float> > new_absol_hit_coord_2 , std::vector < std::vector <float> > old_absol_hit_coord_2 )
// {
//     int quantity_of_points_1 = absol_hit_coord_1.size();
//     int quantity_of_points_2 = new_absol_hit_coord_2.size();
//     Vector3f collision;

//     for( int i = 0 ; i < quantity_of_points_1 ; ++i)
//     {
//         for( int j = 0 ; j < quantity_of_points_2 ; ++j)
//         {
//             if( i == quantity_of_points_1 - 1 )
//             {
//                 Vector3f
//                 first_point_hitbox = {absol_hit_coord_1[i][0] ,absol_hit_coord_1[i][1] ,0 } ,
//                 second_point_hitbox = {absol_hit_coord_1[0][0] ,absol_hit_coord_1[0][1] ,0 } , 

//                 old_point_hitbox = {old_absol_hit_coord_2[j][0],old_absol_hit_coord_2[j][1],0},
//                 new_point_hitbox = {new_absol_hit_coord_2[j][0],new_absol_hit_coord_2[j][1],0};

//                 std::vector<std::vector<float>> angle_and_points = {{0,0},{0,0},{0,0}};
                


//                 if(areCrossing(first_point_hitbox,second_point_hitbox,old_point_hitbox,new_point_hitbox,angle_and_points))
//                 {
//                     return angle_and_points;
//                 }

//             }
//             else
//             {   
//                 Vector3f
//                 first_point_hitbox = {absol_hit_coord_1[i][0] ,absol_hit_coord_1[i][1] ,0 } ,
//                 second_point_hitbox = {absol_hit_coord_1[i+1][0] ,absol_hit_coord_1[i+1][1] ,0 } , 

//                 old_point_hitbox = {old_absol_hit_coord_2[j][0],old_absol_hit_coord_2[j][1],0},
//                 new_point_hitbox = {new_absol_hit_coord_2[j][0],new_absol_hit_coord_2[j][1],0};

//                 std::vector<std::vector<float>> angle_and_points = {{0,0},{0,0},{0,0}};

//                 if(areCrossing(first_point_hitbox,second_point_hitbox,old_point_hitbox,new_point_hitbox,angle_and_points))
//                 {
//                     return angle_and_points;
//                 }
                
//             }
            
//         }

//     }

// }


// class qqq::PolygonReflection: public qqq::Script
// {
// public:
//     void update();  // move this function to PhysicsManager or somewhere else
//     void ifCollision(qqq::GameObject* another);
// };


void qqq::PolygonReflection::update()
{
    float dt = qqq::relativeTime();
    owner -> moveVdt();
    
// }

// void qqq::PolygonReflection::ifCollision(qqq::GameObject* another)
// {   
    
//     ///сделаем массив старых положений хитбоксов и новых  для этого обьекта /////
//     int this_points_quantity_1 = static_cast<qqq::Collider*>(owner->colliders[0])->getQuantityOfBodyPoints();
//     std::vector < std::vector <float>> rel_hitbox_coord_1 = static_cast<qqq::Collider*>(owner->colliders[0])->getRelativeHitboxCoordinates();

//     std::vector < std::vector <float> > new_absol_hit_coord_1;
//     std::vector < std::vector <float> > old_absol_hit_coord_1;

//     for( int i = 0 ; i < this_points_quantity_1 ; ++i )
//     {
//         new_absol_hit_coord_1.push_back({ rel_hitbox_coord_1[i][0]+owner->position[0] , rel_hitbox_coord_1[i][1]+owner->position[1] });
//         old_absol_hit_coord_1.push_back({ rel_hitbox_coord_1[i][0]+owner->old_position[0] , rel_hitbox_coord_1[i][1]+owner->old_position[1] });

//     }

//     ///сделаем массив старых положений хитбоксов и новых  для другого обьекта /////

//     int this_points_quantity_2 = static_cast<qqq::Collider*>(another->colliders[0])->getQuantityOfBodyPoints();
//     std::vector < std::vector <float>> rel_hitbox_coord_2 = static_cast<qqq::Collider*>(another->colliders[0])->getRelativeHitboxCoordinates();

//     std::vector < std::vector <float> > new_absol_hit_coord_2;
//     std::vector < std::vector <float> > old_absol_hit_coord_2;

//     for( int i = 0 ; i < this_points_quantity_2 ; ++i )
//     {
//         new_absol_hit_coord_2.push_back({ rel_hitbox_coord_2[i][0]+another->position[0] , rel_hitbox_coord_2[i][1]+another->position[1] });
//         old_absol_hit_coord_2.push_back({ rel_hitbox_coord_2[i][0]+another->old_position[0] , rel_hitbox_coord_2[i][1]+another->old_position[1] });

//     }
    
//     ////////////////////////////////////////////////////////////////////////////////
//     // теперь нужно проверить пересечение всех приращений со сторонами хитбокса для обоих обьектов  ////

//     std::vector<std::vector<float>> angle_and_points; 
//     angle_and_points = findCollisionOneObj(new_absol_hit_coord_1,new_absol_hit_coord_2,old_absol_hit_coord_2);
//     angle_and_points = findCollisionOneObj(new_absol_hit_coord_2,new_absol_hit_coord_1,old_absol_hit_coord_1);

//     ////////////////////////////////////////////////////////////////////////////////////
//     //// меняем скорости

//     float 
//     sin = angle_and_points[0][0],
//     cos = angle_and_points[0][1];

//     // зададим через матрицу перехода свзять координат в разных СО
//     float V_csi_before_1_obj = cos * this -> owner -> velocity[0] + sin * this -> owner -> velocity[1];
//     float V_eta_before_1_obj = (-1) * sin * this -> owner -> velocity[0] + cos * this -> owner -> velocity[1];

//     float V_csi_before_2_obj = cos * another -> velocity[0] + sin * another -> velocity[1];
//     float V_eta_before_2_obj = (-1) * sin * another -> velocity[0] + cos * another -> velocity[1];

//     float csi_coord_1_obj =  cos * angle_and_points[1][0] + sin * angle_and_points[1][1];
//     float eta_coord_1_obj = (-1) * sin * angle_and_points[1][0] + cos * angle_and_points[1][1];

//     float csi_coord_2_obj =  cos * angle_and_points[2][0] + sin * angle_and_points[2][1];
//     float eta_coord_2_obj = (-1) * sin * angle_and_points[2][0] + cos * angle_and_points[2][1];
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
 
//     }
//