/* 
 * File:   BaseRender.hpp
 * Author: romain
 *
 * Created on 8 mars 2014, 18:12
 */

#ifndef BASERENDER_HPP
#define	BASERENDER_HPP

#pragma once
#include <stdlib.h>
#include <pspgu.h>
#include "../system/Singleton.hpp"


#define RGB16(r,v,b) ((((b)>>3)<<11) | (((v)>>2)<<5) | ((r)>>3))
#define RGBA(r, v, b, a) ((r) | ((v)<<8) | ((b)<<16) | ((a)<<24))

namespace NotEngine {
    
    namespace Graphic {

        /**
         * Base class to manage the graphics subsystem
         * 
         * Important hint:
         * Much of GU command must be called inside a list. That involve
         * calling start() and finish() between each gu call batch
         */
        class BaseRender : public System::Singleton<BaseRender> {
            private:
                /// Default GU list (Does it act like the WII fifo?)
                unsigned int* guList;
                
                /// Double buffer for double buffer rendering
                void* framebuffer[2];
               
                /// The depth buffer
                void*  depthbuffer;

                /// Used to keep trace of the current framebuffer used
                void* currentFramebuffer;
                
                /// Keep trace of the framebuffer format
                unsigned int framebufferFormat;

        protected:
                friend class System::Singleton<BaseRender>;
                BaseRender();

            public:
                /**
                 * Define some common list size.
                 * The more you send gu commands more you need a big list
                 */
                static const unsigned int TINY_LIST_SIZE    =  64 * 1024;
                static const unsigned int DEFAULT_LIST_SIZE = 256 * 1024;
                static const unsigned int BIG_LIST_SIZE     = 512 * 1024;

                /**
                 * Define some default framebuffer related value
                 */
                static const unsigned int   FRAMEBUFFER_STRIDE = 512;
                static const unsigned int   SCREEN_WIDTH       = 480;
                static const unsigned int   SCREEN_HEIGHT      = 272;
                static const unsigned int   SCREEN_HALF_WIDTH  = 480/2;
                static const unsigned int   SCREEN_HALF_HEIGHT = 272/2;
                static const float          SCREEN_ASPECT      = 480.0f/272.0f;

                virtual ~BaseRender();
                
                /// Return the amount of available VRAM
                size_t getVramAvail ();
                
                /// Allocate some VRAM return the pointer
                void* getVram (size_t size);

                /// Free some previously allocated VRAM memory
                void freeVram (void* ptr);

                /// Return the amount of memory (in bytes) needed for the corresponding width*height*fmt
                unsigned int getMemorySize (unsigned int width, unsigned int height, unsigned int fmt);

                /// Initialize GU
                bool initialize (unsigned int fbFmt = GU_PSM_5650, size_t listSize = DEFAULT_LIST_SIZE);

                /// Shutdown GU
                void shutdown ();

                /// Swap the current framebuffer
                void swapBuffers ();

                /// Return the current framebufer in use
                void* getFramebuffer ();
                
                /// Return the framebuffer format
                unsigned int getFramebufferFmt ();

                /// Start filling the default display list
                void start ();
                
                /// Start filling a new guList
                void start (unsigned int mode, unsigned int* list);
                
                /// Finish the current guList
                void finish ();
                
                /// Sync the current list
                void sync (unsigned int mode = 0, unsigned int what = 0);
                
                /// Wait for the next Vertical Retrace
                void waitVBlank ();
                
                /// Change the current drawbuffer to another one
                void drawBufferList (unsigned int fbFmt, void* fbPtr, unsigned int fbStride);

                /// Change the current drawbuffer to the default framebuffer
                void drawBufferList ();

                /// Return some aligned memory from current display list
                void* getMemory (size_t size);

                /// Call a previously filled guList
                void callList (const unsigned int* list);

                /// Set a new gu viewport
                void viewport (unsigned int width = SCREEN_WIDTH, unsigned int height = SCREEN_HEIGHT);
        };
        
    } // namespace Graphic
    
} // namespace NotEngine

#endif	/* BASERENDER_HPP */
