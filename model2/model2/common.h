#ifndef COMMON_H
#define COMMON_H

#include "stdfix_emu.h"

/* Basic constants */

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
//#define PLUS_6DB 1.99526
#define MINUS_2DB FRACT_NUM(0.794328)
#define MINUS_4DB FRACT_NUM(0.630957)
#define MINUS_12DB FRACT_NUM(0.251189) 
#define MINUS_3DB FRACT_NUM(0.70795)
/////////////////////////////////////////////////////////////////////////////////
// Constant definitions
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////

/* DSP type definitions */
typedef short DSPshort;            /* DSP integer */
typedef unsigned short DSPushord;  /* DSP unsigned integer */
typedef int DSPint;                /* native integer */
typedef fract DSPfract;            /* DSP fixed-point fractional */
typedef long_accum DSPaccum;       /* DSP fixed-point fractional */

#endif
