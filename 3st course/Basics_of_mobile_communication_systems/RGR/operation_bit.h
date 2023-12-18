#ifndef OPERATION_BIT_H
#define OPERATION_BIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#include "header.h"


#define FIN_TO_BYTE(BIT) (BIT / SHIFT) * SHIFT + ( (BIT % SHIFT) ? SHIFT: 0)
//#define DEBUG_SREZ

void print_bit_char(u_char a, int count_bit, FILE *out);
void print_bit(u_char *p, int count_bit, FILE *out);
u_char srez(u_char *data, int st, int en);
void shift_data(u_char *data, int len_byte);
void shift_bit_data(u_char *data, int len_byte, int nbit);
int get_bit(u_char *package, int pos);
int set_bit(u_char *package, int pos, int val);
u_char srez_left_res(u_char *data, int st, int en);
void xor_array(u_char *a_res, u_char *b, int nbit);
void shift_bit_add_new_bit(u_char *data, int nbit, u_char new_bit);

#endif