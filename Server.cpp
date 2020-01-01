//
// Created by orit on 12/17/19.
//

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include "Server.h"

using namespace std;

void Server::runServer(int client_socket) {
    SymbolTable *s = s->getTable();
    this->buildSimStringArray();
    this->client_socket = client_socket;
    this->readData();
    close(client_socket);
}

void Server::readData() {
    string data, parsedData;
    char buffer[256];
    int valRead;
    while (true) {
        bzero(buffer, 256);
        valRead = read(this->client_socket, buffer, 256);
        data.append(buffer);
        while (data.find('\n') == string::npos) {
            int currRead;
            bzero(buffer, 256);
            currRead = read(this->client_socket, buffer, 256);
            valRead += currRead;
            data.append(buffer);
        }
        parsedData = data.substr(0, data.find('\n'));
        data.erase(0, data.find('\n') + 1);
        vector<string> stringVector = this->splitString(parsedData, ",");
        vector<float> values = this->convertData(stringVector);
        this->updateTable(values);
    }
}

vector<string> Server::splitString(string data, string del) {
    vector<string> dataVector;
    while (data.find(del) != string::npos) {
        dataVector.push_back(data.substr(0, data.find(del)));
        data.erase(0, data.find(del) + 1);
    }
    dataVector.push_back(data);
    return dataVector;
}

vector<float> Server::convertData(vector<string> dataVector) {
    vector<float> numVector;
    float value;
    for (string str: dataVector) {
        try {
            value = stof(str);
        } catch (exception *e) {
            cerr << "falied for: \"" + str + "\"" << endl;
            value = 0;
        }
        numVector.push_back(value);
    }
    return numVector;
}


void Server::buildSimStringArray() {
    simArr[airspeed_indicator] = string("/instrumentation/airspeed-indicator/indicated-speed-kt");
    simArr[time_warp] = string("/sim/time/warp");
    simArr[switches_magnetos] = string("/controls/switches/magnetos");
    simArr[heading_indicator] = string("/instrumentation/heading-indicator/offset-deg");
    simArr[altimeter_indicated_altitude] = string("/instrumentation/altimeter/indicated-altitude-ft");
    simArr[altimeter_pressure_alt] = string("/instrumentation/altimeter/pressure-alt-ft");
    simArr[attitude_indicator_indicated_pitch] = string("/instrumentation/attitude-indicator/indicated-pitch-deg");
    simArr[attitude_indicator_indicated_roll] = string("/instrumentation/attitude-indicator/indicated-roll-deg");
    simArr[attitude_indicator_internal_pitch] = string("/instrumentation/attitude-indicator/internal-pitch-deg");
    simArr[attitude_indicator_internal_roll] = string("/instrumentation/attitude-indicator/internal-roll-deg");
    simArr[encoder_indicated_altitude] = string("/instrumentation/encoder/indicated-altitude-ft");
    simArr[encoder_pressure_alt] = string("/instrumentation/encoder/pressure-alt-ft");
    simArr[gps_indicated_altitude] = string("/instrumentation/gps/indicated-altitude-ft");
    simArr[gps_indicated_ground_speed] = string("/instrumentation/gps/indicated-ground-speed-kt");
    simArr[gps_indicated_vertical_speed] = string("/instrumentation/gps/indicated-vertical-speed");
    simArr[indicated_heading] = string("/instrumentation/heading-indicator/indicated-heading-deg");
    simArr[magnetic_compass_indicated_heading] = string("/instrumentation/magnetic-compass/indicated-heading-deg");
    simArr[indicated_slip_skid] = string("/instrumentation/slip-skid-ball/indicated-slip-skid");
    simArr[indicated_turn_rate] = string("/instrumentation/turn-indicator/indicated-turn-rate");
    simArr[vertical_speed] = string("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
    simArr[flight_aileron] = string("/controls/flight/aileron");
    simArr[flight_elevator] = string("/controls/flight/elevator");
    simArr[flight_rudder] = string("/controls/flight/rudder");
    simArr[flight_flaps] = string("/controls/flight/flaps");
    simArr[engine_throttle] = string("/controls/engines/engine/throttle");
    simArr[current_engine_throttle] = string("/controls/engines/current-engine/throttle");
    simArr[switches_master_avionics] = string("/controls/switches/master-avionics");
    simArr[switches_starter] = string("/controls/switches/starter");
    simArr[active_engine_auto_start] = string("/engines/active-engine/auto-start");
    simArr[flight_speedbrake] = string("/controls/flight/speedbrake");
    simArr[brake_parking] = string("/sim/model/c172p/brake-parking");
    simArr[engine_primer] = string("/controls/engines/engine/primer");
    simArr[current_engine_mixture] = string("/controls/engines/current-engine/mixture");
    simArr[switches_master_bat] = string("/controls/switches/master-bat");
    simArr[switches_master_alt] = string("/controls/switches/master-alt");
    simArr[engine_rpm] = string("/engines/engine/rpm");
}
