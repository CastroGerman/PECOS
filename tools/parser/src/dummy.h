/* 
 * File:   dummy.h
 * 
 * This file contains dummy functions to test all possible branches scenarios, 
 * that means not only different encodings but also veneer extension. 
 * 
 * Author: German Castro
 */

#ifndef DUMMY_H
#define	DUMMY_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

void VarianTheFirst(uint32_t *vector, uint32_t length) __attribute__((section (".sec_VarianTheFirst")));
void AnduinTheSecond(uint32_t *value) __attribute__((section (".sec_AnduinTheSecond")));

#ifdef	__cplusplus
}
#endif

#endif	/* DUMMY_H */