//String Know how
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void stringLength(void);
void stringCopy(void);
void stringCat(void);
void stringCmp(void);
void stringSearch(void);
void stringSpn(void);
char *searchStrOnString(char *s,char c);
void StringCheck(void);

int main(int argc,char *argv[])
{
	// stringLength();
	// stringCopy();
	// stringCat();
	// stringCmp();
	// stringSearch();
	// stringSpn();
	StringCheck();

	char source[] = "Rome was not built in a day.";
	char search = 'k';
	char *result;
	result = searchStrOnString(source,search);
	printf("=> %s\n", result);
	return 0;
}

void stringLength(void)
{
	char input[80];
	char try[] = "qazxswedc";
    size_t length;
	
    puts("請輸入字串...");
    gets(input);
	
    length = strlen(input);
	
    printf("字串長度：%u\n", length);
    printf("try字串長度：%u\n", strlen(try));
}
//Notes/////////////////
/*
在 字串（字 元陣 列） 中說過，在C語言中，字串是一個字元陣列，最後一個字元以空字元'\0'作結尾，
若要得知字串所含字元長度（不包括空字元），則可以使用strlen()函式：
size_t strlen(const char*);

size_t是unsigned型態，在大部份系統是定義為unsigned int，
但在64位元系統中可以是unsigned long。strlen()會傳回字元陣列中第一個字元(Str[0])至空字元的長度值"減1：
*/

void stringCopy()
{
    char input[80];
    char tmp[80];
	
    puts("請輸入字串...");
    scanf("%s",input);
	
    strcpy(tmp, input);
    printf("複製整個字串：%s\n", tmp);

    // 重設所有字元為空字元
    memset(tmp, '\0', sizeof(tmp));
    strncpy(tmp, input, 4);
    printf("複製部份字串：%s\n", tmp);
}
/* Notes
如果要進行字串複製，可以使用strcpy()函式，若要複製字串中若干字元內容，則可以使用strncpy()：
char* strcpy(char*, const char*);
char* strncpy(char*, const char*, size_t);
*/

void stringCat(void)
{
	char str1[80] = "xyz";
    char str2[] = "abc";
	
    printf("串接前：%s\n", str1);
	
    strcat(str1, str2);
    printf("串接後：%s\n", str1);
	
    strncat(str1, str2, 2);
    printf("串接後：%s\n", str1);
}
/* Notes
若要串接兩個字串，則要使用strcat()，若要串接部份字串，則可以使用strncat()：
*/

void stringCmp(void)
{
	char password[] = "123456";
	char input_password[7];

	printf("Input your password:");
	scanf("%s",input_password);
	if(strcmp(password,input_password) == 0)
	{
		printf("Your password is right.\n");
	}else{
		printf("Your password is wrong.\n");
	}
}
/*Notes
strcmp(str1, str2)會比較字串str1與str2的大小，若相同就傳回0，str1大於str2則傳回大於0的值，小於則傳回小於0的值，
比較的標準是依字典順序 比對，例如若str1大於str2，表示str1在字典中的順序是在str2之後。
strncmp()則是比較兩個字串中指定的字元數目是否相同
*/

void stringSearch(void)
{
	char search[80];
	char source[80];
	char *loc;
	printf("Please input ur source:");
	scanf("%s",source);

	printf("Input your search word:");
	scanf("%s",search);

	loc = strstr(source,search);
	if (loc == NULL)
	{
		printf("搜尋不到符合的字串\n");
	}else{
		printf("在索引位置 %d 處找到子字串\n", loc - source);
		printf("%c\n",source[loc - source]);
	}
}
/*Notes
第一個參數是被搜尋字串，第二個參數是想要搜尋的子字串，如果沒找到子字串則傳回NULL，
如果搜尋到第一個符合的子字串，則 傳回符合位置的指標，若想要得知子字串是在哪一個索引位置，
則可以利用該指標減去字串（字元陣列）開頭的指標，得到的位移量即為符合的索引位置

strchr()函式找出字串中的指定字元第一次出現，
若找到則傳回該字元的指標，否則傳回NULL，您可以用找到的指標位置減去字串（字元陣列）開頭位址，
如此就可以得到其於字串中的索引位置，而strrchr()則是與strchr()類似，只不過它是反向搜尋：
char* strchr(const char*, int);
char* strrchr(const char*, int);
*/

void stringSpn(void)
{
	char str1[80];
    char str2[80];
    size_t loc;
	
    printf("輸入字串：");
    scanf("%s",str1);
	
    printf("搜尋子字串：");
    scanf("%s",str2);
	
    loc = strspn(str1, str2);
	
    if(loc == strlen(str1)) {
        printf("完全匹配\n");
    }
    else {
        printf("從索引位置 %d 處開始不匹配\n", loc);
    }

    //==========strcspn========
    char str3[80];
    char str4[80];
    size_t locCount;
	
    printf("輸入字串：");
    scanf("%s",str3);
	
    printf("搜尋子字串內相關的字元：");
    scanf("%s",str4);
	
    locCount = strcspn(str3, str4);
	
    if(locCount == strlen(str3)) {
        printf("沒有任何字元匹配\n");
    }
    else {
        printf("索引位置 %d 處匹配到字元\n", locCount);
    }
}
/*Notes
strspn()函式則用來比較兩個字串，找出兩個字串中開始不匹配的地方
strspn()會傳回兩個字串開始不匹配的第一個字元索引位置，否則傳回0

strcspn()函式則是找出一個字串中與另一個字串任何字元第一次匹配的索引位置，若無則傳回字串長度
*/

/* Write a subroutine that finds the last occurrence of character(c) in string(s). 
   Returns a pointer at the last occurrence of c in string s, or NULL if c is not found 
   char * strrchr(char *s,char c)  
 */
char * searchStrOnString(char *s,char c)
{
  char *searchResult;
  searchResult = strchr(s, c);
   
  while (searchResult!=NULL)
  {
  	printf("strchr Result : %s\n", searchResult);
    printf ("found at %d\n",searchResult-s+1);
    searchResult=strchr(searchResult+1,c);
  }

  char *searchLastResult;
  searchLastResult = strrchr(s,c);
  if (searchLastResult == NULL)
  {
  	printf("This character is not found\n");
  }else{
  	printf("strrchr Result : %s\n", searchLastResult);
  	printf("Found at %d\n",searchLastResult-s+1);
  }

  return searchResult;
}

void StringCheck(void)
{
	char check = '^';
	printf("It's not number or char  %c\n", isalnum(check) ? 'Y' : 'N'); 

	char check_2 = '8';
	printf("It's  number or char %c\n", isalnum(check_2) ? 'Y' : 'N');
}

/*Notes for 字串轉換
若要測試字元為數字、字母、大寫、小寫等等，可以使用ctype.h中的isxxxx()函式，例如：
isalnum(int c)：是否為字母或數字
isalpha(int c)：是否為字母
iscntrl(int c)：是否為控制字元
isdigit(int c)：是否為數字
islower(int c)：是否為小寫字母
isprint(int c)：是否為列印字元
ispunct(int c)：是否為標點符號
isspace(int c)：是否為空白
isupper(int c)：是否為大寫字母
isxdigit(int c)：是否為16進位數字
*/


