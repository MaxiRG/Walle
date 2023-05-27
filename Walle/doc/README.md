

![Austral Ingenieria](https://encrypted-tbn0.gstatic.com/images?q=tbn%3AANd9GcQooGo7vQn4t9-6Bt46qZF-UY4_QFpYOeh7kVWzwpr_lbLr5wka)


# Proyecto 31-web-led

## Secciones

- [Objetivo](#objetivo)  
- [Hardware](#hardware)  
- [Programa](#programa)  
- [platformio.ini](#platformio.ini)  
- [Bibliotecas](#bibliotecas)  
- [Constantes](#constantes)  
- [WiFi](#wifi)  



## Objetivo

      Manejo de LED a traves de la pagina de Web.  
      En realidad, esta página de Web, residente en el mismo ESP32.  
      permite cambiar el estado del LED, por lo cual se trata de
      un caso de control sin estado (stateless)

## Hardware

       Conectar Anodo de LED a GPIO "LED"  
       Conectar Catodo de LED a un extremo de resistor de 220 ohm  
       Conectar el otro extremo del resistor de 220 ohm a GND  

## Programa

 El programa es una modificación respecto del proyecto 30-1st-web  
 No se necesita biblioteca adicional, solo las ya incluidas propias de Arduino  
 Solo se deben incluir _Wifi.h_ y _WebServer.h_ (13-14) y se debe crear un objeto de tipo WebServer denominado _server_ en el port 80 (18)  

 Se crean tres rutinas de respuesta a requerimientos, cuales son:  

 _handleRoot_ que presenta la página con el botón de _toggle LED_ (línea 21)  
 _handleLED_ que responde al URI /LED que hace cambiar el estado del LED (línea 33)    
 _handleNotFound_ que responde a un URI inexistente (línea 44)  

   Mención especial merece _handleLED_ ya que lo que hace en la línea 38 es justamente cambiar el estado del LED (de ahí la calidad _stateless_ del servidor)  

   Las restantes funciones son las tradicionales _setup_ y _loop_

   53: _setup_  
   55-57: inicializa el objeto _Serial_  
   59:    inicializa el GPIO "LED" como salida  
   61:    se conecta a Wifi  
   63-65: registra las funciones del servidor  
   67-68: arranca el servidor y finaliza  

   72: _loop_  
   74: se sienta a esperar clientes

## platformio.ini

 Aparte de la tradicional inicialización de _SERIAL_BAUD_, solo se define el GPIO "LED"  
 No hay acceso a bibliotecas externas  

## Bibliotecas

 Como se dijo en el título anterior, no hay acceso a bibliotecas externas.  
 Se usan bibliotecas ya existentes en Arduino para WiFi, por lo cual se incluye _WiFi.h_ (13) y _WebServer.h_ (14)  

## Constantes

 La únicas constantes existentes en el programa, es el acceso a _SERIAL_BAUD_ para la inicialización del objeto _Serial_ y la constante _LED_ para el acceso al GPIO donde se encuentra conectado el ánodo del led,  
 Para el acceso a las constantes necesarias para conectarse a WiFi, ver el ítem siguiente


## WiFi

> Para acceso a WiFi simplificado usado en este proyecto, ver archivo _esp32wifi.md_ en este mismo directorio.



