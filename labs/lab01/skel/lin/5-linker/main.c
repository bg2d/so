/**
 * SO, 2016
 * Lab #1, Introduction
 *
 * Task #3-karma, Linux
 *
 * Having fun with link-time & run-time
 */
int str(void);

/* The above declaration defines a symbol to a function 
 * named str. In str.c is declared a char pointer to a 
 * string, named std. A funciton call is a jump and 
 * execute to an address indicated by a pointer. 
 * A function name is a pointer to the first funciton's 
 * instruction. At link time the linker verifies that there 
 * is a definition for str() function, but at run-time, when 
 * the function is called the execution jumps at the address 
 * pointed by str pointer, which points to "SO" string 
 * which is a memory location in .data segment -> segmentation 
 * fault.
 * */

int main(void)
{
	str();

	return 0;
}
