/*
* Project 4 testfile
*/

#include "AudioProcessor.h"
#include <iostream>

/*
* MY FUNCTIONS
*/
void printVector(const std::vector<short>& in_vector)
{
	for (auto i : in_vector)
		std::cout << i << " ";

	std::cout << std::endl;
}

/*
* PROF'S FUNCTIONS
*/
void TestCompress();
void TestCutOutSilence();
void TestStretchTwice();
void TestNormalize();


int main()
{
	AudioProcessor ap1;

	/**************************************************************************************************
	*
	*                                           COMPRESS TESTS
	*
	**************************************************************************************************/
	std::cout << "<--------------------\n<--------------------\nTESTING COMPRESS\n-------------------->\n-------------------->\n";
	std::cout << "1 --- Testing size of 0.\n";
	std::cout << "Should print: PRINTS: ";
	printVector(ap1.Compress({}, 10, 1.5));
	//
	std::cout << "2 --- Testing threshold less than 0. Should throw error...\n";
	try
	{
		ap1.Compress({ 10 }, -1, 1.0);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl;
	}
	//
	std::cout << "3 --- Testing rate less than 1. Should throw error...\n";
	try
	{
		ap1.Compress({ 10 }, 1, 0);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl;
	}
	//
	std::cout << "4 --- Testing on: {1, 4, 25, 15, 0, -7, -40, 10}, threshold=10,  rate=1.5...\n";
	std::cout << "Should print: 1, 4, 20, 13, 0, -7, -30, 10: PRINTS: ";
	printVector(ap1.Compress({ 1, 4, 25, 15, 0, -7, -40, 10 }, 10, 1.5));
	//
	std::cout << "5 --- Testing on: {5, 4, 9, -10, 0, -9, -4, 10}, threshold=10,  rate=1.5...\n";
	std::cout << "Should print: 5, 4, 9, -10, 0, -9, -4, 10: PRINTS: ";
	printVector(ap1.Compress({ 5, 4, 9, -10, 0, -9, -4, 10 }, 10, 1.5));
	//
	std::cout << "6 --- Testing on: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, threshold=8,  rate=1.8...\n";
	std::cout << "Should print: 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 10, 10, 11, 11, 12: PRINTS: ";
	printVector(ap1.Compress({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }, 8, 1.8));
	//
	std::cout << "7 --- Testing on: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, threshold=8,  rate=1.1...\n";
	std::cout << "Should print: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 13, 14: PRINTS: ";
	printVector(ap1.Compress({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }, 8, 1.1));
	//
	/**************************************************************************************************
	*
	*                                        CUTOUTSILENCE TESTS
	*
	**************************************************************************************************/
	std::cout << "<--------------------\n<--------------------\nTESTING CUTOUTSILENCE\n-------------------->\n-------------------->\n";
	std::cout << "8 --- Testing size of 0.\n";
	std::cout << "Should print: PRINTS: ";
	printVector(ap1.CutOutSilence({}, 5, 2));
	//
	std::cout << "9 --- Testing level less than 0. Should throw error...\n";
	try
	{
		ap1.Compress({ 10 }, -1, 1);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl;
	}
	//
	std::cout << "10 --- Testing silence length less than 1. Should throw error...\n";
	try
	{
		ap1.Compress({ 10 }, 0, 0);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl;
	}
	//
	std::cout << "11 --- Testing on: {1, -3, 10, 25, 56, -1, -2, -16, -20, -8, -1, 1, 7, 12}, level=10,  silenceLength=3...\n";
	std::cout << "Should print: 25, 56, -1, -2, -16, -20, 12: PRINTS: ";
	printVector(ap1.CutOutSilence({ 1, -3, 10, 25, 56, -1, -2, -16, -20, -8, -1, 1, 7, 12 }, 10, 3));
	//
	std::cout << "12 --- Testing on: {1, -3, 10, 25, 56, -1, -2, -16, -20, -8, -1, 1, 7, 12, -1, 9, -9}, level=10,  silenceLength=3...\n";
	std::cout << "Should print: 25, 56, -1, -2, -16, -20, 12: PRINTS: ";
	printVector(ap1.CutOutSilence({ 1, -3, 10, 25, 56, -1, -2, -16, -20, -8, -1, 1, 7, 12, -1, 9, -9 }, 10, 3));
	//
	std::cout << "13 --- Testing on: {1, -3, 10, 25, 56, -1, -2, -16, -20, -8, -1, 1, 7, 12, -1, 9, -9}, level=10,  silenceLength=5...\n";
	std::cout << "Should print: 1, -3, 10, 25, 56, -1, -2, -16, -20, -8, -1, 1, 7, 12, -1, 9, -9: PRINTS: ";
	printVector(ap1.CutOutSilence({ 1, -3, 10, 25, 56, -1, -2, -16, -20, -8, -1, 1, 7, 12, -1, 9, -9 }, 10, 5));
	//
	std::cout << "14 --- Testing on: {1, 12, -1, 9, -9}, level=0,  silenceLength=1...\n";
	std::cout << "Should print: 1, 12, -1, 9, -9: PRINTS: ";
	printVector(ap1.CutOutSilence({ 1, 12, -1, 9, -9 }, 0, 1));
	//
	std::cout << "15 --- Testing on: {1, 12, -1, 9, -9}, level=13,  silenceLength=1...\n";
	std::cout << "Should print: PRINTS: ";
	printVector(ap1.CutOutSilence({ 1, 12, -1, 9, -9 }, 13, 1));
	//
	std::cout << "16 --- Testing on: {1, 12, -1, 9, -9}, level=13,  silenceLength=4...\n";
	std::cout << "Should print: PRINTS: ";
	printVector(ap1.CutOutSilence({ 1, 12, -1, 9, -9 }, 13, 4));
	//
	std::cout << "17 --- Testing on: {15, 12, -1, 9, -90}, level=13,  silenceLength=2...\n";
	std::cout << "Should print: 15, -90 PRINTS: ";
	printVector(ap1.CutOutSilence({ 15, 12, -1, 9, -90 }, 13, 2));
	//
	std::cout << "17A --- Testing on: {11, 12, 13, 1, 2, 3}, level=10,  silenceLength=3...\n";
	std::cout << "Should print: 11, 12, 13 PRINTS: ";
	printVector(ap1.CutOutSilence({ 11, 12, 13, 1, 2, 3 }, 10, 3));
	//
	/**************************************************************************************************
	*
	*                                       STRETCHTWICE TESTS
	*
	**************************************************************************************************/
	std::cout << "<--------------------\n<--------------------\nTESTING STRETCHTWICE\n-------------------->\n-------------------->\n";
	std::cout << "18 --- Testing size of 0.\nShould print: PRINTS: ";
	printVector(ap1.StretchTwice({}));
	//
	std::cout << "19 --- Testing size of 1.\nShould print: 6 PRINTS: ";
	printVector(ap1.StretchTwice({ 6 }));
	//
	std::cout << "20 --- Testing on: {1, 2, 3, 4, 5, 6}...\n";
	std::cout << "Should print: 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6 PRINTS: ";
	printVector(ap1.StretchTwice({ 1, 2, 3, 4, 5, 6 }));
	//
	std::cout << "21 --- Testing on: {-1, -2, -3, -4, -5, -6}...\n";
	std::cout << "Should print: -1, -2, -2, -3, -3, -4, -4, -5, -5, -6, -6 PRINTS: ";
	printVector(ap1.StretchTwice({ -1, -2, -3, -4, -5, -6 }));
	//
	std::cout << "22 --- Testing on: {1, 0}...\n";
	std::cout << "Should print: 1, 1, 0 PRINTS: ";
	printVector(ap1.StretchTwice({ 1, 0 }));
	//
	std::cout << "23 --- Testing on: {0, 0, 0}...\n";
	std::cout << "Should print: 0, 0, 0, 0, 0 PRINTS: ";
	printVector(ap1.StretchTwice({ 0, 0, 0 }));
	//
	std::cout << "24 --- Testing on: {-99, 0}...\n";
	std::cout << "Should print: -99, -50, 0 PRINTS: ";
	printVector(ap1.StretchTwice({ -99, 0 }));
	//
	/**************************************************************************************************
	*
	*                                         NORMALIZE TESTS
	*
	**************************************************************************************************/
	std::cout << "<--------------------\n<--------------------\nTESTING NORMALIZE\n-------------------->\n-------------------->\n";
	std::cout << "25 --- Testing size of 0.\n";
	std::cout << "Should print: PRINTS: ";
	printVector(ap1.Normalize({}, 5));
	//
	std::cout << "26 --- Testing normalizeTarget less than 1. Should throw error...\n";
	try
	{
		ap1.Normalize({ 5, 10, 100 }, 0);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl;
	}
	//
	std::cout << "27 --- Testing on: {0, 0, 0}, normalizeTarget=5...\n";
	std::cout << "Should print: 0, 0, 0 PRINTS: ";
	printVector(ap1.Normalize({ 0, 0, 0 }, 5));
	//
	std::cout << "28 --- Testing on: {0, 10}, normalizeTarget=5...\n";
	std::cout << "Should print: 0, 5 PRINTS: ";
	printVector(ap1.Normalize({ 0, 10 }, 5));
	//
	std::cout << "29 --- Testing on: {0, -10, 0}, normalizeTarget=5...\n";
	std::cout << "Should print: 0, -5, 0 PRINTS: ";
	printVector(ap1.Normalize({ 0, -10, 0 }, 5));
	//
	std::cout << "30 --- Testing on: {0, -1, 1, -2, 2, -3, 3, -4, 4, -5, 5, -6, 6}, normalizeTarget=3...\n";
	std::cout << "Should print: 0, -1, 1, -1, 1, -2, 2, -2, 2, -3, 3, -3, 3 PRINTS: ";
	printVector(ap1.Normalize({ 0, -1, 1, -2, 2, -3, 3, -4, 4, -5, 5, -6, 6 }, 3));
	//
	std::cout << "31 --- Testing on: {1, 3, 3, 7}, normalizeTarget=7...\n";
	std::cout << "Should print: 1, 3, 3, 7 PRINTS: ";
	printVector(ap1.Normalize({ 1, 3, 3, 7 }, 7));
	//
	/**************************************************************************************************
	*
	*                                          PROF'S TESTS
	*
	**************************************************************************************************/
	std::cout << "<--------------------\n<--------------------\nUSING PROF'S TESTS\n-------------------->\n-------------------->\n";
	std::cout << "If nothing prints from his tests that means you passed. Good work, bud! You're a rising star, I tell you.\n" << std::endl;
	TestCompress();
	TestCutOutSilence();
	TestStretchTwice();
	TestNormalize();

	std::cout << "You've reached the end of this test file..." << std::endl;

	return 0;
} // END main

/**************************************************************************************************
***************************************************************************************************
*
* FUNCTION DEFINITIONS:
*
***************************************************************************************************
**************************************************************************************************/

void TestCompress()
{
	AudioProcessor aProc;

	// INPUT 1
	std::vector<short> input{ 1, 2, 5, 6, 10, 0, -2, -5, -6, -8 };
	std::vector<short> expected{ 1, 2, 5, 5, 7, 0, -2, -5, -5, -6 };
	auto output{ aProc.Compress(input, 5, 3) };

	if (output != expected)
		std::cout << "bad Compressor! failed on input 1." << std::endl;

	///////////
	bool exceptonThrown{ false };
	try
	{
		auto util = aProc.Compress({ 1,2 }, -1, 2);
	}
	catch (std::invalid_argument& e)
	{
		exceptonThrown = true;
	}

	if (!exceptonThrown)
		std::cout << "bad Compressor! threshold<0 didn't throw the exception." << std::endl;

	///////////
	exceptonThrown = false;
	try
	{
		auto util = aProc.Compress({ 1,2 }, 1, 0.5f);
	}
	catch (std::invalid_argument& e)
	{
		exceptonThrown = true;
	}

	if (!exceptonThrown)
		std::cout << "bad Compressor! rate<1 didn't throw the exception." << std::endl;
}

void TestCutOutSilence()
{
	AudioProcessor aProc;

	// INPUT 1
	std::vector<short> input{ 1, 2, 5, 6, 10, 0, -2, -5, -5, -8 };
	std::vector<short> expected{ 1, 2, 5, 6, 10, -8 };
	auto output{ aProc.CutOutSilence(input, 5, 4) };

	if (output != expected)
		std::cout << "bad CutOutSilence! failed on input 1." << std::endl;

	// INPUT 2
	input = { 1, 2, 5, 6, -4, 4, 10, 0, -2, -5, -4 };
	expected = { 6, -4, 4, 10 };
	output = aProc.CutOutSilence(input, 5, 3);

	if (output != expected)
		std::cout << "bad CutOutSilence! failed on input 2." << std::endl;

	// INPUT 3
	input = { 1, 2, 5, 6, -4, 4, -2, -5, 10, 0, -4 };
	expected = { 1, 2, 5, 6, 10, 0, -4 };
	output = aProc.CutOutSilence(input, 5, 4);

	if (output != expected)
		std::cout << "bad CutOutSilence! failed on input 3." << std::endl;

	///////////
	bool exceptonThrown{ false };
	try
	{
		auto util = aProc.CutOutSilence({ 1,2 }, -1, 2);
	}
	catch (std::invalid_argument& e)
	{
		exceptonThrown = true;
	}

	if (!exceptonThrown)
		std::cout << "bad CutOutSilence! silenceLevel<0 didn't throw the exception." << std::endl;

	///////////
	exceptonThrown = false;
	try
	{
		auto util = aProc.CutOutSilence({ 1,2 }, 1, 0);
	}
	catch (std::invalid_argument& e)
	{
		exceptonThrown = true;
	}

	if (!exceptonThrown)
		std::cout << "bad CutOutSilence! silenceMinLength<1 didn't throw the exception." << std::endl;
}

void TestStretchTwice()
{
	AudioProcessor aProc;

	// INPUT 1
	std::vector<short> input{ 1, 2, 6, -5, -10, 1 };
	std::vector<short> expected{ 1, 2, 2, 4, 6, 1, -5, -8, -10, -5, 1 };
	auto output{ aProc.StretchTwice(input) };

	if (output != expected)
		std::cout << "bad StretchTwice! failed on input 1." << std::endl;

	//////////
	if (aProc.StretchTwice({}) != std::vector<short>{})
		std::cout << "bad StretchTwice! failed on the empty input std::vector." << std::endl;

	//////////
	if (aProc.StretchTwice({ 4 }) != std::vector<short>{4})
		std::cout << "bad StretchTwice! failed on the single-element input std::vector." << std::endl;
}

void TestNormalize()
{
	AudioProcessor aProc;

	// INPUT 1
	std::vector<short> input{ 1, 2, -5, 8 };
	std::vector<short> expected{ 2, 3, -8, 12 };
	auto output{ aProc.Normalize(input, 12) };

	if (output != expected)
		std::cout << "bad Normalize! failed on input 1." << std::endl;

	// INPUT 2
	input = { -10, 2, -5, 8 };
	expected = { -20, 4, -10, 16 };
	output = aProc.Normalize(input, 20);

	if (output != expected)
		std::cout << "bad Normalize! failed on input 2." << std::endl;

	///////////
	bool exceptonThrown{ false };
	try
	{
		auto util = aProc.Normalize({ 1,2 }, 0);
	}
	catch (std::invalid_argument& e)
	{
		exceptonThrown = true;
	}

	if (!exceptonThrown)
		std::cout << "bad Normalize! normalizeTarget<1 didn't throw the exception." << std::endl;
}

// END Source.cpp 