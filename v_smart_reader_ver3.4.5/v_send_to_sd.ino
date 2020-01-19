unsigned char send_to_sd(const char* _year,const char* _month,const char* _time,const char* data){
while (!check_sd_card());
  if (!sd.chdir()) Serial.println("access to root failed");
  if (!sd.exists(_year)) {
    if (!sd.mkdir(_year)) Serial.println("cant create directory");
  }//must be terminated

  sd.chdir("year");
  if (!sd.exists(_month)) {
    if (!sd.mkdir(_month)) Serial.println("cant make nested directory");//terminate
  }

  sd.chdir(_month);
  
if(have_cycle_number){
char tmp_cycle_number[11];
memset(tmp_cycle_number,'\0',sizeof(tmp_cycle_number));
itoa(cycle_number,tmp_cycle_number,10);
strcat(tmp_cycle_number,".txt.");
if(!file.exists(tmp_cycle_number)) {
if(!file.open("tmp.txt",O_WRONLY | O_CREAT | O_APPEND)) Serial.println("cant make file");//all wrong returns should 
//terminate the whole program with error code
if(!file.rename(tmp_cycle_number)) Serial.println("cant rename");
}
if(!file.open(tmp_cycle_number,O_WRONLY | O_CREAT | O_APPEND)) Serial.println("cant make file");//all wrong returns should 

}

else {
  if(!file.open("tmp.txt",O_WRONLY | O_CREAT | O_APPEND)) Serial.println("cant make file");//all wrong returns should 
//terminate the whole program with error code
  }

file.print(_time);
file.println(data);
file.print("\r\n\r\n");
file.close();


return 1;///return right value
}
