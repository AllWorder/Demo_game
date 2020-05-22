#include <cmath>


class Vector3f{

    public:
        Vector3f(){

            x = 0;
            y = 0;
            z = 0;

        }

        Vector3f(float x , float y , float z){

            this->x = x;
            this->y = y;
            this->z = z;

        }

        Vector3f operator-(Vector3f vec)
        {
            return{ x - vec.x , y - vec.y , z - vec.z};
        }

        Vector3f operator+(Vector3f vec){

            return{ x + vec.x , y + vec.y , z + vec.z};

        }

        Vector3f operator*(float const1){

            x*= const1;
            y*= const1;
            z*= const1;

        }

        Vector3f operator/(float const1){

            x /= const1;
            y /= const1;
            z /= const1;
            
        }

        void operator=(Vector3f vec){
            
            this->x = vec.x;
            this->y = vec.y;
            this->z = vec.z;

        }
        
        bool operator==(Vector3f vector){
            if(this->x == vector.x and this->y == vector.y and this->z == vector.z){

                return true;
            }
            else return false;
        }

        float& operator[](int value)
        {
            if( value == 0)
            {
                return this->x;
            }
            if( value == 1)
            {
                return this->y;
            }
            if( value == 2)
            {
                return this->z;
            }
        }

        float x = 0,
            y = 0,
            z = 0;

    private:        

};



Vector3f cross(Vector3f vec1 , Vector3f vec2)
{   
    Vector3f result;
    result[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
    result[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
    result[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
    return result;

}
