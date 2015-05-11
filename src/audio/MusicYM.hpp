/* 
 * File:   MusicYM.hpp
 * Author: romain
 *
 * Created on 10 mars 2014, 20:58
 */

#ifndef MUSICYM_HPP
#define	MUSICYM_HPP

#pragma once
#include "Music.hpp"
#include <StSoundLibrary.h>

namespace NotEngine {
    
    namespace Audio {
        
        class MusicYM : public Music {
            private:
                YMMUSIC*      ym;           // To store the handle of the YM music
                ymMusicInfo_t ymMusicInfo;  // To store the YM informations

            protected:
                void compute (void* buf, unsigned int length);

            public:
                int registers[14]; // store the YM registers
        
                /**
                  * Construct the YM Bgm from memory
                  */
                MusicYM(void* memory, unsigned int size);

                virtual ~MusicYM();

                void play ();
                void stop ();
        
                unsigned int getPos();
        };
        
    } // namespace Audio
    
} // namespace NotEngine

#endif	/* MUSICYM_HPP */
