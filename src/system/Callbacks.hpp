/* 
 * File:   Callbacks.hpp
 * Author: romain
 *
 * Created on 8 mars 2014, 21:27
 */

#ifndef CALLBACKS_HPP
#define	CALLBACKS_HPP

#pragma once
#include <pspkerneltypes.h>
#include "../system/Singleton.hpp"

namespace NotEngine {
    
    namespace System {

        /**
         * This is intented to ease the creation of tiny PSP program by 
         * avoiding the need to rewrite all the time the common callbacks
         * used by the system.
         * 
         * instance() MUST be called at program startup.
         */
        class Callbacks : public System::Singleton<Callbacks> {
            private:
                static bool exitRequest;
                
                static int exitCallback   (int arg1, int arg2, void* common);
                
                static int callbackThread (SceSize args, void* argp);

            protected:
                friend class System::Singleton<Callbacks>;
                Callbacks();

            public:
                virtual ~Callbacks();

                int  initialize();
                bool isRunning();
        };
        
    } // namespace System
    
} // namespace NotEngine

#endif	/* CALLBACKS_HPP */

