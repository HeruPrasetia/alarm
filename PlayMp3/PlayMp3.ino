#include <SoftwareSerial.h>
#include <DFMiniMp3.h>

class Mp3Notify {
public:
  static void PrintlnSourceAction(DfMp3_PlaySources source, const char* action) {
    if (source & DfMp3_PlaySources_Sd) {
        Serial.print("SD Card, ");
    }
    if (source & DfMp3_PlaySources_Usb) {
        Serial.print("USB Disk, ");
    }
    if (source & DfMp3_PlaySources_Flash) {
        Serial.print("Flash, ");
    }
    Serial.println(action);
  }
  static void OnError(uint16_t errorCode) {
    // see DfMp3_Error for code meaning
    Serial.println();
    Serial.print("Com Error ");
    Serial.println(errorCode);
  }
  static void OnPlayFinished(DfMp3_PlaySources source, uint16_t track) {
    Serial.print("Play finished for #");
    Serial.println(track);  
  }
  static void OnPlaySourceOnline(DfMp3_PlaySources source) {
    PrintlnSourceAction(source, "online");
  }
  static void OnPlaySourceInserted(DfMp3_PlaySources source) {
    PrintlnSourceAction(source, "inserted");
  }
  static void OnPlaySourceRemoved(DfMp3_PlaySources source) {
    PrintlnSourceAction(source, "removed");
  }
};

//DFMiniMp3<HardwareSerial, Mp3Notify> mp3(Serial1);

SoftwareSerial secondarySerial(0, 2); // RX, TX
DFMiniMp3<SoftwareSerial, Mp3Notify> mp3(secondarySerial);

void setup() {
  Serial.begin(115200);
  Serial.println("initializing...");
  mp3.begin();
  uint16_t volume = mp3.getVolume();
  Serial.print("volume ");
  Serial.println(volume);
  mp3.setVolume(24);
  uint16_t count = mp3.getTotalTrackCount(DfMp3_PlaySource_Sd);
  Serial.print("files ");
  Serial.println(count);  
  Serial.println("starting...");
}


void loop() {
  Serial.println("track 1"); 
  mp3.playMp3FolderTrack(1);  // sd:/mp3/0001.mp3
  delay(5000);
  
  Serial.println("track 2"); 
  mp3.playMp3FolderTrack(2); // sd:/mp3/0002.mp3 
  delay(5000);
 
  Serial.println("track 3");
  mp3.playMp3FolderTrack(3); // sd:/mp3/0002.mp3
  delay(5000); 
}
