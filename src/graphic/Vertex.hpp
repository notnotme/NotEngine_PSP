/* 
 * File:   Vertex.hpp
 * Author: romain
 *
 * Created on 8 mars 2014, 21:11
 */

#ifndef VERTEX_HPP
#define	VERTEX_HPP

#pragma once
#include <psptypes.h>

/**
 * This file contain all vertex struct used by the engine
 */
namespace NotEngine {
    
    namespace Graphic {

        struct Vertex {
            ScePspFVector3 p;
        };

        struct VertexUV {
            ScePspFVector2 uv;
            ScePspFVector3 p;
        };

        struct VertexC {
            unsigned int color;
            ScePspFVector3 p;
        };

        struct VertexCUV {
            ScePspFVector2 uv;
            unsigned int color;
            ScePspFVector3 p;
        };

        struct SVertex {
            ScePspSVector3 p;
        };

        struct SVertexUV {
            ScePspSVector2 uv;
            ScePspSVector3 p;
        };

        struct SVertexC {
            unsigned int color;
            ScePspSVector3 p;
        };

        struct SVertexCUV {
            ScePspSVector2 uv;
            unsigned int color;
            ScePspSVector3 p;
        };
        
    } // namespace Graphic

} // namespace NotEngine

#endif	/* VERTEX_HPP */

