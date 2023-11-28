
 
#ifndef BMP280_h
#define BMP280_h
//NOTA 3.3V, NOMBRE DEL SENSOR BMP280, PROTOCOLO I2C, SDA-A4 y SCL-A5

#include <Wire.h>
#include <Adafruit_Sensor.h> 
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme; // I2C
unsigned long delayTime;

class BMP280{
  public:
  void lec( void );

};

void BMP280 :: lec( void ) {
  
  Serial.println("----BMP280----");
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");
  
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
}
#endif

 
