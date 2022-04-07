#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include<locale.h>
#include <conio.h>

char* myVariables[1000]; // variables in memory (1000 is max variable count)
int variableIndex = 0;
int myIntegers[1000] = {0}; //  Integers that represents variables. For example: myVariables[5] ---> myIntegers[5]
int integerIndex = 0;
int i;

bool isKeyword(char* input){
	if(!strcmp(input,"move") || !strcmp(input,"out") || !strcmp(input,"add") || !strcmp(input,"sub") || !strcmp(input,"int") ||
	!strcmp(input,"to") || !strcmp(input,"from") || !strcmp(input,"loop") || !strcmp(input,"times") || !strcmp(input,"newline") )
	{ 
		return true;
	}
	return false; 
}

bool isVariable(char* input){
	int length = strlen(input);
	if (length > 20) { // variable can nat be more than 20 characters
		return false;
	}
	int i;					
	for (i = 0; i < length; i++) { // controls the every character in input and decided whether is variable or not
		if (!((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z') || (input[i] == '_'))) {
			return false;
		}		
		if (input[0] == '_') {
			return false;
		}		
	}
	return true;	
}
bool isInteger(char* input) {

	int length = strlen(input);

	if (length > 100) { // integer can nat be more than 100 decimal digit
		return false;
	}
	int i;	
	for (i = 0; i < length; i++) {
		
		if(i == 0 && !(isdigit(input[i]) || input[i] == '-') ){ // checks if first character '-' or digit. 
			return false;
		}		
		else {
			if (!(isdigit(input[i]) )){ // controls every character after first character
				return false;
			}
		}					
	}
	return true;
}


bool isIntegerVariable(char* input) { // checks if input match with our variables in memory.
	int i;
	for (i = 0; i < variableIndex; i++) {
		if (!strcmp(input, myVariables[i])) {
			return true;
		}
	}
	return false;
}
bool isStringConstant(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre)-1,
           lenstr = strlen(str);
    return lenstr < lenpre ? false : memcmp(pre, str, lenpre) == 0;
}

void parse( char*  myCode){
	int i;	
	int lineCount = 0;
	char *lines[1000]; // our lines
	char *eachLine = strtok(myCode,".");
	while(eachLine != NULL){ // we split the lines into one line by points and assigned it to line list 
		lines[lineCount++] = eachLine;
		eachLine = strtok(NULL, ".");
	}
	for(i=0;i< lineCount; i++){
		int wordCount = 0;
		char *words[1000];
		char *eachWord = strtok(lines[i], " \n\r,");
		while (eachWord != NULL) {
			words[wordCount++] = eachWord;
			eachWord = strtok(NULL, " \n\r,"); // we split the line into one word by specific characters
		}
		if (wordCount == 0) { return; } // if there is no word
		
		// WHEN THE WORD IS INT keyword
		if (!strcmp(words[0], "int")) {
			printf("Keyword int \n");
			// VARIABLE  IS EXPECTED AFTER 'INT' KEYWORD
			if (isVariable(words[1])) {
				printf("Identifier %s \n", words[1]);
				
				myVariables[variableIndex++] = words[1]; // we add the variable to variable list
				myIntegers[integerIndex++] = 0;// Variables are initialized with the value 0 .
			}
			else {
				printf("ERROR!!  %s is not a variable. Variable is expected.\n", words[1]);
			}
			//End Of Line
			if (wordCount == 2) { 
				printf("End of Line\n"); 
			}
			else {
				printf("ERROR!! End of line ('.')  is expected.\n");// THERE IS ERROR WHEN 3 KEYWORD
			}
		}// END OF INT IDENTIFY OPERATION
		
		// WHEN THE WORD IS MOVE keyword
		else if (!strcmp(words[0], "move")) {
			printf("Keyword move\n");
			// Integer Or Variable is expected after move keyword.		
			int moveInt; // integer constant			
			if (isInteger(words[1])) {
				printf("IntConstant %s \n", words[1]);				
				moveInt = atoi(words[1]);
			}
			
			else if (isIntegerVariable(words[1])) { // if we want to assign the variable, we must find related variable in our varieble list			
				printf("Identifier %s \n", words[1]);
				int i;
				for ( i = 0; i < variableIndex; i++) {
					if (!strcmp(myVariables[i], words[1])) { // we find variable index and assign corresponding integer to moveInt 
						moveInt = myIntegers[i];
						break;
					}
				}
			}
			else {
				printf("ERROR!! %s is not a integer or variable. Integer or variable are expected after MOVE keyword.\n", words[1]);
			}	
			// It must be 'TO' keyword in move operation
			if (!strcmp(words[2], "to")) {
				printf("Keyword to \n");
			}
			else {
				printf("ERROR!! Keyword 'to' is expected in move operation .\n");
				
			}
			// it must be variable after 'to' keyword .
			if (isIntegerVariable(words[3])) {
				printf("Identifier %s \n", words[3]);
				int i;
				for (i = 0; i < variableIndex; i++) {
					if (!strcmp(myVariables[i], words[3])) { // we did 'move operation'.
						myIntegers[i] = moveInt;
						break;
					}
				}
			}
			else {
				printf("ERROR!! %s is not a variable. Variable is expected .\n", words[3]);
			}

			//End Of Line
			if (wordCount == 4) {
				printf("End of Line \n");
			}
			else {
				printf("ERROR!! End of line ('.')  is expected after MOVE operation .\n");
			}						
		} // END OF MOVE OPERATÝON
		
		//WHEN THE WORD IS ADD KEYWORD
		else if (!strcmp(words[0], "add")) {
			printf("Keyword add \n");
			//It must be variable or integer after add keyword!!			
			int addInt = 0;			
			if (isInteger(words[1])) {
				printf("IntConstant  %s \n", words[1]);
				addInt = atoi(words[1]);
			}
			else if (isIntegerVariable(words[1])) { // if we want to add the variable, we must find related variable in our varieble list
				printf("Identifier  %s \n", words[1]);
				int i;
				for (i = 0; i < variableIndex; i++) { 
					if (!strcmp(myVariables[i], words[1])) {  // we find variable index and assign corresponding integer to addInt
						addInt = myIntegers[i]; 
						break;
					}
				}
			}
			else {
				printf("ERROR!! %s is not a integer or variable. Integer or variable are expected after ADD Keyword.\n", words[1]);
			}			
			//It must be 'to' keyword now
			if (!strcmp(words[2], "to")) {
				printf("Keyword to \n");
			}
			else {
				printf("ERROR!! Keyword 'to' is expected in ADD OPERATION .\n");
			}
			//It must be Variable now . ( for example: add 5 to VAR ) 

			if (isIntegerVariable(words[3])) {
				printf("Identifier %s \n", words[3]);
				int i;
				for (i = 0; i < variableIndex; i++) {
					if (!strcmp(myVariables[i], words[3])) {
						myIntegers[i] += addInt; // result of addition
						break;
					}
				}
			}
			else {
				printf("ERROR!! %s is not a variable. Variable is expected to ADD OPERATION .\n", words[3]);
			}
			//End Of Line
			if (wordCount == 4) {
				printf("End of Line \n");
			}
			else {
				printf("ERROR!! End of line is expected after ADD OPERATION.\n");
			}
		}// END OF ADD OPERATION	
		// WHEN DE WORD IS SUB KEYWORD
		
		else if (!strcmp(words[0], "sub")) {
			printf("Keyword sub \n");

			// It must Integer Or Variable after sub keyword
			int subInt = 0;
			if (isInteger(words[1])) {
				printf("IntConstant %s \n", words[1]);
				subInt = atoi(words[1]);
			}
			else if (isIntegerVariable(words[1])) {
				printf("Identifier %s \n", words[1]);
				int i;
				for (i = 0; i < variableIndex; i++) {
					if (!strcmp(myVariables[i], words[1])) {
						subInt = myIntegers[i];
						break;
					}
				}
			}
			else {
				printf("ERROR!! %s is not a integer or variable. Integer or variable are expected.\n", words[1]);
			}
			//  FROM

			if (!strcmp(words[2], "from")) {
				printf("Keyword from \n");
			}
			else {
				printf("ERROR!! Keyword 'from' is expected. \n");
			}

			//Variable

			if (isIntegerVariable(words[3])) {
				printf("Identifier %s \n", words[3]);
				int i;
				for (i = 0; i < variableIndex; i++) {
					if (!strcmp(myVariables[i], words[3])) {
						myIntegers[i] -= subInt;
						break;
					}
				}
			}
			else {
				printf("ERROR!! %s is not a variable. Variable is expected in SUB Operation .\n", words[3]);

			}

			//End Of Line
			if (wordCount == 4) {
				printf("End of Line \n");
			}
			else {
				printf("ERROR! End of line is expected in SUB operation.\n");

			}
		}
		// WHEN THE WORD IS OUT KEYWORD
		else if (!strcmp(words[0], "out")) {
			printf("Keyword out \n");
			if(wordCount == 2){
				if (isInteger(words[1])) {
				printf("IntConstant %s \n", words[1]);

				}	
				else if (isIntegerVariable(words[1])) {
				printf("Identifier %s \n", words[1]);
				}
				else{
					printf("ERROR!! Integer, variable or string are expected.\n");					
				}
				printf("End of Line \n");				
				
			}
			else{
				int i;
				for(i=1;i<wordCount;i++ ){
					if(!strcmp(words[i], "newline")){
						printf("Keyword newline \n");
						if(i<wordCount-1){ // we added seperator until the last word
							printf("Seperator \n");
						}						
					}
					else if (isInteger(words[i])) {
						printf("IntConstant %s \n", words[i]);
						if(i<wordCount-1){
							printf("Seperator \n");
						}
						
					}		
					else if (isIntegerVariable(words[i])) {
						printf("Identifier %s \n", words[i]);
						if(i<wordCount-1){
							printf("Seperator \n");
						}
					}
					else if(isStringConstant("\"",words[i])){						
						printf("String Constant %s \n",words[i]);
						if(i<wordCount-1){
							printf("Seperator \n");
						}
					}
					else{
						if(isKeyword(words[i])){
							printf("ERROR!! End of line is expected! \n ");
						}
						else{
							printf("ERROR!! INVALID INPUT ! newline,int constant, variable or string are expected. \n ");							
						}																								
					}
				}
				printf("End of Line \n");							
			}						
		}
		// END OF OUT OPERATION
		
		else if (!strcmp(words[0], "]")) {
			printf("Closeblock \n");
			int i;
			char newCode[100] = "";
			for ( i = 1; i < wordCount; i++) {
				strcat(newCode, " ");
				strcat(newCode, words[i]);
			}
			strcat(newCode, ".");
			parse(newCode);		
		}
		
		//LOOP
		else if (!strcmp(words[0], "loop")) {
			printf("Keyword loop \n");
			int loopInt=0;
			if (isInteger(words[1])) {
				printf("IntConstant %s \n", words[1]);

				loopInt = atoi(words[1]);
			}
			else if (isIntegerVariable(words[1])) {
				printf("Identifier %s \n", words[1]);
				int i;
				for (i = 0; i < variableIndex; i++) {
					if (!strcmp(myVariables[i], words[1])) {
						loopInt = myIntegers[i];
						break;
					}
				}
			}
			else {
				printf("ERROR!! %s is not a integer or variable. Integer or variable are expected.\n", words[1]);
			}

			//Times
	
			if (!strcmp(words[2], "times")) {
				printf("Keyword times \n");
			}
			else {
				printf("ERROR! Keyword times is expected.\n");
			}
			//Buraya open block siktirnamesi eklenecek.
			
			if (!strcmp(words[3], "[")) {
				printf("Openblock \n");
				//Code
				int i;
				char newCode[100] = "";
				for ( i = 4; i < wordCount; i++) {
					strcat(newCode, " ");
					strcat(newCode, words[i]);
				}
				strcat(newCode, ".");
				parse(newCode);		
			}
			else {
				printf("ERROR! Openblock parenthesis is expected.\n");
			}
		}
	}
}

char commentLine[100]; char a[100]; char b[100];
void isComment(char* str) {
	bool trueComment = false;
	int j;
	int i;
	for ( i = 0; i < strlen(str); i++) {
		if (str[i] == '{') {
			for (j = i; j < strlen(str); j++) {
				if (str[j] == '}') {
					substring(str, i + 1, j - i - 1, commentLine);
					printf("Comment Line: '%s'\n", commentLine);

					substring(str, 0, i, a);
					substring(str, j + 1, strlen(str), b);
					strcat(a, b);
					strcpy(str, a);

					trueComment = true;

					isComment(str);
				}
			}
			if (!trueComment) {
				printf("Comment Line is not completed.\n");
				exit(0);
			}
		}
	}
}
int substring(char *source, int from, int n, char *target) {
	int length, i;
	for (length = 0; source[length] != '\0'; length++);
	if (from > length) {
		printf("Starting index is invalid.\n");
		return 1;
	}
	if ((from + n) > length) {
		n = (length - from);
	}
	for (i = 0; i < n; i++) {
		target[i] = source[from + i];
	}
	target[i] = '\0';
}		

int main() {
	FILE *fp;
	long lSize;
	char *code;
	
	fp = fopen("myscript.ba", "rb");
	if (!fp) perror("myscript.ba"), exit(1);

	fseek(fp, 0L, SEEK_END);
	lSize = ftell(fp);
	rewind(fp);

	code = calloc(1, lSize + 1);
	if (!code) fclose(fp), fputs("memory alloc fails", stderr), exit(1);

	if (1 != fread(code, lSize, 1, fp)) {
		fclose(fp), free(code), fputs("entire read fails", stderr), exit(1);
	}

	isComment(code);
	parse(code);
	
}
