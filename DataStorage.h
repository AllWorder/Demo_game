#ifndef __DATA_STORAGE__
#define __DATA_STORAGE__


#include <string>
#include <map>
#include <vector>
#include "GraphicsManager.h"
#include "API.h"

class qqqP::DataStorage{
    public:
        ~DataStorage();
        bool addObject(std::string object_name, qqq::GameObject* obj);
        bool deleteObject(std::string object_name);
        void setVectorOfRelativeHitboxCoordinatesByName(std::string name_of_picture, std::vector < std::vector<int> > vector_of_coordinates);
        void updateAll();
        std::vector < std::vector <int> > getVectorOfRelativeHitboxCoordinatesByName(std::string name_of_picture);
        qqq::GameObject* getObject(std::string object_name);
        std::vector<qqq::GameObject*> getAll();
    private:
        std::map < std::string, qqq::GameObject* > map_of_game_objects;
        std::map < std::string, std::vector < std::vector<int> >  > map_of_relative_hitbox_coordinates_for_each_picture;
};

#endif



    


