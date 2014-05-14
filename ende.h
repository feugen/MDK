char frage[2];

void ende (void)
{
	printf("\n\n gefällt dir dieses Programm? (j/n):");
		fgets(frage,2,stdin);
printf("frage='%s'", frage);
		while (frage[0] == 'n')
			{printf("\n\nDu bist Scheisse und  dumm - hahaha, was hast du nun davon.”");
			}
		if (frage[0] == 'j')
			{printf("\n\nDanke, nun kannst du www.super-physik.de besuchen :-)\n\n");
			}
		else {printf("Du hast die Taste nicht getroffen, aber was solls...\n\n ");
			}
}
