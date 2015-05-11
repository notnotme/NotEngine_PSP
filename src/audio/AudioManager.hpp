/* 
 * File:   AudioManager.hpp
 * Author: romain
 *
 * Created on 10 mars 2014, 20:27
 */

#ifndef AUDIOMANAGER_HPP
#define	AUDIOMANAGER_HPP

#pragma once
#include <psptypes.h>
#include "Music.hpp"
#include "../system/Singleton.hpp"

namespace NotEngine {
    
    namespace Audio {
        
        class AudioManager : public System::Singleton<AudioManager> {
            private:
                static void audioMusicCallback(void* buf, u32 length, void* userdata);

            protected:
                friend class System::Singleton<AudioManager>;
                AudioManager();
                
            public:
                
                enum AudioChannel {
                    CH_0 = 0,
                    CH_1 = 1,
                    CH_2 = 2,
                    CH_3 = 3
                };
                
                virtual ~AudioManager();
                
                void initialize ();
                void shutdown   ();
                
                bool setChannelCallback(AudioChannel channel, const Music* music);
        };
        
    } // namespace Audio
    
} // namespace NotEngine

#endif	/* AUDIOMANAGER_HPP */
