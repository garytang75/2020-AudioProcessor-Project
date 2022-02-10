# 2020-AudioProcessor-Project
Inspired by the audio processing tasks. The audio is presented as an array of numbers in the computer. Array manipulation. 


##Description

vector Compress(const vector & audio, short threshold, float rate)
This function returns the compressed version of the given audio.
 
Example: audio={1, 4, 25, 15, 0, -7, -40, 10} , threshold=10,  rate=1.5
Output: {1, 4, 20, 13, 0, -7, -30, 10} // values affected by compression are shown in bold.
 
vector CutOutSilence(const vector & audio, short level, int silenceLength)
Silence is a portion of audio where all numbers/samples are in the range [-level, level].
CutOutSilince returns the version of audio where all silences of at least silenceLength length are removed.
If level<0 or silenceLength<1, throw the std::invalid_argument exception
 
Example: audio={1, -3, 10, 25, 56, -1, -2, -16, -20, -8, -1, 1, 7, 12}, level=10, silenceLength=3
Output: {25, 56, -1, -2, -16, -20, 12}
The portions of audio in bold are the portions which we cut out. Pay attention, the fragment {-1, -2} in the audio is also a silence but its length is below the minimum silenceLength so we leave it in the result.
 
vector StretchTwice(const vector & audio)
Returns the version of audio where between each pair of original samples from audio an extra sample appears. This extra sample is an average (arithmetic mean) of the two original samples.
The average can be a floating-point value. In that case, it should be rounded to the closest short. If both upper and lower shorts are equally far, chose the one with the larger absolute value.
 
Example: audio={1, 4, 23, -2, -28, 10 }
Output: {1, 3, 4, 14, 23, 11, -2, -15, -28, -9, 10} // original values are in bold
 
vector Normalize(const vector & audio, short normalizeTarget).
Normalize returns a version of audio where all samples are proportionally increases or decreased to ensure that the largest absolute value from all resulting samples is exactly normalizeTarget.
While normalizing, you can get floating-point values. Such values should be rounded to the closest short. If both upper and lower shorts are equally far, chose the one with the larger absolute value.
If normalizeTarget<1, throw the std::invalid_argument exception
 
Example 1: audio={1, 3, -2, 5, -4, 0}  normilizeTarget=10
Output: {2, 6, -4, 10, -8, 0}
Explanation: all samples from the original audio were multiplied by 2, so that the largest absolute value in the result is 10.
 
Example 2: audio={-1, -30, 3, 15, 16, -7}  normilizeTarget=20
Output: {-1, -20, 2, 10, 11, -5}
Explanation: all samples from the original audio were multiplied by 0.6666666, so that the largest absolute value in the result is 20.
