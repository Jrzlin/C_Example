//陣列、字串、指標
#include <stdio.h>
#include <stdlib.h>
#define LENGTH 10

void arrayLength(void);
void arrayStart(void);
void towDimarray(void);
void strArray(void);

int main(void) {

	printf("Welcome to Array World\n");
	arrayStart();
    arrayLength();
    towDimarray();
    strArray();
    return 0;

}

void arrayStart(void)
{
	int iarr[LENGTH] = {0};
    int i;
    
    for(i = 0; i < LENGTH; i++) {
        printf("%d ", iarr[i]);
    }
    putchar('\n');

    for(i = 0; i < LENGTH; i++) {
        iarr[i] = i; 
    }

    for(i = 0; i < LENGTH; i++) {
        printf("%d ", iarr[i]); 
    }
    putchar('\n');
}

void arrayLength(void)
{
	int iarr[] = {1, 2, 3, 4, 5, 6};
	printf("陣列長度：%lu\n", sizeof(iarr) / sizeof(iarr[0]));
}

#define ROW 5
#define COLUMN 10
void towDimarray(void)
{
	int dimArray[ROW][COLUMN];
	int i, j;

    for(i = 0; i < ROW; i++) {
        for(j = 0; j < COLUMN; j++) {
            dimArray[i][j] = (i+1) * (j+1); 
        }
    }

    for(i = 0; i < ROW; i++) { 
        for(j = 0; j < COLUMN; j++) {
            printf("%d\t", dimArray[i][j]);
        }
        putchar('\n');    
    } 
}

void strArray(void)
{
	//char str[] = {'h', 'e', 'l', 'l', 'o', '\0'};
	char str[] = "hello"; 
  	int length = sizeof(str)/sizeof(str[0]);
 	printf("str length is : %d\n", length);
  	int i;
  	for(i = 0; i < length; i++) { 
    	if(str[i] == '\0')
      	puts("null"); 
    	else 
      	printf("%c ", str[i]); 
  	} 
  	putchar('\n');
}

//Note
/*
int irr[10] = {0}; 
double darr[10] = {0.0}; 
char carr[10] = {'\0'};

int iarr[5] = {0, 1, 2, 3, 4}; 
double darr[5] = {0.0, 0.1, 0.2, 0.3, 0.4}; 
char carr[5] = {'A', 'B', 'C', 'D', 'E'}; 

int iarr[2][3] = {{1, 2, 3}, 
                  {4, 5, 6}};

int iarr[2][3] = {1, 2, 3, 
                  4, 5, 6};

char str[] = {'h', 'e', 'l', 'l', 'o', '\0'};

空字元在作條件判斷時，會被視為0，所以上式還可以這麼寫：
if( ! str[0] ) {
    puts ("字串為空");
}

#####
char str[80];
printf("輸入字串：");
scanf("%s", str);
printf("您輸入的字串為 %s\n", str);

這個程式片段可以取得使用者的字串輸入，所輸入的字串長度不得超過80個字元，80個字元的上限包括空白字元，所以實際上可以輸入79個字元；如果輸入的 字元超出所宣告的上限，會發生不可預期的錯誤。 

在使用scanf()取得使用者輸入的字串時，格式指定字是使用%s，而變數前不用再加上&，因為實際上，字串（字元陣列）變數名稱本 身，即表示記憶體位址資訊。

要指定新的字串值給它時，您不能像下面的方式指定： 
char str[80]; 
str = "Just";

而必須要一個字元一個字元的指定至陣列中，並在最後加上空白字元，例如： 
char str[80] = {'\0'}; 
str[0] = 'J'; 
str[1] = 'u'; 
str[2] = 's'; 
str[3] = 't'; 
str[4] = '\0'; 
puts(str);

##
字串處理


*/