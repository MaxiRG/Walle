/*
 *  wifi_ruts.cpp
 *      Routines for WiFi management
 */

#include <Arduino.h>

#include <WiFi.h>

#include "wifi_ruts.h"
#include "wifi_data.h"

void
wifi_connect(void)
{
    WiFi.begin(MY_SSID, MY_PASS);

    while( WiFi.status() != WL_CONNECTED )
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println();
    Serial.println("______________");
    Serial.print( "Baud Rate = " );
    Serial.println( SERIAL_BAUD );
    Serial.print( "Conectado a ");
    Serial.println( MY_SSID );
    Serial.print( "MAC = ");
    Serial.println( WiFi.macAddress() );
    Serial.print( "local IP = " );
    Serial.println( WiFi.localIP() );
    Serial.println("______________");
}
