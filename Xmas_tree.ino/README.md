# Brief Code Documentation

## CONSTANTS
```c
ROW_HOLD_TIME 			// Time Interval ($\mu s$) a Row value cannot change
COLUMN_HOLD_TIME     	// Time Interval ($\mu s$) a Row value cannot change
RND_LED_HOLD_TIME       // Base Time Interval a LED is ON in the Random Mode
SPIRAL_LED_HOLD_TIME 	// Time Interval (ms) a LED is ON in the Spiral Mode 
N_PERSIST_ITER		 	// Number of iterations a LED state persists
```

## Functions
```c
// Implements the Random Generator Algorithm
uint8_t lfsr();

// "moves" the active leds one row up
void ascend();

// "moves" the active leds one row down
void descend();

// Complete sequence: "moves" the active leds up and down across all rows
void ascend_and_descend();

// "moves" the active leds one column clockwise
void clockwise();

// "moves" the active leds one column counter_clockwise
void counter_clockwise();

// "moves" the only active led spirally
// clockwise and then one row down
void spiral_down_clockwise();

// "moves" the only active led spirally
// counter_clockwise and then one row up
void spiral_up_counter_clockwise();

// Blinks all leds
void blink();

/*
 * Random LED Behaviour
 *
 * INPUTS
 *    - n_leds: number of leds to be active during the time interval
 *    - faster: boolean variable that selects the LEDs alternation speed
 *    - scale_factor: increases the time of the function execution
 *
 */
void random_seq(uint8_t n_leds, uint8_t faster, uint8_t scale_factor);

// Abstraction layer for setting rows & columns
void set_columns(uint8_t columns);
void set_rows(uint8_t rows);
```

## Pseudo-Random Algorithm 
The Random Algorithm used is a Linear-feedback shift register  
The Algorithm starts with a seed and then using a polynom performs a sequence of XOR Operations.    
The result of this operations is a new bit that is either retrieved and concatenated to the binary data string  

For more informations, visit the [Wikipedia Page on LSFR](https://en.wikipedia.org/wiki/Linear-feedback_shift_register)
