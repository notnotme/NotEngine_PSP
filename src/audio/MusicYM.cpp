/* 
 * File:   MusicYM.cpp
 * Author: romain
 * 
 * Created on 10 mars 2014, 20:58
 */

#include "MusicYM.hpp"

namespace NotEngine {
    
    namespace Audio {
        
        MusicYM::MusicYM(void* memory, unsigned int size) : Music() {
            ym = ymMusicCreate();
            if (ymMusicLoadMemory(ym, memory, size) != 0) {
                ymMusicGetInfo(ym, &ymMusicInfo);
                ymMusicSetLoopMode(ym, 1);
                ymMusicSetLowpassFiler(ym, 1);
            } else {
                // not good
            }
        }

        MusicYM::~MusicYM() {
            ymMusicDestroy(ym);
            ym = 0;
        }

        void MusicYM::compute(void* buf, unsigned int length) {
            ymMusicCompute(ym, (ymsample*) buf, length);
            for (int i=0; i<14; i++) {
                // update the ym register array
                registers[i] = ymMusicGetRegister(ym, i);
            }

            // StSound output mono 16 bit sample, but audiolib take stereo 16bit sample.
            short *s = (short *)buf;
            short *d = (short *)buf;
            s += length-1;
            d += length*2-1;
            while (length--) {
                *d = *s;
                *(d-1) = *s;
                s--;
                d -= 2;
            }
        }

        void MusicYM::play() {
            Music::play();
            ymMusicPlay(ym);
        }

        void MusicYM::stop() {
            Music::stop();
            ymMusicStop(ym);
        }

        unsigned int MusicYM::getPos() {
            return ymMusicGetPos(ym);
        }
        
    } // namespace Audio
    
} // namespace NotEngine
