#include "AnySerial.h"

/*
 * AnySerial - Wrapper class for HardwareSerial, SoftwareSerial & AltSoftSerial
 * Copyright (C) 2014 Aaron Turner
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Wrapper class around:
 * SoftwareSerial
 * AltSoftSerial
 * HardwareSerial (Serial, Serial[123])
 *
 * The goal of AnySerial is to make writing libraries which
 * use the serial port more cross platform and easier to use.
 *
 * Rather then hard coding a specific Serial port or pins,
 * you can now just accept an AnySerial object to your
 * constructor and you don't care what what kind of serial
 * port it is (hardware or serial), you can just interact
 * with it normally.
 *
 * Just be sure to import the necessary SoftwareSerial.h or
 * AltSoftSerial.h BEFORE importing AnySerial.h so that
 * AnySerial will be compiled with the necessary support.
 *
 * AnySerial always supports hardware serial ports (Serial,
 * Serial1, etc)
 */

// HardwareSerial
AnySerial::AnySerial(HardwareSerial *port) {
    serialport.hardware = port;
    port_type = anyserial_hardware;
    debug_flag = 0;
}

void
AnySerial::attach(HardwareSerial *port) {
    serialport.hardware = port;
    port_type = anyserial_hardware;
    debug_flag = 0;
}


AnySerial::~AnySerial() {
    end();
}

/*
 * What kind of port are we?
 */
anyserial_t
AnySerial::get_port_type() {
    return port_type;
}


void
AnySerial::attach_debug(AnySerial *port) {
    debug_port = port;
}

int
AnySerial::debug(int onoff = -1) {
    switch (onoff) {
        case -1:
            return debug_flag;
            break;
        case 0:
            debug_flag = 0;
            return 0;
            break;
        case 1:
            debug_flag = 1;
            return 1;
            break;
    }
    return -1;
}
