
// API defined by framework
#include <app/app.h>

// Somewhat similar API behind facade.
// I.E. the real app that we delegate to.
#include "blinker.h"


/*
 * Alternate apps: constant duty cycle, or task scheduled duty cycle
 *
 * This is a constant duty cycle app.
 * It wakes regularly, every xxx seconds.
 */




void App::onPowerOnReset() {
	App::configureSleepingGPIO();
	// assert app's pins (LED) configured

	// initialize state
	Blinker::init();
}


void App::onWakeForAlarm() {
	// require app's persistent GPIO still configured (LED)

	/*
	 * app state transition
	 *
	 * In general design, there can be many tasks, using scheduler.
	 * For a design with only one task, do it now.
	 */
    Blinker::onAlarm();
}



Duration App::constantDurationOfSleep() {
	return 10;
}



EpochTime App::timeToWake() {
    return Blinker::timeToWake();
}



void App::configureSleepingGPIO() {
	/*
	 * App retains state of an LED during sleep.
	 * The LED is off during sleep, but the SoC chip is retaining its off state.
	 */
    Blinker::configureGPIO();
}
