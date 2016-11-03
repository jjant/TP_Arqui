/* sampleCodeModule.c */

void putc(int);
void puts(char *);

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;


int main() {
	//All the following code may be removed 
	puts("Estoy en el modulo, usando puts!");
	//Test if BSS is properly set up
	/*if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;
*/
	return 0xDEADBEEF;
}