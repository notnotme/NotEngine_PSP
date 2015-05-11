/* 
 * File:   Render2D.hpp
 * Author: romain
 *
 * Created on 9 mars 2014, 08:29
 */

#ifndef RENDER2D_HPP
#define	RENDER2D_HPP

#pragma once
#include <psptypes.h>
#include "Sprite.hpp"
#include "SpriteList.hpp"
#include "../system/Singleton.hpp"

namespace NotEngine {
    
    namespace Graphic {
        
        /**
         * A simple 2D Renderer and blitter.
         * 
         * Capable of drawing some simple 2D shapes and
         * some Sprites call by call or by batching.
         * 
         * This is just a renderer class, it doesn't care of the current
         * rendering state (ex, matrices, texture enable, GU vertice color, blending and so...)
         * 
         * The blitter doesn't car at all about matrices, changing them before blitting will not
         * change anything, but the sprite use the current GU matrices to render the Sprite's
         * shape on screen.
         */
        class Render2D : public System::Singleton<Render2D> {
            protected:
                friend class System::Singleton<Render2D>;
                Render2D();

            public:
                virtual ~Render2D();
                
                /**
                 * Common function to blit on screen. This use GU_TRANSFORM_2D
                 * so matrix synchronisation isn't necessary
                 */
                void blit(const ScePspSVector4& quad);
                void blit(const ScePspSVector4& quad, unsigned int color);
                void blit(const ScePspSVector4& quad, const ScePspSVector4& uv);
                void blit(const ScePspSVector4& quad, const ScePspSVector4& uv, unsigned int color);

                void blit(const ScePspFVector4& quad);
                void blit(const ScePspFVector4& quad, unsigned int color);
                void blit(const ScePspFVector4& quad, const ScePspFVector4& uv);
                void blit(const ScePspFVector4& quad, const ScePspFVector4& uv, unsigned int color);

                /**
                 * Functions that blit on screen, current matrices will apply to final rendering,
                 * you have to be sure that all the current GU matrices are in cache or it will
                 * not draw anything.
                 */
                void render(const Sprite& sprite);
                void render(const SpriteRS& spriteRS);

                void render(const SpriteList* list);
                void render(const SpriteListRS* listRS);
        };

    } // namespace Graphic

} // namespace NotEngine

#endif	/* RENDER2D_HPP */

