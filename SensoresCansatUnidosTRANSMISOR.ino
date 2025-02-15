// RadioHead ASK EMISOR------------ emisor modulo pequeño, receptor modulo grande
// SPI, CONEXIONES-> 12-DATA, VCC-5V, GND-GND
//#include <RH_ASK.h>
#include <SPI.h> 
#include <VirtualWire.h>
// FIN DOCUMENTACION ASK EMISOR------------
#include "GPS.h" //libreria_gps
GPSS gpss; //clase_publica, apodo;


#include "BMP280.h" //libreria_bmp280
BMP280 sp; //clase_publica, apodo;

#define TIEMPO_TAREA_1 1000 //variabletiempo, tiempoParaEjecutar
uint64_t tiempoActual = 0, //tiempoactual
     tiempoTranscurrido_tarea1 = 0; //tiempotranscurrido

void tarea1 ( void ){
  
  if ( tiempoActual - tiempoTranscurrido_tarea1 >= TIEMPO_TAREA_1 ) { ///resta del tiempo actual-transcurrido, condicionTiempo
    tiempoTranscurrido_tarea1 = tiempoActual; //reinciamos la variable para que vuelta a iniciar el conteo.
    sp.lec();    //ejecuta de la libreria BMP280
  }//IF 
  }//TAREA1



void setup(void) {

 Serial.begin (115200); //Iniciando baudrate
   // Se inicializa el MODULO DE RF
    vw_setup(2000); // velocidad: Bits per segundo
    vw_set_tx_pin(12); //Pin 2 como salida para el RF 
   //GPS
   serialgps.begin(9600); //Iniciamos el puerto serie del gps
   //Imprimimos en el monitor serial:
   Serial.println("GPS GY-GPS6MV2 Leantec");
   Serial.println(" ---Buscando senal--- ");  
   Serial.println("");                   //Configuración BaudRate a 9600 bits por segundo 
  //BME280
  Serial.println(F("BME280 test"));
  bool status;
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
   status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }//if status
 Serial.println ( F ( "Ha iniciado el sistema" ) );  //termina de iniciar todos los sistemas
 
}//setup fin

void loop(void) {
  //DECLARACION DATOS BMP280
  float temperatura;
  float presion;
  float altitud;
  float humedad;
  //DECLARACION DATOS GPS
  float latitud;
  float longitud;
  float altitudGPS;
  float latitude, longitude;
  gps.f_get_position(&latitude, &longitude);
  
  tiempoActual = millis ( );  //funcion para saber cuanto tiempo transcurrido paso en el lop 
  gpss.lec();//se ejecuta cada 100 milisegundos.
   tarea1();
  // ACOMODO DATOS BMP280
  temperatura=bme.readTemperature();//dato TEMPERATURA
  Serial.println(temperatura);
  presion=bme.readPressure()/ 100.0F; //dato PRESION ATMOSFERICA
  altitud=bme.readAltitude(SEALEVELPRESSURE_HPA);//dato ALTITUD
  humedad=bme.readHumidity();//dato HUMEDAD
  
  // ACOMODO DATOS GPS
  latitud=latitude;
  longitud=longitude;
  altitudGPS=gps.f_altitude();
  
  delay(100);
  
  
    char buf[VW_MAX_MESSAGE_LEN]; // Cadena para enviar
    String str=""; 
    
   //ENVIO DATO DE LATITUD
    str="l"+String (latitud,5); //convertimos el entero a String y agremos un inicio de trama
    Serial.println(str); 
    str.toCharArray(buf,sizeof(buf)); //convertimos el String en un array
    vw_send((uint8_t *)buf, strlen(buf)); //Enviamos el array
    vw_wait_tx(); //Esperamos hasta que el mensaje se envie

   //ENVIO DATO DE LONGITUD
    str="o"+String(longitud,5); //convertimos el entero a String y agramos un inicio de trama
    Serial.println(str);
    str.toCharArray(buf,sizeof(buf)); //convertimos el String en un array
    vw_send((uint8_t *)buf, strlen(buf)); //Enviamos el array
    vw_wait_tx(); //Esperamos hasta que el mensaje se envie

    //ENVIO DATO DE presion
    str="p"+String(presion); //convertimos el entero a String y agramos un inicio de trama
    Serial.println("presion"+ str);
    str.toCharArray(buf,sizeof(buf)); //convertimos el String en un array
    vw_send((uint8_t *)buf, strlen(buf)); //Enviamos el array
    vw_wait_tx(); //Esperamos hasta que el mensaje se envie
 
    //ENVIO DATO DE altitudGPS
    str="A"+String(altitudGPS,5); //convertimos el entero a String y agramos un inicio de trama
    str.toCharArray(buf,sizeof(buf)); //convertimos el String en un array
    vw_send((uint8_t *)buf, strlen(buf)); //Enviamos el array
    vw_wait_tx(); //Esperamos hasta que el mensaje se envie

    //ENVIO DATO DE temperatura
    str="T"+String(temperatura); //convertimos el entero a String y agramos un inicio de trama
    str.toCharArray(buf,sizeof(buf)); //convertimos el String en un array
    vw_send((uint8_t *)buf, strlen(buf)); //Enviamos el array
    vw_wait_tx(); //Esperamos hasta que el mensaje se envie

    
    
    //ENVIO DATO DE altitud
    str="B"+String(altitud,5); //convertimos el entero a String y agramos un inicio de trama
    str.toCharArray(buf,sizeof(buf)); //convertimos el String en un array
    vw_send((uint8_t *)buf, strlen(buf)); //Enviamos el array
    vw_wait_tx(); //Esperamos hasta que el mensaje se envie

    //ENVIO DATO DE humedad
    str="H"+String(humedad); //convertimos el entero a String y agramos un inicio de trama
    str.toCharArray(buf,sizeof(buf)); //convertimos el String en un array
    vw_send((uint8_t *)buf, strlen(buf)); //Enviamos el array
    vw_wait_tx(); //Esperamos hasta que el mensaje se envie

}//lop fin
