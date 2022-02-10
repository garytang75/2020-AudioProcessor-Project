#include "AudioProcessor.h"

//Compress function
std::vector<short> AudioProcessor::Compress(const std::vector<short>& audio, const short& threshold, const float &rate)  {
	std::vector<short> compressed = {};
	//Error Checking if threshold and rate below the requirement, will throw invalid_argument
	if (threshold >= 0 && rate > 1.0) {
		if (audio.size() == 0) {
			return compressed;
		}
		else {
			for (unsigned i = 0; i <= audio.size() -1; i++) {
				//if the value in vector is negative, turn it positive
				if (audio[i] < 0) {
					temp = float(audio[i] * -1);
					if (temp > threshold) {
						//using formula professor provided
						temp = ((temp - threshold) / rate + threshold) * -1;
						//push_back the rounded value
						compressed.push_back(std::round(temp));
						//set temp back to 0
						temp = 0;
					}
					else {
						//if less than threshold, push in the compress vector
						compressed.push_back(std::round(temp * -1));
					}
				}
				//if the value is positive
				else {
					temp = audio[i];
					//push in the compressed vector by using professor's formula
					if (temp > threshold) {
						temp = ((temp - threshold) / rate + threshold);
						compressed.push_back(std::round(temp));
						temp = 0;
					}
					else {
						compressed.push_back(std::round(temp));
					}
				}
			}
		}
		return compressed;
	}
	else {
		throw std::invalid_argument("\n ERROR, Threshold or Rate is out of range");
	}
}

//CutOutSilence Function
std::vector<short> AudioProcessor::CutOutSilence(const std::vector<short>& audio, const short &level, const int &silenceLength)  {
	//create two temp vector *I know it is not efficient, but it works
	std::vector<short> silence = {};
	std::vector<short> silaudio = {};
	//Error checking, lvl >= 0 and silenceLength greater or = to 1
	if (level >= 0 && silenceLength >= 1) {
		if (audio.size() == 0) {
			return silaudio;
		}
		for (unsigned i = 0; i < audio.size(); i++) {
			//if the abs value is less than the level, we push value to both temp vector
			if (abs(audio[i]) <= level) {
				silence.push_back(audio[i]);
				silaudio.push_back(audio[i]);
			}
			//once we see a value greater than lvl, I check if the silience vector size is greater or less than the silence Length
			//if it is less than the length, we clear the silence vector and push the current value into the audio vector
			else if (abs(audio[i]) > level && silence.size() < unsigned(silenceLength)) {
				silence.clear();
				silaudio.push_back(audio[i]);
			}
			//if it is greater than the length, we pop_back audio by using silence length and clear the silence vector
			else if (abs(audio[i]) > level && silence.size() >= unsigned(silenceLength)) {
				for (unsigned i = 0; i < silence.size(); i++) {
					silaudio.pop_back();
				}
				silence.clear();
				silaudio.push_back(audio[i]);
			}
			//check at the end, if the silience period is at the end
			if (i == audio.size() - 1 && silence.size() >= unsigned(silenceLength)){
				for (unsigned i = 0; i < silence.size(); i++) {
					silaudio.pop_back();
				}
				silence.clear();
			}
		}
		return silaudio;
	}
	else {
		throw std::invalid_argument("/n Level or SilenceLength out of range");
	}
	
}

//StretchTwice Function
std::vector<short> AudioProcessor::StretchTwice(const std::vector<short>& audio)  {
	std::vector<short> stretch = {};
	if (audio.size() == 0) {
		return stretch;
	}
	//if the audio size is 1, we return the vector with the single value
	else if (audio.size() == 1) {
		stretch.push_back(audio[0]);
		return stretch;
	}
	//any other size, we push the value into temp vec and do arithimetic on the value in the vector by using a temp
	else {
		for (unsigned i = 0; i < audio.size() - 1; i++) {
			stretch.push_back(audio[i]);
			temp = float(audio[i]);
			temp = float(temp + audio[i + 1]) / 2.0;
			stretch.push_back(std::round(temp));
			temp = 0;
		}
		stretch.push_back(audio[audio.size() - 1]);
		return stretch;
	}
}

//Normalize function
std::vector<short> AudioProcessor::Normalize(const std::vector<short>& audio, const short &normalizeTarget)  {
	//Error checking, make sure the normalizeTarget is within range
	if (normalizeTarget >= 1) {
		std::vector<short> normal = {};
		float temp1;
		if (audio.size() == 0) {
			return normal;
		}
		else {
			for (unsigned i = 0; i <= audio.size() - 1; i++) {
				normal.push_back(abs(audio[i]));
			}
			//find the index of the max value in the vector
			int maxindex = std::max_element(normal.begin(), normal.end()) - normal.begin();
			normal.clear();
			//using the max value to get the number we need to use to multiply the rest of the vector
			temp1 = fabs(float(normalizeTarget) / float(audio[maxindex]));
			//multiple other value in the vector and the highest value will be the normalizieTarget
			for (unsigned i = 0; i <= audio.size() - 1; i++) {
				temp = float(audio[i]) * temp1;
				normal.push_back(round(temp));
			}
		}
		return normal;
	}
	else {
		throw std::invalid_argument("/n NormalizeTarget out of range ");
	}
}




