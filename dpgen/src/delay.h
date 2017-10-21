#ifndef DELAY_H
#define DELAY_H
/*************/
/*
 * File: Delay.h
 * Author: Andres Rebeil
 * NetID: andres07
 * Date: October 21st, 2017
 *
 * Description: 
 */
 /**************************************************************************************************/
//DELAY DEFINES
//REGISTER DELAY
#define REG_1B 2.616
#define REG_2B 2.644
#define REG_8B 2.879
#define REG_16B 3.061
#define REG_32B 3.602
#define REG_64b 3.966
//ADDER DELAY
#define ADD_1B 2.704
#define ADD_2B 3.713
#define ADD_8B 4.924
#define ADD_16B 5.638
#define ADD_32B 7.270
#define ADD_64B 9.566
//SUBTRACT DELAY
#define SUB_1B 3.024
#define SUB_2B 3.412
#define SUB_8B 4.890
#define SUB_16B 5.569
#define SUB_32B 7.253
#define SUB_64B 9.566
//MULTIPLIER DELAY
#define MUL_1B 2.438
#define MUL_2B 3.651
#define MUL_8B 7.453
#define MUL_16B 7.811
#define MUL_32B 12.395
#define MUL_64B 15.354
//COMPARATOR DELAY
#define COMP_1B 3.031
#define COMP_2B 3.934
#define COMP_8B 5.949
#define COMP_16B 6.256
#define COMP_32B 7.264
#define COMP_64B 8.416
//MUX2x1 DELAY
#define MUX_1B 4.083
#define MUX_2B 4.115
#define MUX_8B 4.815
#define MUX_16B 5.623
#define MUX_32B 8.079
#define MUX_64B 8.766
//SHR DELAY
#define SHR_1B 3.644
#define SHR_2B 4.007
#define SHR_8B 5.178
#define SHR_16B 6.460
#define SHR_32B 8.819
#define SHR_64B 11.095
//SHL DELAY
#define SHL_1B 3.614
#define SHL_2B 3.980
#define SHL_8B 5.152
#define SHL_16B 6.549
#define SHL_32B 8.565
#define SHL_64B 11.220
 //DIV DELAY
#define DIV_1B 0.619
#define DIV_2B 2.144
#define DIV_8B 15.439
#define DIV_16B 33.093
#define DIV_32B 86.312
#define DIV_64B 243.223
//MOD DELAY
#define MOD_1B 0.758
#define MOD_2B 2.149
#define MOD_8B 16.078
#define MOD_16B 35.563
#define MOD_32B 88.142
#define MOD_64B 250.583
//INC DELAY
#define INC_1B 1.792
#define INC_2B 2.218
#define INC_8B 3.3111
#define INC_16B 3.471
#define INC_32B 4.347
#define INC_64B 6.200
//DEC DELAY
#define DEC_1B 1.792
#define DEC_2B 2.218
#define DEC_8B 3.108
#define DEC_16B 3.701
#define DEC_32B 4.685
#define DEC_64B 6.503
 
#endif //Delay_H

