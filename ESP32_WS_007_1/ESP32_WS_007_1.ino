/////////////////////////////////////////ID/////////////////////////////////////////
#define NODE 1
#define VERSION 1.01
#define NOEUX 0

//////////////////////////////////////TaskHandle_t //////////////////////////////////
//TaskHandle_t Map1;
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

/////////////////////////////////////////Adresse/////////////////////////////////////
#define adr (((1+(NODE-1))*15)-14)
#define NUM_LEDS_PER_STRIP 150
int N_L_P_S = NUM_LEDS_PER_STRIP;

/////////////////////////////////////////Debug///////////////////////////////////////
#define DEBUG 1
#define DEBUG_dmx 1
#define DEBUG_STR 1

/////////////////////////////////////////lib/////////////////////////////////////////
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ArtnetWifi.h>//https://github.com/rstephan/ArtnetWifi
unsigned long lastRefresh = 0;
#define REFRESH 10

#if defined(ARDUINO) && ARDUINO >= 100
// No extras
#elif defined(ARDUINO) // pre-1.0
// No extras
#elif defined(ESP_PLATFORM)
#include "arduinoish.hpp"
#endif

#define HBSIZE 32
char nodeName[HBSIZE];
byte myID;

///////////////////////////////Lib esp32_digital_led_lib//////////////////////////////
#include "esp32_digital_led_lib.h"
#define min(m,n) ((m)<(n)?(m):(n))
#define NUM_STRIPS 4
int PINS[NUM_STRIPS] = {23, 22, 18, 5};
const int numberOfChannels = NUM_STRIPS * NUM_LEDS_PER_STRIP * 3;
const int numberOfLed = NUM_STRIPS * NUM_LEDS_PER_STRIP ;
strand_t STRANDS[NUM_STRIPS];
strand_t * strands [] = { &STRANDS[0], &STRANDS[1], &STRANDS[2], &STRANDS[3]};
bool randArray[numberOfLed];

///////////////////////////////////dmx variables////////////////////////////////////
float pi_n_0_r[NUM_LEDS_PER_STRIP];
float pi_n_0_g[NUM_LEDS_PER_STRIP];
float pi_n_0_b[NUM_LEDS_PER_STRIP];
float pi_n_1_r[NUM_LEDS_PER_STRIP];
float pi_n_1_g[NUM_LEDS_PER_STRIP];
float pi_n_1_b[NUM_LEDS_PER_STRIP];
float pi_n_2_r[NUM_LEDS_PER_STRIP];
float pi_n_2_g[NUM_LEDS_PER_STRIP];
float pi_n_2_b[NUM_LEDS_PER_STRIP];
float pi_n_3_r[NUM_LEDS_PER_STRIP];
float pi_n_3_g[NUM_LEDS_PER_STRIP];
float pi_n_3_b[NUM_LEDS_PER_STRIP];

float pi_0_r[NUM_LEDS_PER_STRIP];
float pi_0_g[NUM_LEDS_PER_STRIP];
float pi_0_b[NUM_LEDS_PER_STRIP];
float pi_1_r[NUM_LEDS_PER_STRIP];
float pi_1_g[NUM_LEDS_PER_STRIP];
float pi_1_b[NUM_LEDS_PER_STRIP];
float pi_2_r[NUM_LEDS_PER_STRIP];
float pi_2_g[NUM_LEDS_PER_STRIP];
float pi_2_b[NUM_LEDS_PER_STRIP];
float pi_3_r[NUM_LEDS_PER_STRIP];
float pi_3_g[NUM_LEDS_PER_STRIP];
float pi_3_b[NUM_LEDS_PER_STRIP];

float pi_0_sr[NUM_LEDS_PER_STRIP];
float pi_0_sg[NUM_LEDS_PER_STRIP];
float pi_0_sb[NUM_LEDS_PER_STRIP];
float pi_1_sr[NUM_LEDS_PER_STRIP];
float pi_1_sg[NUM_LEDS_PER_STRIP];
float pi_1_sb[NUM_LEDS_PER_STRIP];
float pi_2_sr[NUM_LEDS_PER_STRIP];
float pi_2_sg[NUM_LEDS_PER_STRIP];
float pi_2_sb[NUM_LEDS_PER_STRIP];
float pi_3_sr[NUM_LEDS_PER_STRIP];
float pi_3_sg[NUM_LEDS_PER_STRIP];
float pi_3_sb[NUM_LEDS_PER_STRIP];

int _Color_mode;
int _Mirror;

unsigned long now;
int effet_etat = 0;
int last_time_effet = 0;
int type_effet = 0;
int _Modulo = 0;
unsigned int _Strobe_ws = 0;
unsigned int l_str;
int type__Modulo = 0;
int str = 0;
int str_l = 0;
int _Pix_pos;
int _Pix_pos_v;
int _Pix_start;
int _Pix_center;
int _Pix_end;
int _Master;
float rrr;
float ggg;
float bbb;
float rr;
float gg;
float bb;
float r;
float g;
float b;
float srr;
float sgg;
float sbb;
int mod;
int _Pix_mod;
unsigned long t_now_effet = 0;
uint8_t strob_count = 0;
uint8_t strob_count_l = 0;
unsigned long _Strobe_ws_last = 0;
unsigned long t_last_l = 0;
#define STROB_FRACTION 5
#define STROB_ON 1
#define STROB_ON_MS 15
#define STROB_FRACTION_L 5
#define STROB_ON_L 1
#define STROB_ON_MS_L 15
int l_s_count = 1;
int _Pix_start_v;
int ref__Pix_pos;
float pix_coef;
float pix_coefi;
float pix_coef_fond;
float pix_coefi_fond;
int M_g;
int M_g_ref;
int M_g1;
int M_g1_ref;
int M_g2;
int M_g2_ref;
int M_g3;
int M_g3_ref;
int M_g4;
int S_seuil;
int old_S_seuil = 0;
int S_count;
int a;
float str_blind_ws = 1;
float str_blind_l = 1;

///////////////////////////////////// Artnet settings /////////////////////////////////////
ArtnetWifi artnet;
//const int startUniverse = 0; // CHANGE FOR YOUR SETUP most software this is 1, some software send out artnet first universe as 0.
const int startUniverse = NOEUX; // CHANGE FOR NOEUX.

// Check if we got all universes
const int maxUniverses = numberOfChannels / 512 + ((numberOfChannels % 512) ? 1 : 0);
bool universesReceived[maxUniverses];
bool sendFrame = 1;
int previousDataLength = 0;

///////////////////////////////////////////////// SETUP ////////////////////////////////////////
void setup() {
#ifdef DEBUG
  Serial.begin(115200);
#endif
  ///////////////////////////////////////////////// NODE ID //////////////////////////////////////
#ifdef NODE_NUMBER
  eeprom_setID((byte)NODE);
#endif

  // NAME
  myID = eeprom_getID();
  String myName("ESP32");
  sprintf(nodeName, "ESP32 %02i %i", myID, VERSION);
#ifdef DEBUG
  Serial.print("Starting ");
  Serial.println(nodeName);
#endif

  leds_init();
  ConnectWifi();
  // OTA
  ota_setup();
  artnet.begin();
  artnet.setArtDmxCallback(onDmxFrame);
  initTest();

  //create a task that will be executed in the Map1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(Map1code, "Map1code", 4096, NULL, 1, NULL, 1);   // core 1 = loop
  xTaskCreatePinnedToCore(effTask, "effTask", 4096, NULL, 1, NULL, 0);    // core 0 = wifi
  //  xTaskCreatePinnedToCore(
  //    Map1code,   /* Task function. */
  //    "Map1",     /* name of task. */
  //    10000,       /* Stack size of task */
  //    NULL,        /* parameter of the task */
  //    1,           /* priority of the task */
  //    &Map1,      /* Task handle to keep track of created task */
  //    0);          /* pin task to core 0 */
  //  delay(500);

}//setup

///////////////////////////////////////// LOOP /////////////////////////////////////////////////
void loop() {
  if (wifi_isok()) artnet.read();
  eff__Modulo();
 // effet();
  if ((millis() - lastRefresh) > REFRESH) {
    if (!wifi_isok())  ledBlack();//passe led noir
    lastRefresh = millis();
  }
  // MILLIS overflow protection
  if (millis() < lastRefresh) {
    lastRefresh = millis();
  }
  // OTA
  ota_loop();
}//loop
