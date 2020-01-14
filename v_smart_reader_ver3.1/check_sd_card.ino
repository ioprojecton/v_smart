bool check_sd_card(void){

  if (!sd.begin(chipSelect, SD_SCK_MHZ(6))) {
    digitalWrite(RLED,HIGH);
    send_to_lcd("SD CARD FAILED....",0,1,false);
    return false;
  }
  digitalWrite(RLED,LOW);
  return true;
}
