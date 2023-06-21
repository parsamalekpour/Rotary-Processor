/*
 * Rotary encoder library for STM/ other C based MCU.
 */

#ifndef rotaryProcessor_h
#define rotaryProcessor_h

// Values returned by 'process'
// No complete step yet.
#define DIR_NONE 0x0
// Clockwise step.
#define DIR_CW 0x10
// Anti-clockwise step.
#define DIR_CCW 0x20
// Default start state
#define R_START 0x0

#define HALF_STEP	0
#define FULL_STEP	1

// Use the half-step state table (emits a code at 00 and 11)
#define RH_CCW_BEGIN 0x1
#define RH_CW_BEGIN 0x2
#define RH_START_M 0x3
#define RH_CW_BEGIN_M 0x4
#define RH_CCW_BEGIN_M 0x5
// Use the full-step state table (emits a code at 00 only)
#define RF_CW_FINAL 0x1
#define RF_CW_BEGIN 0x2
#define RF_CW_NEXT 0x3
#define RF_CCW_BEGIN 0x4
#define RF_CCW_FINAL 0x5
#define RF_CCW_NEXT 0x6



class RotaryProcessor{

	public:
		RotaryProcessor(unsigned int pinA, unsigned int pinB ,unsigned char mode);
		unsigned char process();
		
	protected:
		unsigned int state = R_START;
		unsigned char _mode = HALF_STEP;
		unsigned int _pinA;
		unsigned int _pinB;
		
		
		/*
		* The below state table has, for each state (row), the new state
		* to set based on the next encoder output. From left to right in,
		* the table, the encoder outputs are 00, 01, 10, 11, and the value
		* in that position is the new state to set.
		*/
		const unsigned char httable[6][4] = {
			// R_START (00)
			{RH_START_M,            RH_CW_BEGIN,     RH_CCW_BEGIN,  R_START},
			// RH_CCW_BEGIN
			{RH_START_M | DIR_CCW, R_START,        RH_CCW_BEGIN,  R_START},
			// R_CW_BEGIN
			{RH_START_M | DIR_CW,  RH_CW_BEGIN,     R_START,      R_START},
			// RH_START_M (11)
			{RH_START_M,            RH_CCW_BEGIN_M,  RH_CW_BEGIN_M, R_START},
			// RH_CW_BEGIN_M
			{RH_START_M,            RH_START_M,      RH_CW_BEGIN_M, R_START | DIR_CW},
			// RH_CCW_BEGIN_M
			{RH_START_M,            RH_CCW_BEGIN_M,  RH_START_M,    R_START | DIR_CCW},
			};

		const unsigned char fttable[7][4] = {
			// R_START
			{R_START,    RF_CW_BEGIN,  RF_CCW_BEGIN, R_START},
			// R_CW_FINAL
			{RF_CW_NEXT,  R_START,     RF_CW_FINAL,  R_START | DIR_CW},
			// R_CW_BEGIN
			{RF_CW_NEXT,  RF_CW_BEGIN,  R_START,     R_START},
			// R_CW_NEXT
			{RF_CW_NEXT,  RF_CW_BEGIN,  RF_CW_FINAL,  R_START},
			// R_CCW_BEGIN
			{RF_CCW_NEXT, R_START,     RF_CCW_BEGIN, R_START},
			// R_CCW_FINAL
			{RF_CCW_NEXT, RF_CCW_FINAL, R_START,     R_START | DIR_CCW},
			// R_CCW_NEXT
			{RF_CCW_NEXT, RF_CCW_FINAL, RF_CCW_BEGIN, R_START},
			};

};

#endif
 
