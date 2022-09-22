#pragma once

#ifndef TIMING_HPP
#define TIMING_HPP

    namespace TimingDate {  

        struct TimingData
        {

            /*La timestamp de la fin de la derni�re image. Les temps sont
                *donn�s en millisecondes depuis un temps ind�fini.
                */
            unsigned lastFrameTimestamp;

           
              //La dur�e de la derni�re en fr�me en millisecondes 
             
            unsigned lastFrameDuration;


            
             //Gets the global timing data object.
            

            static TimingData& get();

        };

    

    }

#endif // TIMING_H