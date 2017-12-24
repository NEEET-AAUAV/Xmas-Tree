/*
                                                                      ,----,
                                                                    ,/   .`|
 ,--,     ,--,           ____                                     ,`   .'  :
 |'. \   / .`|         ,'  , `.                                 ;    ;     /
 ; \ `\ /' / ;      ,-+-,.' _ |                               .'___,/    ,' __  ,-.
 `. \  /  / .'   ,-+-. ;   , ||             .--.--.           |    :     |,' ,'/ /|
  \  \/  / ./   ,--.'|'   |  || ,--.--.    /  /    '          ;    |.';  ;'  | |' | ,---.     ,---.
   \  \.'  /   |   |  ,', |  |,/       \  |  :  /`./          `----'  |  ||  |   ,'/     \   /     \
    \  ;  ;    |   | /  | |--'.--.  .-. | |  :  ;_                '   :  ;'  :  / /    /  | /    /  |
   / \  \  \   |   : |  | ,    \__\/: . .  \  \    `.             |   |  '|  | ' .    ' / |.    ' / |
  ;  /\  \  \  |   : |  |/     ," .--.; |   `----.   \            '   :  |;  : | '   ;   /|'   ;   /|
./__;  \  ;  \ |   | |`-'     /  /  ,.  |  /  /`--'  /            ;   |.' |  , ; '   |  / |'   |  / |
|   : / \  \  ;|   ;/        ;  :   .'   \'--'.     /             '---'    ---'  |   :    ||   :    |
;   |/   \  ' |'---'         |  ,     .-./  `--'---'                              \   \  /  \   \  /
`---'     `--`                `--`---'                                             `----'    `----'

                                                   ,----,
         ,--.                                    ,/   .`|
       ,--.'|    ,---,.    ,---,.    ,---,.    ,`   .'  :
   ,--,:  : |  ,'  .' |  ,'  .' |  ,'  .' |  ;    ;     /
,`--.'`|  ' :,---.'   |,---.'   |,---.'   |.'___,/    ,'
|   :  :  | ||   |   .'|   |   .'|   |   .'|    :     |
:   |   \ | ::   :  |-,:   :  |-,:   :  |-,;    |.';  ;
|   : '  '; |:   |  ;/|:   |  ;/|:   |  ;/|`----'  |  |
'   ' ;.    ;|   :   .'|   :   .'|   :   .'    '   :  ;
|   | | \   ||   |  |-,|   |  |-,|   |  |-,    |   |  '
'   : |  ; .''   :  ;/|'   :  ;/|'   :  ;/|    '   :  |
|   | '`--'  |   |    \|   |    \|   |    \    ;   |.'
'   : |      |   :   .'|   :   .'|   :   .'    '---'
;   |.'      |   | ,'  |   | ,'  |   | ,'
'---'        `----'    `----'    `----'


Project and designed by
* André Gradim
* Pedro Martins

With the helping of:
* Hugo Leal
* Beatriz Silva

NEEET 2017-18
*/


// MACROS
#define vector_len(X) (sizeof(X) / sizeof(X[0]))
#define ENABLE_DECODERS() digitalWrite(11, HIGH)
#define DISABLE_DECODERS() digitalWrite(11, LOW)

// TIMES
#define ROW_HOLD_TIME 250        // us
#define COLUMN_HOLD_TIME 400     // us
#define RND_LED_HOLD_TIME 300    // us
#define SPIRAL_LED_HOLD_TIME 30  // ms
#define N_PERSIST_ITER 500

// TREE CONSTANTS
#define MAX_ROWS 8
#define MAX_COLUMNS 8

// RANDOM CONSTANTS
#define FASTER_RND_SEQ 1
#define SLOWER_RND_SEQ 0




/*
 *  FUNCTION HEADERS DECLARATION
 */
uint8_t lfsr();
void ascend();
void descend();
void ascend_and_descend();
void clockwise();
void counter_clockwise();
void set_columns(uint8_t columns);
void set_rows(uint8_t rows);
void blink();
void random_seq(uint8_t n_leds, uint8_t faster, uint8_t scale_factor);
void spiral_down_clockwise();
void spiral_up_counter_clockwise();

/*
 *  VARIABLE DECLARATION
 */
// mapping real column order with decoder outputs
uint8_t colums_order[12] = {0, 1, 2, 4, 2, 5, 3, 5, 6, 7, 6, 1};
uint8_t rows_order[8] = {0, 1, 2, 3, 4, 5, 6, 7};

// counters
uint8_t columns = 0x00;
uint8_t rows = 0x00;

uint8_t flag = 0;
uint8_t flag_counter = 0;



/*
 *  PINOUT CONFIGURATION
 */

void setup() {
  // Enable Decoder
  pinMode(11, OUTPUT);      // D11

  // CONTROL  IC1
  pinMode(7, OUTPUT);       // D7
  pinMode(6, OUTPUT);       // D6
  pinMode(5, OUTPUT);       // D5

  // CONTROL  IC2
  pinMode(4, OUTPUT);       // D4
  pinMode(3, OUTPUT);       // D3
  pinMode(2, OUTPUT);       // D2
}


void loop() {
  uint8_t k;
  ENABLE_DECODERS();

  while(true)
  {
    for(k = 0; k < 1*2*MAX_ROWS; k++)
    {
      ascend_and_descend();
    }
    for(k = 0; k < 2; k++)
    {
      spiral_down_clockwise();
    }
    for(k = 0; k < 60; k++)
    {
      random_seq(13, SLOWER_RND_SEQ, 2);
    }
    for(k = 0; k < 2*MAX_COLUMNS; k++)
    {
      clockwise();
    }
    for(k = 0; k < 200; k++)
    {
      random_seq(4, FASTER_RND_SEQ, 1);
    }
    for(k = 0; k < 3*MAX_COLUMNS; k++)
    {
      counter_clockwise();
    }
    for(k = 0; k < 90; k++)
    {
      random_seq(7, FASTER_RND_SEQ, 10);
    }
    for(uint8_t k = 0; k < 4*2*MAX_ROWS; k++)
    {
      ascend_and_descend();
    }
    for(k = 0; k < 130; k++)
    {
      random_seq(20, SLOWER_RND_SEQ, 4);
    }
    for(k = 0; k < 3; k++)
    {
      spiral_up_counter_clockwise();
    }
    for(k = 0; k < 2*MAX_COLUMNS; k++)
    {
      clockwise();
    }
    for(k = 0; k < 2*MAX_COLUMNS; k++)
    {
      counter_clockwise();
    }
    for(k = 0; k < 2*MAX_ROWS; k++)
    {
      descend();
    }
    for(k = 0; k < 80; k++)
    {
      random_seq(4, FASTER_RND_SEQ, 1);
    }
    for(k = 0; k < MAX_ROWS; k++)
    {
      ascend();
    }
    spiral_down_clockwise();
    //blink();
  }
}


/*
 * Linear-feedback shift register algorithm
 * Feedback polynomial: x^16 + x^15 + x^13 + x^9 + x^6 + x^4 + x^2 + 1
 *
 * Returns a random bit (0, 1)
 *
 */
uint8_t lfsr(){
  static uint16_t seed = 0xACE1;
  static uint16_t rndNum = seed;

  uint8_t rndBit = ((rndNum >> 0) ^ (rndNum >> 1) ^ (rndNum >> 3) ^ (rndNum >> 7) ^ (rndNum >> 10) ^ (rndNum >> 12) ^ (rndNum >> 14)) & 1;
  rndNum = (rndNum >> 1) | (rndBit << 15);

  return rndBit;
}

// "moves" the active leds one row up
void ascend(){
      set_rows(rows);
      for(int k = 0, columns = 0; k < N_PERSIST_ITER; k++, columns++)
      {
        set_columns(columns);
        columns = (columns == vector_len(colums_order) ? 0 : columns);
        delayMicroseconds(ROW_HOLD_TIME);
      }
      rows = (rows == MAX_ROWS ? 0 : --rows);
}

// "moves" the active leds one row down
void descend(){
      set_rows(rows);
      for(int k = 0, columns = vector_len(colums_order); k < N_PERSIST_ITER; k++, columns--)
      {
        set_columns(columns);
        columns = (columns == 0 ? vector_len(colums_order) : columns);
        delayMicroseconds(ROW_HOLD_TIME);
      }
      rows = (rows == MAX_ROWS ? 0 : ++rows);
}

// Complete sequence: "moves" the active leds up and down across all rows
void ascend_and_descend(){
  flag == 1 ? descend() : ascend();

  if(flag_counter == 7)
  {
    flag = !flag;
    flag_counter = 0;
  }
  flag_counter++;
}

// "moves" the active leds one column clockwise
void clockwise(){
  set_columns(columns);
  for(int k = 0, rows = 0; k < N_PERSIST_ITER; k++, rows++)
  {
    set_rows(rows);
    rows = (rows == MAX_ROWS ? 0 : rows);
    delayMicroseconds(COLUMN_HOLD_TIME);
  }
  columns = (columns == vector_len(colums_order) ? 0 : ++columns);
}

// "moves" the active leds one column counter_clockwise
void counter_clockwise(){
  set_columns(columns);
  for(int k = 0, rows = 0; k < N_PERSIST_ITER; k++, rows++)
  {
    set_rows(rows);
    rows = (rows == MAX_ROWS ? 0 : rows);
    delayMicroseconds(COLUMN_HOLD_TIME);
  }
  columns = (columns == 0 ? vector_len(colums_order) : --columns);
}

// "moves" the only active led spirally
// clockwise and then one row down
void spiral_down_clockwise(){
  for(uint8_t k = 0, rows = 0; k < MAX_ROWS; k++, rows++)
  {
    set_rows(rows);
    for(uint8_t m = 0, columns = 0; m < vector_len(colums_order); m++, columns++)
    {
      set_columns(columns);
      columns = (columns == vector_len(colums_order) ? 0 : columns);
      delay(SPIRAL_LED_HOLD_TIME);
    }
  }
}

// "moves" the only active led spirally
// counter_clockwise and then one row up
void spiral_up_counter_clockwise(){
  for(uint8_t k = (MAX_ROWS-1), rows = (MAX_ROWS-1); k > 0; k--, rows--)
  {
    set_rows(rows);
    for(uint8_t m = 0, columns = 0; m < vector_len(colums_order); m++, columns--)
    {
      set_columns(columns);
      columns = (columns == 0 ? vector_len(colums_order) : columns);
      delay(SPIRAL_LED_HOLD_TIME);
    }
  }
}

// Blinks all leds
void blink(){

  for(int r = 0, rows = 0; r < N_PERSIST_ITER; r++, rows++)
  {
    set_rows(rows);
    for(int c = 0, columns = 0; c < N_PERSIST_ITER; c++, columns++)
    {
      set_columns(columns);
      columns = (columns == vector_len(colums_order) ? 0 : columns);
    }
    rows = (rows == MAX_ROWS ? 0 : rows);
  }
  DISABLE_DECODERS();
  delay(1000);
  ENABLE_DECODERS();
}

/*
 * Random LED Behaviour
 *
 * INPUTS
 *    - n_leds: number of leds to be active during the time interval
 *    - faster: boolean variable that selects the LEDs alternation speed
 *    - scale_factor: increases the time of the function execution
 *
 */
void random_seq(uint8_t n_leds, uint8_t faster, uint8_t scale_factor){
    uint8_t leds_seq[n_leds];
    for(uint8_t k = 0; k < n_leds; k++)
    {
      leds_seq[k] = ( (lfsr()) << 7 ) | ( (lfsr()) << 6 ) | ( (lfsr()) << 5 ) | \
                    ( (lfsr()) << 2 ) | ( (lfsr()) << 1 ) | ( lfsr() );
    }

    for(int m = 0; m < N_PERSIST_ITER; m++)
    {
      for(int k = 0; k < n_leds; k++)
      {
        columns = leds_seq[k] & 0b00000111;
        rows    = (leds_seq[k] & 0b11100000) >> 5;
        set_columns(columns);
        set_rows(rows);
        if(!faster) delayMicroseconds(RND_LED_HOLD_TIME / scale_factor);
      }
      if(faster) delayMicroseconds(RND_LED_HOLD_TIME / scale_factor);
    }
}

/*
 * Abstraction layer for setting rows & columns
 *
 */
void set_columns(uint8_t columns)
{
  digitalWrite(4, colums_order[columns] & 0x01);
  digitalWrite(3, colums_order[columns] & 0x02);
  digitalWrite(2, colums_order[columns] & 0x04);
}

void set_rows(uint8_t rows)
{
  digitalWrite(7, rows & 0x01);
  digitalWrite(6, rows & 0x02);
  digitalWrite(5, rows & 0x04);
}
