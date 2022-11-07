#pragma once

#include <chrono>
#include <iostream>

#ifndef TIMING_HPP

#define TIMING_HPP

/**
 * Represents all the information that the demo might need about the
 * timing of the game: current time, fps, frame number, and so on.
 */
namespace Timing
{
	inline float getLastFrameDuration(std::chrono::system_clock::time_point start, std::chrono::system_clock::time_point stop)
	{
		float lastFrameDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(start - stop).count();
		return lastFrameDuration;
	}

};//namespace Timing

#endif // TIMING_H

