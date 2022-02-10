/*
VERSÃO API: 5.0 (10-01-2018)
AUTOR: FERNANDO SIMPLICIO
API PARA NODEMCU ESP32

Copyright (c) 2013-2016 Microgenios.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/
#ifndef _GENIOT_HTTPS_H_
#define _GENIOT_HTTPS_H_



#include <Arduino.h>
#include "cJSON.h"
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>



#define HTTPSERVER "https://www.geniot.io"
#define DEBUG false

typedef struct Value {
  char  *id;
  char *context;
  float value_id;
  unsigned long timestamp;
} Value;


class Geniot {
 public:
    Geniot(char* token_geniot);
	
    bool send( void );
	bool read( char * variable_id ); 

	void add(char *, char *);
    void add(char *variable_id, float value);
    void add(char *variable_id, float value, char *ctext);
    void add(char *variable_id, float value, unsigned long timestamp);
    void add(char *variable_id, float value, char *ctext, unsigned long timestamp);
    bool wifiConnection(char *ssid, char *pass);

	void vPrintString( const char *pcString);
	void vPrintStringAndFloat( const char *pcString, float ulValue );
	void vPrintStringAndInteger( const char *pcString, uint32_t ulValue );
	void vPrintTwoStrings(const char *pcString1, const char *pcString2);

	float geniotValue; 
	char geniotText[100];

 private:

    char* _token_geniot;
	
    uint8_t maxValues;
    uint8_t currentValue;
    Value * val;

    WiFiMulti wifiMulti;
	portMUX_TYPE myMutex = portMUX_INITIALIZER_UNLOCKED;

	const char* ca = \ 
	"-----BEGIN CERTIFICATE-----\n" \ 
	"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n" \
	"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n" \
	"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n" \
	"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n" \
	"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n" \
	"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n" \
	"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n" \
	"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n" \
	"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n" \
	"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n" \
	"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n" \
	"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n" \
	"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n" \
	"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n" \
	"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n" \
	"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n" \
	"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n" \
	"rqXRfboQnoZsG4q5WTP468SQvvG5\n" \
	"-----END CERTIFICATE-----\n";


	
};

#endif