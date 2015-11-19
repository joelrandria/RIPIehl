//
// Created by 60FDP.s-1 on 14/11/2015.
//

#ifndef HELLO_WORLD_MAT4_H
#define HELLO_WORLD_MAT4_H

#include <string.h>
#include <iomanip>

#include "Vec4.h"

/*
 * Matrix 4x4 order in row major
 */

class Mat4{
public :
    float mat[16];

    /*
     * Constructor
     */
    Mat4(const bool & Id){
        memset(mat, 0, sizeof(float) * 16);
        if (Id){
            mat[0] = 1; mat[5] = 1; mat[10] = 1; mat[15] = 1;
        }
    }

    Mat4(const float & m11 = 1, const float & m12 = 0, const float & m13 = 0, const float & m14 = 0,
         const float & m21 = 0, const float & m22 = 1, const float & m23 = 0, const float & m24 = 0,
         const float & m31 = 0, const float & m32 = 0, const float & m33 = 1, const float & m34 = 0,
         const float & m41 = 0, const float & m42 = 0, const float & m43 = 0, const float & m44 = 1){

            mat[0] = m11; mat[1] = m12; mat[2] = m13; mat[3] = m14;
            mat[4] = m21; mat[5] = m22; mat[6] = m23; mat[7] = m24;
            mat[8] = m31; mat[9] = m32; mat[10] = m33; mat[11] = m34;
            mat[12] = m41; mat[13] = m42; mat[14] = m43; mat[15] = m44;
    }

    Mat4(const float * m){
        for(unsigned int i = 0; i < 16; ++i){
            mat[i] = m[i];
        }
    }

    Mat4(const Mat4 & M) {
        for (unsigned int i = 0; i < 16; ++i) {
            mat[i] = M.mat[i];
        }
    }

    template <class A, class B, class C, class D>
    Mat4(const Vec4<A> & v1, const Vec4<B> & v2, const Vec4<C> & v3, const Vec4<D> & v4){
        mat[0] = v1.x; mat[1] = v1.y; mat[2] = v1.z; mat[3] = v1.t;
        mat[4] = v2.x; mat[5] = v2.y; mat[6] = v2.z; mat[7] = v2.t;
        mat[8] = v3.x; mat[9] = v3.y; mat[10] = v3.z; mat[11] = v3.t;
        mat[12] = v4.x; mat[13] = v4.y; mat[14] = v4.z; mat[15] = v4.t;
    };

    inline Mat4 identity(){
        return Mat4(true);
    }

    /*
     * Proxy for operator[][]
     */
    /*
    class Row{
    public :
        float * line;

        Row(const float & i) {line = i;}
        Row(float & i) : line(&i){}
        inline const float & operator[](const unsigned int & j) const {return line[j]; }
        inline float & operator[](const unsigned int & j) {return line[j]; }
    };
     */

    /*
     * Reader
     */
    inline const float & operator()(const unsigned int & i, const unsigned int & j) const { return mat[4*i + j]; }
    //inline Row operator[](const unsigned int & i) const { return Row(mat[4 * i]);}

    /*
     * Writer
     */
    inline float & operator()(const unsigned int & i, const unsigned int & j){ return mat[4 * i + j]; }
    //inline Row operator[](const unsigned int & i){ return Row(mat[4 * i]);}

    /*
     * other accessor
     * */

    operator const float*() const { return mat; }
    operator float*() { return mat; }

    /*
     * Binary operation with a vector
     */
    template <class T> friend inline Vec4f & operator*(const Mat4 & m, const Vec4<T> &v) {
        Vec4f result;
        result.x = v.x * m(0,0) + v.y * m(0,1) + v.z * m(0,2) + v.t * m(0,3);
        result.y = v.x * m(1,0) + v.y * m(1,1) + v.z * m(1,2) + v.t * m(1,3);
        result.z = v.x * m(2,0) + v.y * m(2,1) + v.z * m(2,2) + v.t * m(2,3);
        result.t = v.x * m(3,0) + v.y * m(3,1) + v.z * m(3,2) + v.t * m(3,3);
        return result;
    }

    template <class T> friend inline Vec4f & operator*(const Vec4<T> &v, const Mat4 & m){
        Vec4f result;
        result.x = v.x * m(0,0) + v.y * m(1,0) + v.z * m(2,0) + v.t * m(3,0);
        result.y = v.x * m(0,1) + v.y * m(1,1) + v.z * m(2,1) + v.t * m(3,1);
        result.z = v.x * m(0,2) + v.y * m(1,2) + v.z * m(2,2) + v.t * m(3,2);
        result.t = v.x * m(0,3) + v.y * m(1,3) + v.z * m(2,3) + v.t * m(3,3);
        return result;
    }

    /*
     * Binary operation with an other matrix
     */
    friend inline Mat4 operator+(const Mat4 & m1, const Mat4 & m2){
        Mat4 result;
        for(unsigned char i = 0; i < 16; ++i){
            result.mat[i] = m1.mat[i] + m2.mat[i];
        }
        return result;
    }

    friend inline Mat4 operator-(const Mat4 & m1, const Mat4 & m2){
        Mat4 result;
        for(unsigned char i = 0; i < 16; ++i){
            result.mat[i] = m1.mat[i] - m2.mat[i];
        }
        return result;
    }

    friend inline Mat4 operator*(const Mat4 & m1, const Mat4 & m2){
        Mat4 result;
        for (unsigned char i = 0; i < 16; ++i){
            float tmp = 0;
            for(unsigned char j = i%4; j < 16; ++j){
                for(unsigned char k = j%4; k < 16; k+=4) {
                    tmp += m1.mat[j] * m2.mat[k];
                }
            }
            result.mat[i] = tmp;
        }
        return result;
    }

    /*
     * Comparison operators
     */

    friend inline bool operator==(const Mat4 & m1, const Mat4 & m2){
        for(unsigned char i = 0; i < 16; ++i){
            if(m1.mat[i] != m2.mat[i]){
                return false;
            }
        }
        return true;
    }

    friend inline bool operator!=(const Mat4 & m1, const Mat4 & m2){
        return !(m1==m2);
    }

    /*
     * Binary operation with a scalar
     */
    template <class A> friend inline Mat4 operator*(const A & a, const Mat4 & m){
        Mat4 result;
        for(unsigned char i = 0; i < 16; ++i){
            result.mat[i] = m.mat[i] * a;
        }
        return result;
    }

    template <class A> friend inline Mat4 operator*(const Mat4 & m, const A & a){
        Mat4 result;
        for(unsigned char i = 0; i < 16; ++i){
            result.mat[i] = m.mat[i] * a;
        }
        return result;
    }

    /*
     * Unary operation
     */
    friend inline Mat4 operator-(const Mat4 & m){
        Mat4 result;
        for(unsigned char i = 0; i < 16; ++i){
            result.mat[i] = -m.mat[i];
        }
        return result;
    }

    /*
     * Affectation operationF
     */
    inline Mat4 operator=(const Mat4 & m){
        for(unsigned char i =0; i < 16; ++i){
            mat[i] = m.mat[i];
        }
        return *this;
    }

    inline Mat4 operator+=(const Mat4 & m){
        for(unsigned char i =0; i < 16; ++i){
            mat[i] += m.mat[i];
        }
        return *this;
    }

    inline Mat4 operator-=(const Mat4 & m){
        for(unsigned char i =0; i < 16; ++i){
            mat[i] -= m.mat[i];
        }
        return *this;
    }

    inline Mat4 operator*=(const Mat4 & m){
        *this = *this * m;
        return *this;
    }


    /*
     * Matrix operations
     */
    inline Mat4 transposed(){
        Mat4 result;
        for (unsigned char i = 0; i < 4; ++i){
            for(unsigned char j = 0; j < 4; ++j){
                result(i,j) = mat[j * 4 +i];
            }
        }
        return result;
    }

    /*
     * based on http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html
     */
    inline float determinant(){
    return mat[0]*mat[5]*mat[10]*mat[15] + mat[0]*mat[6]*mat[11]*mat[13] + mat[0]*mat[7]*mat[9]*mat[14] +
            mat[1]*mat[4]*mat[11]*mat[14] + mat[1]*mat[6]*mat[8]*mat[15] + mat[1]*mat[7]*mat[10]*mat[12] +
            mat[2]*mat[4]*mat[9]*mat[15] + mat[2]*mat[5]*mat[11]*mat[12] + mat[2]*mat[7]*mat[8]*mat[13] +
            mat[3]*mat[4]*mat[10]*mat[13] + mat[3]*mat[5]*mat[8]*mat[14] + mat[3]*mat[6]*mat[9]*mat[12]

           - mat[0]*mat[5]*mat[11]*mat[14] - mat[0]*mat[6]*mat[9]*mat[15] - mat[0]*mat[7]*mat[10]*mat[13]
            - mat[1]*mat[4]*mat[10]*mat[15] - mat[1]*mat[6]*mat[11]*mat[12] - mat[1]*mat[7]*mat[8]*mat[14]
            - mat[2]*mat[4]*mat[11]*mat[13] - mat[2]*mat[5]*mat[8]*mat[15] - mat[2]*mat[7]*mat[9]*mat[12]
            - mat[3]*mat[4]*mat[9]*mat[14] - mat[3]*mat[5]*mat[10]*mat[12] - mat[3]*mat[6]*mat[8]*mat[13];

    }

    inline Mat4 inverted(){
        Mat4 result;
        result.mat[0] = mat[5]*mat[10]*mat[15] + mat[6]*mat[11]*mat[13] + mat[7]*mat[9]*mat[14]
                    - mat[5]*mat[11]*mat[14] - mat[6]*mat[9]*mat[15] - mat[7]*mat[10]*mat[13];
        result.mat[1] = mat[1]*mat[11]*mat[14] + mat[2]*mat[9]*mat[15] + mat[3]*mat[10]*mat[13]
                    - mat[1]*mat[10]*mat[14] - mat[2]*mat[11]*mat[13] - mat[3]*mat[9]*mat[14];
        result.mat[2] = mat[1]*mat[6]*mat[15] + mat[2]*mat[7]*mat[13] + mat[3]*mat[5]*mat[14]
                    - mat[1]*mat[7]*mat[14] - mat[2]*mat[5]*mat[15] - mat[3]*mat[6]*mat[13];
        result.mat[3] = mat[1]*mat[7]*mat[10] + mat[2]*mat[5]*mat[11] + mat[3]*mat[6]*mat[9]
                    - mat[1]*mat[6]*mat[11] - mat[2]*mat[7]*mat[9] - mat[3]*mat[5]*mat[10];

        result.mat[4] = mat[4]*mat[11]*mat[14] + mat[6]*mat[8]*mat[15] + mat[7]*mat[10]*mat[12]
                    - mat[4]*mat[10]*mat[15] - mat[6]*mat[11]*mat[12] - mat[7]*mat[8]*mat[14];
        result.mat[5] = mat[0]*mat[10]*mat[15] + mat[2]*mat[11]*mat[12] + mat[3]*mat[8]*mat[14]
                    - mat[0]*mat[11]*mat[14] - mat[2]*mat[8]*mat[15] - mat[3]*mat[10]*mat[12];
        result.mat[6] = mat[0]*mat[7]*mat[14] + mat[2]*mat[4]*mat[15] + mat[3]*mat[6]*mat[12]
                    - mat[0]*mat[6]*mat[15] - mat[2]*mat[7]*mat[12] - mat[3]*mat[4]*mat[14];
        result.mat[7] = mat[0]*mat[6]*mat[11] + mat[2]*mat[7]*mat[8] + mat[3]*mat[4]*mat[10]
                    - mat[0]*mat[7]*mat[10] - mat[2]*mat[4]*mat[11] - mat[3]*mat[6]*mat[8];

        result.mat[8] = mat[4]*mat[9]*mat[15] + mat[5]*mat[11]*mat[12] + mat[7]*mat[8]*mat[13]
                    - mat[4]*mat[11]*mat[13] - mat[5]*mat[8]*mat[15] - mat[7]*mat[9]*mat[12];
        result.mat[9] = mat[0]*mat[11]*mat[13] + mat[1]*mat[8]*mat[15] + mat[3]*mat[9]*mat[12]
                    - mat[0]*mat[9]*mat[15] - mat[1]*mat[11]*mat[12] - mat[3]*mat[8]*mat[13];
        result.mat[10] = mat[0]*mat[5]*mat[15] + mat[1]*mat[7]*mat[12] + mat[3]*mat[4]*mat[13]
                    - mat[0]*mat[7]*mat[13] - mat[1]*mat[4]*mat[15] - mat[3]*mat[5]*mat[12];
        result.mat[11] = mat[0]*mat[7]*mat[9] + mat[1]*mat[4]*mat[11] + mat[3]*mat[5]*mat[8]
                    - mat[0]*mat[5]*mat[11] - mat[1]*mat[7]*mat[8] - mat[3]*mat[4]*mat[9];

        result.mat[12] = mat[4]*mat[10]*mat[13] + mat[5]*mat[8]*mat[14] + mat[6]*mat[9]*mat[12]
                    - mat[4]*mat[9]*mat[14] - mat[5]*mat[10]*mat[12] - mat[6]*mat[8]*mat[13];
        result.mat[13] = mat[0]*mat[9]*mat[14] + mat[1]*mat[10]*mat[12] + mat[2]*mat[8]*mat[13]
                    - mat[0]*mat[10]*mat[13] - mat[1]*mat[8]*mat[14] - mat[2]*mat[9]*mat[12];
        result.mat[14] = mat[0]*mat[6]*mat[13] + mat[1]*mat[4]*mat[14] + mat[2]*mat[5]*mat[14]
                    - mat[0]*mat[5]*mat[14] - mat[1]*mat[6]*mat[12] - mat[2]*mat[4]*mat[13];
        result.mat[15] = mat[0]*mat[5]*mat[10] + mat[1]*mat[6]*mat[8] + mat[2]*mat[4]*mat[9]
                    - mat[0]*mat[6]*mat[9] - mat[1]*mat[4]*mat[10] - mat[2]*mat[5]*mat[8];

        result = result * (pow(this->determinant(),-1));
        return result;
    }

    /*
     * Basic transformation
     */

    /*
     * Rotations
     */
    inline Mat4 RotateX(const float & x){
        *this *= Mat4(1, 0, 0, 0,
                      0, cosf(x), -sinf(x), 0,
                      0, sinf(x), cosf(x), 0,
                      0, 0, 0, 1);
        return *this;
    }

    inline Mat4 RotateY(const float & y){
        *this *= Mat4(cosf(y), 0, sinf(y), 0,
                      0, 1, 0, 0,
                      -sinf(y), 0, cosf(y), 0,
                      0, 0, 0, 1);
        return *this;
    }

    inline Mat4 RotateZ(const float & z){
        *this *= Mat4(cosf(z), -sinf(z), 0, 0,
                      sinf(z), cosf(z), 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1);
        return *this;
    }

    inline Mat4 Rotate(const float & x, const float & y, const float & z){
        RotateX(x).RotateY(y).RotateZ(z);
        return *this;
    }

    template <class A> inline Mat4 Rotate(const Vec3<A> & v){
        RotateX(v.x);
        RotateY(v.y);
        RotateZ(v.z);
        return *this;
    }

    /*
     * Translations
     */
    inline Mat4 TranslateX(const float & x){
        mat[3] += x;
        return *this;
    }

    inline Mat4 TranslateY(const float & y){
        mat[7] += 7;
        return *this;
    }

    inline Mat4 TranslateZ(const float & z){
        mat[11] += z;
        return *this;
    }

    inline Mat4 Translate(const float & x, const float & y, const float & z){
        TranslateX(x);
        TranslateY(y);
        TranslateZ(z);
        return *this;
    }
    template <class A> inline Mat4 Translate(const Vec3<A> & v){
        TranslateX(v.x);
        TranslateY(v.y);
        TranslateZ(v.z);
        return *this;
    }

    /*
     * Scale
     */
    inline Mat4 ScaleX(const float & x){
        *this *= Mat4(x, 0, 0, 0,
                        0, 1, 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1);
        return *this;
    }

    inline Mat4 ScaleY(const float & y){
        *this *= Mat4(1, 0, 0, 0,
                      0, y, 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1);
        return *this;
    }

    inline Mat4 ScaleZ(const float & z){
        *this *= Mat4(1, 0, 0, 0,
                      0, 1, 0, 0,
                      0, 0, z, 0,
                      0, 0, 0, 1);
        return *this;
    }

    inline Mat4 Scale(const float & x, const float & y, const float z){
        ScaleX(x);
        ScaleY(y);
        ScaleZ(z);
        return *this;
    }

    template <class A> inline Mat4 Scale(const Vec3<A> & v){
        ScaleX(v.x);
        ScaleY(v.y);
        ScaleZ(v.z);
        return *this;
    }

    /*
     * Stream
     */

    friend std :: istream & operator>>( std :: istream & stream, Mat4 & a ){
        for( unsigned char i = 0; i < 16; ++i ){
            stream >> a.mat[i];
        }
        return stream;
    }

    friend std :: ostream & operator<<( std :: ostream & stream, const Mat4 & a ){
        for( unsigned char i = 0; i < 16; ++i){
            stream << std :: setw(10) << a.mat[i] << " ";
            if ( !((i+1)%4) && (i!=15)) {
                stream << std :: endl;
            }
        }
        return stream;
    }
};

#endif //HELLO_WORLD_MAT4_H
