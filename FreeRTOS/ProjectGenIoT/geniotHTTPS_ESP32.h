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



#define HTTPSERVER "https://www.geniot.com.br"
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
  "	-----BEGIN CERTIFICATE-----\n"
  " YOUR CERTIFICATE HERE\n"
  "-----END CERTIFICATE-----";
};

#endif