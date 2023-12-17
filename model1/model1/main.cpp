
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "WAVheader.h"
#include "inverter.h"
#define BLOCK_SIZE 16
#define MAX_NUM_CHANNEL 8

// Number of channels
#define INPUT_NUM_CHANNELS 2
#define OUTPUT_NUM_CHANNELS 4

// Channel IDs. 
// Should input and output channel IDs be separated?
#define LEFT_CH 0
#define RIGHT_CH 1
#define LEFTS_CH 2
#define RIGHTS_CH 3

// Gain linear values. 
#define MINUS_2DB 0.794328
#define MINUS_4DB 0.630957
#define MINUS_12DB 0.251189 
#define MINUS_3DB 0.70795

// IO Buffers
static double sampleBuffer[MAX_NUM_CHANNEL][BLOCK_SIZE];

// Processing related variables
static double inputGain = MINUS_3DB;
static double variablesGain[INPUT_NUM_CHANNELS];
static double limiterThreshold = 0.999;

inverter_data_t inverter;

enum enable { ON=1, OFF=0 };
static int enable = ON;

enum mode_controls { MODE0=0, MODE1=1 };
static int mode = MODE0;

double saturation(double in)
{
	// Simple limiter since we know that pre-Gain adds 6dB
	if (in > limiterThreshold)
	{
		return limiterThreshold;
	}
	else if (in < -limiterThreshold)
	{
		return -limiterThreshold;
	}

	return in;
}


void gainProcessing(double pIn[][BLOCK_SIZE], double pOut[][BLOCK_SIZE])
{
	double* ptrInL = *(pIn+ LEFT_CH);
	double* ptrOutL = *(pOut+ LEFT_CH);
	double* ptrInR = *(pIn + RIGHT_CH);
	double* ptrOutR = *(pOut + RIGHT_CH);
	double* lsSamplePrt = *(pOut + LEFTS_CH) ;
	double* rsSamplePrt = *(pOut + RIGHTS_CH) ;
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		*ptrInL = *ptrInL * inputGain;
		*ptrInR = *ptrInR * inputGain;

		*ptrOutL = saturation(*ptrInL);
		*ptrOutR = saturation(*ptrInR);

		*lsSamplePrt = *ptrInL;
		*rsSamplePrt = *ptrInR;

		ptrInL++;
		ptrOutL++;
		ptrInR++;
		ptrOutR++;
		lsSamplePrt++;
		rsSamplePrt++;

	}
	//MODE0 invertuje 
	if (mode == MODE0)
	{
		ptrInL = *(pIn + LEFT_CH);
		ptrOutL = *(pOut + LEFT_CH);
		ptrInR = *(pIn + RIGHT_CH);
		ptrOutR = *(pOut + RIGHT_CH);
		gst_audio_invert_transform(&inverter, ptrInL, ptrOutL, BLOCK_SIZE);
		gst_audio_invert_transform(&inverter, ptrInR, ptrOutR, BLOCK_SIZE);
	}

}

/////////////////////////////////////////////////////////////////////////////////
// @Author	<student name>
// @Date		<date>  
//
// Function:
// main
//
// @param - argv[0] - Input file name
//        - argv[1] - Output file name
// @return - nothing
// Comment: main routine of a program
//
// E-mail:	<email>
//
/////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	FILE* wav_in = NULL;
	FILE* wav_out = NULL;
	char WavInputName[256];
	char WavOutputName[256];
	WAV_HEADER inputWAVhdr, outputWAVhdr;

	// Init channel buffers
	for (int i = 0; i < MAX_NUM_CHANNEL; i++)
		memset(&sampleBuffer[i], 0, BLOCK_SIZE);

	// Open input and output wav files
	//-------------------------------------------------
	strcpy(WavInputName, argv[1]);
	wav_in = OpenWavFileForRead(WavInputName, "rb");
	strcpy(WavOutputName, argv[2]);
	wav_out = OpenWavFileForRead(WavOutputName, "wb");
	//-------------------------------------------------
	
	//arg
	if (argc >= 3) {
		enable = atoi(argv[3]); // 0 OFF DOK JE 1 ON
		inputGain = atof(argv[4]);
		mode = atoi(argv[5]); // mode 1 da ne prolazi kroz inverter a 0 da prolazi
	}

	// Read input wav header
	//-------------------------------------------------
	ReadWavHeader(wav_in, inputWAVhdr);
	//-------------------------------------------------

	//init
	audio_invert_init(&inverter, 0.3, 0.9);

	// Set up output WAV header
	//-------------------------------------------------	
	outputWAVhdr = inputWAVhdr;

	if (enable == OFF)
	{
		outputWAVhdr.fmt.NumChannels = inputWAVhdr.fmt.NumChannels;
	}
	else if (enable == ON)
	{
		outputWAVhdr.fmt.NumChannels = OUTPUT_NUM_CHANNELS; // change number of channels
	}
	

	int oneChannelSubChunk2Size = inputWAVhdr.data.SubChunk2Size / inputWAVhdr.fmt.NumChannels;
	int oneChannelByteRate = inputWAVhdr.fmt.ByteRate / inputWAVhdr.fmt.NumChannels;
	int oneChannelBlockAlign = inputWAVhdr.fmt.BlockAlign / inputWAVhdr.fmt.NumChannels;

	outputWAVhdr.data.SubChunk2Size = oneChannelSubChunk2Size * outputWAVhdr.fmt.NumChannels;
	outputWAVhdr.fmt.ByteRate = oneChannelByteRate * outputWAVhdr.fmt.NumChannels;
	outputWAVhdr.fmt.BlockAlign = oneChannelBlockAlign * outputWAVhdr.fmt.NumChannels;


	// Write output WAV header to file
	//-------------------------------------------------
	WriteWavHeader(wav_out, outputWAVhdr);

	// Processing loop
	//-------------------------------------------------	
	{
		int sample;
		int BytesPerSample = inputWAVhdr.fmt.BitsPerSample / 8;
		const double SAMPLE_SCALE = -(double)(1 << 31);		//2^31
		int iNumSamples = inputWAVhdr.data.SubChunk2Size / (inputWAVhdr.fmt.NumChannels * inputWAVhdr.fmt.BitsPerSample / 8);

		// exact file length should be handled correctly...
		for (int i = 0; i < iNumSamples / BLOCK_SIZE; i++)
		{
			for (int j = 0; j < BLOCK_SIZE; j++)
			{
				for (int k = 0; k < inputWAVhdr.fmt.NumChannels; k++)
				{
					sample = 0; //debug
					fread(&sample, BytesPerSample, 1, wav_in);
					sample = sample << (32 - inputWAVhdr.fmt.BitsPerSample); // force signextend
					sampleBuffer[k][j] = sample / SAMPLE_SCALE;				// scale sample to 1.0/-1.0 range		
				}
			}

			if (enable == ON )gainProcessing(sampleBuffer, sampleBuffer);

			for (int j = 0; j < BLOCK_SIZE; j++)
			{
				for (int k = 0; k < outputWAVhdr.fmt.NumChannels; k++)
				{
					sample = sampleBuffer[k][j] * SAMPLE_SCALE;	// crude, non-rounding 			
					sample = sample >> (32 - inputWAVhdr.fmt.BitsPerSample);
					fwrite(&sample, outputWAVhdr.fmt.BitsPerSample / 8, 1, wav_out);
				}
			}
		}
	}

	// Close files
	//-------------------------------------------------	
	fclose(wav_in);
	fclose(wav_out);
	//-------------------------------------------------	

	return 0;
}