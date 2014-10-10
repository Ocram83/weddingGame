/*
    AllegroWrapper - A wrapper for the Allegro library (version 4)
    Copyright (C) 2013, Mario Alviano

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "SampleSound.h"

#include "Allegro.h"

SampleSound::SampleSound(const string& filename, int _volume, int _panning, int _frequency, int _loop)
: volume(_volume), panning(_panning), frequency(_frequency), loop(_loop) {
    assert(0 <= volume && volume <= 255);
    assert(0 <= panning && panning <= 255);
    assert(0 <= frequency);

    data = load_sample(filename.c_str());
    assert(data != NULL);
}

SampleSound::~SampleSound() {
    destroy_sample(data);
}

void SampleSound::play() {
    play_sample(data, volume, panning, frequency, loop);
}

void SampleSound::stop() {
    stop_sample(data);
}

bool SampleSound::setVolume(int value) {
    if(0 <= value && value <= 255) {
        volume = value;
        adjust();
        return true;
    }
    return false;
}

bool SampleSound::setPanning(int value) {
    if(0 <= value && value <= 255) {
        panning = value;
        adjust();
        return true;
    }
    return false;
}

bool SampleSound::setFrequency(int value) {
    if(0 <= value) {
        frequency = value;
        adjust();
        return true;
    }
    return false;
}

void SampleSound::setLoop(bool value) {
    loop = value;
    adjust();
}
    
void SampleSound::adjust() {
    adjust_sample(data, volume, panning, frequency, loop);
}

