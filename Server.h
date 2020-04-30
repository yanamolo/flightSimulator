//
// Created by orit on 17/12/2019.
//

#ifndef EX3_SERVER_H
#define EX3_SERVER_H

#include <netinet/in.h>
#include "SymbolTable.h"
#include "Defines.h"

using namespace std;

class Server {
    float info[36];
    string sims[36];
public:
    void runServer(int port);
    void parseInfo(string buffer);
    void creatArr();
    string subTheString(string sub, int start, int end);
};

enum sim_vars{
    air_speed = 0,
    wrap,
    magnetos,
    heading,
    indicated_altitude,
    pressure,
    indicated_pitch,
    indicated_roll,
    internal_pitch,
    internal_roll,
    encoder_altitude,
    encoder_pressure,
    gps_altitude,
    gps_ground_speed,
    gps_vertical_speed,
    indicated_heading,
    magnetic_compass,
    slip_skid,
    turn_indicator,
    speed_indicator,
    aileron,
    elevator,
    rudder,
    flaps,
    throttle,
    current_throttle,
    avionics,
    starter,
    autostart,
    speedbreak,
    breakparking,
    primer,
    mixture,
    master_bat,
    master_alt,
    rpm
};

#endif //EX3_SERVER_H
