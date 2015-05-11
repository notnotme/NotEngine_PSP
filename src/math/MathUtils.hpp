/* 
 * File:   MathUtils.hpp
 * Author: romain
 *
 * Created on 9 mars 2014, 10:42
 */

#ifndef MATHUTILS_HPP
#define	MATHUTILS_HPP

#pragma once
#include <psptypes.h>
#include <pspgu.h>

namespace NotEngine {
    
    namespace Math {
        
        /**
         * VERY simple math utils.
         */
        class MathUtils {
            private:
                MathUtils();

            public:
                /// Well..
                static const float PI180 = GU_PI / 180;
                
                static float radians    (float degree);
                static float clamp      (float x, float min, float max);
                static float smoothstep (float edge0, float edge1, float x);
                
                static float magnitude(const ScePspFVector3 vector);
                static void subtract(ScePspFVector3& dest, const ScePspFVector3& v1, const ScePspFVector3& v2);
                static void add(ScePspFVector3& dest, const ScePspFVector3& v1, const ScePspFVector3& v2);
                static void scale(ScePspFVector3& vector, float value);
                static void normalize(ScePspFVector3& vector);
        };

    } // namespace Math

} // namespace NotEngine

#endif	/* MATHUTILS_HPP */
