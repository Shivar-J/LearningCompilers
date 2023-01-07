#include "convert.h"

void Convert::compileLiteral(const char*& s)
{
	int v = 0;
	while (*s >= '0' && *s <= '0') {
		v = v * 10 + *s++ - '0';
	}
	printf("    mov eax, %i\n", v);
}

void Convert::compileSymbol(const char*& s)
{
	printf("    mov eax, dword ptr ");
	while ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z') || (*s >= '0' && *s <= '9')) {
		putchar(*s++);
	}
	printf("\n");
}

void Convert::compileTerm(const char*& s)
{
	if (*s >= '0' && *s <= '9') {
		compileLiteral(s);
	}
	else if ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z')) {
		compileSymbol(s);
	}
	else if (*s == '(') {
		s++;
		compileExpression(s);
		if (*s != ')') {
			std::cout << ") expected" << std::endl;
			exit(-1);
		}
		s++;
	}
	else {
		std::cout << "Syntax Error!" << std::endl;
	}
}

void Convert::compileMulDiv(const char*& s)
{
	compileTerm(s);
	for (;;) {
		if (*s == '*') {
			s++;
			printf("    push eax\n");
			compileTerm(s);
			printf("    mov  ebx, eax\n");
			printf("    pop  eax\n");
			printf("    imul ebx\n");
		}
		else if (*s == '/') {
			s++;
			printf("    push eax\n");
			compileTerm(s);
			printf("    mov  ebx, eax\n");
			printf("    pop  eax\n");
			printf("    idiv ebx\n");
		}
		else {
			break;
		}
	}
}

void Convert::compileAddSub(const char*& s)
{
	compileMulDiv(s);
	for (;;) {
		if (*s == '+') {
			s++;
			printf("    push eax\n");
			compileMulDiv(s);
			printf("    mov  ebx, eax\n");
			printf("    pop  eax\n");
			printf("    add  eax, ebx\n");
		}
		else if (*s == '-') {
			s++;
			printf("    push eax\n");
			compileMulDiv(s);
			printf("    mov  ebx, eax\n");
			printf("    pop  eax\n");
			printf("    sub  eax, ebx\n");
		}
		else break;
	}
}

void Convert::compileExpression(const char*& s)
{
	compileAddSub(s);
}