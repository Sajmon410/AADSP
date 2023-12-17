
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "WAVheader.h"
#include "inverter.h"
#include "common.h"

// IO Buffers
static DSPfract sampleBuffer[MAX_NUM_CHANNEL][BLOCK_SIZE];

// Processing related variables
static DSPfract inputGain = MINUS_3DB;
static DSPfract variablesGain[INPUT_NUM_CHANNELS];
static DSPfract limiterThreshold = FRACT_NUM(0.999);

inverter_data_t inverter;

enum enable { ON=1, OFF=0 };
static DSPint enable = ON;

enum mode_controls { MODE0=0, MODE1=1 };
static DSPint mode = MODE0;

DSPfract saturation(DSPfract in)
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


void gainProcessing(DSPfract pIn[][BLOCK_SIZE], DSPfract pOut[][BLOCK_SIZE])
{
	DSPfract* ptrInL = *(pIn+ LEFT_CH);
	DSPfract* ptrOutL = *(pOut+ LEFT_CH);
	DSPfract* ptrInR = *(pIn + RIGHT_CH);
	DSPfract* ptrOutR = *(pOut + RIGHT_CH);
	DSPfract* lsSamplePrt = *(pOut + LEFTS_CH) ;
	DSPfract* rsSamplePrt = *(pOut + RIGHTS_CH) ;
	for (DSPint i = 0; i < BLOCK_SIZE; i++)
	{
		*ptrInL = (DSPfract)*ptrInL * inputGain;
		*ptrInR = (DSPfract)*ptrInR * inputGain;

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
	for (DSPint i = 0; i < MAX_NUM_CHANNEL; i++)
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
	audio_invert_init(&inverter, FRACT_NUM(0.3), FRACT_NUM(0.9));

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
	

	DSPint oneChannelSubChunk2Size = inputWAVhdr.data.SubChunk2Size / inputWAVhdr.fmt.NumChannels;
	DSPint oneChannelByteRate = inputWAVhdr.fmt.ByteRate / inputWAVhdr.fmt.NumChannels;
	DSPint oneChannelBlockAlign = inputWAVhdr.fmt.BlockAlign / inputWAVhdr.fmt.NumChannels;

	outputWAVhdr.data.SubChunk2Size = oneChannelSubChunk2Size * outputWAVhdr.fmt.NumChannels;
	outputWAVhdr.fmt.ByteRate = oneChannelByteRate * outputWAVhdr.fmt.NumChannels;
	outputWAVhdr.fmt.BlockAlign = oneChannelBlockAlign * outputWAVhdr.fmt.NumChannels;


	// Write output WAV header to file
	//-------------------------------------------------
	WriteWavHeader(wav_out, outputWAVhdr);

	// Processing loop
	//-------------------------------------------------	
	{
		DSPint sample;
		DSPint BytesPerSample = inputWAVhdr.fmt.BitsPerSample / 8;
		const double SAMPLE_SCALE = -(double)(1 << 31);		//2^31
		DSPint iNumSamples = inputWAVhdr.data.SubChunk2Size / (inputWAVhdr.fmt.NumChannels * inputWAVhdr.fmt.BitsPerSample / 8);

		// exact file length should be handled correctly...
		for (DSPint i = 0; i < iNumSamples / BLOCK_SIZE; i++)
		{
			for (DSPint j = 0; j < BLOCK_SIZE; j++)
			{
				for (DSPint k = 0; k < inputWAVhdr.fmt.NumChannels; k++)
				{
					sample = 0; //debug
					fread(&sample, BytesPerSample, 1, wav_in);
					sample = sample << (32 - inputWAVhdr.fmt.BitsPerSample); // force signextend
					sampleBuffer[k][j] = sample / SAMPLE_SCALE;				// scale sample to 1.0/-1.0 range		
				}
			}

			if (enable == ON )gainProcessing(sampleBuffer, sampleBuffer);

			for (DSPint j = 0; j < BLOCK_SIZE; j++)
			{
				for (DSPint k = 0; k < outputWAVhdr.fmt.NumChannels; k++)
				{
					sample = sampleBuffer[k][j].toLong();	// crude, non-rounding 			
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