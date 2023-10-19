#define _LCD_TYPE 2 // 1 означает подключение по шине I2C, а 2 - по десятиконтактной схеме.
#include <LCD_1602_RUS_ALL.h>
#include <string.h>


enum class LCDPins {RS = 7, EN, D4, D5, D6, D7}; // Нумерация продолжится сама.
LCD_1602_RUS <LiquidCrystal> lcd((int)LCDPins::RS, (int)LCDPins::EN, (int)LCDPins::D4, (int)LCDPins::D5, (int)LCDPins::D6, (int)LCDPins::D7);


void setup()
{
  const int COLUMNS = 16, ROWS = 2;
  lcd.begin(COLUMNS, ROWS);
  lcd.print("Влажность почвы:");
}


inline void show_seconds_in_lcd()
{
  int seconds = millis() / 1000;
  String seconds_in_string = String(seconds);
  int last_number_of_seconds = seconds % 10;

  if (last_number_of_seconds == 0 || last_number_of_seconds >= 5)
    lcd.print(seconds_in_string + " секунд. ");
  
  else if (last_number_of_seconds >= 2 and last_number_of_seconds <= 4)
    lcd.print(seconds_in_string + " секунды.");
  
  else if (last_number_of_seconds == 1)
    lcd.print(seconds_in_string + " секунда.");
}


inline int normalize_moisture(const int &moisture)
{
  int normalized_moisture = map(moisture, 520, 410, 0, 100);

  if (normalized_moisture < 0) return 0;
  else return normalized_moisture;
}


void loop()
{
  lcd.setCursor(0, 1);

  int moisture = normalize_moisture(analogRead(A5));
  String moisture_in_string = String(moisture) + "%  ";

  lcd.print(moisture_in_string);

  delay(1000);
}
