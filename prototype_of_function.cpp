#include <SFML/Graphics.hpp>
#include "Singleton.h"
#include "API.h"
#include "GameObject.h"
#include <fstream>
#include <cmath>

// class PrototypeOfFuncionIfCollide : public qqq::Script
// {
//     public:

//         void ifCollision(qqq::GameObject* another)
//         {   
            
//             if( true )
//             {

//                 double sin = -1;
//                 double cos = 0;

            
//                 if (this -> owner -> position[0] == another -> position[0])
//                 {
//                     if (this -> owner -> position[1] < another -> position[1])
//                     {
//                         sin = 1;
//                         cos = 0;
//                     }
//                     else 
//                     {
//                         sin = -1;
//                         cos = 0;
//                     }
//                 }
//                 else {
//                     double k = (another -> position[1] - this -> owner -> position[1]) / (another -> position[0] - this -> owner -> position[0]);
//                     sin = k / (sqrt(pow(k, 2) + 1));
//                     cos = 1 / (sqrt(pow(k, 2) + 1));
//                 }

//                 // зададим через матрицу перехода свзять координат в разных СО

//                 float V_csi_before_1_obj = cos * this -> owner -> velocity_before_hitting[0] + sin * this -> owner -> velocity_before_hitting[1];
//                 float V_eta_before_1_obj = (-1) * sin * this -> owner -> velocity_before_hitting[0] + cos * this -> owner -> velocity_before_hitting[1];

//                 float V_csi_before_2_obj = cos * another -> velocity_before_hitting[0] + sin * another -> velocity_before_hitting[1];
//                 float V_eta_before_2_obj = (-1) * sin * another -> velocity_before_hitting[0] + cos * another -> velocity_before_hitting[1];

//                 float csi_coord_1_obj =  cos * this -> owner -> position[0] + sin * this -> owner -> position[1];
//                 float eta_coord_1_obj = (-1) * sin * this -> owner -> position[0] + cos * this -> owner -> position[1];

//                 float csi_coord_2_obj =  cos * another -> position[0] + sin * another -> position[1];
//                 float eta_coord_2_obj = (-1) * sin * another -> position[0] + cos * another -> position[1];
//                 // выразил скорости в новой СК , теперь поменяем нормальные составляющие и проверим, требуется ли в данном 
//                 // рассталкивать эти обьекты

//                 if (    csi_coord_2_obj > csi_coord_1_obj and V_csi_before_2_obj < 0 and V_csi_before_1_obj > 0 or
//                         csi_coord_2_obj < csi_coord_1_obj and V_csi_before_2_obj > 0 and V_csi_before_1_obj < 0 or
//                         csi_coord_2_obj > csi_coord_1_obj and V_csi_before_1_obj - V_csi_before_2_obj > 0       or
//                         csi_coord_2_obj < csi_coord_1_obj and V_csi_before_1_obj - V_csi_before_2_obj < 0           )
//                 {

//                     V_csi_before_1_obj = V_csi_before_2_obj;

//                     // теперь переходим к старым координатам

//                     double V_x_1_obj_after_hitting = cos * V_csi_before_1_obj - sin * V_eta_before_1_obj;
// 			        double V_y_1_obj_after_hitting = sin * V_csi_before_1_obj + cos * V_eta_before_1_obj;
                    
//                     this -> owner -> velocity_after_hitting[0] = V_x_1_obj_after_hitting;
//                     this -> owner -> velocity_after_hitting[1] = V_y_1_obj_after_hitting;

//                 }
//             }
//         }
// };



class Button
{
    public:
        Button(sf::Vector2i left_top_angle , sf::Vector2i right_bottom_angle)
        {
            coordinates_of_left_top_angle = left_top_angle;
            coordinates_of_right_bottom_angle = right_bottom_angle;
        }

        void setTextureAndSpriteOfNotPressedButton (std::string name_of_not_pressed_button )
        {
            texture_of_not_pressed_button.loadFromFile(name_of_not_pressed_button);
            sprite_of_not_pressed_button.setTexture(texture_of_not_pressed_button);
        }

        // void setTextureAndSpriteOfPressedButton (std::string name_of_pressed_button )
        // {
        //     texture_of_pressed_button.loadFromFile(name_of_pressed_button);
        //     sprite_of_pressed_button.setTexture(texture_of_pressed_button);
        // }

        bool checkForPressed(sf::RenderWindow& window , sf::Event& event)
        {   
            bool mouse_on_botton = sf::IntRect(coordinates_of_left_top_angle,coordinates_of_right_bottom_angle - coordinates_of_left_top_angle).contains(sf::Mouse::getPosition(window));

            if( mouse_on_botton and event.type == sf::Event::MouseButtonPressed)
            {
                return true;
            }
            return false;
        }

        void draw(sf::RenderWindow& window)
        {
            window.draw(sprite_of_not_pressed_button);
        }

        void setPosition(int x , int y)
        {
            sprite_of_not_pressed_button.setPosition({x,y});
        }

        // bool checkForReleased(sf::RenderWindow& window , sf::Event& event)
        // {
        //     bool mouse_on_botton = sf::IntRect(coordinates_of_left_top_angle,coordinates_of_right_bottom_angle - coordinates_of_left_top_angle).contains(sf::Mouse::getPosition(window));
        //     if( mouse_on_botton and event.type == sf::Event::MouseButtonReleased(sf::Mouse::Left , window))
        //     {
        //         return true;
        //     }

        //     return false;
        // }


    private:

        sf::Vector2i coordinates_of_left_top_angle;
        sf::Vector2i coordinates_of_right_bottom_angle;


        sf::Texture texture_of_not_pressed_button;
        sf::Sprite sprite_of_not_pressed_button;
        sf::Texture texture_of_pressed_button;
        sf::Sprite sprite_of_pressed_button;
};

void checkForButtonPressed(sf::RenderWindow& window , Button button_next )
{

}

void settingHitboxPointsWithMouse(sf::RenderWindow& window, std::string name_of_pictures_folder)
{
    qqqP::Singleton* singleton = qqqP::Singleton::getInstance();
    qqqP::DataStorage* data_storage =  &singleton -> data_storage;

    std::ifstream pictures_folder;
    pictures_folder.open(name_of_pictures_folder);

    std::string name_of_picture;

    Button button_NEXT = { { 520 , 0 } , {600,90} };
    button_NEXT.setTextureAndSpriteOfNotPressedButton("image.png");
    button_NEXT.setPosition(520,0);

    
   
   
    while( getline(pictures_folder,name_of_picture) ) /// считывание работает выводит каждое имя отдельно
    { 
        std::cout << name_of_picture<<std::endl;
        sf::Texture texture;
        sf::Sprite sprite;

        int x_poition_of_sprite = window.getSize().x / 2 ;
        int y_position_of_sprite = window.getSize().y / 2 ;
        
        texture.loadFromFile(name_of_picture);
        sprite.setTexture(texture);
        sprite.setPosition( x_poition_of_sprite , y_position_of_sprite );
        
        std::vector < std::vector<int> > vector_of_relative_hitbox_points;
    
        sf::VertexArray lines;
        int size_of_lines = 0;
        float x = 0.0f, y = 0.0f;
        
        
        sf::Event event;
        while(window.isOpen())
        {
            
            if( window.pollEvent(event) )
            {   
                window.clear(sf::Color(255, 255, 255));
                window.draw(sprite);
                window.draw(lines);
                button_NEXT.draw(window);

                if(button_NEXT.checkForPressed(window,event))
                {
                    break;
                }

                if( event.type == sf::Event::MouseButtonPressed )
                {  
                    vector_of_relative_hitbox_points.push_back( { sf::Mouse::getPosition().x - x_poition_of_sprite, sf::Mouse::getPosition().y - y_position_of_sprite } );
                    
                    x = sf::Mouse::getPosition(window).x;
                    y = sf::Mouse::getPosition(window).y;

                    
                    
                    if(size_of_lines != 0)
                        lines.resize(--size_of_lines);

                    lines.append( sf::Vertex( sf::Vector2f (x,y) , sf::Color::Red , sf::Vector2f (0.0f,0.0f) ) ) ;   
                    lines.setPrimitiveType ( sf::LinesStrip );
                    lines.append( lines[0] );
                    size_of_lines += 2;
   
                }

                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }

            window.display();
        }
        

        data_storage -> setVectorOfRelativeHitboxCoordinatesByName(name_of_picture,vector_of_relative_hitbox_points);

    }
    


    pictures_folder.close();
}

int main()
{
     sf::RenderWindow window(sf::VideoMode(600, 600), "test");

     settingHitboxPointsWithMouse(window,"all.txt");

    return 0;
}
