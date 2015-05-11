/* 
 * File:   AudioManager.cpp
 * Author: romain
 * 
 * Created on 10 mars 2014, 20:27
 */

#include "AudioManager.hpp"

#include <string.h>
#include <pspaudiolib.h>

namespace NotEngine {
    
    namespace Audio {
        
        AudioManager::AudioManager() : System::Singleton<AudioManager>() {
        }

        AudioManager::~AudioManager() {
        }
        
        void AudioManager::initialize() {
            pspAudioInit();
        }
        
        void AudioManager::shutdown() {
            pspAudioEndPre();
            pspAudioEnd();
        }
        
        void AudioManager::audioMusicCallback(void* buf, unsigned int length, void* userdata) {
            Music* music = (Music*) userdata;

            if (music->isPlaying && !music->isPaused){ 
                music->compute(buf, length);
            } else {
                memset(buf, 0, length*4);
            }
        }

        
        bool AudioManager::setChannelCallback(AudioChannel channel, const Music* music) {
            if(channel >= PSP_NUM_AUDIO_CHANNELS)
                return false;

            if(music == 0) {
                pspAudioSetChannelCallback((int) channel, 0, 0);
            } else {
                pspAudioSetChannelCallback((int) channel, audioMusicCallback, (void*) music);
            }
            return true;
        }
        
    } // namespace Audio
    
} // namespace NotEngine
