#include "stack.h"

Stack *createStack() {
	Stack *stack = safeMalloc(sizeof(*stack));
	stack->defaultStackSize = 32;
	stack->stackPointer = -1;
	stack->items = safeMalloc(sizeof(*stack->items) * stack->defaultStackSize);
	return stack;
}

StackItem getStackItem(Stack *stack, int index) {
	if (index > stack->stackPointer) {
		errorMessage("error: could not retrieve value at index %d\n", index);
		return NULL;
	} 
	return stack->items[index];
}

void pushToStackAtIndex(Stack *stack, StackItem item, int index) {
	// much more efficient to reallocate exponentially,
	// instead of reallocating after adding an item
	if (stack->stackPointer >= stack->defaultStackSize) {
		stack->defaultStackSize *= 2;
		if (DEBUG_MODE) debugMessage("stack size expanded to: %d\n", stack->defaultStackSize);

		StackItem *tmp = realloc(stack->items, sizeof(*stack->items) * stack->defaultStackSize);
		if (!tmp) {
			perror("realloc: failed to allocate memory for stack items");
			return;
		}
		else {
			stack->items = tmp;
		}
	}
	stack->items[index] = item;
}

void pushToStack(Stack *stack, StackItem item) {
	pushToStackAtIndex(stack, item, ++stack->stackPointer);
}

StackItem popStack(Stack *stack) {
	if (stack->stackPointer < 0) {
		errorMessage("error: cannot pop value from empty stack\n");
		return NULL;
	}
	return stack->items[stack->stackPointer--];
}

void destroyStack(Stack *stack) {
	free(stack->items);
	free(stack);
	debugMessage("Destroyed stack");
}
