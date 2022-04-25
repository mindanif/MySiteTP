#pragma once
struct elem
{
	char value;
	int index;
	elem* next = nullptr;
};
void push(elem*& stack, char value, int index);
bool pop(elem*& stack, char& value, int index);
char* peek(elem* stack);
int* peek_ind(elem* stack);
bool clear(elem*& stack);
bool open_bracket(char symbol);
bool closing_bracket(char symbol);
char getOpenBracketPair(char bracket);
void checking_brackets(elem* stack, char* dec_str, int& first_ind, int& second_ind);