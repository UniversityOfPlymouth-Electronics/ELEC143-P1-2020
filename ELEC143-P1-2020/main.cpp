#include "mbed.h"
#include "../lib/uopmsb/uop_msb_2_0_0.h"
#include "BMP280_SPI.h"

using namespace uop_msb_200;

// function prototypes
// checkTimers() checks the three timers for temperaturte, light and pressure returns 3 bit value
// where bits are temperature (MSB), light, pressure (LSB)
// 7 = all three
// 6 = temperature and light
// 5 = temperature and pressure
// 4 = temperature
// 3 = light and pressure
// 2 = light
// 1 = pressure
// 0 = none
int checkTimers();  


//On board LEDs
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

//On board switch
DigitalIn BlueButton(USER_BUTTON);

//LCD Display
LCD_16X2_DISPLAY disp;

//Buzzer
Buzzer buzz;

//Traffic Lights
DigitalOut traf1RedLED(TRAF_RED1_PIN,1);
DigitalOut traf1YelLED(TRAF_YEL1_PIN);
DigitalOut traf1GrnLED(TRAF_GRN1_PIN);
DigitalInOut traf2RedLED(TRAF_RED2_PIN, PIN_OUTPUT, OpenDrainNoPull, 1);
DigitalInOut traf2YelLED(TRAF_YEL2_PIN, PIN_OUTPUT, OpenDrainNoPull, 1);
DigitalInOut traf2GrnLED(TRAF_GRN2_PIN, PIN_OUTPUT, OpenDrainNoPull, 1);

//Light Levels
AnalogIn ldr(AN_LDR_PIN);

//LCD Backlight - consider PwmOut for this :)
DigitalOut backLight(LCD_BKL_PIN);

// Timers
Timer temperatureTimer ;

// Time periods in microseconds
unsigned int temperaturePeriod = (10*1000000), temperatureTimerElapsedTime = 0;

int main()
{
    int timerCheckValue = 0; // return value from checking timers 
    //Environmental sensor;
    EnvironmentalSensor sensor;

    //LCD Backlight ON
    backLight = 1;

    // Start timers
    temperatureTimer.start();

    while (true) {

        timerCheckValue = checkTimers();
        switch(timerCheckValue)
        {
            case 7:     // All three timers
                break;
            case 6:     // temperature and light
                break;
            case 5:     // temperature and pressure
                break;
            case 4:     // temperature
                break;
            case 3:     // light and pressure
                break;
            case 2:     // light
                break;
            case 1:     // pressure
                break;
            case 0:     // none
                break;
            default:    // shouldn't happen so print error message
                printf("timerCheckValue error\n");
                break;                
        }

        
        led1 = 1;
        led2 = 1;
        led3 = 1;
        wait_us(500000);
        led1 = 0;
        led2 = 0;
        led3 = 0;  
        wait_us(500000);    

        disp.cls();
        disp.printf("LDR: %0.3f", ldr.read());

        float temperature=0.0f, pressure=0.0f;
        temperature=sensor.getTemperature();
        pressure=sensor.getPressure();

        printf("%.1fC %.1fmBar\n",temperature,pressure);     
    }
}

int checkTimers()
{
    int returnValue = 0;
    temperatureTimerElapsedTime = temperatureTimer.elapsed_time().count();
    if (temperatureTimerElapsedTime > temperaturePeriod)
    {
        printf("Temp clock = %d\n", temperatureTimerElapsedTime); 
        temperatureTimer.reset();
        returnValue += 4;
    }

    return returnValue;
}
