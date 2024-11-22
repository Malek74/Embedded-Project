#ifndef ultrasonic
#define ultrasonic

#include <stdint.h>

// Function prototypes
void ultrasonic_Init(void);                // Initialize GPIO pins
uint32_t ultrasonic_GetDistance(void);     // Get distance in centimeters
void DelayMicroseconds(uint32_t us);   // Microsecond delay function

#endif // ultrasonic_H