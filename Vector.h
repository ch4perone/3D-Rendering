#ifndef PROJECT_VECTOR_H
#define PROJECT_VECTOR_H

#include<iostream>
#include<math.h>
#include<assert.h>

class Vector {


public:

    float x, y, z;
    bool initialized;

    Vector();
    Vector(float x, float y, float z);

    //addition
    Vector operator+(const Vector &vec);
    Vector &operator+=(const Vector &vec);

    //subtraction
    Vector operator-(const Vector &vec);
    Vector &operator-=(const Vector &vec);

    //multiplication
    Vector operator*(float value);
    Vector &operator*=(float value);

    //division
    Vector operator/(float value);
    Vector &operator/=(float value);

    //equality
    Vector &operator=(const Vector &vec);

    float dot_product(const Vector &vec); //dot-product
    Vector operator%(const Vector &vec); //cross-product


    float length();
    Vector normalize();

    //gives square of the vector
    float square();

    //gives distance between two vectors
    float distance(const Vector &vec);
    Vector directionTo(const Vector &vec);
    Vector offsetAllAxis(float value);
    // f show_X(); //return x
    // f show_Y(); //return y
    // f show_Z(); //return z

    //display value of vectors
    void display();


};


#endif //PROJECT_VECTOR_H
