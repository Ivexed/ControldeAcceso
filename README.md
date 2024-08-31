#  Trabajo Final - Control de acceso

##  Informe de avance

## Cumplimiento de los Requerimientos

A continuación, se indica en la **Tabla 1** el estado de situación para cada uno de los requerimientos expresados en la planificación, indicando con un circulo de color verde si se considera que ya se ha cumplido, en color amarillo si aún no se ha cumplido pero se podrá cumplir, y en color rojo si aún no se ha cumplido y se tiene dudas si se podrá cumplir.

| **ID** | **Requerimiento**                                                                                                   | **Estado**    |
|--------|---------------------------------------------------------------------------------------------------------------------|---------------|
| 1      | Introducción de un PIN para desbloquear la puerta mediante teclado matricial.                                       | 🟢           | 
| 2      | El sistema debe permitir la configuración y personalización del PIN.                                                | 🟡            |
| 3      | Al introducir un PIN correcto, el sistema debe apagar el LED de estado.                                             | 🟢            |
| 3.1    | Al introducir un PIN incorrecto, el sistema debe realizar un parpadeo constante.                                    | 🟢 |
| 3.2    | Al introducir un PIN incorrecto más de 3 veces seguidas, el indicador LED debe permanecer prendido.                 | 🟢  |
| 4      | Al introducir un PIN correcto, el sistema debe emitir un aviso sonoro.                                              | 🟢   |
| 4.1    | Al introducir un PIN incorrecto, el sistema debe emitir un aviso sonoro de una duración mayor que en el caso anterior. | 🟢  |
| 4.2    | Al introducir un PIN incorrecto más de 3 veces seguidas, el sistema emitirá un aviso sonoro de larga duración y luego se apagará. | 🟢 |
| 5      | Lectura de un sensor analógico (LDR).                                                                               | 🟢   |
| 6      | Activación de una lámpara, dependiendo del valor leído del sensor analógico.                                        | 🟢  |
| 7      | El sistema debe permitir la configuración de día y hora a través del teclado.                                       | 🟡   |
| 8      | El sistema debe mostrar información sobre el estado, la hora y el día en un display LCD.                            | 🟡  |
| 9      | Conexión a una cerradura eléctrica, pestillo o pulsador de salida.                                                  | 🔴  |

**Tabla 1 – Situación actual de requerimientos**

Los requerimientos cuyo estado se representan con un circulo de color rojo se evaluaron de este modo principalmente debido a la falta de tiempo y al desafio que el código actual presenta, lo cual retrasa el progreso. De esta manera se planea enfocarse en los requerimientos que se consideraron esenciales para el proyecto, priorizándolos y dejando temporalmente de lado los menos críticos, hasta alcanzar los objetivos principales.
