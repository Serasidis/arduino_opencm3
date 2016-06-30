// to add license


/*
 * Arduino srl
 * Firmware and Library Development Team
 *
 * Francesco Alessi (alfran) - francesco@arduino.org
 * 2016 Jun 9: Edited for Arduino STAR OTTO first release
 */


#ifndef Arduino_h
#define Arduino_h

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// some libraries and sketches depend on this
// AVR stuff, assuming Arduino.h or WProgram.h
// automatically includes it...
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "binary.h"
#include "itoa.h"

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

void yield(void);

/* sketch */
extern void setup( void ) ;
extern void loop( void ) ;

typedef void (*voidFuncPtr)( void ) ;

#define WEAK __attribute__ ((weak))

#ifdef __cplusplus
} // extern "C"

#include "Tone.h"

#endif // __cplusplus

// Include board variant
#include "variant.h"
#include "WProgram.h"

#endif // Arduino_h



#include "variant.h"

