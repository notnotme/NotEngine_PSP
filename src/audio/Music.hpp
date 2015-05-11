/* 
 * File:   Music.hpp
 * Author: romain
 *
 * Created on 10 mars 2014, 20:41
 */

#ifndef MUSIC_HPP
#define	MUSIC_HPP

#pragma once
#include <psptypes.h>

namespace NotEngine {
    
    namespace Audio {
        
        class Music {
            private:
                Music(const Music& copy);
                void operator=(Music const&);
                
            protected:
                friend class AudioManager;

                bool isPlaying; // Playing status
                bool isPaused;  // Pause status

                /**
                  * Compute a chunk of length byte of music
                  */
                virtual void compute(void* buf, unsigned int length) = 0;

            public:
                Music();
                virtual ~Music();
                
                void play();
                void pause();
                void resume();
                void stop();

                /**
                  * return the position in ms
                  */
                virtual unsigned int getPos () = 0;
        };        
        
    } // namespace Audio
    
} // namespace NotEngine

#endif	/* MUSIC_HPP */
