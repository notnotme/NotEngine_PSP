/* 
 * File:   Music.cpp
 * Author: romain
 * 
 * Created on 10 mars 2014, 20:41
 */

#include "Music.hpp"

namespace NotEngine {
    
    namespace Audio {

        Music::Music() : isPlaying(false), isPaused(false) {
        }

        Music::~Music() {
        }

        void Music::play() {
            isPlaying = true;
            isPaused = false;
        }

        void Music::pause() {
            isPaused = true;
        }

        void Music::resume() {
            isPaused = false;
        }

        void Music::stop() {
            isPlaying = false;
        }
        
    } // namespace Audio
    
} // namespace NotEngine
