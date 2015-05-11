/* 
 * File:   SpriteList.hpp
 * Author: romain
 *
 * Created on 9 mars 2014, 12:35
 */

#ifndef SPRITELIST_HPP
#define	SPRITELIST_HPP

#pragma once
#include "Vertex.hpp"
#include "Sprite.hpp"

namespace NotEngine {
    
    namespace Graphic {
        
        class AbstractSpriteList {
            private:
                AbstractSpriteList(const AbstractSpriteList& copy);
                void operator=(AbstractSpriteList const&);
                
            protected:
                friend class Render2D;

                unsigned int maxVertices;
                unsigned int numVertices;
                VertexCUV*   vertices;

                AbstractSpriteList (unsigned int maxVertices);
            
            public:
                virtual ~AbstractSpriteList ();

                void beginUpdate  ();
                void finishUpdate ();
        };

        class SpriteList : public AbstractSpriteList {
            public:
                static const unsigned int VERTICES_PER_SPRITE = 2;

                SpriteList(unsigned int spriteCapacity);
                virtual ~SpriteList();
                
                bool put(const Sprite& sprite);
        };        
        
        class SpriteListRS : public AbstractSpriteList {
            public:
                static const unsigned int VERTICES_PER_SPRITE = 6;

                SpriteListRS(unsigned int spriteCapacity);
                virtual ~SpriteListRS();
                
                bool put(const SpriteRS& spriteRS);
        };        

    } // namespace Graphic
    
} // namespace NotEngine

#endif	/* SPRITELIST_HPP */

