#pragma once

#ifndef TIMING_HPP
#define TIMING_HPP

    namespace TimingDate {  

        struct TimingData
        {

            /*La timestamp de la fin de la dernière image. Les temps sont
                *donnés en millisecondes depuis un temps indéfini.
                */
            unsigned lastFrameTimestamp;

           
              //La durée de la dernière en frème en millisecondes 
             
            unsigned lastFrameDuration;


            
             //Gets the global timing data object.
            

            static TimingData& get();

        };

    

    }

#endif // TIMING_H