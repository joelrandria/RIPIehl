//
// Created by 60FDP.s-1 on 11/11/2015.
//

#ifndef HELLO_WORLD_VEC3_H
#define HELLO_WORLD_VEC3_H

#include "Vec2.h"
//#include <math.h>
//#include <iostream>

template<class T>
class Vec3{
public:
    union{
        struct { T x, y, z; };
        T v[3];
    };

    /*
     * Constructor
     */
    template <class A, class B, class C> Vec3(const A & _x = 0, const B & _y = 0, const C & _z = 0) : x(_x), y(_y), z(_z) {}
    template <class A> Vec3(const A * v) : x(v[0]), y(v[1]), z(v[2]) {}
    template <class A> Vec3(const Vec3<A> &v) : x(v.x), y(v.y), z(v.z) {}

    template <class C> explicit Vec3(const C & c) : x(c[0]), y(c[1]), z(c[2]){}

    template <class A, class C> Vec3(const Vec2<C> & v, const A & a) : x(v.x), y(v.y), z(a) {}
    template <class A, class C> Vec3(const A & a, const Vec2<C> & v) : x(a), y(v.x), z(v.y) {}

    ~Vec3() {}

    /*
     * writer
     */
    inline T &operator[](const int &i) {return v[i];}
    inline T &operator[](const unsigned int &i) {return v[i];}

    /*
     * reader
     */
    inline const T &operator[](const int &i) const {return v[i];}
    inline const T &operator[](const unsigned int &i) const {return v[i];}

    template <class A, class B, class C> inline void set(const A &_x, const B &_y, const C &_z) { x=_x; y=_y; z=_z;}
    operator const T*() const { return v; }
    operator T*() { return v; }

    template <class C> inline Vec3<T> operator=(const Vec3<C> &a) { x = a.x; y = a.y; z = a.z; return *this; }
    template <class C> inline Vec3<T> operator+=(const Vec3<C> &a) { x += a.x; y += a.y; z += a.z; return *this; }
    template <class C> inline Vec3<T> operator-=(const Vec3<C> &a) { x -= a.x; y -= a.y; z -= a.z; return *this; }

    //inline Vec3 operator*=(const T &s) { x *= s; y *= s; return *this; }
    //inline Vec3 operator/=(const T &s) { x /= s; y /= s; return *this; }

    /*
     * Binary operation with an other vector
     */
    template <class C> friend inline Vec3<T> operator+(const Vec3<T> &a, const Vec3<C> &b) { return Vec3<T>( a.x+b.x, a.y+b.y, a.z+b.z); }
    template <class C> friend inline Vec3<T> operator-(const Vec3<T> &a, const Vec3<C> &b) { return Vec3<T>( a.x-b.x, a.y-b.y, a.z-b.z ); }

    //JM element by element
    template <class C> friend inline Vec3<T> mulByElement(const Vec3<T> &a, const Vec3<C> &b) { return Vec3<T>( a.x*b.x, a.y*b.y, a.z*b.z ); }
    template <class C> friend inline Vec3<T> divByElement(const Vec3<T> &a, const Vec3<C> &b) { return Vec3<T>( a.x/b.x, a.y/b.y, a.z/b.z); }

    /*
     * Unary operation with one vector
     */
    friend inline Vec3 operator-(const Vec3 &a) { return Vec3<T>(-a.x, -a.y, -a.z); }

    /*
     * Binary operation with a scalar
     */
    template <class A> friend inline Vec3 operator+(const Vec3<T> &a, const A & s) { return Vec3<T>( a.x+s, a.y+s, a.z+s); }
    template <class A> friend inline Vec3 operator-(const Vec3<T> &a, const A & s) { return Vec3<T>( a.x-s, a.y-s, a.z-s); }
    template <class A> friend inline Vec3 operator*(const Vec3<T> &a, const A & s) { return Vec3<T>( a.x*s, a.y*s, a.z*s); }
    template <class A> friend inline Vec3 operator/(const Vec3<T> &a, const A & s) { return Vec3<T>( a.x/s, a.y/s, a.z/s); }

    template <class A> friend inline Vec3 operator+(const A &s, const Vec3<T> &a ) { return Vec3<T>( a.x+s, a.y+s, a.z+s); }
    template <class A> friend inline Vec3 operator*(const A &s, const Vec3<T> &a ) { return Vec3<T>( a.x*s, a.y*s, a.z*s); }

    /*
     * Boolean operator
     */
    template <class A> friend inline bool operator!=(const Vec3<T> &a, const Vec3<A> &b) { return !(a==b); }
    template <class A> friend inline bool operator==(const Vec3<T> &a, const Vec3<A> &b) { return (a-b).norm() < 1.0E-10f; }

    //JM
    template <class C> friend inline bool operator>(const Vec3<T> &a, const Vec3<C> &b) { return (a - b).norm() > 1.0E-10f; }
    template <class C> friend inline bool operator<(const Vec3<T> &a, const Vec3<C> &b) { return (a - b).norm() < -1.0E-10f; }
    template <class C> friend inline bool operator<=(const Vec3<T> &a, const Vec3<C> &b) { return !(a>b);}
    template <class C> friend inline bool operator>=(const Vec3<T> &a, const Vec3<C> &b) { return !(a<b);}

    /*
     * Dot product
     */
    template <class C> friend inline T dot(const Vec3<T> &a, const Vec3<C> &b) { return a.x*b.x + a.y*b.y; }
    template <class C> friend inline T operator*(const Vec3<T> &a, const Vec3<C> &b) { return dot(a,b); }

    /*! Norm of the vector */
    inline float norm() const {return sqrt(static_cast< float >( x*x + y*y + z*z) );}
    inline T squaredNorm() const {return (x*x + y*y + z*z);}

    /*! Normalize the vector */
    inline Vec3 &normalize() { *this /= static_cast< T >(norm()); return *this; }

    /*! I/O operator */
    friend std::istream &operator >>(std::istream &stream, Vec3 &v) { return stream >> v.x >> v.y >> v.z; }
    friend std::ostream &operator <<(std::ostream &stream, const Vec3<T> &v) { return stream << v.x << " " << v.y << " " << v.z; }
};

typedef Vec3< double       > Vec3d ;
typedef Vec3< float        > Vec3f ;
typedef Vec3< int          > Vec3i ;
typedef Vec3< unsigned int > Vec3ui ;

#endif //HELLO_WORLD_VEC3_H
