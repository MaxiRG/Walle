


![Austral Ingenieria](https://encrypted-tbn0.gstatic.com/images?q=tbn%3AANd9GcQooGo7vQn4t9-6Bt46qZF-UY4_QFpYOeh7kVWzwpr_lbLr5wka)

<!--
    Ésta es la forma de poner comentarios en MarkDown
-->

# Sobre WiFi en ESP32 y la simplificación para el curso de Introducción a la computación

## Objetivo

>    Si bien hay mucha información sobre el uso de WiFi para el ESP32 bajo Arduino o PlatformIO, teniendo en cuenta el poco tiempo disponible en el curso, se ha tomado la resolución de usar un método muy directo, simple y uniforme para todos los ejercicios y proyectos para el uso de WiFi; esto no obsta para que, si hay un proyecto que sea específicamente sobre detalles o formas de uso de WiFi, no se traten especialmente

>    Teniendo en cuenta que lo mejor sería ocultar el acceso a Wifi, ya que es requerido en muchos proyectos por ser una de las características más atractivas del ESP32, la mejor forma debería haber sido construir una biblioteca bajo Arduino y/o PlatformIO; sin embargo, ello hubiese sido una disgresión en el curso para aprender como se realiza una biblioteca, por lo cual, y teniendo en cuenta el poco tiempo disponible, se trató de no hacerlo de dicha manera.

>    Obviamente, la forma que se implementó es quizás la mas directa pero la menos profesional, ya que como se verá, esta forma implica copiar código que se repite en cada uno de los proyectos que se encare con Wifi

## Implementacion

  >  La implementación se realizó mediante un archivo de código en C que se denomina _wifi_ruts.cpp_ y un archivo de encabezamiento denominado _wifi_ruts.h_, donde se encuentra el prototipo de la única función que implementa el archivo _cpp_, a saber _wifi_connect_.

>    Estos archivos se compilan junto con el fuente del proyecto, por lo cual _en cada proyecto que se realice con WiFi_ deben incluirse en el directorio _src_

>    Un cuidado adicional que se debe tener es que antes de llamar a la única función _wifi_connect_, se debería haber inicializado el objeto _Serial_ ya que la función usa la consola para informar de la secuencia de conexión a WiFi

## Datos del punto de acceso a WiFi

>    Otro tema, es que debe conocerse tanto el nombre (MY_SSID) como la clave (MY_PASS) del punto de acceso a Wifi; obviamente, el mejor lugar para ponerla debería haber sido _plaformio.ini_ que es donde se pone generalmente la configuarción de todo proyecto que se aborde; sin embargo, por tratarse de textos libres ambos, pueden contener caracteres especiales que incluso traigan problema cuando se colocan en _platformio.ini_ (especialmente cuando en ese texto existen espacios que, en algunos casos, pueden tomarse como terminadores de _strings_).

>    Es por ello, que se decidió crear un archivo adicional que se denomina _wifi_data.h_, que es de tipo _include_ de _C_, con lo cual la sintaxis de los _strings_ es bien clara y conocida; teniendo en cuenta el ambiente que se trabaja en la Universidad, se previó que los datos de WiFi podian ser los que se encuentran en la Universidad y en la casa o trabajo de cada uno, con lo cual se previeron solo dos lugares con dicha informacion

>    Si se observa dentro del archivo, se verá que hay una sentencia de compilación condicional _#if_ para elegir si se compila para la Universidad, con lo cual deberia decir _#if 1_ o para la casa o trabajo, con lo cual debería decir _#if 0_.

>    *MUY IMPORTANTE:* recordar que el ESP32 es un microcomputador de reducidas proporciones y costo, con lo cual no soporta conexiones de WiFi de 5.8 GHZ y solamente de 2.4 GHZ. Téngalo muy especialmente en cuenta, porque es uno de los errores más comunes por los cuales no se puede conectar al punto de acceso