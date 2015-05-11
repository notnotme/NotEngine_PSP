/* 
 * File:   SpriteList.cpp
 * Author: romain
 * 
 * Created on 9 mars 2014, 12:35
 */

#include "SpriteList.hpp"

#include <malloc.h>
#include <psputils.h>
#include <pspmath.h>
#include "../math/MathUtils.hpp"

namespace NotEngine {
    
    namespace Graphic {
        
        AbstractSpriteList::AbstractSpriteList(unsigned int maxVertices) : maxVertices(maxVertices), numVertices(0), vertices(0) {
            vertices = (VertexCUV*) memalign(16, maxVertices * sizeof(VertexCUV));
        }

        AbstractSpriteList::~AbstractSpriteList() {
            if(vertices != 0)
                free(vertices);
        }

        void AbstractSpriteList::beginUpdate() {
            numVertices = 0;
        }

        void AbstractSpriteList::finishUpdate() {
            sceKernelDcacheWritebackRange(vertices, numVertices*sizeof(VertexCUV));
        }
        
        SpriteList::SpriteList(unsigned int tileCapacity) : AbstractSpriteList(tileCapacity * VERTICES_PER_SPRITE) {
        }

        SpriteList::~SpriteList() {
        }

        bool SpriteList::put(const Sprite& sprite) {
            if(vertices == 0 || numVertices >= maxVertices)
                return false;

            vertices[numVertices].p.x        = sprite.position.x;
            vertices[numVertices].p.y        = sprite.position.y;
            vertices[numVertices].p.z        = sprite.position.z;
            vertices[numVertices].uv.x       = sprite.uv.x;
            vertices[numVertices].uv.y       = sprite.uv.y;
            vertices[numVertices].color      = sprite.tint;
            numVertices++;

            vertices[numVertices].p.x        = sprite.position.x + sprite.size.x;
            vertices[numVertices].p.y        = sprite.position.y + sprite.size.y;
            vertices[numVertices].p.z        = sprite.position.z;
            vertices[numVertices].uv.x       = sprite.uv.z;
            vertices[numVertices].uv.y       = sprite.uv.w;
            vertices[numVertices].color      = sprite.tint;
            numVertices++;
            
            return true;
        }

        SpriteListRS::SpriteListRS(unsigned int spriteCapacity) : AbstractSpriteList(spriteCapacity * VERTICES_PER_SPRITE) {
        }

        SpriteListRS::~SpriteListRS() {
        }
        
        bool SpriteListRS::put(const SpriteRS& spriteRS) {
            if(vertices == 0 || numVertices >= maxVertices)
                return false;

            float sinn,coss; // add 90 or the angle will be incorrect!
            vfpu_sincos((spriteRS.angle + 90.0f) * Math::MathUtils::PI180, &sinn, &coss);

            ScePspFVector2 size;
            size = (ScePspFVector2) {(spriteRS.size.x*spriteRS.scale.x)/2, (spriteRS.size.y*spriteRS.scale.y)/2};
            
            float a = -size.x * sinn;
            float b =  size.x * coss;
            float f = -size.y * sinn;
            float g =  size.y * coss;

            vertices[numVertices].p.x        = (a - g) + spriteRS.position.x;
            vertices[numVertices].p.y        = (b + f) + spriteRS.position.y;
            vertices[numVertices].p.z        = spriteRS.position.z;
            vertices[numVertices].uv.x       = spriteRS.uv.x;
            vertices[numVertices].uv.y       = spriteRS.uv.y;
            vertices[numVertices].color      = spriteRS.tint;
            numVertices++;

            vertices[numVertices].p.x        = (-a  -g) + spriteRS.position.x;
            vertices[numVertices].p.y        = (-b + f) + spriteRS.position.y;
            vertices[numVertices].p.z        = spriteRS.position.z;
            vertices[numVertices].uv.x       = spriteRS.uv.z;
            vertices[numVertices].uv.y       = spriteRS.uv.y;
            vertices[numVertices].color      = spriteRS.tint;
            numVertices++;

            vertices[numVertices].p.x        = (-a + g) + spriteRS.position.x;
            vertices[numVertices].p.y        = (-b - f) + spriteRS.position.y;
            vertices[numVertices].p.z        = spriteRS.position.z;
            vertices[numVertices].uv.x       = spriteRS.uv.z;
            vertices[numVertices].uv.y       = spriteRS.uv.w;
            vertices[numVertices].color      = spriteRS.tint;
            numVertices++;

            vertices[numVertices] = vertices[numVertices-3];
            numVertices++;

            vertices[numVertices] = vertices[numVertices-2];
            numVertices++;

            vertices[numVertices].p.x        = (a + g) + spriteRS.position.x;
            vertices[numVertices].p.y        = (b - f) + spriteRS.position.y;
            vertices[numVertices].p.z        = spriteRS.position.z;
            vertices[numVertices].uv.x       = spriteRS.uv.x;
            vertices[numVertices].uv.y       = spriteRS.uv.w;
            vertices[numVertices].color      = spriteRS.tint;
            numVertices++;
            
            return true;
        }

    } // namespace Graphic
    
} // namespace NotEngine