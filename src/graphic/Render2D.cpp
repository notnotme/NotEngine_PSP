 /*
  * File:   Render2D.cpp
  * Author: romain
  * 
  * Created on 9 mars 2014, 08:29
  */

#include "Render2D.hpp"

#include <pspmath.h>
#include "../math/MathUtils.hpp"
#include "Vertex.hpp"
#include "BaseRender.hpp"

namespace NotEngine {
    
    namespace Graphic {
        
        Render2D::Render2D() : System::Singleton<Render2D>() {
        }
        
        Render2D::~Render2D() {
        }
        
        void Render2D::blit(const ScePspSVector4& quad) {
            SVertex* svertices = (SVertex*) BaseRender::instance()->getMemory(2 * sizeof(SVertex));

            svertices[0].p.x = quad.x;
            svertices[0].p.y = quad.y;
            svertices[0].p.z = 0;

            svertices[1].p.x = quad.x+quad.z;
            svertices[1].p.y = quad.y+quad.w;
            svertices[1].p.z = 0;

            sceGuDrawArray (GU_SPRITES, GU_VERTEX_16BIT|GU_TRANSFORM_2D, 2, 0, svertices);
        }

        void Render2D::blit(const ScePspSVector4& quad, unsigned int color) {
            SVertexC* svertices = (SVertexC*) BaseRender::instance()->getMemory(2 * sizeof(SVertexC));

            svertices[0].color = color;
            svertices[0].p.x = quad.x;
            svertices[0].p.y = quad.y;
            svertices[0].p.z = 0;

            svertices[1].color = color;
            svertices[1].p.x = quad.x+quad.z;
            svertices[1].p.y = quad.y+quad.w;
            svertices[1].p.z = 0;

            sceGuDrawArray (GU_SPRITES, GU_COLOR_8888|GU_VERTEX_16BIT|GU_TRANSFORM_2D, 2, 0, svertices);
        }

        void Render2D::blit(const ScePspSVector4& quad, const ScePspSVector4& uv) {
            SVertexUV* svertices = (SVertexUV*) BaseRender::instance()->getMemory(2 * sizeof(SVertexUV));

            svertices[0].uv.x = uv.x; 
            svertices[0].uv.y = uv.y;
            svertices[0].p.x = quad.x; 
            svertices[0].p.y = quad.y; 
            svertices[0].p.z = 0;

            svertices[1].uv.x = uv.z;
            svertices[1].uv.y = uv.w;
            svertices[1].p.x = quad.x+quad.z;
            svertices[1].p.y = quad.y+quad.w;
            svertices[1].p.z = 0;

            sceGuDrawArray (GU_SPRITES, GU_TEXTURE_16BIT|GU_VERTEX_16BIT|GU_TRANSFORM_2D, 2, 0, svertices);
        }

        void Render2D::blit(const ScePspSVector4& quad, const ScePspSVector4& uv, unsigned int color) {
            SVertexCUV* svertices = (SVertexCUV*) BaseRender::instance()->getMemory(2 * sizeof(SVertexCUV));

            svertices[0].uv.x = uv.x; 
            svertices[0].uv.y = uv.y;
            svertices[0].color = color;
            svertices[0].p.x = quad.x; 
            svertices[0].p.y = quad.y; 
            svertices[0].p.z = 0;

            svertices[1].uv.x = uv.z; 
            svertices[1].uv.y = uv.w;
            svertices[1].color = color;
            svertices[1].p.x = quad.x+quad.z;
            svertices[1].p.y = quad.y+quad.w; 
            svertices[1].p.z = 0;

            sceGuDrawArray (GU_SPRITES, GU_TEXTURE_16BIT|GU_COLOR_8888|GU_VERTEX_16BIT|GU_TRANSFORM_2D, 2, 0, svertices);
        }

        void Render2D::blit(const ScePspFVector4& quad) {
            Vertex* fvertices = (Vertex*) BaseRender::instance()->getMemory(2 * sizeof(Vertex));

            fvertices[0].p.x = quad.x;
            fvertices[0].p.y = quad.y;
            fvertices[0].p.z = 0;

            fvertices[1].p.x = quad.x+quad.z;
            fvertices[1].p.y = quad.y+quad.w;
            fvertices[1].p.z = 0;

            sceGuDrawArray (GU_SPRITES, GU_VERTEX_32BITF|GU_TRANSFORM_2D, 2, 0, fvertices);
        }

        void Render2D::blit(const ScePspFVector4& quad, unsigned int color) {
            VertexC* fvertices = (VertexC*) BaseRender::instance()->getMemory(2 * sizeof(VertexC));

            fvertices[0].color = color;
            fvertices[0].p.x = quad.x; 
            fvertices[0].p.y = quad.y; 
            fvertices[0].p.z = 0;

            fvertices[1].color = color;
            fvertices[1].p.x = quad.x+quad.z;
            fvertices[1].p.y = quad.y+quad.w;
            fvertices[1].p.z = 0;

            sceGuDrawArray (GU_SPRITES, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_2D, 2, 0, fvertices);
        }

        void Render2D::blit(const ScePspFVector4& quad, const ScePspFVector4& uv) {
            VertexUV* fvertices = (VertexUV*) BaseRender::instance()->getMemory(2 * sizeof(VertexUV));

            fvertices[0].uv.x = uv.x;
            fvertices[0].uv.y = uv.y;
            fvertices[0].p.x = quad.x; 
            fvertices[0].p.y = quad.y; 
            fvertices[0].p.z = 0;

            fvertices[1].uv.x = uv.z; 
            fvertices[1].uv.y = uv.w;
            fvertices[1].p.x = quad.x+quad.z; 
            fvertices[1].p.y = quad.y+quad.w; 
            fvertices[1].p.z = 0;

            sceGuDrawArray (GU_SPRITES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_2D, 2, 0, fvertices);
        }

        void Render2D::blit(const ScePspFVector4& quad, const ScePspFVector4& uv, unsigned int color) {
            VertexCUV* fvertices = (VertexCUV*) BaseRender::instance()->getMemory(2 * sizeof(VertexCUV));

            fvertices[0].uv.x = uv.x; 
            fvertices[0].uv.y = uv.y;
            fvertices[0].color = color;
            fvertices[0].p.x = quad.x; 
            fvertices[0].p.y = quad.y; 
            fvertices[0].p.z = 0;

            fvertices[1].uv.x = uv.z; 
            fvertices[1].uv.y = uv.w;
            fvertices[1].color = color;
            fvertices[1].p.x = quad.x+quad.z; 
            fvertices[1].p.y = quad.y+quad.w; 
            fvertices[1].p.z = 0;

            sceGuDrawArray (GU_SPRITES, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_2D, 2, 0, fvertices);
        }


        void Render2D::render(const Sprite& sprite) {
            VertexCUV* fvertices = (VertexCUV*) BaseRender::instance()->getMemory(2 * sizeof(VertexCUV));

            fvertices[0].p.x        = sprite.position.x;
            fvertices[0].p.y        = sprite.position.y;
            fvertices[0].p.z        = sprite.position.z;
            fvertices[0].uv.x       = sprite.uv.x;
            fvertices[0].uv.y       = sprite.uv.y;
            fvertices[0].color      = sprite.tint;

            fvertices[1].p.x        = sprite.position.x + sprite.size.x;
            fvertices[1].p.y        = sprite.position.y + sprite.size.y;
            fvertices[1].p.z        = sprite.position.z;
            fvertices[1].uv.x       = sprite.uv.z;
            fvertices[1].uv.y       = sprite.uv.w;
            fvertices[1].color      = sprite.tint;

            sceGuDrawArray (GU_SPRITES, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 2, 0, fvertices);
        }

        void Render2D::render(const SpriteRS& spriteRS) {
            VertexCUV* fvertices = (VertexCUV*) BaseRender::instance()->getMemory(4 * sizeof(VertexCUV));

            float sinn,coss; // add 90 or the angle will be incorrect!
            vfpu_sincos((spriteRS.angle + 90.0f) * Math::MathUtils::PI180, &sinn, &coss);

            ScePspFVector2 size = {(spriteRS.size.x*spriteRS.scale.x)/2, (spriteRS.size.y*spriteRS.scale.y)/2};
            
            float a = -size.x * sinn;
            float b =  size.x * coss;
            float f = -size.y * sinn;
            float g =  size.y * coss;

            fvertices[0].p.x        = (a +-g) + spriteRS.position.x;
            fvertices[0].p.y        = (b + f) + spriteRS.position.y;
            fvertices[0].p.z        = spriteRS.position.z;
            fvertices[0].uv.x       = spriteRS.uv.x;
            fvertices[0].uv.y       = spriteRS.uv.y;
            fvertices[0].color      = spriteRS.tint;

            fvertices[1].p.x        = (-a +-g) + spriteRS.position.x;
            fvertices[1].p.y        = (-b + f) + spriteRS.position.y;
            fvertices[1].p.z        = spriteRS.position.z;
            fvertices[1].uv.x       = spriteRS.uv.z;
            fvertices[1].uv.y       = spriteRS.uv.y;
            fvertices[1].color      = spriteRS.tint;

            fvertices[2].p.x        = (-a + g) + spriteRS.position.x;
            fvertices[2].p.y        = (-b +-f) + spriteRS.position.y;
            fvertices[2].p.z        = spriteRS.position.z;
            fvertices[2].uv.x       = spriteRS.uv.z;
            fvertices[2].uv.y       = spriteRS.uv.w;
            fvertices[2].color      = spriteRS.tint;

            fvertices[3].p.x        = (a + g) + spriteRS.position.x;
            fvertices[3].p.y        = (b +-f) + spriteRS.position.y;
            fvertices[3].p.z        = spriteRS.position.z;
            fvertices[3].uv.x       = spriteRS.uv.x;
            fvertices[3].uv.y       = spriteRS.uv.w;
            fvertices[3].color      = spriteRS.tint;

            sceGuDrawArray (GU_TRIANGLE_FAN, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 4, 0, fvertices);
        }
        
        void Render2D::render(const SpriteList* list) {
            sceGuDrawArray (GU_SPRITES, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, list->numVertices, 0, list->vertices);
        }

        void Render2D::render(const SpriteListRS* listRS) {
            sceGuDrawArray (GU_TRIANGLES, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, listRS->numVertices, 0, listRS->vertices);
        }
        
    } // namespace Graphics
    
} // namespace NotEngine
