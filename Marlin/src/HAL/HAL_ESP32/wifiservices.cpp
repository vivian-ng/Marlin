/*
  wifiservices.cpp -  wifi services functions class

  Copyright (c) 2014 Luc Lebosse. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifdef ARDUINO_ARCH_ESP32

#include "../../inc/MarlinConfigPre.h"

#if ENABLED(WIFISUPPORT)

#include "HAL.h"
#include <WiFi.h>
#include <FS.h>
#include <SPIFFS.h>
#include <Preferences.h>
#include "wificonfig.h"
#include "wifiservices.h"
#ifdef ENABLE_MDNS
#include <ESPmDNS.h>
#endif
#ifdef ENABLE_OTA
#include <ArduinoOTA.h>
#endif
#ifdef ENABLE_HTTP
#include "web_server.h"
#endif

WiFiServices wifi_services;

WiFiServices::WiFiServices(){
}
WiFiServices::~WiFiServices(){
    end();
}

bool WiFiServices::begin(){
    bool no_error = true;
    //Sanity check
    if(WiFi.getMode() == WIFI_OFF) return false;
    String h;
    Preferences prefs;
    //Get hostname
    String defV = DEFAULT_HOSTNAME;
    prefs.begin(NAMESPACE, true);
    h = prefs.getString(HOSTNAME_ENTRY, defV);
    prefs.end();
    WiFi.scanNetworks (true);
    //Start SPIFFS
    SPIFFS.begin(true);

#ifdef ENABLE_OTA
    ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else {// U_SPIFFS
        // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
        type = "filesystem";
        SPIFFS.end();
        }
      MYSERIAL0.printf("OTA:Start OTA updating %s]\r\n", type.c_str());
    })
    .onEnd([]() {
      MYSERIAL0.println("OTA:End");
      
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      MYSERIAL0.printf("OTA:OTA Progress: %u%%]\r\n", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      MYSERIAL0.printf("OTA: Error(%u)\r\n", error);
      if (error == OTA_AUTH_ERROR) MYSERIAL0.println("OTA:Auth Failed]");
      else if (error == OTA_BEGIN_ERROR) MYSERIAL0.println("OTA:Begin Failed");
      else if (error == OTA_CONNECT_ERROR) MYSERIAL0.println("OTA:Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) MYSERIAL0.println("OTA:Receive Failed");
      else if (error == OTA_END_ERROR) MYSERIAL0.println("OTA:End Failed]");
    });
  ArduinoOTA.begin();
#endif
#ifdef ENABLE_MDNS
     //no need in AP mode
     if(WiFi.getMode() == WIFI_STA){
        //start mDns
        if (!MDNS.begin(h.c_str())) {
            MYSERIAL0.println("Cannot start mDNS");
            no_error = false;
        } else {
            MYSERIAL0.printf("Start mDNS with hostname:%s\r\n",h.c_str());
        }
    }
#endif
#ifdef ENABLE_HTTP
    web_server.begin();
#endif
    return no_error;
}
void WiFiServices::end(){
#ifdef ENABLE_HTTP
    web_server.end();
#endif
    //stop OTA
#ifdef ENABLE_OTA
    ArduinoOTA.end();
#endif
    //Stop SPIFFS
    SPIFFS.end();
    
#ifdef ENABLE_MDNS
    //Stop mDNS
    //MDNS.end();
#endif 
}

void WiFiServices::handle(){
#ifdef ENABLE_OTA
    ArduinoOTA.handle();
#endif
#ifdef ENABLE_HTTP
    web_server.handle();
#endif
}

#endif // ENABLE_WIFI

#endif // ARDUINO_ARCH_ESP32
