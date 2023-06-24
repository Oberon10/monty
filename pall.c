#include "monty.h"
/**
 * f_pall - Displays the element in the stack
 * @head: the top of the stack
 * @counter: not used
 * Return: void
*/
void f_pall(stack_t **head, unsigned int counter)
{
	stack_t *hd;
	(void)counter;

	hd = *head;
	if (hd == NULL)
		return;
	while (hd)
	{
		printf("%d\n", hd->n);
		hd = hd->next;
	}
}
