/* 
 * File:   TextureManager.hpp
 * Author: romain
 *
 * Created on 9 mars 2014, 21:34
 */

#ifndef TEXTUREMANAGER_HPP
#define	TEXTUREMANAGER_HPP

#pragma once
#include <map>
#include <psptypes.h>
#include "../system/Singleton.hpp"

namespace NotEngine {
    
    namespace Graphic {
        
        /**
         * A struct that define a Texture. It is copyable, and just hold the
         * texture image information and a pointer to the datas.
         */
        struct Texture {
            unsigned int   fmt;
            unsigned short width;
            unsigned short height;
            unsigned short stride;
            unsigned short mipmaps;
            unsigned short swizzled;
            void* datas;
        };
        
        /**
         * Handle the loading and freeing of the Texture.
         * An identifier is used (filename for textures on ms, custom name for memory images)
         * to retrieve the previously loaded texture (but not after freeing).
         */
        class TextureManager : public System::Singleton<TextureManager> {
            private:
                /// Handle texture loaded from ms
                std::map<const char*, Texture> fileMap;
                
                /// Handle files loaded from memory
                std::map<const char*, Texture> memoryMap;

                TextureManager(const TextureManager& copy);

                bool checkIfExist(const char* name);
                
            protected:
                friend class System::Singleton<TextureManager>;
                TextureManager();

            public:
                virtual ~TextureManager();
                
                /**
                 * Load some texture from the ms into the manager (TODO)
                 */
                bool loadTexture(const char* name);
                
                /**
                 * Load a texture from memory, wich is intended to be a raw
                 * texture (containing only the pixels) stored in the executable.
                 * 
                 * This does NOT free the datas pointer when using free*Texture
                 * you will have to do it manually if you malloc some memory to build
                 * a texture yourself
                 */
                bool loadTexture(const char* nameid, unsigned int fmt, unsigned short width, unsigned short height, unsigned short stride, unsigned short mipmaps, unsigned short swizzled, void* datas);

                /**
                 * Free one or more Texture previously loaded.
                 */
                void freeTexture    (const char* name);
                void freeAllTexture ();
                
                /**
                 * Return a Texture previously loaded. You can don't care of what
                 * will being the Texture returned since it's just a copy. It doesn't
                 * modify the true texture APPART de datas pointer which must not be
                 * deleted manually.
                 */
                Texture getTexture(const char* name);
        };
        
    } // namespace Graphic
    
} // namespace NotEngine

#endif	/* TEXTUREMANAGER_HPP */
