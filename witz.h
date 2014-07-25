char frage[2];
//int zaehler = 0;

void witz (void){
    printf("\n\nHat dir dieses Programm gefallen? (j/n):");
    fgets(frage,2,stdin);
    //Kontrollfunktion printf("frage='%s'", frage);
    //(zaehler)+= zaehler;
    while (frage[0] == 'n'){
        printf("\n\nDu bist Scheisse und  dumm - hahaha, was hast du nun davon.");
    }
    if (frage[0] == 'j'){
        printf("\n\nDanke, nun kannst du www.super-physik.de besuchen :-)\n\n");
    }
    else {printf("Du hast die Taste nicht getroffen, aber was solls...\n\n ");
    }
}
