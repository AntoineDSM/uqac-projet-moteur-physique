//Date de cr�ation : 16/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification : 16/09/22
//Modifi� par : Victor GUIRAUD

#pragma once


#ifndef PRECISION_HPP
#define PRECISION_HPP

#include <float.h>
#define real_pow powf

namespace Precision {

	inline double carre(double x)
	{
		return x * x;
	}

<<<<<<< HEAD
<<<<<<< HEAD
=======
    inline void swapNums(int nums[],
        int first, int second, int secondArray[])
=======
    inline void swapNums(int nums[], int first, int second, int secondArray[])
>>>>>>> origin/Axel
    {
        int curr = nums[first];
        int currSecond = secondArray[first];
        nums[first] = nums[second];
        secondArray[first] = secondArray[second];
        nums[second] = curr;
        secondArray[second] = currSecond;
    }

<<<<<<< HEAD
>>>>>>> origin/Victor
=======

>>>>>>> origin/Axel
    inline void sort(int num[] ,int len, int secondArray[])
    {
        bool isSwapped;
        for (int i = 0; i < len; i++)
        {
            isSwapped = false;
            for (int j = 1; j < len - i; j++)
            {
                if (num[j] < num[j - 1])
                {
                    swapNums(num, j, (j - 1), secondArray);
                    isSwapped = true;
                }
            }
            if (!isSwapped)
            {
                break;
            }
        }
    }

<<<<<<< HEAD
<<<<<<< HEAD
    inline void swapNums(int nums[],
        int first, int second, int secondArray[])
    {
        int curr = nums[first];
        int currSecond = secondArray[first];
        nums[first] = nums[second];
        secondArray[first] = secondArray[second];
        nums[second] = curr;
        secondArray[second] = currSecond;
    }
=======
    

>>>>>>> origin/Victor

=======
   
>>>>>>> origin/Axel
}//namespace Precision

#endif PRECISION_HPP