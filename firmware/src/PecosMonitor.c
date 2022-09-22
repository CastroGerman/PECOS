/*
 * File: PecosMonitor.c
 *
 * This file was made following the official ARM�v7-M Architecture Reference Manual
 * https://web.eecs.umich.edu/~prabal/teaching/eecs373-f10/readings/ARMv7-M_ARM.pdf
 *
 * Author: German Castro
 */

#include "PecosMonitor.h"
#include <assert.h>
#include <stdio.h>

/*------ Usage Fault Manager Facilities ------*/

UsageFaultManagerSignal UsageFaultManager_ClearTrapStatus_DIVBYZERO(UsageFaultManager * const me) {
	*(me->CFSR) |= (1UL << 25U);
	return USAGEFAULTMANAGER_OK_SIG;
}

UsageFaultManagerSignal UsageFaultManager_EnableHandler(UsageFaultManager * const me) {
	*(me->SHCSR) |= (1UL << 18U);
	return USAGEFAULTMANAGER_OK_SIG;
}

UsageFaultManagerSignal UsageFaultManager_EnableTrap_DIVBYZERO(UsageFaultManager * const me) {
	*(me->CCR) |= (1UL << 4U);
	return USAGEFAULTMANAGER_OK_SIG;
}

uint8_t UsageFaultManager_GetTrapStatus_DIVBYZERO(UsageFaultManager * const me) {
	return ((*(me->CFSR) >> 25U) & 1UL);
}

uint8_t UsageFaultManager_GetTrapStatus_UNALIGNED(UsageFaultManager * const me) {
	return ((*(me->CFSR) >> 24U) & 1UL);
}

uint8_t UsageFaultManager_GetTrapStatus_NOCP(UsageFaultManager * const me) {
	return ((*(me->CFSR) >> 19U) & 1UL);
}

uint8_t UsageFaultManager_GetTrapStatus_INVPC(UsageFaultManager * const me) {
	return ((*(me->CFSR) >> 18U) & 1UL);
}

uint8_t UsageFaultManager_GetTrapStatus_INVSTATE(UsageFaultManager * const me) {
	return ((*(me->CFSR) >> 17U) & 1UL);
}

uint8_t UsageFaultManager_GetTrapStatus_UNDEFINSTR(UsageFaultManager * const me) {
	return ((*(me->CFSR) >> 16U) & 1UL);
}

void UsageFaultManager_ctor(UsageFaultManager * const me, volatile uint32_t *CCR, volatile uint32_t *CFSR, volatile uint32_t *SHCSR) {
	static const UsageFaultManagerVT vTable = {
			.ClearTrapStatus_DIVBYZERO = &UsageFaultManager_ClearTrapStatus_DIVBYZERO,
			.EnableHandler = &UsageFaultManager_EnableHandler,
			.EnableTrap_DIVBYZERO = &UsageFaultManager_EnableTrap_DIVBYZERO,
			.GetTrapStatus_DIVBYZERO = &UsageFaultManager_GetTrapStatus_DIVBYZERO,
            .GetTrapStatus_INVPC = &UsageFaultManager_GetTrapStatus_INVPC,
            .GetTrapStatus_INVSTATE = &UsageFaultManager_GetTrapStatus_INVSTATE,
            .GetTrapStatus_NOCP = &UsageFaultManager_GetTrapStatus_NOCP,
            .GetTrapStatus_UNALIGNED = &UsageFaultManager_GetTrapStatus_UNALIGNED,
            .GetTrapStatus_UNDEFINSTR = &UsageFaultManager_GetTrapStatus_UNDEFINSTR
	};
	me->vptr = &vTable;
	assert(CCR);
	me->CCR = CCR;
	assert(CFSR);
	me->CFSR = CFSR;
	assert(SHCSR);
	me->SHCSR = SHCSR;
}

/*------ Bus Fault Manager Facilities ------*/

BusFaultManagerSignal BusFaultManager_EnableHandler(BusFaultManager * const me) {
	*(me->SHCSR) |= (1UL << 18U);
	return BUSFAULTMANAGER_OK_SIG;
}

uint8_t BusFaultManager_GetTrapStatus_BFARVALID(BusFaultManager * const me) {
    return ((*(me->CFSR) >> 15U) & 1UL);
}

uint8_t BusFaultManager_GetTrapStatus_LSPERR(BusFaultManager * const me) {
    return ((*(me->CFSR) >> 13U) & 1UL);
}

uint8_t BusFaultManager_GetTrapStatus_STKERR(BusFaultManager * const me) {
    return ((*(me->CFSR) >> 12U) & 1UL);
}

uint8_t BusFaultManager_GetTrapStatus_UNSTKERR(BusFaultManager * const me) {
    return ((*(me->CFSR) >> 11U) & 1UL);
}

uint8_t BusFaultManager_GetTrapStatus_IMPRECISERR(BusFaultManager * const me) {
    return ((*(me->CFSR) >> 10U) & 1UL);
}

uint8_t BusFaultManager_GetTrapStatus_PRECISERR(BusFaultManager * const me) {
    return ((*(me->CFSR) >> 9U) & 1UL);
}

void BusFaultManager_ctor(BusFaultManager * const me, volatile uint32_t *CCR, volatile uint32_t *CFSR, volatile uint32_t *SHCSR) {
	static const BusFaultManagerVT vTable = {
			.EnableHandler = &BusFaultManager_EnableHandler,
			.GetTrapStatus_BFARVALID = &BusFaultManager_GetTrapStatus_BFARVALID,
            .GetTrapStatus_LSPERR = &BusFaultManager_GetTrapStatus_LSPERR,
            .GetTrapStatus_STKERR = &BusFaultManager_GetTrapStatus_STKERR,
            .GetTrapStatus_UNSTKERR = &BusFaultManager_GetTrapStatus_UNSTKERR,
            .GetTrapStatus_IMPRECISERR = &BusFaultManager_GetTrapStatus_IMPRECISERR,
            .GetTrapStatus_PRECISERR = &BusFaultManager_GetTrapStatus_PRECISERR
	};
	me->vptr = &vTable;
	assert(CCR);
	me->CCR = CCR;
	assert(CFSR);
	me->CFSR = CFSR;
	assert(SHCSR);
	me->SHCSR = SHCSR;
}


/*------ System Manager Facilities ------*/

SystemManagerSignal SystemManager_PrintFaultStackFrame(SystemManager * const me, uint32_t excReturn, uint32_t calleeStackSizeUsed) {
	uint32_t *stackFrame = NULL;
	/* Add self stack size used */
	calleeStackSizeUsed += 0x10;
	/* Check if MSP or PSP was being used */
	if ((excReturn >> 2U) & 1UL) {
		__asm__ ("mrs %[stackFrame], psp" : [stackFrame] "=r" (stackFrame));
	} else {
		__asm__ ("mrs %[stackFrame], msp" : [stackFrame] "=r" (stackFrame));
	}

	printf("\r\n[Fault Stack Frame]\r\n");
	printf("r0 = 0x%lx\r\n", stackFrame[0 + calleeStackSizeUsed/4]);
	printf("r1 = 0x%lx\r\n", stackFrame[1 + calleeStackSizeUsed/4]);
	printf("r2 = 0x%lx\r\n", stackFrame[2 + calleeStackSizeUsed/4]);
	printf("r3 = 0x%lx\r\n", stackFrame[3 + calleeStackSizeUsed/4]);
	printf("r12 = 0x%lx\r\n", stackFrame[4 + calleeStackSizeUsed/4]);
	printf("LR = 0x%lx\r\n", stackFrame[5 + calleeStackSizeUsed/4]);
	printf("PC = 0x%lx\r\n", stackFrame[6 + calleeStackSizeUsed/4]);
	printf("PSR = 0x%lx\r\n", stackFrame[7 + calleeStackSizeUsed/4]);
	return SYSTEMMANAGER_OK_SIG;
}

__attribute__((__noreturn__))
void SystemManager_ResetSystem(SystemManager * const me) {
	/* Ensure all outstanding memory accesses included
	 * buffered write are completed before reset */
	__asm__ volatile ("dsb sy":::"memory");
	*(me->AIRCR) = (uint32_t)(	(0x5FAUL << 16U) |
								((*me->AIRCR) & (7UL << 8U)) | /* Keep priority group unchanged */
								(1UL << 2U));
	/* Ensure completion of memory access */
	__asm__ volatile ("dsb sy":::"memory");
	/* Wait until reset */
	for(;;) {
		__asm__("nop");
	}
}

void SystemManager_ctor(SystemManager * const me, volatile uint32_t *AIRCR) {
	static const SystemManagerVT vTable = {
			.PrintFaultStackFrame = &SystemManager_PrintFaultStackFrame,
			.ResetSystem = &SystemManager_ResetSystem
	};
	me->vptr = &vTable;
	assert(AIRCR);
	me->AIRCR = AIRCR;
}


/*------ PECOS Monitor Facilities ------*/

PecosMonitorSignal PecosMonitor_PrintFaultStackFrame(PecosMonitor * const me, uint32_t calleeStackSizeUsed) {
	me->sysMngr.vptr->PrintFaultStackFrame(&(me->sysMngr), me->excReturn, calleeStackSizeUsed + 0x08);
	return PECOSMONITOR_OK_SIG;
}

PecosMonitorSignal PecosMonitor_SaveExcReturn(PecosMonitor * const me, uint32_t excReturn) {
	me->excReturn = excReturn;
	return PECOSMONITOR_OK_SIG;
}

void PecosMonitor_ctor(PecosMonitor * const me, volatile uint32_t *AIRCR, volatile uint32_t *CCR, volatile uint32_t *CFSR, volatile uint32_t *SHCSR) {
	static const PecosMonitorVT vTable = {
			.PrintFaultStackFrame = &PecosMonitor_PrintFaultStackFrame,
			.SaveExcReturn = &PecosMonitor_SaveExcReturn
	};
	me->vptr = &vTable;
	me->excReturn = 0;
	SystemManager_ctor(&(me->sysMngr), AIRCR);
	UsageFaultManager_ctor(&(me->usgFltMngr), CCR, CFSR, SHCSR);
	BusFaultManager_ctor(&(me->busFltMngr), CCR, CFSR, SHCSR);
}
