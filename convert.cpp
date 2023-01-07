#include "convert.h"

void Convert::compileLiteral(const char*& s)
{
	int v = 0;
	while (*s >= '0' && *s <= '9') {
		v = v * 10 + *s++ - '0';
	}
	fprintf(file ,"%p    mov eax, %i\n", (void*)&s, v);
}

void Convert::compileSymbol(const char*& s)
{
	fprintf(file ,"%p    mov eax, dword ptr ", (void*)&s);
	while ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z') || (*s >= '0' && *s <= '9')) {
		putchar(*s++);
	}
	fprintf(file, "\n");
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
}

void Convert::compileMulDiv(const char*& s)
{
	compileTerm(s);
	for (;;) {
		if (*s == '*') {
			s++;
			fprintf(file, "%p    push eax\n", (void*)&s);
			compileTerm(s);
			fprintf(file, "%p    mov  ebx, eax\n", (void*)&s);
			fprintf(file, "%p    pop  eax\n", (void*)&s);
			fprintf(file, "%p    imul ebx\n", (void*)&s);
		}
		else if (*s == '/') {
			s++;
			fprintf(file, "%p    push eax\n", (void*)&s);
			compileTerm(s);
			fprintf(file, "%p    mov  ebx, eax\n", (void*)&s);
			fprintf(file, "%p    pop  eax\n", (void*)&s);
			fprintf(file, "%p    idiv ebx\n", (void*)&s);
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
			fprintf(file, "%p    push eax\n", (void*)&s);
			compileMulDiv(s);
			fprintf(file, "%p    mov  ebx, eax\n", (void*)&s);
			fprintf(file, "%p    pop  eax\n", (void*)&s);
			fprintf(file, "%p    add  eax, ebx\n", (void*)&s);
		}
		else if (*s == '-') {
			s++;
			fprintf(file, "%p    push eax\n", (void*)&s);
			compileMulDiv(s);
			fprintf(file, "%p    mov  ebx, eax\n", (void*)&s);
			fprintf(file, "%p    pop  eax\n", (void*)&s);
			fprintf(file, "%p    sub  eax, ebx\n", (void*)&s);
		}
		else break;
	}
}

void Convert::compileExpression(const char*& s)
{
	compileAddSub(s);
}