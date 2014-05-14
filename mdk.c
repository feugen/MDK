/* Siehe feature_test_macros(7) für Details */
#define _POSIX_C_SOURCE 200809L

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sqlite3.h> // sqlite-devel installieren um zu kompilieren
#include <mysql/mysql.h> //mysql-devel, Unterordner distributionsspezifisch!
#include <unistd.h> // für chdir() Funktion
#include "hilfe.h" // Die Hilfefunktion (hilfe()) wird hiermit eingebunden.
#include "suche.h" // Die Suchfunktion (suche()) wird hiermit eingebunden.
#include "konvertierung.h" // Die Konvertierungsfunktion wird eingebunden.
#include "witz.h" // Die Witzfunktion wird eingebunden.

void logo()
{printf("=============================\n");
printf("=====www.super-physik.de=====\n");
printf("=============================\n\n");
}

char *korrektur; //Pointer für die Korrekturfunktion
//Korrekturfunktion um \n am Ende der Variablen zu löschen.
//Für konvertierung.h und suche.h
void korrekturfunktion(const char *variable)
{
 korrektur=strchr(variable, '\n');
 if (korrektur)
        *korrektur='\0';
}

int main (int argc, char **argv)
{
	char zwischenspeicher[3]; 
	/* wird benötigt, weil das Einlesen mit fgets ein Char benötigt,
 	wir jedoch für Switch ein INT brauchen. Sscanf konvertiert es in INT.
	Zeichenlänge ist 2, da \n als 1 Zeichen beim Einlesen draufgeht */

	int menueeingabe;

	system ("clear"); // löschen der vorhergehenden Konsolenausgabe 
        logo();

	do{printf("Bitte Operation eingeben:\n\n");
	   printf("-1- Hilfe anzeigen\n");
	   printf("-2- Datenbanken suchen\n");
	   printf("-3- Datenbank konvertieren\n\n");
	   printf("-4- Programmende\n");
	   printf("-5- Witziges Programmende :-)\n");
	   printf("\nBitte die Auswahl eintippen:");
	   fgets(zwischenspeicher,3, stdin); // Einlesen der Tastatureingabe, Ziel: Zwischenspeicher, 3 Zeichen lang.
	   sscanf(zwischenspeicher, "%d", &menueeingabe); // Konvertierung des Char nach Int
	   system("clear"); // löschen des Bildschirms, nicht perfekt aber akzeptabel für die Konsole.
		switch(menueeingabe)
			{case 1 : logo();
					hilfe();
				  printf("\n=============================\n\n");
					break;
			 case 2 : logo();
				  	suche();
			 	  printf("\n=============================\n\n");
					break;
			 case 3 : logo();
				  	konvertierung(argc, argv);
				  printf("\n=============================\n\n");
					break;
			 case 4 : logo();
				  printf("Programm beendet\n\n");
				  printf("\n=============================\n\n");
					return EXIT_SUCCESS;
			 case 5 : logo();
                                  	witz();
				  printf("\n=============================\n\n");
                                	return EXIT_SUCCESS;
			 default : logo();
				   printf("Falsche Eingabe - nochmal versuchen\n\n");
				   printf("\n=============================\n\n");
				//hier kann man ausgeben, was falsch eingegeben wurde.
			}
	  }
	while(menueeingabe != 4);
	return EXIT_SUCCESS;
}
