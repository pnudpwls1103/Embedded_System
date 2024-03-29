/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                             (c) Copyright 2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                     BOARD SUPPORT PACKAGE (BSP)
*
*                                       IAR Development Kits
*                                              on the
*
*                                    STM32F429II-SK KICKSTART KIT
*
* Filename      : bsp.c
* Version       : V1.00
* Programmer(s) : FF
*                 YS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define   BSP_MODULE
#include  <bsp.h>
#include  <os.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define BSP_GPIOB_LED1		DEF_BIT_00
#define BSP_GPIOB_LED2		DEF_BIT_07
#define BSP_GPIOB_LED3		DEF_BIT_14

#define BSP_GPIOC_PUSH		DEF_BIT_13
#define BSP_GPIOG_BUTTON0	DEF_BIT_2
#define BSP_GPIOG_BUTTON1	DEF_BIT_3
#define BSP_GPIOG_BUTTONE	DEF_BIT_1

/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             REGISTERS
*********************************************************************************************************
*/

#define  BSP_REG_DEM_CR                           (*(CPU_REG32 *)0xE000EDFC)
#define  BSP_REG_DWT_CR                           (*(CPU_REG32 *)0xE0001000)
#define  BSP_REG_DWT_CYCCNT                       (*(CPU_REG32 *)0xE0001004)
#define  BSP_REG_DBGMCU_CR                        (*(CPU_REG32 *)0xE0042004)

                                                                /* -         RCC REGISTER DEFINES                     - */
#define  BSP_REG_RCC_BASE_ADDR                    ((CPU_INT32U)(0x40023800))

#define  BSP_REG32_RCC_CR                         (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x00u ))
#define  BSP_REG32_RCC_PLLCFGR                    (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x04u ))
#define  BSP_REG32_RCC_CFGR                       (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x08u ))
#define  BSP_REG32_RCC_CIR                        (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x0Cu ))
#define  BSP_REG32_RCC_AHB1RSTR                   (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x10u ))
#define  BSP_REG32_RCC_AHB2RSTR                   (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x14u ))
#define  BSP_REG32_RCC_AHB3RSTR                   (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x18u ))
#define  BSP_REG32_RCC_APB1RSTR                   (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x20u ))
#define  BSP_REG32_RCC_APB2RSTR                   (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x24u ))
#define  BSP_REG32_RCC_AHB1ENR                    (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x30u ))
#define  BSP_REG32_RCC_AHB2ENR                    (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x34u ))
#define  BSP_REG32_RCC_AHB3ENR                    (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x38u ))
#define  BSP_REG32_RCC_APB1ENR                    (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x40u ))
#define  BSP_REG32_RCC_APB2ENR                    (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x44u ))
#define  BSP_REG32_RCC_AHB1LPENR                  (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x50u ))
#define  BSP_REG32_RCC_AHB2LPENR                  (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x54u ))
#define  BSP_REG32_RCC_AHB3LPENR                  (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x58u ))
#define  BSP_REG32_RCC_APB1LPENR                  (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x60u ))
#define  BSP_REG32_RCC_APB2LPENR                  (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x64u ))
#define  BSP_REG32_RCC_BDCR                       (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x70u ))
#define  BSP_REG32_RCC_CSR                        (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x74u ))
#define  BSP_REG32_RCC_SSCGR                      (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x80u ))
#define  BSP_REG32_RCC_PLLI2SCFGR                 (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x84u ))
#define  BSP_REG32_RCC_PLLSAICFGR                 (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x88u ))
#define  BSP_REG32_RCC_DCKCFGR                    (*(CPU_REG32 *)( BSP_REG_RCC_BASE_ADDR + 0x8Cu ))

                                                                /* -               FLASH REGISTER DEFINES             - */
#define  BSP_REG_FLASH_BASE_ADDR                  (( CPU_INT32U )(0x40023C00))

#define  BSP_REG32_FLASH_ACR                      (*(CPU_REG32 *)( BSP_REG_FLASH_BASE_ADDR + 0x00u ))
#define  BSP_REG32_FLASH_KEYR                     (*(CPU_REG32 *)( BSP_REG_FLASH_BASE_ADDR + 0x04u ))
#define  BSP_REG32_FLASH_OPTKEYR                  (*(CPU_REG32 *)( BSP_REG_FLASH_BASE_ADDR + 0x08u ))
#define  BSP_REG32_FLASH_SR                       (*(CPU_REG32 *)( BSP_REG_FLASH_BASE_ADDR + 0x0Cu ))
#define  BSP_REG32_FLASH_CR                       (*(CPU_REG32 *)( BSP_REG_FLASH_BASE_ADDR + 0x10u ))
#define  BSP_REG32_FLASH_OPTCR                    (*(CPU_REG32 *)( BSP_REG_FLASH_BASE_ADDR + 0x14u ))
#define  BSP_REG32_FLASH_OPTCR1                   (*(CPU_REG32 *)( BSP_REG_FLASH_BASE_ADDR + 0x18u ))



/*
*********************************************************************************************************
*                                            REGISTER BITS
*********************************************************************************************************
*/

#define  BSP_DBGMCU_CR_TRACE_IOEN_MASK                 0x10u
#define  BSP_DBGMCU_CR_TRACE_MODE_ASYNC                0x00u
#define  BSP_DBGMCU_CR_TRACE_MODE_SYNC_01              0x40u
#define  BSP_DBGMCU_CR_TRACE_MODE_SYNC_02              0x80u
#define  BSP_DBGMCU_CR_TRACE_MODE_SYNC_04              0xC0u
#define  BSP_DBGMCU_CR_TRACE_MODE_MASK                 0xC0u

#define  BSP_BIT_DEM_CR_TRCENA                    DEF_BIT_24
#define  BSP_BIT_DWT_CR_CYCCNTENA                 DEF_BIT_00


                                                                /* -                    RCC BLOCK                     - */
#define  HSE_TIMEOUT_VAL                              0x0500u
#define  BSP_MSK_HSECFG                           0x00FF0000u
#define  BSP_BIT_RCC_CR_HSION                     DEF_BIT_00
#define  BSP_BIT_RCC_CR_HSEBYP                    DEF_BIT_18
#define  BSP_BIT_RCC_CR_HSEON                     DEF_BIT_16
#define  BSP_BIT_RCC_CR_HSERDY                    DEF_BIT_17
#define  BSP_MSK_RCC_CFGR_HPRE                    0x000000F0u
#define  BSP_MSK_RCC_CFGR_SYSCLKDIV1              0x00000000u
#define  BSP_MSK_RCC_CFGR_SYSCLKDIV2              0x00000080u
#define  BSP_MSK_RCC_CFGR_SYSCLKDIV4              0x00000090u
#define  BSP_MSK_RCC_CFGR_SYSCLKDIV8              0x000000A0u
#define  BSP_MSK_RCC_CFGR_SYSCLKDIV16             0x000000B0u
#define  BSP_MSK_RCC_CFGR_SYSCLKDIV64             0x000000C0u
#define  BSP_MSK_RCC_CFGR_SYSCLKDIV128            0x000000D0u
#define  BSP_MSK_RCC_CFGR_SYSCLKDIV256            0x000000E0u
#define  BSP_MSK_RCC_CFGR_SYSCLKDIV512            0x000000F0u
#define  BSP_MSK_RCC_CFGR_PPRE1                   0x00001C00u
#define  BSP_MSK_RCC_CFGR_PPRE2                   0x0000E000u
#define  BSP_MSK_RCC_CFGR_HCLK_DIV1               0x00000000u
#define  BSP_MSK_RCC_CFGR_HCLK_DIV2               0x00001000u
#define  BSP_MSK_RCC_CFGR_HCLK_DIV4               0x00001400u
#define  BSP_MSK_RCC_CFGR_HCLK_DIV8               0x00001800u
#define  BSP_MSK_RCC_CFGR_HCLK_DIV16              0x00001C00u
#define  BSP_MSK_RCC_CFGR_SWS_HSI                 0x00000000u
#define  BSP_MSK_RCC_CFGR_SWS_HSE                 0x00000004u
#define  BSP_MSK_RCC_CFGR_SWS_PLL                 0x00000008u
#define  BSP_MSK_RCC_CFGR_SWS                     0x0000000Cu
#define  BSP_MSK_RCC_CFGR_SW_HSI                  0x00000000u
#define  BSP_MSK_RCC_CFGR_SW_HSE                  0x00000001u
#define  BSP_MSK_RCC_CFGR_SW_PLL                  0x00000002u
#define  BSP_MSK_RCC_CFGR_SW                      0x00000003u
                                                                /* -                     PLL BLOCK                    - */
#define  BSP_BIT_RCC_PLLCFGR_PLLM                          8u
#define  BSP_BIT_RCC_PLLCFGR_PLLN                        336u
#define  BSP_BIT_RCC_PLLCFGR_PLLP                          2u
#define  BSP_BIT_RCC_PLLCFGR_PLLQ                          7u
#define  BSP_BIT_RCC_CR_PLLON                     DEF_BIT_24
#define  BSP_BIT_RCC_CR_PLLRDY                    DEF_BIT_25
#define  BSP_MSK_RCC_PLLCFGR_PLLSRC_HSE           0x00400000u
#define  BSP_MSK_RCC_PLLCFGR_RST                  0x24003010u
#define  BSP_MSK_SYSCLK_SRC_PLLCLK                0x00000002u
#define  BSP_MSK_PLLCFGR_PLLSRC_HSE               0x00400000u
#define  BSP_MSK_PLLCFGR_PLLSRC_HSI               0x00000000u
                                                                /* -                    FLASH BLOCK                   - */
#define  BSP_BIT_FLASH_ACR_PRFTEN                 DEF_BIT_08
#define  BSP_BIT_FLASH_ACR_ICEN                   DEF_BIT_09
#define  BSP_BIT_FLASH_ACR_DCEN                   DEF_BIT_10
#define  BSP_MSK_FLASHLATENCY_0WS                 0x00000000u
#define  BSP_MSK_FLASHLATENCY_1WS                 0x00000001u
#define  BSP_MSK_FLASHLATENCY_2WS                 0x00000002u
#define  BSP_MSK_FLASHLATENCY_3WS                 0x00000003u
#define  BSP_MSK_FLASHLATENCY_4WS                 0x00000004u
#define  BSP_MSK_FLASHLATENCY_5WS                 0x00000005u
#define  BSP_MSK_FLASHLATENCY_6WS                 0x00000006u
#define  BSP_MSK_FLASHLATENCY_7WS                 0x00000007u
#define  BSP_MSK_FLASHLATENCY_8WS                 0x00000008u
#define  BSP_MSK_FLASHLATENCY_9WS                 0x00000009u
#define  BSP_MSK_FLASHLATENCY_10WS                0x0000000Au
#define  BSP_MSK_FLASHLATENCY_11WS                0x0000000Bu
#define  BSP_MSK_FLASHLATENCY_12WS                0x0000000Cu
#define  BSP_MSK_FLASHLATENCY_13WS                0x0000000Du
#define  BSP_MSK_FLASHLATENCY_14WS                0x0000000Eu
#define  BSP_MSK_FLASHLATENCY_15WS                0x0000000Fu


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  BSP_LED_Init  (void);
static	void  USART_Config(void);
static  void  BSP_PUSH_BUTTON_Init(void);
static  void  BSP_PUSH_BUTTON0_Init(void);
static  void  BSP_PUSH_BUTTON1_Init(void);
static  void  BSP_PUSH_BUTTONE_Init(void);


/*
*********************************************************************************************************
*                                               BSP_Init()
*
* Description : Initialize the Board Support Package (BSP).
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) This function SHOULD be called before any other BSP function is called.
*
*               (2) CPU instruction / data tracing requires the use of the following pins :
*                   (a) (1) Asynchronous      :  PB[3]
*                       (2) Synchronous 1-bit :  PE[3:2]
*                       (3) Synchronous 2-bit :  PE[4:2]
*                       (4) Synchronous 4-bit :  PE[6:2]
*
*                   (c) The application may wish to adjust the trace bus width depending on I/O
*                       requirements.
*********************************************************************************************************
*/

void  BSP_Init (void)
{
    CPU_INT32U reg_val;
    CPU_INT32U hse_rdyctr;

    BSP_IntInit();
                                                                /* ---------- RESET CLOCK CONFIG. REGISTERS ----------- */

    DEF_BIT_SET(BSP_REG32_RCC_CR,BSP_BIT_RCC_CR_HSION);         /* Set HSION bit                                        */

    BSP_REG32_RCC_CFGR  = (CPU_INT32U)0u;                       /* Reset CFGR register                                  */

    BSP_REG32_RCC_CR    &= 0xFEF6FFFFu;                         /* Reset HSEON, CSSON and PLLON bits                    */

    BSP_REG32_RCC_PLLCFGR = BSP_MSK_RCC_PLLCFGR_RST;            /* Reset PLLCFGR register                               */

    DEF_BIT_CLR(BSP_REG32_RCC_CR, BSP_BIT_RCC_CR_HSEBYP);       /* Reset HSEBYP bit                                     */

                                                                /* ----------- HSE OSCILLATOR CONFIGURATION ----------- */
                                                                /* HSE = 8MHz Ext. crystal.                             */
    DEF_BIT_CLR(BSP_REG32_RCC_CR,BSP_MSK_HSECFG);

    DEF_BIT_SET(BSP_REG32_RCC_CR,BSP_BIT_RCC_CR_HSEON);
                                                                /* Wait for HSE to Start Up                             */
    do {
        hse_rdyctr++;
    } while ((hse_rdyctr < HSE_TIMEOUT_VAL)  &&
              DEF_BIT_IS_CLR(BSP_REG32_RCC_CR, BSP_BIT_RCC_CR_HSERDY));


    if (hse_rdyctr == HSE_TIMEOUT_VAL) {
        return;
    }
                                                                /* --------------- SET UP THE AHB PRESCALER ----------- */
                                                                /* HCLK = AHBCLK  = PLL / AHBPRES(1) = 168MHz.          */
    reg_val = (CPU_INT32U)0u;
    reg_val = BSP_REG32_RCC_CFGR;

    DEF_BIT_CLR(reg_val, BSP_MSK_RCC_CFGR_HPRE);                /* Clear HPRE[3:0] bits                                 */

    DEF_BIT_SET(reg_val, BSP_MSK_RCC_CFGR_SYSCLKDIV1);          /* Set HPRE[3:0] bits according to RCC_SYSCLK value     */

    BSP_REG32_RCC_CFGR = reg_val;                               /* Store the new value in RCC_CFGR register             */

                                                                /* ---------------- CONFIGURE APB2 CLOCK -------------- */
                                                                /*   APB2CLK = AHBCLK  / APB2DIV(2) = 84MHz.            */
    reg_val = BSP_REG32_RCC_CFGR;

    DEF_BIT_CLR(reg_val, BSP_MSK_RCC_CFGR_PPRE2);                /* Clear PPRE2[2:0] bits                                */

    DEF_BIT_SET(reg_val, BSP_MSK_RCC_CFGR_HCLK_DIV2 << 3u);     /* Set PPRE2[2:0] bits according to RCC_HCLK value      */

    BSP_REG32_RCC_CFGR = reg_val;                               /* Store the new value                                  */

                                                                /* ---------------- CONFIGURE APB1 CLOCK -------------- */
                                                                /* APB1CLK = AHBCLK  / APB1DIV(4) = 42MHz (max).        */
    reg_val = BSP_REG32_RCC_CFGR;

    DEF_BIT_CLR(reg_val,BSP_MSK_RCC_CFGR_PPRE1);                /* Clear PPRE1[2:0] bits                                */

    DEF_BIT_SET(reg_val, BSP_MSK_RCC_CFGR_HCLK_DIV4);           /* Set PPRE1[2:0] bits according to RCC_HCLK value      */

                                                                /* Store the new value in RCC_CFGR register             */
    BSP_REG32_RCC_CFGR    =     reg_val;
                                                                /* ------------- CONFIGURE AND ENABLE PLL ------------- */
                                                                /* PLL_M = 8, PLL_N = 336, PLL_P = 2, PLL_Q = 7         */
                                                                /* PLLCLK    = HSE * (PLLN / PLLM)      = 336MHz.       */
                                                                /* SYSCLK    = PLLCLK / PLLP            = 168MHz.       */
                                                                /* OTG_FSCLK = PLLCLK / PLLQ            =  48MHz.       */

    BSP_REG32_RCC_PLLCFGR = ( BSP_BIT_RCC_PLLCFGR_PLLM       )               |
                            ( BSP_BIT_RCC_PLLCFGR_PLLN << 6u )               |
                            ( BSP_MSK_PLLCFGR_PLLSRC_HSE     )               |
                            ((BSP_BIT_RCC_PLLCFGR_PLLP >> 1u ) -1u ) << 16u  |
                            ( BSP_BIT_RCC_PLLCFGR_PLLQ << 24u);

    DEF_BIT_SET( BSP_REG32_RCC_CR, BSP_BIT_RCC_CR_PLLON);
                                                                /* Wait for PLL to lock.                                */
    while ( DEF_BIT_IS_CLR( BSP_REG32_RCC_CR,
                            BSP_BIT_RCC_CR_PLLRDY)) {
        ;
    }
                                                                /* ------------- CONFIGURE FLASH MEMORY --------------- */

    DEF_BIT_SET(BSP_REG32_FLASH_ACR, BSP_MSK_FLASHLATENCY_5WS); /* Allow 5 Flash Wait States when HCLK > 120MHz.        */

                                                                /* Enable Prefetch, Instruction Cache, and Data Cache.  */
    DEF_BIT_SET(BSP_REG32_FLASH_ACR, (BSP_BIT_FLASH_ACR_PRFTEN  |
                                      BSP_BIT_FLASH_ACR_ICEN    |
                                      BSP_BIT_FLASH_ACR_DCEN));
                                                                /* -------- SELECT PLL OUTPUT AS SYSTEM CLOCK --------- */
                                                                /* HCLK = SYSCLK = PLL = 168MHz.                        */
    DEF_BIT_SET(BSP_REG32_RCC_CFGR, BSP_MSK_SYSCLK_SRC_PLLCLK);


    while((BSP_REG32_RCC_CFGR & BSP_MSK_RCC_CFGR_SWS)             /* Wait until PLL is selected as system clock source    */
                              != BSP_MSK_RCC_CFGR_SWS_PLL){
        ;
    }

    BSP_LED_Init();                                             /* Initialize user LEDs                                 */
    USART_Config();
    BSP_PUSH_BUTTON_Init();										/* Initialize user Push button							*/
    BSP_PUSH_BUTTON0_Init();
    BSP_PUSH_BUTTON1_Init();
    BSP_PUSH_BUTTONE_Init();

#ifdef TRACE_EN                                                 /* See project / compiler preprocessor options.         */
    BSP_CPU_REG_DBGMCU_CR |=  BSP_DBGMCU_CR_TRACE_IOEN_MASK;    /* Enable tracing (see Note #2).                        */
    BSP_CPU_REG_DBGMCU_CR &= ~BSP_DBGMCU_CR_TRACE_MODE_MASK;    /* Clr trace mode sel bits.                             */
    BSP_CPU_REG_DBGMCU_CR |=  BSP_DBGMCU_CR_TRACE_MODE_SYNC_04; /* Cfg trace mode to synch 4-bit.                       */
#endif
}


/*
*********************************************************************************************************
*                                            BSP_CPU_ClkFreq()
*
* Description : Read CPU registers to determine the CPU clock frequency of the chip.
*
* Argument(s) : none.
*
* Return(s)   : The CPU clock frequency, in Hz.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT32U  BSP_CPU_ClkFreq (void)
{
    RCC_ClocksTypeDef  rcc_clocks;


    RCC_GetClocksFreq(&rcc_clocks);

    return ((CPU_INT32U)rcc_clocks.HCLK_Frequency);
}


/*
*********************************************************************************************************
*                                            BSP_Tick_Init()
*
* Description : Configure and Initialize the OS Tick Services (SysTick).
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_Tick_Init (void)
{
    CPU_INT32U  cpu_clk_freq;
    CPU_INT32U  cnts;
    
    
    cpu_clk_freq = BSP_CPU_ClkFreq();                           /* Determine SysTick reference freq.                    */
    
#if (OS_VERSION >= 30000u)
    cnts = (cpu_clk_freq / (CPU_INT32U)OSCfg_TickRate_Hz);      /* Determine nbr SysTick increments                     */
#else
    cnts = (cpu_clk_freq / (CPU_INT32U)OS_TICKS_PER_SEC);       /* Determine nbr SysTick increments.                    */
#endif
    
    OS_CPU_SysTickInit(cnts);                                   /* Init uC/OS periodic time src (SysTick).              */
}


/*
*********************************************************************************************************
*                                          Setup_Gpio()
*
* Description : Configure LED GPIOs directly
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s)     :
*              LED1 PB0
*              LED2 PB7
*              LED3 PB14
*
*********************************************************************************************************
*/

static void  BSP_LED_Init()
{
   GPIO_InitTypeDef led_init = {0};

   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
   RCC_AHB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

   led_init.GPIO_Mode   = GPIO_Mode_OUT;
   led_init.GPIO_OType  = GPIO_OType_PP;
   led_init.GPIO_Speed  = GPIO_Speed_2MHz;
   led_init.GPIO_PuPd   = GPIO_PuPd_NOPULL;
   led_init.GPIO_Pin    = GPIO_Pin_0 | GPIO_Pin_7 | GPIO_Pin_14;

   GPIO_Init(GPIOB, &led_init);

}

static void  BSP_PUSH_BUTTON_Init()
{
   GPIO_InitTypeDef button_init = {0};

   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
   RCC_AHB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

   button_init.GPIO_Mode   = GPIO_Mode_IN;
   button_init.GPIO_PuPd   = GPIO_PuPd_DOWN;
   button_init.GPIO_Pin    = GPIO_Pin_13;

   GPIO_Init(GPIOC, &button_init);

}

static void  BSP_PUSH_BUTTON0_Init()
{
   GPIO_InitTypeDef button0_init = {0};

   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
   RCC_AHB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

   button0_init.GPIO_Mode   = GPIO_Mode_IN;
   button0_init.GPIO_PuPd   = GPIO_PuPd_DOWN;
   button0_init.GPIO_Pin    = GPIO_Pin_2;

   GPIO_Init(GPIOG, &button0_init);

}

static void  BSP_PUSH_BUTTON1_Init()
{
   GPIO_InitTypeDef button1_init = {0};

   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
   RCC_AHB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

   button1_init.GPIO_Mode   = GPIO_Mode_IN;
   button1_init.GPIO_PuPd   = GPIO_PuPd_DOWN;
   button1_init.GPIO_Pin    = GPIO_Pin_3;

   GPIO_Init(GPIOG, &button1_init);

}

static void  BSP_PUSH_BUTTONE_Init()
{
   GPIO_InitTypeDef buttonE_init = {0};

   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
   RCC_AHB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

   buttonE_init.GPIO_Mode   = GPIO_Mode_IN;
   buttonE_init.GPIO_PuPd   = GPIO_PuPd_DOWN;
   buttonE_init.GPIO_Pin    = GPIO_Pin_1;

   GPIO_Init(GPIOG, &buttonE_init);

}


/*
*********************************************************************************************************
*                                              BSP_LED_Off()
*
* Description : Turn OFF any or all the LEDs on the board.
*
* Argument(s) : led     The ID of the LED to control:
*
*                       0    turns OFF ALL the LEDs
*                       1    turns OFF user LED1
*                       2    turns OFF user LED2
*                       3    turns OFF user LED3
*                       4    turns OFF user LED4
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Off (CPU_INT08U  led)
{
    switch (led) {
        case 0u:
             GPIO_ResetBits(GPIOB, BSP_GPIOB_LED1);
             GPIO_ResetBits(GPIOB, BSP_GPIOB_LED2);
             GPIO_ResetBits(GPIOB, BSP_GPIOB_LED3);
             break;


        case 1u:
        	GPIO_ResetBits(GPIOB, BSP_GPIOB_LED1);
             break;


        case 2u:
        	GPIO_ResetBits(GPIOB, BSP_GPIOB_LED2);
             break;


        case 3u:
        	GPIO_ResetBits(GPIOB, BSP_GPIOB_LED3);
             break;

        default:
             break;
    }
}

/*
*********************************************************************************************************
*                                             BSP_LED_On()
*
* Description : Turn ON any or all the LEDs on the board.
*
* Argument(s) : led     The ID of the LED to control:
*
*                       0    turns ON ALL  LEDs
*                       1    turns ON user LED1
*                       2    turns ON user LED2
*                       3    turns ON user LED3
*                       4    turns ON user LED4
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_On (CPU_INT08U led)
{
    switch (led) {
        case 0u:
             GPIO_ResetBits(GPIOB, BSP_GPIOB_LED1);
             GPIO_ResetBits(GPIOB, BSP_GPIOB_LED2);
             GPIO_ResetBits(GPIOB, BSP_GPIOB_LED3);
             break;


        case 1u:
             GPIO_SetBits(GPIOB, BSP_GPIOB_LED1);
             break;


        case 2u:
        	GPIO_SetBits(GPIOB, BSP_GPIOB_LED2);
             break;


        case 3u:
        	 GPIO_SetBits(GPIOB, BSP_GPIOB_LED3);
             break;

        default:
             break;
    }
}


/*
*********************************************************************************************************
*                                            BSP_LED_Toggle()
*
* Description : TOGGLE any or all the LEDs on the board.
*
* Argument(s) : led     The ID of the LED to control:
*
*                       0    TOGGLE ALL the LEDs
*                       1    TOGGLE user LED1
*                       2    TOGGLE user LED2
*                       3    TOGGLE user LED3
*                       4    TOGGLE user LED4
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Toggle (CPU_INT08U  led)
{
    CPU_INT32U  pins;


    switch (led) {
        case 0u:
        	/* Read data (current state of output pins) in GPIOA    */
        	/* Tells which pins (other than pin for LED1) are ON    */
        	/* If there are any,turn them OFF and leave LED1 ON     */
             pins  =  GPIO_ReadOutputData(GPIOB);
             pins ^=  BSP_GPIOB_LED1;
             GPIO_SetBits(  GPIOB,   pins  &  BSP_GPIOB_LED1);
             GPIO_ResetBits(GPIOB, (~pins) &  BSP_GPIOB_LED1);


             pins  =  GPIO_ReadOutputData(GPIOB);
             pins ^=  BSP_GPIOB_LED2;
             GPIO_SetBits(  GPIOB,   pins  &  BSP_GPIOB_LED2);
             GPIO_ResetBits(GPIOB, (~pins) &  BSP_GPIOB_LED2);

             pins  =  GPIO_ReadOutputData(GPIOB);
             pins ^=  BSP_GPIOB_LED3;
             GPIO_SetBits(  GPIOB,   pins  &  BSP_GPIOB_LED3);
             GPIO_ResetBits(GPIOB, (~pins) &  BSP_GPIOB_LED3);
             break;


        case 1u:
            pins  =  GPIO_ReadOutputData(GPIOB);
            pins ^=  BSP_GPIOB_LED1;
            GPIO_SetBits(  GPIOB,   pins  &  BSP_GPIOB_LED1);
            GPIO_ResetBits(GPIOB, (~pins) &  BSP_GPIOB_LED1);
             break;


        case 2u:
       	     pins  = GPIO_ReadOutputData(GPIOB);
       	     pins ^= BSP_GPIOB_LED2;
       	     GPIO_SetBits(  GPIOB,   pins   &  BSP_GPIOB_LED2);
       	     GPIO_ResetBits(GPIOB, (~pins)  &  BSP_GPIOB_LED2);
             break;


        case 3u:
       	     pins  = GPIO_ReadOutputData(GPIOB);
       	     pins ^= BSP_GPIOB_LED3;
       	     GPIO_SetBits(  GPIOB,   pins   &  BSP_GPIOB_LED3);
       	     GPIO_ResetBits(GPIOB, (~pins)  &  BSP_GPIOB_LED3);
             break;

        default:
             break;
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                          CPU_TS_TmrInit()
*
* Description : Initialize & start CPU timestamp timer.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : CPU_TS_Init().
*
*               This function is an INTERNAL CPU module function & MUST be implemented by application/
*               BSP function(s) [see Note #1] but MUST NOT be called by application function(s).
*
* Note(s)     : (1) CPU_TS_TmrInit() is an application/BSP function that MUST be defined by the developer
*                   if either of the following CPU features is enabled :
*
*                   (a) CPU timestamps
*                   (b) CPU interrupts disabled time measurements
*
*                   See 'cpu_cfg.h  CPU TIMESTAMP CONFIGURATION  Note #1'
*                     & 'cpu_cfg.h  CPU INTERRUPTS DISABLED TIME MEASUREMENT CONFIGURATION  Note #1a'.
*
*               (2) (a) Timer count values MUST be returned via word-size-configurable 'CPU_TS_TMR'
*                       data type.
*
*                       (1) If timer has more bits, truncate timer values' higher-order bits greater
*                           than the configured 'CPU_TS_TMR' timestamp timer data type word size.
*
*                       (2) Since the timer MUST NOT have less bits than the configured 'CPU_TS_TMR'
*                           timestamp timer data type word size; 'CPU_CFG_TS_TMR_SIZE' MUST be
*                           configured so that ALL bits in 'CPU_TS_TMR' data type are significant.
*
*                           In other words, if timer size is not a binary-multiple of 8-bit octets
*                           (e.g. 20-bits or even 24-bits), then the next lower, binary-multiple
*                           octet word size SHOULD be configured (e.g. to 16-bits).  However, the
*                           minimum supported word size for CPU timestamp timers is 8-bits.
*
*                       See also 'cpu_cfg.h   CPU TIMESTAMP CONFIGURATION  Note #2'
*                              & 'cpu_core.h  CPU TIMESTAMP DATA TYPES     Note #1'.
*
*                   (b) Timer SHOULD be an 'up'  counter whose values increase with each time count.
*
*                   (c) When applicable, timer period SHOULD be less than the typical measured time
*                       but MUST be less than the maximum measured time; otherwise, timer resolution
*                       inadequate to measure desired times.
*
*                   See also 'CPU_TS_TmrRd()  Note #2'.
*********************************************************************************************************
*/

#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
void  CPU_TS_TmrInit (void)
{
    CPU_INT32U  fclk_freq;


    fclk_freq = BSP_CPU_ClkFreq();

    BSP_REG_DEM_CR     |= (CPU_INT32U)BSP_BIT_DEM_CR_TRCENA;    /* Enable Cortex-M4's DWT CYCCNT reg.                   */
    BSP_REG_DWT_CYCCNT  = (CPU_INT32U)0u;
    BSP_REG_DWT_CR     |= (CPU_INT32U)BSP_BIT_DWT_CR_CYCCNTENA;

    CPU_TS_TmrFreqSet((CPU_TS_TMR_FREQ)fclk_freq);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                           CPU_TS_TmrRd()
*
* Description : Get current CPU timestamp timer count value.
*
* Argument(s) : none.
*
* Return(s)   : Timestamp timer count (see Notes #2a & #2b).
*
* Caller(s)   : CPU_TS_Init(),
*               CPU_TS_Get32(),
*               CPU_TS_Get64(),
*               CPU_IntDisMeasStart(),
*               CPU_IntDisMeasStop().
*
*               This function is an INTERNAL CPU module function & MUST be implemented by application/
*               BSP function(s) [see Note #1] but SHOULD NOT be called by application function(s).
*
* Note(s)     : (1) CPU_TS_TmrRd() is an application/BSP function that MUST be defined by the developer
*                   if either of the following CPU features is enabled :
*
*                   (a) CPU timestamps
*                   (b) CPU interrupts disabled time measurements
*
*                   See 'cpu_cfg.h  CPU TIMESTAMP CONFIGURATION  Note #1'
*                     & 'cpu_cfg.h  CPU INTERRUPTS DISABLED TIME MEASUREMENT CONFIGURATION  Note #1a'.
*
*               (2) (a) Timer count values MUST be returned via word-size-configurable 'CPU_TS_TMR'
*                       data type.
*
*                       (1) If timer has more bits, truncate timer values' higher-order bits greater
*                           than the configured 'CPU_TS_TMR' timestamp timer data type word size.
*
*                       (2) Since the timer MUST NOT have less bits than the configured 'CPU_TS_TMR'
*                           timestamp timer data type word size; 'CPU_CFG_TS_TMR_SIZE' MUST be
*                           configured so that ALL bits in 'CPU_TS_TMR' data type are significant.
*
*                           In other words, if timer size is not a binary-multiple of 8-bit octets
*                           (e.g. 20-bits or even 24-bits), then the next lower, binary-multiple
*                           octet word size SHOULD be configured (e.g. to 16-bits).  However, the
*                           minimum supported word size for CPU timestamp timers is 8-bits.
*
*                       See also 'cpu_cfg.h   CPU TIMESTAMP CONFIGURATION  Note #2'
*                              & 'cpu_core.h  CPU TIMESTAMP DATA TYPES     Note #1'.
*
*                   (b) Timer SHOULD be an 'up'  counter whose values increase with each time count.
*
*                       (1) If timer is a 'down' counter whose values decrease with each time count,
*                           then the returned timer value MUST be ones-complemented.
*
*                   (c) (1) When applicable, the amount of time measured by CPU timestamps is
*                           calculated by either of the following equations :
*
*                           (A) Time measured  =  Number timer counts  *  Timer period
*
*                                   where
*
*                                       Number timer counts     Number of timer counts measured
*                                       Timer period            Timer's period in some units of
*                                                                   (fractional) seconds
*                                       Time measured           Amount of time measured, in same
*                                                                   units of (fractional) seconds
*                                                                   as the Timer period
*
*                                                  Number timer counts
*                           (B) Time measured  =  ---------------------
*                                                    Timer frequency
*
*                                   where
*
*                                       Number timer counts     Number of timer counts measured
*                                       Timer frequency         Timer's frequency in some units
*                                                                   of counts per second
*                                       Time measured           Amount of time measured, in seconds
*
*                       (2) Timer period SHOULD be less than the typical measured time but MUST be less
*                           than the maximum measured time; otherwise, timer resolution inadequate to
*                           measure desired times.
*********************************************************************************************************
*/

#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
CPU_TS_TMR  CPU_TS_TmrRd (void)
{
    CPU_TS_TMR  ts_tmr_cnts;


    ts_tmr_cnts = (CPU_TS_TMR)BSP_REG_DWT_CYCCNT;

    return (ts_tmr_cnts);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                         CPU_TSxx_to_uSec()
*
* Description : Convert a 32-/64-bit CPU timestamp from timer counts to microseconds.
*
* Argument(s) : ts_cnts   CPU timestamp (in timestamp timer counts [see Note #2aA]).
*
* Return(s)   : Converted CPU timestamp (in microseconds           [see Note #2aD]).
*
* Caller(s)   : Application.
*
*               This function is an (optional) CPU module application programming interface (API)
*               function which MAY be implemented by application/BSP function(s) [see Note #1] &
*               MAY be called by application function(s).
*
* Note(s)     : (1) CPU_TS32_to_uSec()/CPU_TS64_to_uSec() are application/BSP functions that MAY be
*                   optionally defined by the developer when either of the following CPU features is
*                   enabled :
*
*                   (a) CPU timestamps
*                   (b) CPU interrupts disabled time measurements
*
*                   See 'cpu_cfg.h  CPU TIMESTAMP CONFIGURATION  Note #1'
*                     & 'cpu_cfg.h  CPU INTERRUPTS DISABLED TIME MEASUREMENT CONFIGURATION  Note #1a'.
*
*               (2) (a) The amount of time measured by CPU timestamps is calculated by either of
*                       the following equations :
*
*                                                                        10^6 microseconds
*                       (1) Time measured  =   Number timer counts   *  -------------------  *  Timer period
*                                                                            1 second
*
*                                              Number timer counts       10^6 microseconds
*                       (2) Time measured  =  ---------------------  *  -------------------
*                                                Timer frequency             1 second
*
*                               where
*
*                                   (A) Number timer counts     Number of timer counts measured
*                                   (B) Timer frequency         Timer's frequency in some units
*                                                                   of counts per second
*                                   (C) Timer period            Timer's period in some units of
*                                                                   (fractional)  seconds
*                                   (D) Time measured           Amount of time measured,
*                                                                   in microseconds
*
*                   (b) Timer period SHOULD be less than the typical measured time but MUST be less
*                       than the maximum measured time; otherwise, timer resolution inadequate to
*                       measure desired times.
*
*                   (c) Specific implementations may convert any number of CPU_TS32 or CPU_TS64 bits
*                       -- up to 32 or 64, respectively -- into microseconds.
*********************************************************************************************************
*/

#if (CPU_CFG_TS_32_EN == DEF_ENABLED)
CPU_INT64U  CPU_TS32_to_uSec (CPU_TS32  ts_cnts)
{
    CPU_INT64U  ts_us;
    CPU_INT64U  fclk_freq;


    fclk_freq = BSP_CPU_ClkFreq();
    ts_us     = ts_cnts / (fclk_freq / DEF_TIME_NBR_uS_PER_SEC);

    return (ts_us);
}
#endif


#if (CPU_CFG_TS_64_EN == DEF_ENABLED)
CPU_INT64U  CPU_TS64_to_uSec (CPU_TS64  ts_cnts)
{
    CPU_INT64U  ts_us;
    CPU_INT64U  fclk_freq;


    fclk_freq = BSP_CPU_ClkFreq();
    ts_us     = ts_cnts / (fclk_freq / DEF_TIME_NBR_uS_PER_SEC);

    return (ts_us);
}
#endif

USART_TypeDef* COM_USART[COMn] = {Nucleo_COM1};
GPIO_TypeDef* COM_TX_PORT[COMn] = {Nucleo_COM1_TX_GPIO_PORT};
GPIO_TypeDef* COM_RX_PORT[COMn] = {Nucleo_COM1_RX_GPIO_PORT};
const uint32_t COM_USART_CLK[COMn] = {Nucleo_COM1_CLK};
const uint32_t COM_TX_PORT_CLK[COMn] = {Nucleo_COM1_TX_GPIO_CLK};
const uint32_t COM_RX_PORT_CLK[COMn] = {Nucleo_COM1_RX_GPIO_CLK};
const uint16_t COM_TX_PIN[COMn] = {Nucleo_COM1_TX_PIN};
const uint16_t COM_RX_PIN[COMn] = {Nucleo_COM1_RX_PIN};
const uint16_t COM_TX_PIN_SOURCE[COMn] = {Nucleo_COM1_TX_SOURCE};
const uint16_t COM_RX_PIN_SOURCE[COMn] = {Nucleo_COM1_RX_SOURCE};
const uint16_t COM_TX_AF[COMn] = {Nucleo_COM1_TX_AF};
const uint16_t COM_RX_AF[COMn] = {Nucleo_COM1_RX_AF};


void STM_Nucleo_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(COM_TX_PORT_CLK[COM] | COM_RX_PORT_CLK[COM], ENABLE);

  if (COM == COM1)
  {
    /* Enable UART clock */
    RCC_APB1PeriphClockCmd(COM_USART_CLK[COM], ENABLE);
  }

  /* Connect PXx to USARTx_Tx*/
  GPIO_PinAFConfig(COM_TX_PORT[COM], COM_TX_PIN_SOURCE[COM], COM_TX_AF[COM]);

  /* Connect PXx to USARTx_Rx*/
  GPIO_PinAFConfig(COM_RX_PORT[COM], COM_RX_PIN_SOURCE[COM], COM_RX_AF[COM]);

  /* Configure USART Tx as alternate function  */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

  GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[COM];
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(COM_TX_PORT[COM], &GPIO_InitStructure);

  /* Configure USART Rx as alternate function  */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[COM];
  GPIO_Init(COM_RX_PORT[COM], &GPIO_InitStructure);

  /* USART configuration */
  USART_Init(COM_USART[COM], USART_InitStruct);

  /* Enable USART */
  USART_Cmd(COM_USART[COM], ENABLE);
}




static void USART_Config(void)
{
  USART_InitTypeDef USART_InitStructure;

  /* USARTx configured as follows:
        - BaudRate = 115200 baud
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  STM_Nucleo_COMInit(COM1, &USART_InitStructure);
}

void send_string(const char *str)
{
    while (*str)
    {
        while(USART_GetFlagStatus(Nucleo_COM1, USART_FLAG_TXE) == RESET);
        USART_SendData(Nucleo_COM1, *str++);
    }
}
