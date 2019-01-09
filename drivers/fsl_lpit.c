<<<<<<< HEAD
/*
 * The Clear BSD License
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_lpit.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpit"
#endif


/*******************************************************************************
* Variables
******************************************************************************/

/*! @brief Array to map LPIT instance number to base pointer. */
static LPIT_Type* const s_lpitBases[] = LPIT_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Clock array name */
static const clock_ip_name_t s_lpitClock[] = LPIT_CLOCKS;

#if defined(LPIT_PERIPH_CLOCKS)
/* Array of LPIT functional clock name. */
static const clock_ip_name_t s_lpitPeriphClocks[] = LPIT_PERIPH_CLOCKS;
#endif

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get the instance for LPIT module.
 *
 * @param base LPIT base address
 */
uint32_t LPIT_GetInstance(LPIT_Type* base);

/*******************************************************************************
 * Code
 ******************************************************************************/

uint32_t LPIT_GetInstance(LPIT_Type* base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_lpitBases); instance++)
    {
        if (s_lpitBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_lpitBases));

    return instance;
}

void LPIT_Init(LPIT_Type* base, const lpit_config_t* config)
{
    assert(config);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)

    uint32_t instance = LPIT_GetInstance(base);

    /* Enable the clock */
    CLOCK_EnableClock(s_lpitClock[instance]);
#if defined(LPIT_PERIPH_CLOCKS)
    CLOCK_EnableClock(s_lpitPeriphClocks[instance]);
#endif

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Reset the timer channels and registers except the MCR register */
    LPIT_Reset(base);

    /* Setup timer operation in debug and doze modes and enable the module */
    base->MCR =
        (LPIT_MCR_DBG_EN(config->enableRunInDebug) | LPIT_MCR_DOZE_EN(config->enableRunInDoze) | LPIT_MCR_M_CEN_MASK);
}

void LPIT_Deinit(LPIT_Type* base)
{
    /* Disable the module */
    base->MCR &= ~LPIT_MCR_M_CEN_MASK;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)

    uint32_t instance = LPIT_GetInstance(base);

    /* Disable the clock */
    CLOCK_DisableClock(s_lpitClock[instance]);
#if defined(LPIT_PERIPH_CLOCKS)
    CLOCK_DisableClock(s_lpitPeriphClocks[instance]);
#endif

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

void LPIT_GetDefaultConfig(lpit_config_t* config)
{
    assert(config);

    /* Timers are stopped in debug mode */
    config->enableRunInDebug = false;
    /* Timers are stopped in doze mode */
    config->enableRunInDoze = false;
}

status_t LPIT_SetupChannel(LPIT_Type* base, lpit_chnl_t channel, const lpit_chnl_params_t* chnlSetup)
{
    assert(chnlSetup);

    uint32_t reg = 0;

    /* Cannot assert the chain bit for channel 0 */
    if ((channel == kLPIT_Chnl_0) && (chnlSetup->chainChannel == true))
    {
        return kStatus_Fail;
    }

    /* Setup the channel counters operation mode, trigger operation, chain mode */
    reg = (LPIT_TCTRL_MODE(chnlSetup->timerMode) | LPIT_TCTRL_TRG_SRC(chnlSetup->triggerSource) |
           LPIT_TCTRL_TRG_SEL(chnlSetup->triggerSelect) | LPIT_TCTRL_TROT(chnlSetup->enableReloadOnTrigger) |
           LPIT_TCTRL_TSOI(chnlSetup->enableStopOnTimeout) | LPIT_TCTRL_TSOT(chnlSetup->enableStartOnTrigger) |
           LPIT_TCTRL_CHAIN(chnlSetup->chainChannel));

    base->CHANNEL[channel].TCTRL = reg;

    return kStatus_Success;
}
=======
/*
 * The Clear BSD License
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_lpit.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpit"
#endif


/*******************************************************************************
* Variables
******************************************************************************/

/*! @brief Array to map LPIT instance number to base pointer. */
static LPIT_Type* const s_lpitBases[] = LPIT_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Clock array name */
static const clock_ip_name_t s_lpitClock[] = LPIT_CLOCKS;

#if defined(LPIT_PERIPH_CLOCKS)
/* Array of LPIT functional clock name. */
static const clock_ip_name_t s_lpitPeriphClocks[] = LPIT_PERIPH_CLOCKS;
#endif

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get the instance for LPIT module.
 *
 * @param base LPIT base address
 */
uint32_t LPIT_GetInstance(LPIT_Type* base);

/*******************************************************************************
 * Code
 ******************************************************************************/

uint32_t LPIT_GetInstance(LPIT_Type* base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_lpitBases); instance++)
    {
        if (s_lpitBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_lpitBases));

    return instance;
}

void LPIT_Init(LPIT_Type* base, const lpit_config_t* config)
{
    assert(config);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)

    uint32_t instance = LPIT_GetInstance(base);

    /* Enable the clock */
    CLOCK_EnableClock(s_lpitClock[instance]);
#if defined(LPIT_PERIPH_CLOCKS)
    CLOCK_EnableClock(s_lpitPeriphClocks[instance]);
#endif

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Reset the timer channels and registers except the MCR register */
    LPIT_Reset(base);

    /* Setup timer operation in debug and doze modes and enable the module */
    base->MCR =
        (LPIT_MCR_DBG_EN(config->enableRunInDebug) | LPIT_MCR_DOZE_EN(config->enableRunInDoze) | LPIT_MCR_M_CEN_MASK);
}

void LPIT_Deinit(LPIT_Type* base)
{
    /* Disable the module */
    base->MCR &= ~LPIT_MCR_M_CEN_MASK;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)

    uint32_t instance = LPIT_GetInstance(base);

    /* Disable the clock */
    CLOCK_DisableClock(s_lpitClock[instance]);
#if defined(LPIT_PERIPH_CLOCKS)
    CLOCK_DisableClock(s_lpitPeriphClocks[instance]);
#endif

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

void LPIT_GetDefaultConfig(lpit_config_t* config)
{
    assert(config);

    /* Timers are stopped in debug mode */
    config->enableRunInDebug = false;
    /* Timers are stopped in doze mode */
    config->enableRunInDoze = false;
}

status_t LPIT_SetupChannel(LPIT_Type* base, lpit_chnl_t channel, const lpit_chnl_params_t* chnlSetup)
{
    assert(chnlSetup);

    uint32_t reg = 0;

    /* Cannot assert the chain bit for channel 0 */
    if ((channel == kLPIT_Chnl_0) && (chnlSetup->chainChannel == true))
    {
        return kStatus_Fail;
    }

    /* Setup the channel counters operation mode, trigger operation, chain mode */
    reg = (LPIT_TCTRL_MODE(chnlSetup->timerMode) | LPIT_TCTRL_TRG_SRC(chnlSetup->triggerSource) |
           LPIT_TCTRL_TRG_SEL(chnlSetup->triggerSelect) | LPIT_TCTRL_TROT(chnlSetup->enableReloadOnTrigger) |
           LPIT_TCTRL_TSOI(chnlSetup->enableStopOnTimeout) | LPIT_TCTRL_TSOT(chnlSetup->enableStartOnTrigger) |
           LPIT_TCTRL_CHAIN(chnlSetup->chainChannel));

    base->CHANNEL[channel].TCTRL = reg;

    return kStatus_Success;
}
>>>>>>> spi
