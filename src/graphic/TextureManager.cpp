/* 
 * File:   TextureManager.cpp
 * Author: romain
 * 
 * Created on 9 mars 2014, 21:34
 */

#include <malloc.h>
#include <string.h>
#include "TextureManager.hpp"

namespace NotEngine {
    
    namespace Graphic {
        
        TextureManager::TextureManager() : System::Singleton<TextureManager>() {
        }

        TextureManager::~TextureManager() {
            freeAllTexture();
        }
        
        bool TextureManager::checkIfExist(const char* nameOrNameId) {
            // check alredy named texture in files or memory
            if (fileMap.find(nameOrNameId) != fileMap.end()) return true;

            // check alredy named texture in files or memory
            else if (memoryMap.find(nameOrNameId) != memoryMap.end()) return true;

            return false;
        }
                
        bool TextureManager::loadTexture(const char* name) {
            if(checkIfExist(name)) return false;
            
            // TODO:
            return false;
        }
        
        bool TextureManager::loadTexture(const char* nameid, unsigned int fmt, unsigned short width, unsigned short height, unsigned short stride, unsigned short mipmaps, unsigned short swizzled, void* datas) {
            if(checkIfExist(nameid)) return false;

            // simply build a struct and add it to the memory map
            Texture texture = {fmt, width,height,stride, mipmaps,swizzled, datas};
            memoryMap[nameid] = texture;
            return true;
        }
        
        void TextureManager::freeTexture(const char* nameOrNameId) {
            if(fileMap.find(nameOrNameId) != fileMap.end()) {
                Texture texture = fileMap[nameOrNameId];
                
                free(texture.datas);
                fileMap.erase(nameOrNameId);
            } else if (memoryMap.find(nameOrNameId) != memoryMap.end()) {
                memoryMap.erase(nameOrNameId);
            }
        }
        
        void TextureManager::freeAllTexture() {
            for(std::map<const char*, Texture>::iterator itr = fileMap.begin(), itr_end = fileMap.end(); itr != itr_end; ++itr) {
                Texture texture = itr->second;
                if(texture.datas != 0)
                    free(texture.datas);
            }
            fileMap.clear();
            memoryMap.clear();
        }
        
        Texture TextureManager::getTexture(const char* nameOrNameId) {
            if (memoryMap.find(nameOrNameId) != memoryMap.end()) {
                return memoryMap[nameOrNameId];
            } 
            
            else if (fileMap.find(nameOrNameId) != fileMap.end()) {
                return fileMap[nameOrNameId];
            }

            // else return an empty invalid texture
            return (Texture) {0, 0,0,0,0,0, 0};
        }
        
    } // namespace Graphics
    
} // namespace NotEngine
