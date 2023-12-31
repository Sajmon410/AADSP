#include <stdio.h>
#include <dsplib\wavefile.h>
#include <stdfix.h>
#include <string.h>
#include "common.h"
#include <stdlib.h>

// IO Buffers
__memY DSPfract sampleBuffer[MAX_NUM_CHANNEL][BLOCK_SIZE];

// Processing related variables
DSPfract inputGain = FRACT_NUM(-0.999);
DSPfract variablesGain[INPUT_NUM_CHANNELS];
DSPfract limiterThreshold =  FRACT_NUM(0.999);
typedef struct {
    DSPfract degree;
    DSPfract gain;
} inverter_data_t;
inverter_data_t inverter = {0.3, 0.9};
enum enable { ON=1, OFF=0 };
DSPint enable = ON;

enum mode_controls { MODE0=0, MODE1=1 };
DSPint mode = MODE0;
#ifdef _GAINPROC_ASM
extern void audio_invert_init(inverter_data_t* data, DSPfract degree, DSPfract gain);
extern void gst_audio_invert_transform(__memY inverter_data_t* data,
		__memY DSPfract* input, __memY DSPfract* output);
extern void gainProcessing(__memY DSPfract pIn[][BLOCK_SIZE],__memY DSPfract pOut[][BLOCK_SIZE]);
#else
void audio_invert_init(inverter_data_t* data, DSPfract degree, DSPfract gain)
{
    data->degree = degree;
    data->gain = gain;
}

void gst_audio_invert_transform(__memY inverter_data_t* data,
		__memY DSPfract* input,__memY DSPfract* output)
{
    DSPfract dry = FRACT_NUM(1.0) - data->degree;
    DSPfract val;
    DSPfract degree1 = data->degree;
    DSPfract gain1 = data->gain;
    __memY DSPfract* inputPtr = input;
    __memY DSPfract* outputPtr = output;
    DSPint i;
    for ( i = 0; i < BLOCK_SIZE; i++) {

        val = (DSPaccum)(dry - degree1);
        val = (DSPfract)(*inputPtr) * val;
        *outputPtr = val * gain1;

        inputPtr++;
        outputPtr++;
    }
}

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


void gainProcessing(__memY DSPfract pIn[][BLOCK_SIZE],__memY DSPfract pOut[][BLOCK_SIZE])
{
	__memY DSPfract* ptrInL = *(pIn+ LEFT_CH);
	__memY DSPfract* ptrOutL = *(pOut+ LEFT_CH);
	__memY DSPfract* ptrInR = *(pIn + RIGHT_CH);
	__memY DSPfract* ptrOutR = *(pOut + RIGHT_CH);
	__memY DSPfract* lsSamplePrt = *(pOut + LEFTS_CH) ;
	__memY DSPfract* rsSamplePrt = *(pOut + RIGHTS_CH) ;
	DSPint i;
	for ( i = 0; i < BLOCK_SIZE; i++)
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
		gst_audio_invert_transform(&inverter, ptrInL, ptrOutL);
		gst_audio_invert_transform(&inverter, ptrInR, ptrOutR);
	}

}
#endif
int main(int argc, char *argv[])
 {
    WAVREAD_HANDLE *wav_in;
    WAVWRITE_HANDLE *wav_out;

	char WavInputName[256];
	char WavOutputName[256];

    DSPint inChannels;
    DSPint outChannels;
    DSPint bitsPerSample;
    DSPint sampleRate;
    DSPint iNumSamples;
    DSPint i;
    DSPint j;

    audio_invert_init(&inverter,0.3,0.9);
	// Init channel buffers
	for(i=0; i<MAX_NUM_CHANNEL; i++)
		for(j=0; j<BLOCK_SIZE; j++)
			sampleBuffer[i][j] = FRACT_NUM(0.0);

	// Open input wav file
	//-------------------------------------------------
	strcpy(WavInputName,argv[0]);
	wav_in = cl_wavread_open(WavInputName);
	 if(wav_in == NULL)
    {
        printf("Error: Could not open wavefile.\n");
        return -1;
    }
	//-------------------------------------------------
	 if (argc >= 3) {
		 enable = 1; // 0 OFF DOK JE 1 ON
		 inputGain = MINUS_3DB;
		 mode = 0; // mode 1 da ne prolazi kroz inverter a 0 da prolazi
	 	}
	// Read input wav header
	//-------------------------------------------------
	inChannels = cl_wavread_getnchannels(wav_in);
    bitsPerSample = cl_wavread_bits_per_sample(wav_in);
    sampleRate = cl_wavread_frame_rate(wav_in);
    iNumSamples =  cl_wavread_number_of_frames(wav_in);
	//-------------------------------------------------

	// Open output wav file
	//-------------------------------------------------
	strcpy(WavOutputName,argv[1]);
	outChannels = OUTPUT_NUM_CHANNELS;
	wav_out = cl_wavwrite_open(WavOutputName, bitsPerSample, outChannels, sampleRate);
	if(!wav_out)
    {
        printf("Error: Could not open wavefile.\n");
        return -1;
    }
	//-------------------------------------------------

	// Processing loop
	//-------------------------------------------------
    {
		int i;
		int j;
		int k;
		int sample;

		// exact file length should be handled correctly...
		for(i=0; i<iNumSamples/BLOCK_SIZE; i++)
		{
			for(j=0; j<BLOCK_SIZE; j++)
			{
				for(k=0; k<inChannels; k++)
				{
					sample = cl_wavread_recvsample(wav_in);
        			sampleBuffer[k][j] = rbits(sample);
				}
			}

			if (enable == ON )gainProcessing(sampleBuffer, sampleBuffer);

			for(j=0; j<BLOCK_SIZE; j++)
			{
				for(k=0; k<outChannels; k++)
				{
					sample = bitsr(sampleBuffer[k][j]);
					cl_wavwrite_sendsample(wav_out, sample);
				}
			}
		}
	}

	// Close files
	//-------------------------------------------------
    cl_wavread_close(wav_in);
    cl_wavwrite_close(wav_out);
	//-------------------------------------------------

    return 0;
 }

