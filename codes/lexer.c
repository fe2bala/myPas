/**@<lexer.c>::**/
#include <lexer.h>

size_t linenumber = 1;

token_t ignoreneutrals(FILE * tape){
    int head;

_ignoreneutrals_start:
    while (isspace(head = getc(tape))) {
	    if (head == '\n') {
		    linenumber++;
	    }
    }
    if ( head == '{' ) {
	    while ( (head = getc(tape)) != '}' ) {
		    if (head == EOF) {
			    return EOF;
		    }
		    if (head == '\n') {
			    linenumber++;
		    }
	    }
	    goto _ignoreneutrals_start;
    }
    ungetc(head, tape);
    return 0;
}

token_t isASGN(FILE * tape)
{
	if ( (lexeme[0] = getc(tape)) == ':' ) {
		if ( (lexeme[1] = getc(tape)) == '=' ) {
			lexeme[2] = 0;
			return ASGN;
		}
		ungetc(lexeme[1], tape);
	}
	ungetc(lexeme[0], tape);
	return lexeme[0] = 0;
}

token_t isRELOP(FILE * tape)
{
	switch (lexeme[0] = getc(tape)) {
	case'<':
		lexeme[1] = getc(tape);
		lexeme[2] = 0;
		switch (lexeme[1]) {
		case'=':
			return LEQ;
		case'>':
			return NEQ;
		}
		ungetc(lexeme[1], tape);
		lexeme[1] = 0;
		return lexeme[0];
	case'>':
		lexeme[1] = getc(tape);
		if (lexeme[1] == '=') {
			lexeme[2] = 0;
			return GEQ;
		} 
		ungetc(lexeme[1], tape);
		lexeme[1] = 0;
		return lexeme[0];
	case'=':
		lexeme[1] = 0;
		return lexeme[0];
	}
	ungetc(lexeme[0], tape);
	return lexeme[0] = 0;
}

token_t isID(FILE * tape)
{
    int i = 0;
    int token;

    if (isalpha(lexeme[i] = getc(tape))) {
        i++;
        while (isalnum(lexeme[i] = getc(tape)))
            i++;
        ungetc(lexeme[i], tape);
        lexeme[i] = 0;
        token = iskeyword(lexeme);
        if (token)
            return token;
        return ID;
    }

    ungetc(lexeme[i], tape);
    return 0;
}

token_t gettoken(FILE * tape)
{
    int             token;
    ignoreneutrals(tape);
    if(token = isID(tape))
        return token;
    if(token = isASGN(tape))
    	return token;
    if(token = isRELOP(tape))
    	return token;

    return token = getc(tape);
}
