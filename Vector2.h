#ifndef VECTOR2_H
#define VECTOR2_H

#include "Math2.h"
#include <iostream>

class Vector2
{
    friend std::ostream& operator<<(std::ostream& output, const Vector2& v);

    public:
            Vector2();
            Vector2(float x, float y);

            void Rotate(float angle);
            void Zero();
            void Normalize();

            float GetAngle() const;
            float Length() const;
            bool IsZero();
            float DotProduct(const Vector2& v);
            static float DotProduct(const Vector2& v1, const Vector2& v2);

            // Operators
            void operator= (const Vector2& v);

            Vector2 operator+ (const Vector2* v);

            Vector2 operator+ (const Vector2& v);
            Vector2 operator- (const Vector2& v);
            Vector2 operator* (const Vector2& v);
            Vector2 operator/ (const Vector2& v);

            void operator+= (const Vector2& v);
            void operator-= (const Vector2& v);
            void operator*= (const Vector2& v);
            void operator/= (const Vector2& v);

            Vector2 operator+ (float f);
            Vector2 operator- (float f);
            Vector2 operator* (float f);
            Vector2 operator/ (float f);

            void operator+= (float f);
            void operator-= (float f);
            void operator*= (float f);
            void operator/= (float f);

            bool operator== (const Vector2& v);
            bool operator!= (const Vector2& v);

    public:
            float x;
            float y;
};

#endif
