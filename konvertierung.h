struct info_zwischenspeicher
        {char bewertung[3];
         char titel[150];
         char interpret[150];
	};
char quell_db[3]; //Menünummer der Datenbank
char ziel_db[3]; //Menünummer der Datenbank
char quell_pfad[700]; //Pfad der Quelldatenbank
char ziel_pfad[700]; //Pfad der Zieldatenbank
char quell_pfad_korrekt[700]; //korrigiert um \n
char ziel_pfad_korrekt[700]; //korrigiert um \n
char mysql_ip[17]; //Wird nur für MySQL benötigt, also Ampache

int mysql_server_init(int argc, char **argv, char **groups);

//Korrekturfunktion um \n am Ende der Variablen zu löschen.
//Funktion in mdk.c definiert, hier nur Prototyp.
void korrekturfunktion(const char *variable);
//Funktion zur Variablenabfrage, MySQL Pfad fehlt, da ein Sonderfall - kommt nur einmal vor.
void variablenabfrage(void)
{
 printf("Auf welchem Rechner im Netzwerk befindet sich die Quelldatenbank? IP eingeben:");
 fgets(ip_zwischenspeicher,sizeof(ip_zwischenspeicher),stdin);
 	korrekturfunktion(ip_zwischenspeicher);
		 if (*quell_db == '4')
			{
			 strcpy(mysql_ip, ip_zwischenspeicher); //weil später benötigt falls Ampache, damit keine 2. Abfrage
			}
 printf("\nNun den Rootnamen des Quellrechners eingeben (meistens \"root\"):");
 fgets(rootname_zwischenspeicher,sizeof(rootname_zwischenspeicher),stdin);
 	korrekturfunktion(rootname_zwischenspeicher);
 sprintf(ssh_kommando,"sshfs %s@%s:/ /tmp/mdk/quelle" ,rootname_zwischenspeicher,ip_zwischenspeicher);
 //Testfunktion
	printf("\n\n%s\n\n", ssh_kommando);
 mkdir("/tmp/mdk", 0775); //sonst klappt die nächste Zeile nicht.
 mkdir("/tmp/mdk/quelle", 0775);
 //Fehlerabfrage einbauen!!!!
	//Fehlerabfrage: peer connection reset=Server läuft nicht, Liste falsch
 	if(system(ssh_kommando) != 0 )
 		printf("Ein Fehler ist aufgetreten, läuft der SSH Server auf dem Zielrechner?\n");
 printf("Auf welchem Rechner im Netzwerk befindet sich die Zieldatenbank? IP eingeben:");
 fgets(ip_zwischenspeicher,sizeof(ip_zwischenspeicher),stdin);
 	korrekturfunktion(ip_zwischenspeicher);
		 if (*ziel_db == '4')
			{
			 strcpy(mysql_ip, ip_zwischenspeicher); //weil später benötigt falls Ampache, damit keine 2. Abfrage
			}
 printf("\nNun den Root Namen des Zielrechners eingeben (meistens \"root\"):");
 fgets(rootname_zwischenspeicher,sizeof(rootname_zwischenspeicher),stdin);
 	korrekturfunktion(rootname_zwischenspeicher);
 sprintf(ssh_kommando,"sshfs %s@%s:/ /tmp/mdk/ziel" ,rootname_zwischenspeicher,ip_zwischenspeicher);
 mkdir("/tmp/mdk/ziel", 0775);
 //Fehlerabfrage einbauen!!! 
 	if(system(ssh_kommando) != 0 )
 		printf("Ein Fehler ist aufgetreten, läuft der SSH Server auf dem Zielrechner?\n");
 //Testfunktion
        printf("\n\n%s\n\n", ssh_kommando);
if (*ziel_db != 1) // 4 kann sowieso nicht sein, wegen Code in konvertierung(), Code gebraucht um nicht Standardpfade abzufragen.
	{
	 printf("Jetzt den kompletten Pfad der Zieldatanbank auf dem Zielrechner eintippen (evtl. Suchfunktion verwenden):");
         fgets(ziel_pfad,70,stdin);
         sprintf(ziel_pfad_korrekt, "/tmp/mdk/ziel%s", ziel_pfad);
	 	korrekturfunktion(ziel_pfad_korrekt);
	}
 else if ((*ziel_db = 1)) //Für XBMC ist der Pfad klar, da immer gleich, also direkt kopieren.
	{
	 strcpy(ziel_pfad_korrekt, "/tmp/mdk/ziel/storage/.xbmc/userdata/Database/MyMusic7.db");
	}
}

void konvertierung(int argc, char **argv)
{printf("Folgende Möglichkeiten haben Sie:\n\n");
 printf("-1- XBMC - Openelec\n");
 printf("-2- Banshee\n");
 printf("-3- Clementine\n");
 printf("-4- Ampache\n");
 printf("\nBitte tippen Sie die Nummer ihrer Quelldatenbenk ein:");
 fgets(quell_db,3,stdin);
 printf("Nun die Nummer der Zieldatenbank eintippen:");
 fgets(ziel_db,70,stdin);

 if (*quell_db == '1')
                {
                if (*ziel_db == '1') //XBMC
                        {
                         printf("Es ist eine schlechte Idee die Datenbank von XBMC nach XBMC zu konvertieren, kopiert sie manuell.\n");
                        }
                else if (*ziel_db != '1')
                        {
			 variablenabfrage();
			 printf("\nDIESE FUNKTION WIRD NOCHT NICHT UNTERSTÜZT!!!\n");
			}
		}
 else if (*quell_db == '2')
                 {
                if (*ziel_db == '2') //Banshee
                        {
                         printf("Es ist eine schlechte Idee die Datenbank von Banshee nach Banshee zu konvertieren, kopiert sie manuell.\n");
                        }
                else if (*ziel_db != '2')
                        {
			 variablenabfrage();
                	 printf("\nDIESE FUNKTION WIRD NOCHT NICHT UNTERSTÜZT!!!\n");
			}
                }
 else if (*quell_db == '3')
                 {
                if (*ziel_db == '3') //Clementine
                        {
                         printf("Es ist eine schlechte Idee die Datenbank von Clementine nach Clementine zu konvertieren, kopiert sie manuell.\n");
                        }
                else if (*ziel_db != '3')
                        {
			 variablenabfrage();
                	 printf("\nDIESE FUNKTION WIRD NOCHT NICHT UNTERSTÜZT!!!\n");
			}
                }
 else if (*quell_db == '4')
                {
		if (*ziel_db == '4') //Ampache
			{
                         printf("Es ist eine schlechte Idee die Datenbank von Ampache nach Ampache zu konvertieren, kopiert sie manuell.\n");
			}
		else if (*ziel_db != '4')
			{
		 	 variablenabfrage();
		 	 //MySQL
		 	 //char mysql_ip[15];
		 	 char mysql_passwort[70];
			 char mysql_datenbankname[70];
			 mysql_library_init(argc, argv, NULL);
			 MYSQL mysql;
			 mysql_init(&mysql);
			 //mysql_options kann verwendet werden um die Logindaten aus der Config auszulesen! - kann man als option einbauen.
			 //Doku dazu: http://dev.mysql.com/doc/refman/5.1/de/mysql-real-connect.html
			 //mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"your_prog_name");
			 //Dokumentation: http://dev.mysql.com/doc/refman/5.1/de/mysql-real-connect.html
			 //Localhost ist bekannt -> umleiten, Achtung Passwort normalerweise blank, root immer da - keine Abfrage?, Datenbankname
			 //abfragen, da bei Ampache variabel -> umleiten.
			 printf("\nAmpache verwendet MySQL, deswegen werden die Verbindungsdaten benötigt"); 
			 printf("\nIP des MySQL Servers eingeben:");
			 fgets(mysql_ip,17,stdin);
	 		 korrekturfunktion(mysql_ip);
			 printf("\nRootpasswort des MySQL Servers eingeben, Achtung,das Passwort ist sichtbar:");
			 //ÄNDERN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
		 	 fgets(mysql_passwort,70,stdin);
			 korrekturfunktion(mysql_passwort);
		 	 printf("\nBei der Ampache Installation wurde ein Datenbankname gewählt, diesen bitte eingeben:");
		 	 fgets(mysql_datenbankname,70,stdin);
			 korrekturfunktion(mysql_datenbankname);
			 //Testfunktion
			 //printf("ausgabe:%s, %s, %s\n", mysql_ip, mysql_passwort, mysql_datenbankname);
		 	 if (!mysql_real_connect(&mysql,mysql_ip,"root",mysql_passwort,mysql_datenbankname,0,NULL,0)) //ACHTUNG!!!!! ABFRAGEN!!!
			 {
			  fprintf(stderr, "Keine MySQL Verbindung zur Datenbank möglich: Fehler: %s\n", mysql_error(&mysql));
			 }
			 //http://dev.mysql.com/doc/refman/5.1/de/c-api-function-overview.html
			 //MySQL Anweisungen, wie siehe Link oberhalb
			 //MySQL Befehl:
			 //SELECT rating.rating, song.title, artist.name FROM rating, song, artist WHERE rating.object_id = song.id
			 //AND song.artist = artist.id AND rating.object_type = 'song' AND rating.rating IS NOT NULL;
	 	 	 mysql_query(&mysql, "SELECT rating.rating, song.title, artist.name FROM rating, song, artist WHERE rating.object_id = song.id AND song.artist = artist.id AND rating.object_type = 'song' AND rating.rating IS NOT NULL");
		 	 MYSQL_RES *mysql_ergebnis = NULL;
		 	 mysql_ergebnis = mysql_store_result(&mysql); //Resultat der Anfrage gespeichert. http://dev.mysql.com/doc/refman/5.1/de/mysql-store-result.html
	 	 	 MYSQL_ROW row;
				//Variable der Struktur, http://www.tutorials.at/c/13-strukturen-dateizugriff.html
		 	 struct info_zwischenspeicher musikdaten;
                 	 if (*ziel_db == '1') // XBMC - Openelec
                        	{
                         	 //SQLite Zieldatenbank wird geöffnet
		 	 	 sqlite3 *sqlite_ziel_db;
				 if(sqlite3_open(ziel_pfad_korrekt, &sqlite_ziel_db) != SQLITE_OK)
                        		{
				 	 printf("SQLite Fehler aufgetreten!!!");
					}
				 //MySQL Zeilen auslesen und zwischenspeichern
				 while((row = mysql_fetch_row(mysql_ergebnis)))
					{
                         	         strcpy(musikdaten.bewertung, row[0]); //falls bewertung als char
                                	 strcpy(musikdaten.titel, row[1]);
                                 	 strcpy(musikdaten.interpret, row[2]);
                           	         //Testfunktion
					 printf("%s, %s, %s\n\n", musikdaten.bewertung, musikdaten.titel, musikdaten.interpret);
				 	 //SQLite Code
					 char *zErrMsg = 0;
					 int rc = 0;
					 char sqlite3_befehl[2500];
					 char sqlite3_stm[2500];
					 sprintf(sqlite3_stm, "UPDATE song SET rating = %s WHERE idArtist = (SELECT song.idArtist FROM song,artist WHERE artist.idArtist = song.idArtist AND song.strTitle = \"%s\" AND artist.strArtist = \"%s\") AND strTitle = (SELECT song.strTitle FROM song, artist WHERE artist.idArtist = song.idArtist AND song.strTitle = \"%s\" AND artist.strArtist = \"%s\")" ,musikdaten.bewertung,musikdaten.titel,musikdaten.interpret,musikdaten.titel,musikdaten.interpret);
					 //Testfunktion
					 printf("sqlite3 test: %s\n\n", ziel_pfad_korrekt);
					 strcpy(sqlite3_befehl, sqlite3_stm);
				 	 korrekturfunktion(sqlite3_befehl);
					 //Testfunktion
				 	 printf("sqlite3 test: %s\n\n", sqlite3_befehl);
				 	 sqlite3_exec(sqlite_ziel_db, sqlite3_befehl, NULL, NULL, NULL);
						if( rc!=SQLITE_OK )
							{
							 fprintf(stderr, "SQL error: %s\n", zErrMsg);
							 sqlite3_free(zErrMsg);
							}
					}
	                       		 sqlite3_close(sqlite_ziel_db);
					 printf("\nDatenbankeinträge aktualisiert - wenn keine Fehler");
					 //Abfrage Verbessern!!!!!!!! Ob es wirklich so ist!!!
					}
			else if (*ziel_db == '2') //Banshee
				 {
                                 //SQLite Zieldatenbank wird geöffnet
                                 sqlite3 *sqlite_ziel_db;
                                 if(sqlite3_open(ziel_pfad_korrekt, &sqlite_ziel_db) != SQLITE_OK)
                                        {
                                         printf("SQLite Fehler aufgetreten!!!");
                                        }
					//MySQL Zeilen auslesen und zwischenspeichern
                                 while((row = mysql_fetch_row(mysql_ergebnis)))
                                        {
                                         strcpy(musikdaten.bewertung, row[0]); //falls bewertung als char
                                         strcpy(musikdaten.titel, row[1]);
                                         strcpy(musikdaten.interpret, row[2]);
                                         //Testfunktion
                                         //printf("%s, %s, %s\n", musikdaten.bewertung, musikdaten.titel, musikdaten.interpret);
                                         //SQLite Code
                                         char *zErrMsg = 0;
                                         int rc = 0;
                                         char sqlite3_befehl[2500];
                                         char sqlite3_stm[2500];
                                         sprintf(sqlite3_stm, "UPDATE CoreTracks SET Rating = %s WHERE ArtistID = (SELECT CoreTracks.ArtistID FROM CoreTracks, CoreArtists WHERE CoreTracks.ArtistID = CoreArtists.ArtistID AND CoreTracks.Title = \"%s\" AND CoreArtists.Name = \"%s\") AND Title = (SELECT CoreTracks.Title FROM CoreTracks, CoreArtists WHERE CoreArtist.ArtistID = CoreTracks.ArtistID AND CoreTracks.Title = \"%s\" AND CoreArtists.Name = \"%s\")",musikdaten.bewertung,musikdaten.titel,musikdaten.interpret,musikdaten.titel,musikdaten.interpret);
                                         //Testfunktion
                                         //printf("sqlite3 test: %s", ziel_pfad_korrekt);
                                         strcpy(sqlite3_befehl, sqlite3_stm);
                                         korrekturfunktion(sqlite3_befehl);
                                         //Testfunktion
                                         //printf("sqlite3 test: %s\n\n", sqlite3_befehl);
                                         sqlite3_exec(sqlite_ziel_db, sqlite3_befehl, NULL, NULL, NULL);
                                                if( rc!=SQLITE_OK )
                                                        {
                                                         fprintf(stderr, "SQL error: %s\n", zErrMsg);
                                                         sqlite3_free(zErrMsg);
                                                        }
                                        }
                                         sqlite3_close(sqlite_ziel_db);
                                         printf("\n Datenbankeinträge aktualisiert - wenn keine Fehler");
                                         //Abfrage Verbessern!!!!!!!! Ob es wirklich so ist!!!
 				}
			else if (*ziel_db == '3') //Clementine
				{
                                 //SQLite Zieldatenbank wird geöffnet
                                 sqlite3 *sqlite_ziel_db;
                                 if(sqlite3_open(ziel_pfad_korrekt, &sqlite_ziel_db) != SQLITE_OK)
                                        {
                                         printf("SQLite Fehler aufgetreten!!!");
                                        }
                                        //MySQL Zeilen auslesen und zwischenspeichern
                                 while((row = mysql_fetch_row(mysql_ergebnis)))
                                        {
                                         strcpy(musikdaten.bewertung, row[0]); //falls bewertung als char
                                         strcpy(musikdaten.titel, row[1]);
                                         strcpy(musikdaten.interpret, row[2]);
                                         //Testfunktion
                                         //printf("%s, %s, %s\n", musikdaten.bewertung, musikdaten.titel, musikdaten.interpret);
                                         //SQLite Code
                                         char *zErrMsg = 0;
                                         int rc = 0;
                                         char sqlite3_befehl[2500];
                                         char sqlite3_stm[2500];
                                         sprintf(sqlite3_stm, "UPDATE songs SET rating = %s WHERE title = \"%s\" AND artist = \"%s\"", musikdaten.bewertung, musikdaten.titel, musikdaten.interpret);
                                         //Testfunktion
                                         //printf("sqlite3 test: %s", ziel_pfad_korrekt);
                                         strcpy(sqlite3_befehl, sqlite3_stm);
                                         korrekturfunktion(sqlite3_befehl);
                                         //Testfunktion
                                         //printf("sqlite3 test: %s\n\n", sqlite3_befehl);
                                         sqlite3_exec(sqlite_ziel_db, sqlite3_befehl, NULL, NULL, NULL);
                                                if( rc!=SQLITE_OK )
                                                        {
                                                         fprintf(stderr, "SQL error: %s\n", zErrMsg);
                                                         sqlite3_free(zErrMsg);
                                                        }
                                        }
                                         sqlite3_close(sqlite_ziel_db);
                                         printf("\n Datenbankeinträge aktualisiert - wenn keine Fehler");
                                         //Abfrage Verbessern!!!!!!!! Ob es wirklich so ist.
                       		}
			mysql_library_end();
               		system("fusermount -u /tmp/mdk/quelle");
               		system("fusermount -u /tmp/mdk/ziel");
			}
                }
else {printf("Falsche Eingabe, Konvertierung beendet.\n");}
}
