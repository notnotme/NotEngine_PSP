/* 
 * File:   BaseRender.cpp
 * Author: romain
 * 
 * Created on 8 mars 2014, 18:12
 */

#include "BaseRender.hpp"

#include <malloc.h>
#include <vram.h>
#include <pspdisplay.h>

namespace NotEngine {

    namespace Graphic {

        BaseRender::BaseRender() : System::Singleton<BaseRender>(), guList(0), depthbuffer(0), currentFramebuffer(0) {
            // Disable warning
            framebuffer[0] = 0;
            framebuffer[1] = 0;
        }

        BaseRender::~BaseRender() {
        }
        
        size_t BaseRender::getMemorySize(unsigned int width, unsigned int height, unsigned int pfmt) {
            switch (pfmt) {
                case GU_PSM_T4:
                    return (width * height) >> 1;

                case GU_PSM_T8:
                    return width * height;

                case GU_PSM_5650:
                case GU_PSM_5551:
                case GU_PSM_4444:
                case GU_PSM_T16:
                    return 2 * width * height;

                case GU_PSM_8888:
                case GU_PSM_T32:
                    return 4 * width * height;

                default:
                    return 0;
            }
        }

        bool BaseRender::initialize(unsigned int fbFmt, size_t listSize) {
            // Get some vram for the framebuffers
            framebufferFormat  = fbFmt;
            framebuffer[0]     = vrelptr(getVram(getMemorySize(FRAMEBUFFER_STRIDE, SCREEN_HEIGHT, framebufferFormat)));
            framebuffer[1]     = vrelptr(getVram(getMemorySize(FRAMEBUFFER_STRIDE, SCREEN_HEIGHT, framebufferFormat)));
            depthbuffer        = vrelptr(getVram(getMemorySize(FRAMEBUFFER_STRIDE, SCREEN_HEIGHT, GU_PSM_4444))); // cannot be changed?
            currentFramebuffer = framebuffer[0];
            
            // Initialize the default display list
            guList = (unsigned int*) memalign(16, listSize);
            if(guList == 0)
                return false;

            // Initialize GU with normal call (no signals)
            sceGuInit();
            sceGuCallMode(0);

            start();
                // Set up the framebuffers and default viewport
                sceGuDrawBuffer  (framebufferFormat, framebuffer[0], FRAMEBUFFER_STRIDE);
                sceGuDispBuffer  (SCREEN_WIDTH, SCREEN_HEIGHT, framebuffer[1], FRAMEBUFFER_STRIDE);
                sceGuDepthBuffer (depthbuffer, FRAMEBUFFER_STRIDE);
                viewport         ();

                // Set some default render states
                sceGuFrontFace   (GU_CW);
                sceGuShadeModel  (GU_SMOOTH);

                sceGuDepthFunc  (GU_GEQUAL);
                sceGuDepthRange (0xFFFF, 0x0000); // inverse from OGL
                sceGuClearDepth (0x00);
                
                sceGuEnable     (GU_DEPTH_TEST);
                sceGuEnable     (GU_ALPHA_TEST);
                sceGuAlphaFunc  (GU_GREATER, 0, 0xFF);
                
                sceGuEnable    (GU_SCISSOR_TEST);
                sceGuEnable    (GU_CULL_FACE);
                sceGuEnable    (GU_CLIP_PLANES);
                
                sceGuTexScale  (1.0f, 1.0f);
                sceGuTexOffset (0.0f, 0.0f);
            finish();
            sync();
            
            sceGuDisplay (GU_TRUE);
            return true;
        }
        
       void BaseRender::shutdown() {
            sceGuTerm();
            if(guList != 0)
                free(guList);

            freeVram(framebuffer[0]);
            freeVram(framebuffer[1]);
            freeVram(depthbuffer);
        }

        void BaseRender::viewport(unsigned int width, unsigned int height) {
            sceGuOffset   (2048 - (width/2), 2048 - (height/2));
            sceGuViewport (2048, 2048, width, height);
            sceGuScissor  (0, 0, width, height);
        }
        
        void BaseRender::swapBuffers() {
            currentFramebuffer = sceGuSwapBuffers();
        }

        void* BaseRender::getFramebuffer() {
            return currentFramebuffer;
        }

         unsigned int BaseRender::getFramebufferFmt() {
            return framebufferFormat;
        }

        void BaseRender::start() {
            sceGuStart(GU_DIRECT, guList);
        }

        void BaseRender::start(unsigned int mode, unsigned int* list) {
            sceGuStart(mode, list);
        }

        void BaseRender::finish() {
            sceGuFinish();
        }
        
         size_t BaseRender::getVramAvail() {
            return vmemavail();
        }

        void* BaseRender::getVram(size_t size) {
            return valloc(size);
        }

        void BaseRender::freeVram(void* ptr) {
            vfree(ptr);
        }
        
        void BaseRender::sync(unsigned int mode, unsigned int what) {
            sceGuSync(mode, what);
        }

        void BaseRender::waitVBlank() {
            sceDisplayWaitVblankStart();
        }

        void BaseRender::drawBufferList() {
            sceGuDrawBufferList	(framebufferFormat, currentFramebuffer, FRAMEBUFFER_STRIDE);	 
        }

        void BaseRender::drawBufferList(unsigned int fbFmt,void* framebuffer, unsigned int fbStride) {
            sceGuDrawBufferList	(fbFmt, framebuffer, fbStride);	 
        }

        void* BaseRender::getMemory(size_t size) {
            return sceGuGetMemory(size);
        }

        void BaseRender::callList(const unsigned int* list) {
            sceGuCallList(list);
        }
        
    } // namespace Graphics
    
} // namespace NotEngine
