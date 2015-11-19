//
// Created by 60FDP.s-1 on 04/11/2015.
//

#ifndef HELLO_WORLD_VEC2_H
#define HELLO_WORLD_VEC2_H

#include <math.h>
#include <iostream>

template<class T>
    class Vec2{
    public:

        union{
            struct { T x, y; };
            T v[2];
        };

        /*
        * Constructor
        */
        template <class A, class B> Vec2(const A & _x = NULL, const B & _y = NULL) : x(_x), y(_y) {}
        template <class A> Vec2(const A * v) : x(v[0]), y(v[1]) {}
        template <class A> Vec2(const Vec2<A> &v) : x(v.x), y(v.y) {}

        template <class C> explicit Vec2(const C & c) : x(c[0]), y(c[1]) {}

        ~Vec2() {}

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

        inline void set(const T &_x, const T &_y) { x=_x; y=_y; }
        operator const T*() const { return v; }
        operator T*() { return v; }

        template <class C> inline Vec2<T> operator=(const Vec2<C> &a) { x = a.x; y = a.y; return *this; }
        template <class C> inline Vec2<T> operator+=(const Vec2<C> &a) { x += a.x; y += a.y; return *this; }
        template <class C> inline Vec2<T> operator-=(const Vec2<C> &a) { x -= a.x; y -= a.y; return *this; }

        //inline Vec2 operator*=(const T &s) { x *= s; y *= s; return *this; }
        //inline Vec2 operator/=(const T &s) { x /= s; y /= s; return *this; }

        /*
         * Binary operation with an other vector
         */
        template <class C> friend inline Vec2<T> operator+(const Vec2<T> &a, const Vec2<C> &b) { return Vec2<T>( a.x+b.x, a.y+b.y ); }
        template <class C> friend inline Vec2<T> operator-(const Vec2<T> &a, const Vec2<C> &b) { return Vec2<T>( a.x-b.x, a.y-b.y ); }

        //JM element by element
        template <class C> friend inline Vec2<T> mulByElement(const Vec2<T> &a, const Vec2<C> &b) { return Vec2<T>( a.x*b.x, a.y*b.y ); }
        template <class C> friend inline Vec2<T> divByElement(const Vec2<T> &a, const Vec2<C> &b) { return Vec2<T>( a.x/b.x, a.y/b.y ); }

        /*
         * Unary operation with one vector
         */
        friend inline Vec2 operator-(const Vec2 &a) { return Vec2<T>( -a.x, -a.y ); }

        /*
         * Binary operation with a scalar
         */
        friend inline Vec2 operator+(const Vec2 &a, const T & s) { return Vec2<T>( a.x+s, a.y+s ); }
        friend inline Vec2 operator-(const Vec2 &a, const T & s) { return Vec2<T>( a.x-s, a.y-s ); }
        friend inline Vec2 operator*(const Vec2 &a, const T & s) { return Vec2<T>( a.x*s, a.y*s ); }
        friend inline Vec2 operator/(const Vec2 &a, const T & s) { return Vec2<T>( a.x/s, a.y/s ); }

        friend inline Vec2 operator+(const T &s, const Vec2 &a ) { return Vec2<T>( a.x+s, a.y+s ); }
        friend inline Vec2 operator*(const T &s, const Vec2 &a ) { return Vec2<T>( a.x*s, a.y*s ); }

        /*
         * Boolean operator
         */
        template <class A> friend inline bool operator!=(const Vec2<T> &a, const Vec2<A> &b) { return !(a==b); }
        template <class A> friend inline bool operator==(const Vec2<T> &a, const Vec2<A> &b) { return (a-b).norm() < 1.0E-10f; }

        //JM
        template <class C> friend inline bool operator>(const Vec2<T> &a, const Vec2<C> &b) { return (a - b).norm() > 1.0E-10f; }
        template <class C> friend inline bool operator<(const Vec2<T> &a, const Vec2<C> &b) { return (a - b).norm() < -1.0E-10f; }
        template <class C> friend inline bool operator<=(const Vec2<T> &a, const Vec2<C> &b) { return !(a>b);}
        template <class C> friend inline bool operator>=(const Vec2<T> &a, const Vec2<C> &b) { return !(a<b);}

        /*
         * Dot product
         */
        template <class C> friend inline T dot(const Vec2<T> &a, const Vec2<C> &b) { return a.x*b.x + a.y*b.y; }
        template <class C> friend inline T operator*(const Vec2<T> &a, const Vec2<C> &b) { return dot(a,b); }

        /*! Norm of the vector */
        inline float norm() const {return sqrt(static_cast< float >( x*x + y*y ) );}
        inline T squaredNorm() const {return (x*x + y*y);}

        /*! Normalize the vector */
        inline Vec2 &normalize() { *this /= static_cast< T >(norm()); return *this; }

        /*! I/O operator */
        friend std::istream &operator >>(std::istream &stream, Vec2 &v) { return stream >> v.x >> v.y; }
        friend std::ostream &operator <<(std::ostream &stream, const Vec2<T> &v) { return stream << v.x << " " << v.y; }
    };

typedef Vec2< double       > Vec2d ;
typedef Vec2< float        > Vec2f ;
typedef Vec2< int          > Vec2i ;
typedef Vec2< unsigned int > Vec2ui ;

#endif //HELLO_WORLD_VEC2_H
