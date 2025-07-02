#ifndef SAMPLE_TOP_HPP
#define SAMPLE_TOP_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "atomic.hpp"
#include "Digitalout.hpp"
#include "Digitalinput.hpp"
#include "analoginput.hpp"
#include "stm32h7xx_hal_rcc.h"
#include "stm32h7xx_hal_dma.h"
#include "stm32h7xx_hal_uart.h"



using namespace cadmium;

struct top_coupled : public Coupled {
    top_coupled(const std::string& id) : Coupled(id) {
        // __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
    
        auto atomique = addComponent<atomic_model>("atomique");

        // Configuration manuelle du GPIO
        static GPIO_InitTypeDef led_config = {
            .Pin = GPIO_PIN_0,
            .Mode = GPIO_MODE_OUTPUT_PP,
            .Pull = GPIO_NOPULL,
            .Speed = GPIO_SPEED_FREQ_LOW,
            .Alternate = 0
        };
          // Configuration manuelle du GPIO
        static GPIO_InitTypeDef input = {
            .Pin = GPIO_PIN_13,
            .Mode = GPIO_MODE_INPUT,
            .Pull = GPIO_NOPULL,
            .Speed = GPIO_SPEED_FREQ_LOW,
            .Alternate = 0
        };
        static GPIO_InitTypeDef analogue = {
            .Pin = GPIO_PIN_0,
            .Mode = GPIO_MODE_ANALOG,
            .Pull = GPIO_NOPULL,
            .Speed = GPIO_SPEED_FREQ_LOW,
            .Alternate = 0
        };

        GPIO_TypeDef* led_port = GPIOB;
        GPIO_TypeDef* inputport = GPIOC;
      
        // Ajout du composant DigitalOutput avec paramètres
        auto digitaloutput = addComponent<DigitalOutput>(
            "digitaloutput",
            led_port,
            &led_config
        );
        auto digitalinput = addComponent<DigitalInput>(
            "digitalinput",
            inputport,
            &input
        );
       
        addCoupling(digitalinput->out,atomique->in);
        addCoupling(atomique->out, digitaloutput->in);
    }
};

#endif  // SAMPLE_TOP_HPP
