//
// Created by 60FDP.s-1 on 12/11/2015.
//

#ifndef HELLO_WORLD_VEC4_H
#define HELLO_WORLD_VEC4_H

#include "Vec3.h"
//#include <math.h>
//#include <iostream>

template<class T>
class Vec4{
public:
    union{
        struct { T x, y, z, t; };
        struct { T r, g, b, a; };
        T v[4];
    };

    /*
     * Constructor
     */
    template <class A, class B, class C, class D>
    Vec4(const A & _x = 0, const B & _y = 0, const C & _z = 0, const D & _t = 0) : x(_x), y(_y), z(_z), t(_t){}
    template <class A> Vec4(const A * v) : x(v[0]), y(v[1]), z(v[2]), t(v[3]){}
    template <class A> Vec4(const Vec4<A> &v) : x(v.x), y(v.y), z(v.z), t(v.t) {}

    template <class C> explicit Vec4(const C & c) : x(c[0]), y(c[1]), z(c[2]), t(c[3]){}

    /*
     * Constructor with Vec2
     */
    template <class A, class B, class C> Vec4(const Vec2<C> & v, const A & a, const B & b) : x(v.x), y(v.y), z(a), t(b) {}
    template <class A, class B, class C> Vec4(const A & a, const Vec2<C> & v, const B & b) : x(a), y(v.x), z(v.y), t(b){}
    template <class A, class B, class C> Vec4(const A & a, const B & b, Vec2<C> & v) : x(a), y(b), z(v.x), t(v.y){}

    template <class A, class C> Vec4(const Vec2<A> & v1, const Vec2<C> & v2) : x(v1.x), y(v1.y), z(v2.x), t(v2.y) {}

    /*
     * Constructor with Vec3
     */
    template <class A, class C> Vec4(const Vec3<C> & v, const A & a) : x(v.x), y(v.y), z(v.z), t(a) {}
    template <class A, class C> Vec4(const A & a, const Vec3<C> & v) : x(a), y(v.x), z(v.y), t(v.z) {}
    ~Vec4() {}

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

    template<class A, class B, class C, class D>
    inline void set(const A &_x, const B &_y, const C &_z, const D & _t) { x=_x; y=_y; z=_z; t =_t;}
    operator const T*() const { return v; }
    operator T*() { return v; }

    template <class C> inline Vec4<T> operator=(const Vec4<C> &a) { x = a.x; y = a.y; z = a.z; t = a.t; return *this; }
    template <class C> inline Vec4<T> operator+=(const Vec4<C> &a) { x += a.x; y += a.y; z += a.z; t += a.t; return *this; }
    template <class C> inline Vec4<T> operator-=(const Vec4<C> &a) { x -= a.x; y -= a.y; z -= a.z; t -= a.t; return *this; }

    //inline Vec4 operator*=(const T &s) { x *= s; y *= s; return *this; }
    //inline Vec4 operator/=(const T &s) { x /= s; y /= s; return *this; }

    /*
     * Binary operation with an other vector
     */
    template <class C> friend inline Vec4<T> operator+(const Vec4<T> &a, const Vec4<C> &b) { return Vec4<T>( a.x+b.x, a.y+b.y, a.z+b.z, a.t+b.t ); }
    template <class C> friend inline Vec4<T> operator-(const Vec4<T> &a, const Vec4<C> &b) { return Vec4<T>( a.x-b.x, a.y-b.y, a.z-b.z, a.t-b.t ); }

    //JM element by element
    template <class C> friend inline Vec4<T> mulByElement(const Vec4<T> &a, const Vec4<C> &b) { return Vec4<T>( a.x*b.x, a.y*b.y, a.z*b.z, a.t*b.t ); }
    template <class C> friend inline Vec4<T> divByElement(const Vec4<T> &a, const Vec4<C> &b) { return Vec4<T>( a.x/b.x, a.y/b.y, a.z/b.z, a.t/b.t); }

    /*
     * Unary operation with one vector
     */
    friend inline Vec4 operator-(const Vec4 &a) { return Vec4<T>(-a.x, -a.y, -a.z, -a.t); }

    /*
     * Binary operation with a scalar
     */
    template <class A> friend inline Vec4 operator+(const Vec4 &a, const A & s) { return Vec4<T>( a.x+s, a.y+s, a.z+s, a.t+s); }
    template <class A> friend inline Vec4 operator-(const Vec4 &a, const A & s) { return Vec4<T>( a.x-s, a.y-s, a.z-s, a.t-s); }
    template <class A> friend inline Vec4 operator*(const Vec4 &a, const A & s) { return Vec4<T>( a.x*s, a.y*s, a.z*s, a.t*s); }
    template <class A> friend inline Vec4 operator/(const Vec4 &a, const A & s) { return Vec4<T>( a.x/s, a.y/s, a.z/s, a.t/s); }

    template <class A> friend inline Vec4 operator+(const A &s, const Vec4 &a ) { return Vec4<T>( a.x+s, a.y+s, a.z+s, a.t+s); }
    template <class A> friend inline Vec4 operator*(const A &s, const Vec4 &a ) { return Vec4<T>( a.x*s, a.y*s, a.z*s, a.t-s); }

    /*
     * Boolean operator
     */
    template <class A> friend inline bool operator!=(const Vec4<A> &a, const Vec4<T> &b) { return !(a==b); }
    template <class A> friend inline bool operator==(const Vec4<A> &a, const Vec4<T> &b) { return (a-b).norm() < 1.0E-10f; }

    //JM
    template <class C> friend inline bool operator>(const Vec4<T> &a, const Vec4<C> &b) { return (a - b).norm() > 1.0E-10f; }
    template <class C> friend inline bool operator<(const Vec4<T> &a, const Vec4<C> &b) { return (a - b).norm() < -1.0E-10f; }
    template <class C> friend inline bool operator<=(const Vec4<T> &a, const Vec4<C> &b) { return !(a>b);}
    template <class C> friend inline bool operator>=(const Vec4<T> &a, const Vec4<C> &b) { return !(a<b);}

    /*
     * Dot product
     */
    template <class C> friend inline T dot(const Vec4<T> &a, const Vec4<C> &b) { return a.x*b.x + a.y*b.y; }
    template <class C> friend inline T operator*(const Vec4<T> &a, const Vec4<C> &b) { return dot(a,b); }

    /*! Norm of the vector */
    inline float norm() const {return sqrt(static_cast< float >( x*x + y*y + z*z + t*t) );}
    inline T squaredNorm() const {return (x*x + y*y + z*z + t*t);}

    /*! Normalize the vector */
    inline Vec4 &normalize() { *this /= static_cast< T >(norm()); return *this; }

    /*! I/O operator */
    friend std::istream &operator >>(std::istream &stream, Vec4 &v) { return stream >> v.x >> v.y >> v.z >> v.t; }
    friend std::ostream &operator <<(std::ostream &stream, const Vec4<T> &v) { return stream << v.x << " " << v.y << " " << v.z << " " << v.t ; }
};

typedef Vec4< double       > Vec4d ;
typedef Vec4< float        > Vec4f ;
typedef Vec4< int          > Vec4i ;
typedef Vec4< unsigned int > Vec4ui ;

typedef Vec4< unsigned char > Color4uc;
typedef Vec4< float > Color4f;
#endif //HELLO_WORLD_VEC4_H
