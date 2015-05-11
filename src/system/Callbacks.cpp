/* 
 * File:   Callbacks.cpp
 * Author: romain
 * 
 * Created on 8 mars 2014, 21:27
 */

#include "Callbacks.hpp"

#include <psploadexec.h>
#include <pspthreadman.h>

namespace NotEngine {
    
    namespace System {
        
        bool Callbacks::exitRequest = false;
        
        Callbacks::Callbacks() : System::Singleton<Callbacks>() {
        }

        Callbacks::~Callbacks() {
        }

        bool Callbacks::isRunning() {
            return !exitRequest;
        }

        int Callbacks::exitCallback(int arg1, int arg2, void *common) { 
            exitRequest = true; 
            return 0; 
        } 

        int Callbacks::callbackThread(SceSize args, void *argp) { 
            int callbackID = sceKernelCreateCallback("Exit Callback", exitCallback, 0); 
            sceKernelRegisterExitCallback(callbackID); 
            sceKernelSleepThreadCB(); 

            return 0; 
        } 

        int Callbacks::initialize() {
            int threadID = sceKernelCreateThread("Callback Update Thread", callbackThread, 18, 4000, THREAD_ATTR_USER, 0); 
            if(threadID >= 0) { 
                sceKernelStartThread(threadID, 0, 0); 
            } 

            return threadID;
        }
        
    } // namespace System
    
} // namespace Graphics
