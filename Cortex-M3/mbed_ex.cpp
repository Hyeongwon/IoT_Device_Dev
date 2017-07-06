//1. Serial.printf, Serial.baud
#if 1
#include "mbed.h"
Serial pc(SERIAL_TX, SERIAL_RX);
int main(){
    
    pc.baud(9600);
    
    while(1) {
        pc.printf("Hello Cortex-M4~\n\r");
        wait(1);
    }
}
#endif

//2. Serial.getc, Serial.readable
#include "mbed.h"
Serial pc(SERIAL_TX, SERIAL_RX);
int main(){
    
    pc.baud(115200);
    
    while(1) {
        if(pc.readable()) {
            char userInput = pc.getc();
            pc.printf("%c\n\r", userInput);
        }
    }
} 

#if 0
//3. DigitalOut
#include "mbed.h"
DigitalOut myled(LED1);
int main() {
    while(1) {
        myled = 1; // LED is ON
        wait(1.0); // 1 sec
        myled = 0; // LED is OFF
        wait(1.0); // 1 sec
    }
}
#endif

#if 0
//4.PWMOut
#include "mbed.h"
PwmOut led(PWM_OUT);
int main() {
    
    while(1) {
        
    for(int fadeValue = 0; fadeValue < 4096; fadeValue++) {
        
        led = fadeValue/4096.0;
        wait(0.001);
    }
    
    for(int fadeValue = 4096; fadeValue > 0; fadeValue--) {
        led = fadeValue/4096.0;
        wait(0.001);
    }
}
}
#endif

#if 0
//5. DigitalIn
#include "mbed.h"
DigitalIn mybutton(USER_BUTTON);
Serial pc(SERIAL_TX, SERIAL_RX);

int main() {
    pc.baud(115200);

    while(1) {
        pc.printf("%d\n\r", mybutton.read());
    }
}
#endif

#if 0
//6. AnalogIn
#include "mbed.h"
AnalogIn analog_value(A0);
Serial pc(SERIAL_TX, SERIAL_RX);
int main() {
    float meas;
    pc.baud(115200);

    while(1) {
        meas = analog_value.read();
        // Converts and read the analog input value (value from 0.0 to 1.0)
        meas = meas * 3300; // Change the value to be in the 0 to 3300 range
        pc.printf("measure = %.0f mV\n\r", meas);
    }
}
#endif

#if 0
//7. 부저
#include "mbed.h"
const int melody[] = {
262, 294, 330, 349, 392, 440, 494, 523,
};
PwmOut mypwm(PWM_OUT);
int main() {

    while(1) {
        for(int thisNote=0; thisNote<8; thisNote++) {
        mypwm.period_us(1000000/melody[thisNote]);
        mypwm.pulsewidth_us(1000000/melody[thisNote]/2);
        wait(1);
    }
}
}
#endif

#if 0
//8. 
#include "mbed.h"
PwmOut servo(PWM_OUT);
int main() {

    servo.period_us(20000); // servo requires a 20ms period
   
    while (1) {
        for(int duty = 450; duty <= 2500; duty++) {
            servo.pulsewidth_us(duty);
            wait(0.001);
        }
        
        servo.pulsewidth_us(450);
        wait(0.5);
    }
}
#endif
