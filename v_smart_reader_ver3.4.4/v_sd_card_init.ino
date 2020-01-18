void sd_card_init(void) { //may need to be changed to bool
  //Serial.println("sd init");

  send_to_lcd("Initializing SD Card", 0, 0, true);
  digitalWrite(RLED, HIGH);

  while (!sd.begin(chipSelect, SD_SCK_MHZ(6))) {
    send_to_lcd("Waiting...", 0, 1, false);
  }
  digitalWrite(RLED, LOW);
  Serial.println("Card initialized OK");

  send_to_lcd("Card Init. PASSED", 0, 1, false);

  send_to_lcd("    Ready to Log    ", 0, 1, true);

}
