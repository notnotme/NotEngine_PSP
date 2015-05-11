/* 
 * File:   Sprite.hpp
 * Author: romain
 *
 * Created on 9 mars 2014, 08:55
 */

#ifndef SPRITE_HPP
#define	SPRITE_HPP

#pragma once
#include <psptypes.h>

/**
 * This file describe all Sprite struct used by the Render2D
 */
namespace NotEngine {
    
    namespace Graphic {
        
        struct Sprite {
            ScePspFVector3 position;
            ScePspFVector2 size;
            ScePspFVector4 uv;
            unsigned int   tint;
            
            Sprite() {
                position = (ScePspFVector3) {0,0,0};
                size     = (ScePspFVector2) {32,32};
                uv       = (ScePspFVector4) {0,0,1,1};
                tint     = 0xFFFFFFFF;
            }
            
            Sprite(ScePspFVector3 position, ScePspFVector2 size, ScePspFVector4 uv, unsigned int tint) :
            position(position), size(size), uv(uv), tint(tint) {
            }
        };
        
        struct SpriteRS : Sprite {
            ScePspFVector2 scale;
            float          angle;
            
            SpriteRS() : Sprite() {
                scale = (ScePspFVector2) {1,1};
                angle = 0;
            }

            SpriteRS(ScePspFVector3 position, ScePspFVector2 size, ScePspFVector4 uv, unsigned int tint, ScePspFVector2 scale, float angle)
            : Sprite(position, size, uv, tint), scale(scale), angle(angle) {
            }
        };

    } // namespace Graphic

} // namespace NotEngine

#endif	/* SPRITE_HPP */

