#ifndef AUDIO_INVERT_H
#define AUDIO_INVERT_H

typedef struct {
    double degree;
    double gain;
} inverter_data_t;

void audio_invert_init(inverter_data_t* data, double degree, double gain);

void gst_audio_invert_transform(inverter_data_t* data, double* input, double* output, unsigned int num_samples);

#endif // AUDIO_INVERT_H