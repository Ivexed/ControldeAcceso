#ifndef _DISPLAYMANAGER_H_
#define _DISPLAYMANAGER_H_

#define REFRESH_TIME_BACKLIGHT 60000

void showPinIntroduction(); // Muestra la combinación en el display
void showSystemState(bool systemState);  // Muestra el estado del sistema (bloqueado/desbloqueado)
void showAttemptsLeft(int attemptsLeft);  // Muestra la cantidad de intentos restantes
void showChangingCombination();  // Muestra el estado de cambio de combinación
void showSetTime();
void displayRealTimeClock();
void showLdrState(bool ldrState);
void backlight();

void checkDisplayConditions();
void interfaceDisplayInit();
void interfaceDisplayUpdate();

#endif // _DISPLAYMANAGER_H_