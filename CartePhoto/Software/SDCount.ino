#include <SPI.h>
#include <SD.h>

File root;

int fileCountOnSD = 0; // for counting files


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  root = SD.open("/");

  printDirectory(root, 0);

  // Now print the total files count
  Serial.println(F("fileCountOnSD: "));
  Serial.println(fileCountOnSD);

  Serial.println("done!");
} // end setup



void loop() {
  // nothing happens after setup finishes.
}



void printDirectory(File dir, int numTabs) {
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
