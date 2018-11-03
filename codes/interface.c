#include <string.h>
#include <interface.h>
#include <lexer.h>

extern size_t linenumber;
extern size_t collummnumber;
extern char *keyword[];

void translator(char *translated, token_t original);

void match(token_t expected){
	char charexp[MAXIDLEN], charlook[MAXIDLEN];

	if(expected == lookahead){
		lookahead = gettoken(source);
	}else{
		translator(charlook, lookahead);
		translator(charexp, expected);

		printf("Token mismatch expected '%s', found '%s'\n", charexp, charlook);
		printf("At line: %d\n", linenumber);
		printf("At collumm: %d/n",collummnumber);
		exit(1);
	}
}

void translator(char *translated, token_t original){
	if(original == -1){
		strcpy(translated, "EOF");
	}else if(original < 1024){
		translated[0] = original;
		translated[1] = 0;
	}else if(original < 8192){
		strcpy(translated, "TOKEN");
	}else{
		strcpy(translated, keyword[original-8192]);
	}
}