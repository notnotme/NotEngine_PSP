/* 
 * File:   GameState.hpp
 * Author: romain
 *
 * Created on 10 mars 2014, 22:16
 */

#ifndef GAMESTATE_HPP
#define	GAMESTATE_HPP

#pragma once
#include <pspctrl.h>

namespace NotEngine {
    
    namespace Game {
        
        class GameState {
            private:
                GameState(const GameState& copy);
                void operator=(GameState const&);

            public:
                GameState();
                virtual ~GameState();
                
                virtual void enter  () = 0;
                virtual void exit   () = 0;
                
                virtual bool update (const SceCtrlData &inputs, float elapsed) = 0;
                virtual void render () = 0;
        };
        
    } // namespace Game
    
} // namespace NotEngine

#endif	/* GAMESTATE_HPP */

