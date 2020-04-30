//
// Created by orit on 18/12/2019.
//

#ifndef EX3_DEFINES_H
#define EX3_DEFINES_H
#define AIRSPEED "/instrumentation/airspeed-indicator/indicated-speed-kt"
#define WRAP "/sim/time/warp"
#define MAGNETOS "/controls/switches/magnetos"
#define HEADING "/instrumentation/heading-indicator/offset-deg"
#define INDICATED_ALTITUDE "/instrumentation/altimeter/indicated-altitude-ft"
#define PRESSURE "/instrumentation/altimeter/pressure-alt-ft"
#define INDICATED_PITCH "/instrumentation/attitude-indicator/indicated-pitch-deg"
#define INDICATED_ROLL "/instrumentation/attitude-indicator/indicated-roll-deg"
#define INTERNAL_PITCH "/instrumentation/attitude-indicator/internal-pitch-deg"
#define INTERNAL_ROLL "/instrumentation/attitude-indicator/internal-roll-deg"
#define ENCODER_ALTITUDE "/instrumentation/encoder/indicated-altitude-ft"
#define ENCODER_PRESSURE "/instrumentation/encoder/pressure-alt-ft"
#define GPS_ALTITUDE "/instrumentation/gps/indicated-altitude-ft"
#define GPS_GROUND_SPEED "/instrumentation/gps/indicated-ground-speed-kt"
#define GPS_VERTICAL_SPEED "/instrumentation/gps/indicated-vertical-speed"
#define INDICATED_HEADING "/instrumentation/heading-indicator/indicated-heading-deg"
#define MAGNETIC_COMPASS "/instrumentation/magnetic-compass/indicated-heading-deg"
#define SLIP_SKID "/instrumentation/slip-skid-ball/indicated-slip-skid"
#define TURN_INDICATOR "/instrumentation/turn-indicator/indicated-turn-rate"
#define SPEED_INDICATOR "/instrumentation/vertical-speed-indicator/indicated-speed-fpm"
#define AILERON "/controls/flight/aileron"
#define ELEVATOR "/controls/flight/elevator"
#define RUDDER "/controls/flight/rudder"
#define FLAPS "/controls/flight/flaps"
#define THROTTLE "/controls/engines/engine/throttle"
#define CURRENT_THROTTLE "/controls/engines/current-engine/throttle"
#define AVIONICS "/controls/switches/master-avionics"
#define STARTER "/controls/switches/starter"
#define AUTOSTART "/engines/active-engine/auto-start"
#define SPEEDBREAK "/controls/flight/speedbrake"
#define BREAKPARKING "/sim/model/c172p/brake-parking"
#define PRIMER "/controls/engines/engine/primer"
#define MIXTURE "/controls/engines/current-engine/mixture"
#define MASTER_BAT "/controls/switches/master-bat"
#define MASTER_ALT "/controls/switches/master-alt"
#define RPM "/engines/engine/rpm"
#define MAXVAL 60000000000000000000000000000000000000000000000000.0
#include "SymbolTable.h"

#include <map>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <iostream>
#include <thread>
#include <mutex>
#include "Interpreter.h"

using namespace std;

#endif //EX3_DEFINES_H
