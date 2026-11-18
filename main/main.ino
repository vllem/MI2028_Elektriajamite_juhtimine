/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
| MI.2028 Elektriajamite juhtimine                                                                                                             |
| Autor: Villem Haug                                                                                                                           | 
| 2026/2027 sügissemester                                                                                                                      | 
|                                                                                                                                              |
| Eesmärk on luua raamistik/tarkvarateek millega saaks juhtida mootoreid lihtsasti ja vähese koodiga.                                          |
| Selleks kasutan C++ klasse: abstraktne Motor ning sellest päritud DCMotor, StepperMotor ja ServoMotor.                                      |
| motorDriver.h sisaldab koodi, mis paneb paika kuidas juhtida mootorit ja juhib mootorit                                                      |
| userInterface.h sisaldab koodi, mis paneb paika kuidas käsitleda serialis sisestatud käske.                                                  |
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Single-header teegid (stb-stiilis, https://github.com/nothings/stb): teostus genereeritakse täpselt ühes failis. 
// Mõtlesin, et suht mõtetu on jantida 4 erineva failiga ning tuli meelde, et single-header teegi moodi asi teeb elu lihtsamaks. 
#include <avr/wdt.h>

#define MOTORDRIVER_IMPLEMENTATION
#define USERINTERFACE_IMPLEMENTATION
#include "motorDriver.h"
#include "userInterface.h"

// StepperMotor stepper(8, 9, 10, 11);  // ULN2003 IN1..IN4 = pinid 8..11
DCMotor dc(3);                       // Alalisvoolumootor: PWM = pin 3
ServoMotor servo_1(5);                 // Servo: signaal = pin 5
ServoMotor servo_2(6);
ServoMotor servo_3(9); 

CommandInterpreter ui;

void setup() {
  Serial.begin(115200);

  //stepper.begin();
  dc.begin();
  servo_1.begin();
  servo_2.begin();
  servo_3.begin();
  
  // Käskudes kasutatavad nimed; esimesena lisatud mootor on vaikimisi valitud
  //ui.add("stepper", stepper);
  ui.add("dc", dc);
  ui.add("servo_1", servo_1);
  ui.add("servo_2", servo_2);
  ui.add("servo_3", servo_3);

  Serial.println(F("Ready. Type 'help' to see available commands."));
  wdt_enable(WDTO_250MS);
}

void loop() {
  wdt_reset();
  ui.poll();
  servo_1.update();
  servo_2.update();
  servo_3.update();
  dc.update();
}
