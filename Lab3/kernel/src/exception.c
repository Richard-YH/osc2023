#include "uart.h"
#include "exception.h"
#include "timer.h"
#include "irq.h"


void el1_interrupt_enable(){
    __asm__ __volatile__("msr daifclr, 0xf");
}

void el1_interrupt_disable(){
    __asm__ __volatile__("msr daifset, 0xf");
}


void el1h_irq_router(){
    // Kernel is running in el1. CLI requires this irq to do async I/O
    if(*IRQ_PENDING_1 & IRQ_PENDING_1_AUX_INT && *CORE0_INTERRUPT_SOURCE & INTERRUPT_SOURCE_GPU) // from aux && from GPU0 -> uart exception  
    {
        uart_interrupt_handler();
    }
}


void el0_sync_router(){
    unsigned long long spsr_el1;
	__asm__ __volatile__("mrs %0, SPSR_EL1\n\t" : "=r" (spsr_el1));

    unsigned long long elr_el1;
	__asm__ __volatile__("mrs %0, ELR_EL1\n\t" : "=r" (elr_el1));

    unsigned long long esr_el1;
	__asm__ __volatile__("mrs %0, ESR_EL1\n\t" : "=r" (esr_el1));

    uart_printf("exception sync_el0_64_router -> spsr_el1 : 0x%x, elr_el1 : 0x%x, esr_el1 : 0x%x\r\n",spsr_el1,elr_el1,esr_el1);

}

void el0_irq_64_router(){
    //uart_puts("source : %x\n", *CORE0_INTERRUPT_SOURCE);
    /*uart_sendline("irq_basic_pending: %x\n",*IRQ_BASIC_PENDING);
    uart_sendline("irq_pending_1: %x\n",*IRQ_PENDING_1);
    uart_sendline("irq_pending_2: %x\n",*IRQ_PENDING_2);
    uart_sendline("source : %x\n\n\n",*CORE0_INTERRUPT_SOURCE);*/

    
    if(*IRQ_PENDING_1 & IRQ_PENDING_1_AUX_INT && *CORE0_INTERRUPT_SOURCE & INTERRUPT_SOURCE_GPU) // from aux && from GPU0 -> uart exception  
    {
        uart_interrupt_handler();
    }
    else if(*CORE0_INTERRUPT_SOURCE & INTERRUPT_SOURCE_CNTPNSIRQ)  //from CNTPNS (core_timer)
    {
        core_timer_handler();
    }
}

void invalid_exception_router(){
    uart_printf("invalid exception\n ");
}



