#include "stack.h"
#include <iostream>
using namespace std;

void push(elem*& stack, char value, int index)
{
	elem* newel = new elem;
	newel->value = value;
	newel->index = index;
	if (!stack)
	{
		stack = newel;
	}
	else
	{
		newel->next = stack;
		stack = newel;
	}
}
char* peek(elem* stack)
{
	if (!stack) return nullptr;
	return &stack->value;
}
int* peek_ind(elem* stack) {
	if (!stack) return nullptr;
	return &stack->index;
}
bool pop(elem*& stack, char& value, int index)
{
	if (!stack) return false;
	elem* rem = stack;
	value = stack->value;
	index = stack->index;
	stack = stack->next;
	delete rem;
	return true;
}
bool clear(elem*& stack)
{
	while (stack)
	{
		elem* rem = stack;
		stack = stack->next;
		delete rem;
	}
	return 1;
}
bool open_bracket(char symbol) {
	return symbol == '(' || symbol == '{' || symbol == '[' || symbol == '<';
}
bool closing_bracket(char symbol) {
	return symbol == ')' || symbol == '}' || symbol == ']' || symbol == '>';
}
char getOpenBracketPair(char bracket) {
	return (bracket == '}') ? '{' : (bracket == ')') ? '(' :
		(bracket == ']') ? '[' : (bracket == '>') ? '<' : '\0';
}
void checking_brackets(elem* stack, char* dec_str, int& first_ind, int& second_ind) {
	bool flag = true;
	for (int i = 0; i < strlen(dec_str); i++) {
		if (open_bracket(dec_str[i])) {
			push(stack, dec_str[i], i);
		}
		else {
			if (closing_bracket(dec_str[i])) {
				char open_brack = getOpenBracketPair(dec_str[i]);
				char val;
				if (peek(stack) && *peek(stack) == open_brack) {
					pop(stack, open_brack, i);
				}
				else {
					int ind = -1;
					flag = false;
					if (peek_ind(stack)) {
						ind = *peek_ind(stack);
					}
					first_ind = ind;
					second_ind = i;
					break;

				}
			}
		}
	}
	if (peek(stack)) {
		first_ind = *peek_ind(stack);
		flag = false;
	}
	if (flag) {
		first_ind = -1;
		second_ind = -1;
	}
}