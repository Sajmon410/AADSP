#ifndef _COMMON_H
#define _COMMON_H

#include <stdfix.h>

// potrebno prekopirati sa pocetka stdfix_emu.h ili ukljuciti ceo stdfix_emu.h!
#if defined(__CCC)

#include <stdfix.h>

#define FRACT_NUM(x) (x##r)
#define LONG_FRACT_NUM(x) (x##lr)
#define ACCUM_NUM(x) (x##lk)

#define FRACT_NUM_HEX(x) (x##r)

#define FRACT_TO_INT_BIT_CONV(x) (bitsr(x))
#define INT_TO_FRACT_BIT_CONV(x) (rbits(x))

#define long_accum long accum
#define long_fract long fract

#endif

/////////////////////////////////////////////////////////////////////////////////
// Constant definitions
/////////////////////////////////////////////////////////////////////////////////
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
#define _GAINPROC_ASM
/* DSP type definitions */
typedef short DSPshort;					/* DSP integer */
typedef unsigned short DSPushort;		/* DSP unsigned integer */
typedef int DSPint;						/* native integer */
typedef fract DSPfract;					/* DSP fixed-point fractional, data reg, memory word format s.31 */
typedef long_accum DSPaccum;					/* DSP fixed-point fractional, accum reg format s8.63 */

#endif //_COMMON_H
