## Selección del Proyecto a Implementar

Para la selección del proyecto final de este curso, se inició con la identificación de diversas opciones que fueron evaluadas mediante un análisis detallado basado en criterios cuantitativos. Se desarrolló una tabla comparativa donde cada proyecto fue valorado según factores clave a los que se asignaron ponderaciones específicas: facilidad y tiempo de implementación (alto), disponibilidad y costo del hardware (medio) y utilidad o relevancia del proyecto (medio).

Cada factor recibió una puntuación del 1 al 10, siendo el valor 10 indicando la máxima favorabilidad. Las ponderaciones fueron calculadas considerando dos dimensiones principales: primero, la conveniencia y factibilidad del proyecto dentro del marco del curso, y segundo, el impacto y valor potencial del proyecto tras su finalización.

El análisis de la conveniencia se enfocó en la aplicabilidad del proyecto, tanto en contextos académicos como comerciales. En cuanto a la factibilidad, se tomó en cuenta el presupuesto disponible y el nivel de interés y compromiso de los participantes, elementos que son determinantes para asegurar el éxito del proyecto.

Las categorías utilizadas para la evaluación fueron:

- **Tiempo de Implementación:** Se evaluó la capacidad del proyecto para ser completado dentro del plazo estipulado, dado que el tiempo es un recurso limitado. La alta ponderación asignada refleja la importancia de este factor en la selección final.

- **Disponibilidad y Costo del Hardware:** Se consideró la facilidad para adquirir los componentes necesarios y el impacto del costo en la viabilidad del proyecto, especialmente en un contexto de presupuesto limitado.
  
- **Aporte de nuevos conocimientos:** Se consederó el aporte de nuevas habilidades que el desarrollador aprenderá durante la realización del proyecto, siendo esta categoria un sinonimo de motivacion.
  
- **Utilidad del Proyecto:** Se analizó el grado en que el proyecto podría ofrecer una solución efectiva y relevante a un problema existente, considerando su potencial valor académico o comercial.

Este enfoque permitió seleccionar el proyecto que mejor equilibraba los diferentes criterios, maximizando las posibilidades de éxito dentro de las limitaciones del curso.
### Tabla 1: Comparativa de Pesos de Proyectos para Selección Final

En la Tabla 1 se aprecia una comparativa de los pesos de tres proyectos propuestos. El proyecto con más peso final es el que resultará elegido como trabajo final.

| Proyecto                  | | | Tiempo de Implementación (10) | Aporte de nuevos Conocimientos (8) | Utilidad del Proyecto (7) | Disponibilidad y Costo del Hardware (5) | Peso Final |
|---------------------------|-------------------------------|-------------------------|---------------------------|------------------------------------------|------------|
| **Sistema de Control de Acceso**  | Puntaje        | 9                         | 8                         | 8                         | 7                                        |            |
|                           | Puntaje Ponderado            | 90                        | 64                        | 56                        | 35                                       | **245**    |
| **Sistema de Monitoreo de Temperatura y Humedad** | Puntaje        | 7                         | 9                         | 8                         | 8                                        |            |
|                           | Puntaje Ponderado            | 70                        | 72                        | 56                        | 40                                       | **238**    |
| **Alarma de Seguridad con Detección de Movimiento** | Puntaje        | 7                         | 8                         | 7                         | 9                                        |            |
|                           | Puntaje Ponderado            | 70                        | 64                        | 49                        | 45                                       | **228**    |
*Tabla 1: Puntajes ponderados de los proyectos para trabajo final*

En este caso el Sustema de control de Acceso es el cual lleva la delantera ya que es el mas viable en terminos de tiempo de implementacion para el mismo en el marco del curso. El sistema de monitoreo de Temperatura y Humedad requeriria un timepo algo mayor debido a que se deben estudiar los sensores qu este sistema implementaria, ademas de necesitar hardware adecuado. Respecto al sistema de alarma de seguridad con deteccion de movimiento, si bien en este caso el hardware esta disponible, se deberia al igual que en el caso anterior estudiar las necesidades de software para implementar lo que demandaria mas tiempo, del disponible.

### Sistema de Control de Acceso
Este proyecto tiene como objetivo desarrollar un sistema de control de acceso inteligente para puertas domiciliarias. El sistema permitirá a los usuarios ingresar un PIN para desbloquear la puerta de manera segura. Además, el sistema será configurable y ofrecerá varias funciones adicionales para mejorar la experiencia del usuario y la seguridad.

Los usuarios podrán configurar y personalizar el PIN a través de un teclado matricial, y el sistema verificará la combinación introducida en tiempo real. En caso de que el PIN sea correcto, se activará un relé que controlará un motor DC para abrir el picaporte de la puerta.

El sistema también contará con un LED indicador que mostrará si el acceso ha sido concedido o denegado, así como con un aviso sonoro para confirmar la autenticación exitosa. Además, un sensor de luz ambiental (LDR) detectará la presencia de oscuridad, lo que activará automáticamente una lámpara para iluminar las teclas, asegurando así su visibilidad en condiciones de baja luz.

Para mejorar la interacción con el usuario, un display LCD mostrará la hora actual, el estado de la lámpara (encendida o apagada), y el estado general del sistema, indicando si se encuentra activo o inactivo. La comunicación entre el sistema y el propietario de la puerta se realizará mediante una conexión UART a una PC, permitiendo el monitoreo y control del sistema desde un ordenador.

En el mercado existen controles de acceso que pueden presentar otras caracteristicas, en este caso se presentan 2 a modo comparativo.

| **Características Técnicas**          | **Control de Accesos SICCBA**                                      | **Control De Acceso Gadnic**                                         |
|---------------------------------------|----------------------------------------------------|--------------------------------------------------------|
| **Capacidad de Usuarios**             | 1.000                                              | 1.500                                                  |
| **Modo de Funcionamiento**            | Tarjeta, teclado, tarjeta + teclado                | Tarjeta, código o combinación de ambos                 |
| **Rango de Lectura**                  | 2 – 5 cm                                           | 1 – 5 cm                                               |
| **Tecnología de Lectura de Tarjeta**  | RFID Marin 125 Khz                                 | EM                                                     |
| **Voltaje de Funcionamiento**         | No especificado                                    | CC 12 V ± 10                                          |
| **Corriente de Trabajo**              | No especificado                                    | < 100 mA                                               |
| **Temperatura de Funcionamiento**     | -20º C – 60º C                                     | 0º C - 60º C                                           |
| **Conexión a Cerradura**              | Eléctrica, pestillo, pulsador de salida            | Electromagnéticas, eléctricas o cerrojos eléctricos   |
| **Indicadores**                       | Lumínicos y sonoros                                | LED y BUZZER          

*Tabla 2: Comparacion de productos comerciales*

Aunque los controles de acceso comerciales, como los que se muestran en la tabla, ofrecen la opción de utilizar RFID además del teclado, este proyecto no incluye esa característica debido a la falta del módulo RFID. Además, se trata de un prototipo desarrollado en un contexto académico.


## Requerimientos

| **ID de Funcionalidad** | **Descripción**                                                   | **Función**                                                                                           |
|-------------------------|-------------------------------------------------------------------|------------------------------------------------------------------------------------------------------|
| 001                     | Introducción de un PIN para desbloquear la puerta.               | Permite a los usuarios ingresar un código PIN para activar el relé y abrir el picaporte de la puerta. |
| 002                     | Configuración y personalización del PIN.                         | Permite a los usuarios configurar y modificar el PIN a través de un teclado matricial.              |
| 003                     | Activación de un LED indicador.                                  | Muestra visualmente si la combinación introducida ha sido aceptada o rechazada.                     |
| 004                     | Emisión de un aviso sonoro.                                      | Proporciona un sonido para confirmar que la combinación introducida es correcta.                    |
| 005                     | Lectura de un sensor analógico (LDR).                             | Detecta la presencia de luz ambiente o oscuridad en el entorno.                                      |
| 006                     | Activación de una lámpara.                                       | Ilumina las teclas en caso de oscuridad, utilizando un relé para encender la lámpara basada en el LDR. |
| 007                     | Mostrar información en un display LCD.                           | Muestra la hora actual, el estado de la lámpara (encendida o apagada), y el estado general del sistema.|
| 008                     | Conexión a una cerradura eléctrica, pestillo o pulsador de salida.| Permite la integración con diferentes tipos de mecanismos de cierre. 


*Tabla 3: Tabla de funciones del control de acceso*



## Casos de Uso
###  Caso de Uso 1: Desbloqueo de la Puerta con PIN

| **Elemento de Caso de Uso** | **Definición**                                                                                                        |
|-----------------------------|----------------------------------------------------------------------------------------------------------------------|
| **Disparador**              | El usuario desea desbloquear la puerta introduciendo un PIN válido.                                                   |
| **Precondición**            | El usuario conoce el PIN válido para desbloquear la puerta y tiene acceso al teclado del sistema.                     |
| **Flujo Básico**            | 1. El usuario introduce el PIN en el teclado. <br> 2. El sistema valida el PIN. <br> 3. Si el PIN es correcto, el sistema activa el relé para desbloquear la puerta. <br> 4. El sistema enciende el LED indicador de acceso y emite un sonido de confirmación. |
| **Flujo Alternativo**       | 1. Si el PIN es incorrecto, el sistema enciende el LED indicador de error y emite un sonido de error. <br> 2. El usuario puede intentar ingresar el PIN nuevamente. <br> 3. Si se superan los intentos permitidos, el sistema activa una alarma de bloqueo. |

###  Caso de Uso 2: Visualización del Estado del Sistema en el LCD

| **Elemento de Caso de Uso** | **Definición**                                                                                                        |
|-----------------------------|----------------------------------------------------------------------------------------------------------------------|
| **Disparador**              | El usuario desea verificar el estado actual del sistema en el display LCD.                                            |
| **Precondición**            | El sistema está encendido y funcionando.                                                                             |
| **Flujo Básico**            | 1. El usuario accede al sistema. <br> 2. El sistema muestra en el LCD la hora actual. <br> 3. El sistema indica el estado de la lámpara (encendida o apagada). <br> 4. El sistema informa si está activo o inactivo. |
| **Flujo Alternativo**       | No aplicable, ya que la visualización en el LCD es un proceso de consulta simple y continuo sin flujos alternativos. |


###  Caso de Uso 3: Activación de la Lámpara en Caso de Oscuridad

| **Elemento de Caso de Uso** | **Definición**                                                                                                        |
|-----------------------------|----------------------------------------------------------------------------------------------------------------------|
| **Disparador**              | El sistema detecta oscuridad mediante el sensor LDR.                                                                 |
| **Precondición**            | El sensor LDR está conectado y funcionando correctamente.                                                             |
| **Flujo Básico**            | 1. El sistema lee el valor del sensor LDR. <br> 2. Si el sensor indica oscuridad, el sistema activa el relé para encender la lámpara. <br> 3. La lámpara se enciende y proporciona iluminación adicional. |
| **Flujo Alternativo**       | 1. Si el sensor LDR indica que hay suficiente luz, la lámpara permanece apagada. <br> 2. El sistema continúa monitoreando la luz ambiente sin cambiar el estado de la lámpara. |
