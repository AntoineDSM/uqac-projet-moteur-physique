#pragma once

#ifndef TIMING_HPP
#define TIMING_HPP

    namespace TimingDate {  

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

    

    }

#endif // TIMING_H