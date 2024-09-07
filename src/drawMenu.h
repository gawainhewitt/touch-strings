#include <bus1_U8g2lib.h>  // my bus1 adaptation of https://github.com/olikraus/u8g2/blob/master/cppsrc/U8g2lib.h - manages I2C display

U8G2_SSD1306_128X64_NONAME_2_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);   //page buffer = 128bytes (_1_ = 128, _2_ = 256, _F_ = 1024)


boolean bigMenu = false;
boolean updateDisplayFlag = true;

int activeMenuInput = 0;
byte menuItems = 3;

void draw() {
  if (bigMenu) {
    u8g2.setFont(u8g2_font_inr21_mr);
    u8g2.setCursor(1, 30);
    u8g2.print(keyName);
    u8g2.setCursor(1, 60);
    u8g2.print(scaleTypeName);
  } else {
    u8g2.setFont(u8g2_font_6x13_tr);
    
    u8g2.setCursor(1, 10);
    u8g2.print("Key: "); 
    u8g2.print(keyName); 
    
    u8g2.setCursor(1, 20);
    u8g2.print("Type: "); 
    u8g2.print(scaleTypeName);

    u8g2.setCursor(1, 30);
    u8g2.print("Sound: "); 
    u8g2.print(currentSound);

    u8g2.setCursor(1, 40);
    

    u8g2.setCursor(1, 50);
    

    u8g2.setCursor(1, 60);
    int volumeToPrint = static_cast<int>(gain*100);
    u8g2.print("Volume: "); u8g2.print(volumeToPrint);
    
    u8g2.drawFrame(0, activeMenuInput * 10, 127, 10);
  }
}

void drawMenu() {
  u8g2.firstPage();
  do {
    draw();
  } while ( u8g2.nextPage() );
}