#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

// Donnees WIFI a renseigner
const char* ssid = "_MON_SSID_";                   // SSID du réseau Wifi
const char* password = "_MOT_DE_PASSE_WIFI_";      // Mot de passe du réseau Wifi.


void setup() {
  Serial.begin(115200);                           // On initialise la vitesse de transmission de la console.
  setup_wifi();                                   // Connexion au Wifi
  initOTA();                                      // Initialisation de l'OTA
 
}

void loop() {
  ArduinoOTA.handle();                            // On verifie si une mise a jour OTA nous est envoyée. Si OUI, la lib ArduinoOTA se charge de faire la MAJ.
  
}



// CONNEXION WIFI
// **************
void setup_wifi() {
  // Connexion au réseau Wifi
  delay(10);
  Serial.println();
  Serial.print("Connection au réseau : ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);            // Passage de la puce en mode client
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    // Tant que l'on est pas connecté, on boucle.
    delay(500);
    Serial.print(".");
  }
  // Initialise la séquence Random
  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connecté");
  Serial.print("Addresse IP : ");
  Serial.println(WiFi.localIP());
}


// INITIALISATION Arduino OTA
// **************************
void initOTA() {
  /* Port par defaut = 8266 */
  // ArduinoOTA.setPort(8266);

  /* Hostname, par defaut = esp8266-[ChipID] */
  ArduinoOTA.setHostname("maStationMeteo");

  /* Pas d'authentication par defaut */
  // ArduinoOTA.setPassword("admin");

  /* Le mot de passe peut également être défini avec sa valeur md5 */
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");
  
  // code à exécuter au démarrage de la mise à jour
  ArduinoOTA.onStart([]() {
    Serial.println("\nDébut de update");
  });
  
  // code à exécuter à la fin de la mise à jour
  ArduinoOTA.onEnd([]() {
    Serial.println("\nFin");
  });
  
  // code à exécuter pendant la mise à jour
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progression : %u%%\r", (progress / (total / 100)));
  });
  
  // code à exécuter en cas d'erreur de la mise à jour
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Erreur[%u] : ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Authentification Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Exécution Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connexion Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Réception Failed");
    else if (error == OTA_END_ERROR) Serial.println("Fin Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Prêt");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
}
