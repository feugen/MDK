//Für popen und pclose
FILE *konsole;
//Zwischenspeicher und Menueeingabe - für das Auswahlmenü benötigt
char zwischenspeicher2[3];

//Die 3 Variablen in suche.h und konvertierung.h benötigt
//Weshalb müssen sie hier definiert sein und nicht in mdk.c? Verstehe ich nicht!
char ip_zwischenspeicher[17]; //IP für SSH Anfrage
char rootname_zwischenspeicher[17]; //Rootname für SSH Anfrage
char ssh_kommando[500]; //Zusammengesetzt aus Rootname und IP

int menueeingabe2;
//Korrekturfunktion um \n am Ende der Variablen zu löschen.
//Definiert in mdk.c, hier nur Prototyp
void korrekturfunktion(const char *variable);

//Übergibt den Suchbefehl an die Konsole.
void suchfunktion(const char *command, const char *type)
{konsole=popen(command, type);
pclose(konsole);
}
//Abfrage ob was gefunden wurde hinzufügen!!!
extern void suche()
{	printf("Die Suchfunktion dient als Hilfe für die Suche nach ");
	printf("den unterstützten Datenbanken auf dem Quell- und ");
	printf("Zielrechner. Die Suche könnt ihr mehrmals aufrufen um mehrere ");
	printf("Rechner auf unterstützte Datenbanken zu durchsuchen. ");
	printf("Die erfolglose Suche heißt NICHT, dass die Konvertierung ");
       	printf("der Datenbank fehlschlagen wird - sie dient nur als ");
       	printf("Hilfestellung.\n\n");

       	printf("Aktuell wird nach folgenden Datenbanken gesucht:\n\n");
       	printf("-1- XBMC oder Openelec\n");
	printf("-2- Banshee\n");
	printf("-3- Clementine\n");
	printf("-4- Ampache\n\n");

	printf("Bitte wählen sie den zu durchsuchenden Rechner aus:\n\n");

	printf("-1- Lokale Suche\n");
	printf("-2- Netzwerksuche\n\n");
	
	printf("Ihre Auswahl?:");
	fgets(zwischenspeicher2,3, stdin); // Einlesen der Tastatureingabe, Ziel: Zwischenspeicher, 3 Zeichen lang.
	sscanf(zwischenspeicher2, "%d", &menueeingabe2); // Konvertierung des Char nach Int
		if (menueeingabe2 == 1 )
			{printf("\nDanke, jetzt noch die Suchmethode auswählen:\n\n");
			 printf("-1- Schnelle Suche (Empfohlen)\n");
			 printf("-2- Sichere Suche (nur im Home Verzeichnis - kann einige Minuten dauern!)\n\n");
				printf("Ihre Auswahl?:");
				fgets(zwischenspeicher2,3, stdin);
        			sscanf(zwischenspeicher2, "%d", &menueeingabe2);
					if (menueeingabe2 == 1)
						{printf("\nFolgende Datenbanken wurden gefunden...\n\n");
						 printf("XBMC Datenbank (Lokal):\n");
							suchfunktion("locate MyMusic7.db","w");
						 printf("\nBanshee Datenbank (Lokal):\n");
							suchfunktion("locate banshee.db", "w");
						 printf("\nClementine Datenbank (Lokal):\n");
							suchfunktion("locate clementine.db","w");
						 printf("\nAmpache Datenbank (Lokal):\n");
							suchfunktion("locate ampache.sql","w");
						}
					else if (menueeingabe2 == 2)
						{printf("\nFolgende Datenbanken wurden gefunden...\n\n");
						 printf("XBMC Datenbank (Lokal):\n");
							suchfunktion("find /home -name MyMusic7.db","w");
								//if(system("find /home -name MyMusic7.db") != '\n')
								//	printf("nichts gefunden\n");
								//funktioniert nicht richtig wenn doch was gefunden wird.
						 printf("\nBanshee Datenbank (Lokal):\n");
							suchfunktion("find /home -name banshee.db","w");
						 printf("\nClementine Datenbank (Lokal):\n");
							suchfunktion("find /home -name clementine.db","w");
						 printf("\nAmpache Datenbank (Lokal):\n");
							suchfunktion("find /home -name ampache.sql","w");
						}
					else {printf("\nFalsche Eingabe - Suchfunktion beendet!!!");}
			}
		else if (menueeingabe2 == 2)
				{printf("\nDanke, jetzt noch die Suchmethode auswählen:\n\n");
				 printf("-1- Schnelle Suche (Empfohlen)\n");
				 printf("-2- Sichere Suche (nur im Home Verzeichnis - kann einige Minuten dauern!)\n\n");
				 printf("Ihre Auswahl?:");
				 fgets(zwischenspeicher2,3, stdin);
				 sscanf(zwischenspeicher2, "%d", &menueeingabe2);
					if (menueeingabe2 == 1)
						{printf("\nBitte geben Sie die IP-Adresse des zu durchsuchenden Rechners ein:");
						 fgets(ip_zwischenspeicher,sizeof(ip_zwischenspeicher),stdin);
							korrekturfunktion(ip_zwischenspeicher);
						 printf("\nNun den Root Namen eingeben (meistens \"root\"):");
						 fgets(rootname_zwischenspeicher,sizeof(rootname_zwischenspeicher),stdin);
						 //rootname_zwischenspeicher Korrektur damit hinten kein /n steht
						 	korrekturfunktion(rootname_zwischenspeicher);
						 sprintf(ssh_kommando,"sshfs %s@%s:/ /tmp/mdk" ,rootname_zwischenspeicher,ip_zwischenspeicher);
							mkdir("/tmp/mdk", 0775);
							//Fehlerabfrage einbauen!!!!
							if(system(ssh_kommando) != 0 )
								printf("Ein Fehler ist aufgetreten, läuft der SSH Server auf dem Zielrechner?");
							//Fehlerabfrage: peer connection reset=Server läuft nicht, Liste falsch
							system("cp /tmp/mdk/var/lib/mlocate/mlocate.db /tmp");
							//notwendig, da Zugriffsprobleme wenn als root Zugriff auf die
							//DB über ssh. Um keine Rechte auf dem Fremdrechner ändern zu
							//müssen, ist das eine Lösung.
							//ACHTUNG wenn XBMC, so FEHLER da kein Locate!!!
							system("chmod 775 /tmp/mlocate.db");
							system("chown root:root /tmp/mlocate.db");
							printf("\n\nFolgende Datenbanken wurden auf %s gefunden...\n\n",ip_zwischenspeicher);
							printf("XBMC Datenbank:\n");
								suchfunktion("locate MyMusic7.db -d /tmp/mlocate.db","w");
							printf("\nBanshee Datenbank:\n");
								suchfunktion("locate banshee.db -d /tmp/mlocate.db","w");
							printf("\nClementine Datenbank:\n");
								suchfunktion("locate clementine.db -d /tmp/mlocate.db","w");
							printf("\nAmpache Datenbank:\n");
								suchfunktion("locate ampache.sql -d /tmp/mlocate.db","w");
							system("rm -f /tmp/mlocate.db");
							//Die fremde Datenbank wird gelöscht, damit kein Unfug passiert.
							system("fusermount -u /tmp/mdk");
							//printf("\nSSH_Kommando Test: %s",ssh_kommando);
						}
					else if (menueeingabe2 == 2)
                                                {printf("\nBitte geben Sie die IP-Adresse des zu durchsuchenden Rechners ein:");
                                                 fgets(ip_zwischenspeicher,sizeof(ip_zwischenspeicher),stdin);
                                                        korrekturfunktion(ip_zwischenspeicher);
                                                 printf("\nNun den Root Namen eingeben (meistens \"root\"):");
                                                 fgets(rootname_zwischenspeicher,sizeof(rootname_zwischenspeicher),stdin);
                                                 //rootname_zwischenspeicher Korrektur damit hinten kein /n steht
                                                        korrekturfunktion(rootname_zwischenspeicher);
                                                 sprintf(ssh_kommando,"sshfs %s@%s:/ /tmp/mdk" ,rootname_zwischenspeicher,ip_zwischenspeicher);
                                                        mkdir("/tmp/mdk", 0755);
                                                        //Fehlerabfrage einbauen!!!!
                                                        if(system(ssh_kommando) != 0)
								printf("Ein Fehler ist aufgetreten, läuft der SSH Server auf dem Zielrechner?");
                                                        //Fehlerabfrage: peer connection reset=Server läuft nicht, Liste fals$
							chdir("/tmp/mdk");
							printf("\n\nFolgende Datenbanken wurden auf %s gefunden...\n\n",ip_zwischenspeicher);
                                                        printf("XBMC Datenbank:\n");
                                                                suchfunktion("find /home -name MyMusic7.db","w");
                                                        printf("\nBanshee Datenbank:\n");
                                                                suchfunktion("find /home -name banshee.db","w");
                                                        printf("\nClementine Datenbank:\n");
                                                                suchfunktion("find /home -name clementine.db","w");
                                                        printf("\nAmpache Datenbank:\n");
                                                                suchfunktion("find /home -name ampache.sql","w");
							chdir("/tmp"); // damit das nachfolgende fusermount funktioniert.
							system("fusermount -u /tmp/mdk");
						}
					else {printf("\nFalsche Eingabe - Suchfunktion beendet!!!");}
			}
		else {printf("Falsche Eingabe!!!");}
printf("\n\n");
}
