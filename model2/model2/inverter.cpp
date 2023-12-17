/**
 *
 * Swaps upper and lower half of audio samples. Mixing an inverted sample on top of
 * the original with a slight delay can produce effects that sound like resonance.
 * Creating a stereo sample from a mono source, with one channel inverted produces wide-stereo sounds.
 *
 */

#include "inverter.h"

void audio_invert_init(inverter_data_t* data, DSPfract degree, DSPfract gain)
{
    data->degree = degree;
    data->gain = gain;
}

void gst_audio_invert_transform(inverter_data_t* data,
    DSPfract* input, DSPfract* output, unsigned int num_samples)
{
    DSPfract dry = FRACT_NUM(1.0) - data->degree;
    DSPfract val;
    DSPfract degree1 = data->degree;
    DSPfract gain1 = data->gain;
    DSPfract* inputPtr = input;
    DSPfract* outputPtr = output;

    for (DSPint i = 0; i < num_samples; i++) {
        
        val = (DSPaccum)(dry - degree1);
        val = (DSPfract)(*inputPtr) * val;
        *outputPtr = val * gain1;

        inputPtr++;
        outputPtr++;
    }
}
