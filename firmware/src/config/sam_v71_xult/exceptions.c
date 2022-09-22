/*******************************************************************************
  System Exceptions File

  File Name:
    exceptions.c

  Summary:
    This file contains a function which overrides the default _weak_ exception
    handlers provided by the interrupt.c file.

  Description:
    This file redefines the default _weak_  exception handler with a more debug
    friendly one. If an unexpected exception occurs the code will stop in a
    while(1) loop.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "interrupts.h"
#include "definitions.h"
#include "main.h"

// *****************************************************************************
// *****************************************************************************
// Section: Exception Handling Routine
// *****************************************************************************
// *****************************************************************************

/* Brief default interrupt handlers for core IRQs.*/

void __attribute__((noreturn)) NonMaskableInt_Handler(void)
{
#if defined(__DEBUG) || defined(__DEBUG_D) && defined(__XC32)
    __builtin_software_breakpoint();
#endif
    printf("NMI\r\n");
    pecosMonitor.sysMngr.vptr->ResetSystem(&(pecosMonitor.sysMngr));
    while (true)
    {
    }
}

void __attribute__((noreturn)) HardFault_Handler(void)
{
#if defined(__DEBUG) || defined(__DEBUG_D) && defined(__XC32)
   __builtin_software_breakpoint();
#endif

    printf("HardFault\r\n");
    pecosMonitor.sysMngr.vptr->ResetSystem(&(pecosMonitor.sysMngr));
   while (true)
   {
   }
}

void __attribute__((noreturn)) DebugMonitor_Handler(void)
{
#if defined(__DEBUG) || defined(__DEBUG_D) && defined(__XC32)
   __builtin_software_breakpoint();
#endif
    printf("DebugMonitor\r\n");
    pecosMonitor.sysMngr.vptr->ResetSystem(&(pecosMonitor.sysMngr));
   while (true)
   {
   }
}

void __attribute__((noreturn)) MemoryManagement_Handler(void)
{
#if defined(__DEBUG) || defined(__DEBUG_D) && defined(__XC32)
   __builtin_software_breakpoint();
#endif
    printf("MemoryManagement\r\n");
    pecosMonitor.sysMngr.vptr->ResetSystem(&(pecosMonitor.sysMngr));
   while (true)
   {
   }
}

void __attribute__((noreturn)) BusFault_Handler(void)
{
#if defined(__DEBUG) || defined(__DEBUG_D) && defined(__XC32)
   __builtin_software_breakpoint();
#endif    
    printf("BusFault");
    if (pecosMonitor.busFltMngr.vptr->GetTrapStatus_BFARVALID(&(pecosMonitor.busFltMngr)) != 0) {       
		printf(" - BFARVALID");
    }
    if (pecosMonitor.busFltMngr.vptr->GetTrapStatus_IMPRECISERR(&(pecosMonitor.busFltMngr)) != 0) {       
		printf(" - IMPRECISERR");
    }
    if (pecosMonitor.busFltMngr.vptr->GetTrapStatus_LSPERR(&(pecosMonitor.busFltMngr)) != 0) {       
		printf(" - LSPERR");
    }
    if (pecosMonitor.busFltMngr.vptr->GetTrapStatus_PRECISERR(&(pecosMonitor.busFltMngr)) != 0) {       
		printf(" - PRECISERR");
    }
    if (pecosMonitor.busFltMngr.vptr->GetTrapStatus_STKERR(&(pecosMonitor.busFltMngr)) != 0) {       
		printf(" - STKERR");
    }
    if (pecosMonitor.busFltMngr.vptr->GetTrapStatus_UNSTKERR(&(pecosMonitor.busFltMngr)) != 0) {       
		printf(" - UNSTKERR");
    }
    printf("\r\n");
   pecosMonitor.sysMngr.vptr->ResetSystem(&(pecosMonitor.sysMngr));
   while (true)
   {
   }
}

void __attribute__((noreturn)) UsageFault_Handler(void)
{
#if defined(__DEBUG) || defined(__DEBUG_D) && defined(__XC32)
   __builtin_software_breakpoint();
#endif
   /* Save EXT_RETURN value before doing anything */
	unsigned int excReturn;
	__asm__ ("mov %[excReturn], lr" : [excReturn] "=r" (excReturn));
	pecosMonitor.vptr->SaveExcReturn(&pecosMonitor, excReturn);
    
	printf("UsageFault");
    
	if (pecosMonitor.usgFltMngr.vptr->GetTrapStatus_DIVBYZERO(&(pecosMonitor.usgFltMngr)) != 0) {
		printf(" - DIVBYZERO");
		pecosMonitor.vptr->PrintFaultStackFrame(&pecosMonitor, 0x08);
	}
    if (pecosMonitor.usgFltMngr.vptr->GetTrapStatus_INVPC(&(pecosMonitor.usgFltMngr)) != 0) {
		printf(" - INVPC");
	}
    if (pecosMonitor.usgFltMngr.vptr->GetTrapStatus_INVSTATE(&(pecosMonitor.usgFltMngr)) != 0) {
		printf(" - INVSTATE");
	}
    if (pecosMonitor.usgFltMngr.vptr->GetTrapStatus_NOCP(&(pecosMonitor.usgFltMngr)) != 0) {
		printf(" - NOCP");
	}
    if (pecosMonitor.usgFltMngr.vptr->GetTrapStatus_UNALIGNED(&(pecosMonitor.usgFltMngr)) != 0) {
		printf(" - UNALIGNED");
	}
    if (pecosMonitor.usgFltMngr.vptr->GetTrapStatus_UNDEFINSTR(&(pecosMonitor.usgFltMngr)) != 0) {
		printf(" - UNDEFINSTR");
	}
    printf("\r\n");
	pecosMonitor.sysMngr.vptr->ResetSystem(&(pecosMonitor.sysMngr));
   while (true)
   {
   }
}
/*******************************************************************************
 End of File
 */
