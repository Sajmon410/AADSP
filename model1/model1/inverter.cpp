/**
 *
 * Swaps upper and lower half of audio samples. Mixing an inverted sample on top of
 * the original with a slight delay can produce effects that sound like resonance.
 * Creating a stereo sample from a mono source, with one channel inverted produces wide-stereo sounds.
 *
 */

#include "inverter.h"

void audio_invert_init(inverter_data_t* data, double degree, double gain)
{
    data->degree = degree;
    data->gain = gain;
}

void gst_audio_invert_transform(inverter_data_t* data,
    double* input, double* output, unsigned int num_samples)
{
    double dry = 1.0 - data->degree;
    double val;

    double* ptrIn = input;
    double* ptrOut = output;

    for (int i = 0; i < num_samples; i++) {
        val = (*ptrIn) * dry - (*ptrIn) * data->degree;
        (*ptrOut) = val * data->gain;

        ptrIn++;
        ptrOut++;
    }
}
