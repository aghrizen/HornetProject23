/*
  Projet Electronique 
  PREVOTEAU, GRONDIN, JORAND, SICOT, MARTINO
  Code permettant
  -initialisation de la caméra 
  -Initialisation du module SD
  -Prise d'une photo et enregistrement sur carte SD 
*/

//Lib Esp32
#include "SD.h"
#include "SPI.h"
#include "esp_camera.h"
#include "FS.h"                // SD Card ESP32
#include "SD_MMC.h"            // SD Card ESP32
#include "soc/soc.h"           // Disable brownour problems
#include "soc/rtc_cntl_reg.h"  // Disable brownour problems
#include "driver/rtc_io.h"

#define EEPROM_SIZE 1


//Pins module Carte SD 
#define MOSI 14
#define MISO 32
#define CLK 13
#define SS 33


#define PWDN_GPIO_NUM    -1
#define RESET_GPIO_NUM   -1
#define XCLK_GPIO_NUM    21
#define SIOD_GPIO_NUM    26
#define SIOC_GPIO_NUM    27

#define Y9_GPIO_NUM      35
#define Y8_GPIO_NUM      34
#define Y7_GPIO_NUM      39
#define Y6_GPIO_NUM      36
#define Y5_GPIO_NUM      19
#define Y4_GPIO_NUM      18
#define Y3_GPIO_NUM       5
#define Y2_GPIO_NUM       4
#define VSYNC_GPIO_NUM   25
#define HREF_GPIO_NUM    23
#define PCLK_GPIO_NUM    22

camera_config_t config;



File root;
int fileCountOnSD = 0; // for counting files


#define CAMERA_MODEL_WROVER_KIT



void setup() {
  
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  
  // Initialising the UI will init the display too.
  

  //delay(200);

  Serial.println("//------------Initialisation-------------//");

  config_init();

  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA; // FRAMESIZE_ + QVGA|CIF|VGA|SVGA|XGA|SXGA|UXGA
    config.jpeg_quality = 5;
    config.fb_count = 2;
  } 
  else {
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 5;
    config.fb_count = 1;
  }

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  s->set_vflip(s, 1);        //1-Upside down, 0-No operation
  s->set_hmirror(s, 0);      //1-Reverse left and right, 0-No operation
  s->set_brightness(s, 1);   //up the blightness just a bit
  s->set_saturation(s, -1);  //lower the saturation


  //permet de définir les pins de la carte pour comm SPI 
  SPI.begin(CLK, MISO, MOSI, SS);

  //on vérifie si module SD présent
  if(!SD.begin(SS)){
    Serial.println("Card Mount Failed");
    //return;
  }
  else{
    Serial.println("Card Mount Ok");
  }
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
    Serial.println("No SD card attached");
    //return;
  }

  root = SD.open("/");
  countingFiles(root, 0);

  // Now print the total files count
  Serial.println(F("fileCountOnSD: "));
  Serial.println(fileCountOnSD);

  for(int i=1;i<=fileCountOnSD;i++){
    String stringToDelete = "picture"+String(i)+".jpg";
    if(SD.exists(stringToDelete.c_str())){
      SD.remove(stringToDelete.c_str());
    }
    else{
      Serial.println("no file to remove");
    }
  }

  countingFiles(root, 0);
  Serial.println("after remove : ");
  Serial.println(fileCountOnSD);
  

  Serial.println("done!");


  Serial.println("//------------Fin Initialisation-------------//");

}


void loop() {

  //partie caméra
  camera_fb_t * fb = NULL;

  fb = esp_camera_fb_get();  
  if(!fb) {
    Serial.println("Camera capture failed");
    return;
  }
  else{
    Serial.println("Camera capture ok");
    fileCountOnSD++;
    String path = "/picture" + String(fileCountOnSD) +".jpg";
    File file = SD.open(path.c_str(), FILE_WRITE);
    if(!file){
      Serial.println("Failed to open file in writing mode");
    } 
    else {
    file.write(fb->buf, fb->len); // payload (image), payload length
    Serial.printf("Saved file to path: %s\n", path.c_str());
    }
    file.close();
  }

  esp_camera_fb_return(fb);
  //tempo d'1s
  delay(1000);
}


//Fonction d'initialisation de la caméra 
void config_init() {
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.fb_count = 1;
}

void countingFiles(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    // for each file count it
    fileCountOnSD++;
  }
}
