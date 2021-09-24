#include "app/utils_ctboard.h"

int main(void){
	//ADRESS DEFINITIONS
	#define SWITCH_ADDR 0x60000200
	#define LED_ADDR 0x60000100
	#define SEVEN_0_ADDR 0x60000110
	#define SEVEN_0_AUTO_ADDR 0x60000114
	#define ROTARY_ADDR 0x60000211
	
	//SEVEN SEGMENT CHARACTER ARRAY
	const uint8_t ssbp[16]={0x0C0, 0x0F9, 0x0A4, 0x0B0, 0x099, 0x092, 0x082, 0x0F8, 0x080, 0x090, 0x088, 0x083, 0x0C6, 0x0A1, 0x086, 0x08E};
	const uint8_t sspd[16]={0x0FE, 0x07E, 0x0FC, 0x07C, 0x0FD, 0x07D, 0x0BD, 0x03D, 0x0BF, 0x03F, 0x09F, 0x01F, 0x0DF, 0x05F, 0x0DE, 0x05E};
	
	//INITIALIZE VARIABLES
	uint32_t sw_state=0;
	uint8_t rotary_state=0;
	
	while(1){
		rotary_state = read_byte(ROTARY_ADDR); //read rotary state and write to variable
		rotary_state&=0x0F; //bitmask rotary state with 0x0F
		sw_state=read_word(SWITCH_ADDR); //read switch states
		sw_state&=0x0FFFF0000; //bitmask switch state because we need the lower LEDs for the rotary and seven segment display
		write_word(LED_ADDR, sw_state); //switch LEDs according to masked variable
		write_byte(SEVEN_0_ADDR, ssbp[rotary_state]); //read seven segment output from the array
		write_byte(SEVEN_0_ADDR+1, sspd[rotary_state]); //write position to second seven segment display
		write_byte(LED_ADDR, rotary_state); //write binary state of rotary switch to LEDs [0..7]
		write_byte(LED_ADDR+1, ssbp[rotary_state]); //write seven segment output to LEDs [8...15] for debugging
	}
}
