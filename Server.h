//
// Created by orit on 17/12/2019.
//

#ifndef EX3_SERVER_H
#define EX3_SERVER_H

#include <netinet/in.h>
#include "SymbolTable.h"
#include "Defines.h"
#include <strings.h>

using namespace std;

class Server {
    int client_socket;
    string simArr[36];

public:
    void runServer(int port);

    void readData();

    void buildSimStringArray();

    vector<string> splitString(string data, string del);

    vector<float> convertData(vector<string> dataVector);

    void updateTable(vector<float> values);
};

enum simVars {
    airspeed_indicator = 0,
    time_warp,
    switches_magnetos,
    heading_indicator,
    altimeter_indicated_altitude,
    altimeter_pressure_alt,
    attitude_indicator_indicated_pitch,
    attitude_indicator_indicated_roll,
    attitude_indicator_internal_pitch,
    attitude_indicator_internal_roll,
    encoder_indicated_altitude,
    encoder_pressure_alt,
    gps_indicated_altitude,
    gps_indicated_ground_speed,
    gps_indicated_vertical_speed,
    indicated_heading,
    magnetic_compass_indicated_heading,
    indicated_slip_skid,
    indicated_turn_rate,
    vertical_speed,
    flight_aileron,
    flight_elevator,
    flight_rudder,
    flight_flaps,
    engine_throttle,
    current_engine_throttle,
    switches_master_avionics,
    switches_starter,
    active_engine_auto_start,
    flight_speedbrake,
    brake_parking,
    engine_primer,
    current_engine_mixture,
    switches_master_bat,
    switches_master_alt,
    engine_rpm
};

#endif //EX3_SERVER_H
