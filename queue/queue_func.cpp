#include "queue.h"
#include <cstring>
inline man create_elem(const char* fullName, const char* gender, int age, const char* jobAddress, double income, const char* purpose)
{
	man m;
	strcpy_s(m.fullName, fullName);
	m.age = age;
	strcpy_s(m.gender, gender);
	strcpy_s(m.jobAddress, jobAddress);
	strcpy_s(m.purpose, purpose);
	m.income = income;
	return m;
}
void enqueue(queue& queue, const char* fullName, const char* gender, int age, const char* jobAddress, double income, const char* purpose)
{
	man newm = create_elem(fullName, gender, age, jobAddress, income, purpose);
	elem* newel = new elem;
	newel->m = newm;
	if (!queue.tail)
	{
		queue.head = queue.tail = newel;
	}
	else
	{
		queue.tail->next = newel;
		queue.tail = newel;
	}
	queue.size++;
}
bool dequeue(queue& queue, man& m)
{
	if (!queue.head)
		return false;
	m = queue.head->m;
	elem* rem = queue.head;
	queue.head = queue.head->next;
	delete rem;
	if (!queue.head) queue.tail = nullptr;
	queue.size--;
	return true;
}
void clear(queue& queue)
{
	while (queue.head)
	{
		elem* rem = queue.head;
		queue.head = queue.head->next;
		delete rem;
	}
	queue.size = 0;
	queue.tail = nullptr;
}