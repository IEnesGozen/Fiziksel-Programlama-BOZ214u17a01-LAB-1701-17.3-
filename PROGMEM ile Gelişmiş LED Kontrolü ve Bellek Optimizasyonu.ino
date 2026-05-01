#include <avr/pgmspace.h> // PROGMEM kullanimi icin gerekli kütüphane

// 256 öğelik parlaklık tablosu RAM yerine Flash belleğe (PROGMEM) kaydediliyor
const byte table[] PROGMEM = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  // ... (256 öğelik tablonun tamamı burada olmalıdır) ...
  250
};

const int rawLedPin = 3;      // Ham (doğrusal) değerle beslenen LED
const int adjustedLedPin = 5; // PROGMEM Tablosundan beslenen (yumuşatılmış) LED

int brightness = 0;
int increment = 1;

void setup() {
  // analogWrite ile sürülen PWM pinleri için pinMode tanımlamasına gerek yoktur.
}

void loop() {
  // Parlaklık yönünü belirle (Artacak mı, azalacak mı?)
  if (brightness > 254) increment = -1;
  else if (brightness < 1) increment = 1;

  brightness = brightness + increment;

  // 1. LED (Pin 3): Doğrusal (ham) artış
  analogWrite(rawLedPin, brightness);

  // 2. LED (Pin 5): Flash bellekten okunan "yumuşatılmış" pürüzsüz değer
  int adjustedBrightness = pgm_read_byte(&table[brightness]); 
  analogWrite(adjustedLedPin, adjustedBrightness);

  delay(10); // Değişimi gözle görebilmek için çok kısa bir bekleme
}
