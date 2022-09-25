//Date de cr�ation : 16/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification : 22/09/22
//Modifi� par : Victor GUIRAUD

#pragma once

#ifndef TIMING_HPP
#define TIMING_HPP



struct TimingData
{

    /**
    * The timestamp when the last frame ended. Times are
    * given in milliseconds since some undefined time.
    */
    unsigned lastFrameTimestamp;

    /**
     * The duration of the last frame in milliseconds.
     */
    unsigned lastFrameDuration;


    /**
    * Gets the global timing data object.
    */

    static TimingData& get();

};

#endif // TIMING_H