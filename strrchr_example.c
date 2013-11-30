/* Write a subroutine that finds the last occurrence of character(c) in string(s). 
   Returns a pointer ti the last occurrence of c in string s, or NULL if c is not found 
   char * strrchr(char *s,char c)  
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
char *searchCharOnString(char *s,char c);
 
int main(int argc,char *argv[])
{
	char source[] = "Rome was not built in a day.";
	char search = 'a';
	char *result;
	result = strrchr(source,search);
	printf("Result => %s\n", result);
	return 0;
}
 
char * strrchr(char *s,char c)
{
  char *searchLastResult;
  searchLastResult = strrchr(s,c);
  if (searchLastResult == NULL)
  {
  	printf("This character is not found\n");
  }else{
  	printf("strrchr Result : %s\n", searchLastResult);
  	printf("Found at %d\n",searchLastResult-s+1);
  }
}