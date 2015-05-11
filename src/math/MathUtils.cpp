/* 
 * File:   MathUtils.cpp
 * Author: romain
 * 
 * Created on 11 mars 2014, 19:37
 */

#include "MathUtils.hpp"

#include <math.h>

namespace NotEngine {
    
    namespace Math {
        
        float MathUtils::radians(float degree) {
            return degree * PI180;
        }
        
        
        float MathUtils::clamp(float x, float min, float max) {
            return x < min ? min : (x > max ? max : x);
        }


        float MathUtils::smoothstep(float edge0, float edge1, float x) {
            float t = clamp((x - edge0) / (edge1 - edge0), 0, 1);
            return t * t * (3 - 2 * t);
        }
        
        void MathUtils::subtract(ScePspFVector3& dest, const ScePspFVector3& v1, const ScePspFVector3& v2) {
            dest.x = v1.x - v2.x;
            dest.y = v1.y - v2.y;
            dest.z = v1.z - v2.z;
        }

        void MathUtils::add(ScePspFVector3& dest, const ScePspFVector3& v1, const ScePspFVector3& v2) {
            dest.x = v1.x + v2.x;
            dest.y = v1.y + v2.y;
            dest.z = v1.z + v2.z;
        }

        void MathUtils::scale(ScePspFVector3& vector, float value) {
            vector.x *= value;
            vector.y *= value;
            vector.z *= value;
        }
        
        float MathUtils::magnitude(const ScePspFVector3 vector) {
            return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
        }
        
        void MathUtils::normalize(ScePspFVector3& vector) {
            float length = MathUtils::magnitude(vector);
            if(length != 0){
                vector.x /= length;
                vector.y /= length;
                vector.z /= length;
            }
        }
    }
}

