void sd_card_init(void) { //may need to be changed to bool
  //Serial.println("sd init");

  send_to_lcd("Initializing SD Card", 0, 0, true);

  while (!sd.begin(chipSelect, SD_SCK_MHZ(6))) {
          //Serial.println("Card Initializing Failed");
    }
  Serial.println("Card initialized OK");

  send_to_lcd("Card Init. PASSED", 0, 1, false);

  send_to_lcd("    Ready to Log    ", 0, 1, true);

}
