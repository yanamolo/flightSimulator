//
// Created by orit on 12/17/19.
//

#include <unistd.h>
#include "Server.h"
using namespace std;

void Server::runServer(int client_socket) {
    SymbolTable *s = s->getTable();
    string strToParse = "", afterParse = "";
    creatArr();
    char buffer[256];
    while (s->getIfRun()) {
        bzero(buffer, 256);
        int valread = read(client_socket, buffer, 256);
        strToParse.append(buffer);
        while (strToParse.find('\n') == string::npos){
            bzero(buffer, 256);
            int curr = read(client_socket, buffer, 256);
            valread += curr;
            strToParse.append(buffer);
        }
        afterParse = strToParse.substr(0, strToParse.find("\n"));
        strToParse.erase(0, strToParse.find("\n") + 1);

        // put string values into the info float list
        parseInfo(afterParse);

        list<string> list_sims = s->getSimsForServer();
        list<string>::iterator it = list_sims.begin();
        int index = 0;
        for (float value: info) {
            s->lockExecute('s', sims[index], "", "", value);
            index++;
        }
    }
    close(client_socket);
}

void Server::parseInfo(string buffer) {
    int i = 0;
    while (buffer.find(",") != string::npos) {
        float val = stof(buffer.substr(0, buffer.find(",")));
        info[i] = val;
        buffer.erase(0, buffer.find(",") + 1);
        i++;
    }
    info[i] = stof(buffer);
}

void Server::creatArr() {

    sims[0] = string(AIRSPEED);
    sims[1] = string(WRAP);
    sims[2] = string(MAGNETOS);
    sims[3] = string(HEADING);
    sims[4] = string(INDICATED_ALTITUDE);
    sims[5] = string(PRESSURE);
    sims[6] = string(INDICATED_PITCH);
    sims[7] = string(INDICATED_ROLL);
    sims[8] = string(INTERNAL_PITCH);
    sims[9] = string(INTERNAL_ROLL);
    sims[10] = string(ENCODER_ALTITUDE);
    sims[11] = string(ENCODER_PRESSURE);
    sims[12] = string(GPS_ALTITUDE);
    sims[13] = string(GPS_GROUND_SPEED);
    sims[14] = string(GPS_VERTICAL_SPEED);
    sims[15] = string(INDICATED_HEADING);
    sims[16] = string(MAGNETIC_COMPASS);
    sims[17] = string(SLIP_SKID);
    sims[18] = string(TURN_INDICATOR);
    sims[19] = string(SPEED_INDICATOR);
    sims[20] = string(AILERON);
    sims[21] = string(ELEVATOR);
    sims[22] = string(RUDDER);
    sims[23] = string(FLAPS);
    sims[24] = string(THROTTLE);
    sims[25] = string(CURRENT_THROTTLE);
    sims[26] = string(AVIONICS);
    sims[27] = string(STARTER);
    sims[28] = string(AUTOSTART);
    sims[29] = string(SPEEDBREAK);
    sims[30] = string(BREAKPARKING);
    sims[31] = string(PRIMER);
    sims[32] = string(MIXTURE);
    sims[33] = string(MASTER_BAT);
    sims[34] = string(MASTER_ALT);
    sims[35] = string(RPM);

}


string Server::subTheString(string sub, int start, int end) {
    string s = "";
    bool flag = false;
    for (int i = 0; i < sub.size(); i++) {
        if (i == start) {
            flag = true;
            if (start == 0) {
                s += sub[i];
            }
            continue;
        } else if (i == end) {
            break;
        } else if (flag == true) {
            s += sub[i];
        }
    }
    return s;
}