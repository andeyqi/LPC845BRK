/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _CLOCK_CONFIG_H_
#define _CLOCK_CONFIG_H_

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_XTAL0_CLK_HZ                         12000000U  /*!< Board xtal0 frequency in Hz */
#define BOARD_XTAL32K_CLK_HZ                          32768U  /*!< Board xtal32K frequency in Hz */

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief This function executes default configuration of clocks.
 *
 */
void BOARD_InitBootClocks(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*******************************************************************************
 ******************** Configuration BOARD_BootClockFRO18M **********************
 ******************************************************************************/
/*******************************************************************************
 * Definitions for BOARD_BootClockFRO18M configuration
 ******************************************************************************/
#define BOARD_BOOTCLOCKFRO18M_CORE_CLOCK           30000000U  /*!< Core clock frequency: 30000000Hz */


/* Clock outputs (values are in Hz): */
#define BOARD_BOOTCLOCKFRO18M_ADC_CLOCK               0UL
#define BOARD_BOOTCLOCKFRO18M_CAPT_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO18M_CLKOUT_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO18M_FROHF_CLOCK             30000000UL
#define BOARD_BOOTCLOCKFRO18M_I2C0_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO18M_I2C1_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO18M_I2C2_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO18M_I2C3_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO18M_IOCON0_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO18M_IOCON1_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO18M_IOCON2_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO18M_IOCON3_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO18M_IOCON4_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO18M_IOCON5_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO18M_IOCON6_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO18M_LOWPOWER_CLOCK          10000UL
#define BOARD_BOOTCLOCKFRO18M_SCT_CLOCK               0UL
#define BOARD_BOOTCLOCKFRO18M_SPI0_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO18M_SPI1_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO18M_SYSPLL_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO18M_SYSTEM_CLOCK            30000000UL
#define BOARD_BOOTCLOCKFRO18M_UART0_CLOCK             0UL
#define BOARD_BOOTCLOCKFRO18M_UART1_CLOCK             0UL
#define BOARD_BOOTCLOCKFRO18M_UART2_CLOCK             0UL
#define BOARD_BOOTCLOCKFRO18M_UART3_CLOCK             0UL
#define BOARD_BOOTCLOCKFRO18M_UART4_CLOCK             0UL
#define BOARD_BOOTCLOCKFRO18M_WWDT_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO18M_DIVTO750K_CLOCK         750000UL

/*******************************************************************************
 * API for BOARD_BootClockFRO18M configuration
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief This function executes configuration of clocks.
 *
 */
void BOARD_BootClockFRO18M(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*******************************************************************************
 ******************** Configuration BOARD_BootClockFRO24M **********************
 ******************************************************************************/
/*******************************************************************************
 * Definitions for BOARD_BootClockFRO24M configuration
 ******************************************************************************/
#define BOARD_BOOTCLOCKFRO24M_CORE_CLOCK           24000000U  /*!< Core clock frequency: 24000000Hz */


/* Clock outputs (values are in Hz): */
#define BOARD_BOOTCLOCKFRO24M_ADC_CLOCK               0UL
#define BOARD_BOOTCLOCKFRO24M_CAPT_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO24M_CLKOUT_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO24M_FROHF_CLOCK             24000000UL
#define BOARD_BOOTCLOCKFRO24M_I2C0_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO24M_I2C1_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO24M_I2C2_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO24M_I2C3_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO24M_IOCON0_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO24M_IOCON1_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO24M_IOCON2_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO24M_IOCON3_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO24M_IOCON4_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO24M_IOCON5_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO24M_IOCON6_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO24M_LOWPOWER_CLOCK          10000UL
#define BOARD_BOOTCLOCKFRO24M_SCT_CLOCK               0UL
#define BOARD_BOOTCLOCKFRO24M_SPI0_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO24M_SPI1_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO24M_SYSPLL_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO24M_SYSTEM_CLOCK            24000000UL
#define BOARD_BOOTCLOCKFRO24M_UART0_CLOCK             0UL
#define BOARD_BOOTCLOCKFRO24M_UART1_CLOCK             0UL
#define BOARD_BOOTCLOCKFRO24M_UART2_CLOCK             0UL
#define BOARD_BOOTCLOCKFRO24M_UART3_CLOCK             0UL
#define BOARD_BOOTCLOCKFRO24M_UART4_CLOCK             0UL
#define BOARD_BOOTCLOCKFRO24M_WWDT_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO24M_DIVTO750K_CLOCK         750000UL

/*******************************************************************************
 * API for BOARD_BootClockFRO24M configuration
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief This function executes configuration of clocks.
 *
 */
void BOARD_BootClockFRO24M(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*******************************************************************************
 ******************** Configuration BOARD_BootClockFRO30M **********************
 ******************************************************************************/
/*******************************************************************************
 * Definitions for BOARD_BootClockFRO30M configuration
 ******************************************************************************/
#define BOARD_BOOTCLOCKFRO30M_CORE_CLOCK           30000000U  /*!< Core clock frequency: 30000000Hz */


/* Clock outputs (values are in Hz): */
#define BOARD_BOOTCLOCKFRO30M_ADC_CLOCK               0UL
#define BOARD_BOOTCLOCKFRO30M_CAPT_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO30M_CLKOUT_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO30M_FROHF_CLOCK             30000000UL
#define BOARD_BOOTCLOCKFRO30M_I2C0_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO30M_I2C1_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO30M_I2C2_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO30M_I2C3_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO30M_IOCON0_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO30M_IOCON1_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO30M_IOCON2_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO30M_IOCON3_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO30M_IOCON4_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO30M_IOCON5_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO30M_IOCON6_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO30M_LOWPOWER_CLOCK          10000UL
#define BOARD_BOOTCLOCKFRO30M_SCT_CLOCK               0UL
#define BOARD_BOOTCLOCKFRO30M_SPI0_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO30M_SPI1_CLOCK              0UL
#define BOARD_BOOTCLOCKFRO30M_SYSPLL_CLOCK            0UL
#define BOARD_BOOTCLOCKFRO30M_SYSTEM_CLOCK            30000000UL
#define BOARD_BOOTCLOCKFRO30M_UART0_CLOCK             0UL
#define BOARD_BOOTCLOCKFRO30M_UART1_CLOCK             0UL
#define BOARD_BOOTCLOCKFRO30M_UART2_CLOCK             0UL
#define BOARD_BOOTCLOCKFRO30M_UART3_CLOCK             0UL
#define BOARD_BOOTCLOCKFRO30M_UART4_CLOCK             0UL
#define BOARD_BOOTCLOCKFRO30M_WWDT_CLOCK              600000UL
#define BOARD_BOOTCLOCKFRO30M_DIVTO750K_CLOCK         750000UL

/*******************************************************************************
 * API for BOARD_BootClockFRO30M configuration
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief This function executes configuration of clocks.
 *
 */
void BOARD_BootClockFRO30M(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*******************************************************************************
 ******************** Configuration BOARD_BootClockPll24M **********************
 ******************************************************************************/
/*******************************************************************************
 * Definitions for BOARD_BootClockPll24M configuration
 ******************************************************************************/
#define BOARD_BOOTCLOCKPLL24M_CORE_CLOCK           24000000U  /*!< Core clock frequency: 24000000Hz */


/* Clock outputs (values are in Hz): */
#define BOARD_BOOTCLOCKPLL24M_ADC_CLOCK               0UL
#define BOARD_BOOTCLOCKPLL24M_CAPT_CLOCK              0UL
#define BOARD_BOOTCLOCKPLL24M_CLKOUT_CLOCK            0UL
#define BOARD_BOOTCLOCKPLL24M_FROHF_CLOCK             24000000UL
#define BOARD_BOOTCLOCKPLL24M_I2C0_CLOCK              0UL
#define BOARD_BOOTCLOCKPLL24M_I2C1_CLOCK              0UL
#define BOARD_BOOTCLOCKPLL24M_I2C2_CLOCK              0UL
#define BOARD_BOOTCLOCKPLL24M_I2C3_CLOCK              0UL
#define BOARD_BOOTCLOCKPLL24M_IOCON0_CLOCK            0UL
#define BOARD_BOOTCLOCKPLL24M_IOCON1_CLOCK            0UL
#define BOARD_BOOTCLOCKPLL24M_IOCON2_CLOCK            0UL
#define BOARD_BOOTCLOCKPLL24M_IOCON3_CLOCK            0UL
#define BOARD_BOOTCLOCKPLL24M_IOCON4_CLOCK            0UL
#define BOARD_BOOTCLOCKPLL24M_IOCON5_CLOCK            0UL
#define BOARD_BOOTCLOCKPLL24M_IOCON6_CLOCK            0UL
#define BOARD_BOOTCLOCKPLL24M_LOWPOWER_CLOCK          10000UL
#define BOARD_BOOTCLOCKPLL24M_SCT_CLOCK               0UL
#define BOARD_BOOTCLOCKPLL24M_SPI0_CLOCK              0UL
#define BOARD_BOOTCLOCKPLL24M_SPI1_CLOCK              0UL
#define BOARD_BOOTCLOCKPLL24M_SYSPLL_CLOCK            24000000UL
#define BOARD_BOOTCLOCKPLL24M_SYSTEM_CLOCK            24000000UL
#define BOARD_BOOTCLOCKPLL24M_UART0_CLOCK             0UL
#define BOARD_BOOTCLOCKPLL24M_UART1_CLOCK             0UL
#define BOARD_BOOTCLOCKPLL24M_UART2_CLOCK             0UL
#define BOARD_BOOTCLOCKPLL24M_UART3_CLOCK             0UL
#define BOARD_BOOTCLOCKPLL24M_UART4_CLOCK             0UL
#define BOARD_BOOTCLOCKPLL24M_WWDT_CLOCK              0UL
#define BOARD_BOOTCLOCKPLL24M_DIVTO750K_CLOCK         750000UL

/*******************************************************************************
 * API for BOARD_BootClockPll24M configuration
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief This function executes configuration of clocks.
 *
 */
void BOARD_BootClockPll24M(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

#endif /* _CLOCK_CONFIG_H_ */

