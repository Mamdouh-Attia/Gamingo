#pragma once

#include "../../vendor/irrKlang/include/irrKlang.h"

namespace our
{

    // handles playing sound effects of all types: fuel, obstacle, goal, level up.
    class SoundSystem {
        // engine object that controls sound files
        irrklang::ISoundEngine* engine;
    public:

        SoundSystem() {
            // start the sound engine with default parameters
            engine = irrklang::createIrrKlangDevice();
        }

        void playSound(const std::string filename, bool playLooped = false) {
            // play fuel effect sound stream, false for looped
            std::string path = "assets/effects/";
            path.append(filename);
            path.append(".mp3");
            engine->play2D(path.c_str(), playLooped);
        }

        void clear() {
            // delete engine
            engine->drop();
        }

    };

}
