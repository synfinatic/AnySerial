#ifndef __ANYSERIAL_H__
#define __ANYSERIAL_H__

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

#include <HardwareSerial.h>
#include <Arduino.h>

typedef enum {
#ifdef AltSoftSerial_h
    anyserial_altsoft,
#endif
#ifdef SoftwareSerial_h
    anyserial_soft,
#endif
#ifdef USBserial_h_
    anyserial_usb,
#endif
    anyserial_hardware
} anyserial_t;

typedef union {
    HardwareSerial *hardware;
#ifdef USBserial_h_
    usb_serial_class *usb;
#endif
#ifdef AltSoftSerial_h
    AltSoftSerial *altsoft;
#endif
#ifdef SoftwareSerial_h
    SoftwareSerial *soft;
#endif
} serialport_t;

class AnySerial : public Stream {
    public:
        AnySerial() { };
        AnySerial(HardwareSerial *port);
        void attach(HardwareSerial *port);
#ifdef AltSoftSerial_h
        AnySerial(AltSoftSerial *port);
        void attach(AltSoftSerial *port);
#endif
#ifdef SoftwareSerial_h
        AnySerial(SoftwareSerial *port);
        void attach(SoftwareSerial *port);
#endif
#ifdef USBserial_h_
        AnySerial(usb_serial_class *port);
        void attach(usb_serial_class *port);
#endif
        ~AnySerial();
        void *port();
        void end();
        void begin(uint32_t baud);
        int peek();
        int read();
        int available();
        void attach_debug(AnySerial *port);
        bool listen();
        bool isListening();
        size_t write(char *str);
        virtual size_t write(const uint8_t *buff, size_t len);
        virtual size_t write(uint8_t byte) { writeByte(byte); return 1; }
        using Print::write;
        void flush() { flushOutput(); }
        void flushInput();
        void flushOutput();
        bool overflow();
        int debug(int onoff);
        int library_version();
        int readBytesUntil(char, char *, int);
        anyserial_t get_port_type();
private:
        int debug_flag;
        anyserial_t port_type;
        serialport_t serialport;
        void writeByte(uint8_t byte);
        AnySerial *debug_port;
};

#ifdef SoftwareSerial_h
AnySerial::AnySerial(SoftwareSerial *port) {
    serialport.soft = port;
    port_type = anyserial_soft;
    debug_flag = 0;
}

void
AnySerial::attach(SoftwareSerial *port) {
    serialport.soft = port;
    port_type = anyserial_soft;
}
#endif

#ifdef AltSoftSerial_h
AnySerial::AnySerial(AltSoftSerial *port) {
    serialport.altsoft = port;
    port_type = anyserial_altsoft;
    debug_flag = 0;
}

void
AnySerial::attach(AltSoftSerial *port) {
    serialport.altsoft = port;
    port_type = anyserial_altsoft;
    debug_flag = 0;
}
#endif

// USBSerial
#ifdef USBserial_h_
AnySerial::AnySerial(usb_serial_class *port) {
    serialport.usb = port;
    port_type = anyserial_usb;
    debug_flag = 0;
}

void
AnySerial::attach(usb_serial_class *port) {
    serialport.usb = port;
    port_type = anyserial_usb;
    debug_flag = 0;
}
#endif


#endif
