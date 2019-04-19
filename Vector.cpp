#include "Vector.h"

Vector::Vector() : initialized(false) {

}

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z), initialized(true) {

}

//addition
Vector Vector::operator+(const Vector &vec) {
    return Vector(this->x + vec.x, this->y + vec.y, this->z + vec.z);
} //tested

Vector& Vector::operator+=(const Vector &vec) {
    this->x +=vec.x;
    this->y +=vec.y;
    this->z +=vec.z;
    return *this;
} //tested

//subtraction//
Vector Vector::operator-(const Vector &vec) {
    return Vector(this->x - vec.x, this->y - vec.y , this->z - vec.z);
} //tested

Vector& Vector::operator-=(const Vector &vec) {
    this->x -= vec.x;
    this->y -= vec.y;
    this->z -= vec.z;
    return *this;
} //tested

//scalar multiplication
Vector Vector::operator*(float value) {
    return Vector(this->x * value, this->y * value, this->z * value);
} //tested

Vector& Vector::operator*=(float value) {
    this->x *= value;
    this->y *= value;
    this->z *= value;
    return *this;
} //tested

//scalar division
Vector Vector::operator/(float value) {
    assert(value!=0);
    return Vector(this->x / value, this->y / value, this->z / value);
} //tested

Vector& Vector::operator/=(float value) {
    assert(value!=0);
    this->x /= value;
    this->y /= value;
    this->z /= value;
    return *this;
} //tested

//equality
Vector& Vector::operator=(const Vector &vec) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
    return *this;
}

//Dot product
float Vector::dot_product(const Vector &vec) {
    return x * vec.x + vec.y * y + vec.z * z;
} //tested

//cross product
Vector Vector::cross_product(const Vector &vec) {
    float ni = y * vec.z - z * vec.y;
    float nj = z * vec.x - x * vec.z;
    float nk = x * vec.y - y * vec.x;
    return Vector(ni,nj,nk);
} //tested

float Vector::length() {
    return sqrt(square());
}

float Vector::square() {
    return x * x + y * y + z * z;
}

Vector Vector::normalize() {
    assert(length()!=0);
    *this /= length();
    return *this;
}

float Vector::distance(const Vector &vec) {
    Vector dist = *this - vec;
    return dist.length();
}

// float Vector::show_X()
// {
//     return x;
// }
//
// float Vector::show_Y()
// {
//     return y;
// }
//
// float Vector::show_Z()
// {
//     return z;
// }

void Vector::display() {
    std::cout << x << " " << y << " " << z << std::endl;
}
