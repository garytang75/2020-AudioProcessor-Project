/*
AudioProcessor.h
Function declaration
*/


#ifndef _AUDIO_PROCESSOR_H_
#define _AUDIO_PROCESSOR_H_


#include <iostream>
#include <vector>
#include <exception>
#include <cmath>
#include <algorithm>

class AudioProcessor {

	//Project Require functions
public:
	std::vector<short> Compress(const std::vector<short>& audio, const short &threshold, const float &rate);
	std::vector<short> CutOutSilence(const std::vector<short>& audio, const short& level, const int &silenceLengh) ;
	std::vector<short> StretchTwice(const std::vector<short>& audio) ;
	std::vector<short> Normalize(const std::vector<short>& audio, const short &normalizeTarget);

	//one temp obj: the temp
private:
	float temp = 0.0;




};


#endif