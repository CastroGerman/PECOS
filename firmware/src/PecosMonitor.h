/* 
 * File:   PecosMonitor.h
 * 
 * This file was made following the official ARM®v7-M Architecture Reference Manual
 * https://web.eecs.umich.edu/~prabal/teaching/eecs373-f10/readings/ARMv7-M_ARM.pdf
 * 
 * Author: German Castro
 */

#ifndef PECOSMONITOR_H
#define	PECOSMONITOR_H

#ifdef	__cplusplus
extern "C" {
#endif


#include <stdint.h>

/*------ Usage Fault Manager Facilities ------*/

typedef enum UsageFaultManagerSignal {
	USAGEFAULTMANAGER_OK_SIG,
	USAGEFAULTMANAGER_ERROR_SIG
}UsageFaultManagerSignal;

typedef struct UsageFaultManager UsageFaultManager;

typedef struct UsageFaultManagerVT {
	UsageFaultManagerSignal (*ClearTrapStatus_DIV0TRP)(UsageFaultManager * const me);
	UsageFaultManagerSignal (*EnableHandler)(UsageFaultManager * const me);
	UsageFaultManagerSignal (*EnableTrap_DIV0TRP)(UsageFaultManager * const me);
	uint8_t (*GetTrapStatus_DIV0TRP)(UsageFaultManager * const me);
}UsageFaultManagerVT;

struct UsageFaultManager {
	const struct UsageFaultManagerVT *vptr; /* Virtual Pointer */
	volatile uint32_t *CCR; /* Configuration Control Register */
	volatile uint32_t *CFSR; /* Configurable Fault Status Register */
	volatile uint32_t *SHCSR; /* System Handler Control and State Register */
};

UsageFaultManagerSignal UsageFaultManager_ClearTrapStatus_DIV0TRP(UsageFaultManager * const me);
UsageFaultManagerSignal UsageFaultManager_EnableHandler(UsageFaultManager * const me);
UsageFaultManagerSignal UsageFaultManager_EnableTrap_DIV0TRP(UsageFaultManager * const me);
uint8_t UsageFaultManager_GetTrapStatus_DIV0TRP(UsageFaultManager * const me);
void UsageFaultManager_ctor(UsageFaultManager * const me, volatile uint32_t *CCR, volatile uint32_t *CFSR, volatile uint32_t *SHCSR);

/*------ System Manager Facilities ------*/

typedef enum SystemManagerSignal {
	SYSTEMMANAGER_OK_SIG,
	SYSTEMMANAGER_ERROR_SIG
}SystemManagerSignal;

typedef struct SystemManager SystemManager;

typedef struct SystemManagerVT {
	SystemManagerSignal (*PrintFaultStackFrame)(SystemManager * const me, uint32_t excReturn, uint32_t calleeStackSizeUsed);
	void (*ResetSystem)(SystemManager * const me);
}SystemManagerVT;

struct SystemManager {
	const struct SystemManagerVT *vptr; /* Virtual Pointer */
	volatile uint32_t *AIRCR; /* Application Interrupt and Reset Control Register */
};

SystemManagerSignal SystemManager_PrintFaultStackFrame(SystemManager * const me, uint32_t excReturn, uint32_t calleeStackSizeUsed);
void SystemManager_ResetSystem(SystemManager * const me);
void SystemManager_ctor(SystemManager * const me, volatile uint32_t *AIRCR);


/*------ PECOS Monitor Facilities ------*/

typedef enum PecosMonitorSignal {
	PECOSMONITOR_OK_SIG,
	PECOSMONITOR_ERROR_SIG
}PecosMonitorSignal;

typedef struct PecosMonitor PecosMonitor;

typedef struct PecosMonitorVT {
	PecosMonitorSignal (*PrintFaultStackFrame)(PecosMonitor * const me, uint32_t calleeStackSizeUsed);
	PecosMonitorSignal (*SaveExcReturn)(PecosMonitor * const me, uint32_t excReturn);
}PecosMonitorVT;

struct PecosMonitor {
	const struct PecosMonitorVT *vptr;
	uint32_t excReturn;
	SystemManager sysMngr;
	UsageFaultManager usgFltMngr;
};

PecosMonitorSignal PecosMonitor_PrintFaultStackFrame(PecosMonitor * const me, uint32_t calleeStackSizeUsed);
PecosMonitorSignal PecosMonitor_SaveExcReturn(PecosMonitor * const me, uint32_t excReturn);
void PecosMonitor_ctor(PecosMonitor * const me, volatile uint32_t *AIRCR, volatile uint32_t *CCR, volatile uint32_t *CFSR, volatile uint32_t *SHCSR);



#ifdef	__cplusplus
}
#endif

#endif	/* PECOSMONITOR_H */

