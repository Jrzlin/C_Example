//test
#include <stdio.h>
#include <stdlib.h>

void type1(void);
void type2(void);
void type3(void);
void type4(void);
void type5(void);
void rectange_interview(void);

int main()
{
	type1();
	printf("\n");
	type2();
	printf("\n");
	type3();
	printf("\n");
	type4();
	printf("\n");
	type5();
	printf("\n");
	rectange_interview();
	return 0;
}
/*
*
**
***
****
*****
*/
void type1(void)
{
	int i, j;

	for (i=1; i<=5; i++)
	{
    	for (j=1; j<=i; j++)
    	{
        	printf("*");
    	}

    	printf("\n");
	}
}

/*
*****
****
***
**
*
*/
void type2(void)
{
	int i, j;

	for (i=5; i>=1; i--)
	{
    	for (j=1; j<=i; j++)
    	{
        	printf("*");
    	}
    printf("\n");
	}
}

/*
    *
   **
  ***
 ****
*****
*/
void type3(void)
{
	int i, j;

	for (i=1; i<=5; i++)
	{ 
	    for (j=1; j<=5; j++)
	    {
	        if (j <= (5-i))
	        {
	            printf(" ");     
	        }
	        else
	        {
	            printf("*");
	        }
	    }

	    printf("\n");
	}
}


/*
*****
 ****
  ***
   **
    *
*/
void type4(void)
{
	int i, j;

	for (i=1; i<=5; i++)
	{
	    for (j=1; j<=5; j++)
	    {
	        if (j >= i)
	        {
	            printf("*");
	        }
	        else
	        {
	            printf(" ");
	        }
	    }

	    printf("\n");
	}
}

void rectange_interview(void)
{
	int a=5;
  	int b,c,d;
		for(b=a;b>=1;b--)
		{
		  for(c=b;c>=1;c--)
		  {
			printf(" ");
		  }
		  for(d=1;d<=(5-b)*2+1;d++)
		  {
			if(d%2==0)
			  printf(" ");
			else
			  printf("*");
		  }
		  printf("\n");
		}
}

/*
輸入你要的符號:$
輸入直角三角形的高:3
   $
  $$$
 $$$$$
*/
void type5(void)
{
	char i;
	int p,g,c,c2;
	printf("輸入你要的符號:");
	scanf("%c",&i);
	printf("輸入直角三角形的高:");
	scanf("%d",&g);
	for(p=g;p>=1;p--)
	{
		for(c=p;c>=1;c--)
		{
			printf(" ");
		}
		for(c2=1;c2<=(g-p)*2+1;c2++)
		{
			printf("%c",i);
		}
	printf("\n");
	}
}

