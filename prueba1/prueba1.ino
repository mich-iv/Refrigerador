#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>

#include <OneWire.h>

#include <DallasTemperature.h>

//#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
//#include <Adafruit_SPITFT.h>
//#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

#include <Adafruit_SSD1306.h>
#include <splash.h>

GFXcanvas1 canvas(29, 29);

// 'fan-propellers', 29x29px
static const uint8_t ventiladorImagen [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc0, 0x00, 
  0x00, 0x7f, 0xf0, 0x00, 0x00, 0x87, 0xfc, 0x00, 0x03, 0x07, 0xe6, 0x00, 0x07, 0x03, 0xc3, 0x00, 
  0x07, 0x83, 0x81, 0x00, 0x0f, 0x83, 0x81, 0x80, 0x0f, 0xc3, 0x03, 0x80, 0x1f, 0xe0, 0x03, 0xc0, 
  0x1f, 0xe0, 0x0f, 0xc0, 0x18, 0x12, 0x3f, 0xc0, 0x10, 0x03, 0x3f, 0xc0, 0x10, 0x02, 0x07, 0xc0, 
  0x10, 0x00, 0x00, 0xc0, 0x00, 0x70, 0x80, 0x40, 0x0b, 0xf0, 0xc0, 0x80, 0x0f, 0xe0, 0xe0, 0x80, 
  0x07, 0xe0, 0xf1, 0x00, 0x07, 0xe0, 0xff, 0x00, 0x03, 0xc0, 0xfe, 0x00, 0x01, 0xe0, 0xfc, 0x00, 
  0x00, 0x61, 0xf0, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00
};

OneWire ourWire(7);
DallasTemperature sensor(&ourWire);

#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);
#if (SSD1306_LCDHEIGHT != 32)
#error("Altura incorrecta, cambie en la librería de Adafruit_SSD1306.h!");
#endif


void setup() {
  // put your setup code here, to run once:
delay(1000);
Serial.begin(9600);
sensor.begin();

display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  // put your main code here, to run repeatedly:
sensor.requestTemperatures();
float temporal = sensor.getTempCByIndex(0);

Serial.print("Temperatura= ");
Serial.print(temporal);
Serial.println(" C");
delay(100);

leer_oled(temporal);
}

void leer_oled(float temperatura) {
display.clearDisplay(); //Borra el buffer
display.drawBitmap(97, 2, ventiladorImagen, 29, 29, WHITE);

display.setTextSize(2); //Establece el tamaño de fuente, admite tamaños de 1 a 8
display.setTextColor(WHITE); //Establece el color
display.drawRect(0, 0, 128, 32, WHITE);
//display.setCursor(5,8); //Establecer las coordenadas para mostrar la posición del texto
display.setCursor(5, 5);
display.print(temperatura);
display.print(" ");
display.setTextSize(1);
//display.setCursor(64, 8);
display.setCursor(64, 5);
display.print((char)247);
display.print("C");

display.setCursor(77, 21);
display.print("V.1");

//para usarlo en la condición de la placa.
//display.setCursor(5, 23);
display.setCursor(3, 22);
display.print("Encendido");
//display.print("  Apagado");



display.display(); //Muestra el texto
}
