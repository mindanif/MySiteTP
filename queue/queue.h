#pragma once

struct man
{
	char fullName[1024];
	char gender[1024];
	int age;
	char jobAddress[1024];
	double income;
	char purpose[1024];

};
struct elem
{
	man m;
	elem* next = nullptr;
};

struct queue
{
	elem* head = nullptr;
	elem* tail = nullptr;
	size_t size = 0;
};
void enqueue(queue& queue, const char* fullName, const char* gender, int age, const char* jobAddress, double income, const char* purpose);
bool dequeue(queue& queue, man& man);
void clear(queue& queue);
