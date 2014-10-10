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

#ifndef SAMPLE_SOUND_H
#define SAMPLE_SOUND_H

#include <allegro.h>
#include <string>
#include <math.h>


using std::string;

class SampleSound {
public:
    SampleSound(const string& filename, int volume = 128, int panning = 128, int frequency = 1000, int loop = FALSE);
    virtual ~SampleSound();
    
    void play();
    void stop();
    
    int getVolume() const { return volume; }
    int getPanning() const { return panning; }
    int getFrequency() const { return frequency; }
    bool getLoop() const { return loop; }
    
    bool setVolume(int value);
    bool setPanning(int value);
    bool setFrequency(int value);
    void setLoop(bool value);
    
    //Poco affidabile!
    inline unsigned long getSampleLength(){return data->len/(pow(2.0,data->bits));}
    
private:
    SAMPLE* data;
    int volume;
    int panning;
    int frequency;
    bool loop;
    
    void adjust();
};

#endif

