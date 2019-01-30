/*
 * Configuration aspect of App
 */

// API defined by framework
#include <app/app.h>

// Somewhat similar API behind facade.
// I.E. the real app that we delegate to.
#include "blinker.h"

// mcu hal layer e.g. MSPWare DriverLib
#include <gpio.h>   // depends on msp430.h   // Pins






void App::configureSleepingGPIO() {
    /*
     * App retains state of an LED during sleep.
     * The LED is off during sleep, but the SoC chip is retaining its off state.
     */
    Blinker::configureGPIO();
}


void App::configureUnusedPinsLowPower() {
    /*
     * Not require LPM5 locked.
     *
     * Only configure pins not connected,
     * since configuring connected pins as output can trigger connected devices.
     *
     * Alternatives for low power:  input with pullup/pulldown or output.
     * Do not leave as input without pull: floats and wastes power.
     */

    // TODO optimize: configure entire register at once

    // P1.0 red LED or LEDP
    // P1.1 not used or green LED or LEDPWM

    // TODO set known OUT
    // hack, if it is launchpad, dark the sourced green led
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN1);
    // P1.2 SPI Slave select (out)
    // P1.3 Alarm (in)
    // P1.4 LEDN
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN5);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN6);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN7);

    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN3);
    // SPI data pins
    //GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN4);
    //GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN5);
    //GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN6);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN7);

    // Only 5 pins on port 3
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN1);
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN2);
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN3);
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN4);

    // Not ensure configuration is effective, since LPM5 might be locked
}


void App::configureUsedPins() {
    // App retains LED state during sleep (but usually off.)
    Blinker::configureGPIO();
}
