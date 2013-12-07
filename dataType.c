#include <stdio.h>
#include <stdlib.h>

void LiteralConstant(void);
void formatSpecifier(void);
void inputMethod(void);
void inputFliter(void);
void conditionalOperator(void);
void incrementANDdecrement(void);
void nineXnine(void);
void doWhile(void);
int more(void);
void gotoLabel(void);

int main(void) {
    printf("型態\t\t大小（bytes）\n");  
	printf("short\t\t%d\n", sizeof(short)); 
	printf("int\t\t%d\n", sizeof(int));
	printf("long\t\t%d\n", sizeof(long));
	printf("float\t\t%d\n", sizeof(float));
	printf("double\t\t%d\n", sizeof(double));  
	printf("long double\t%d\n", sizeof(long double));    
	printf("char\t\t%d\n", sizeof(char));    
	LiteralConstant();
	formatSpecifier();
	conditionalOperator();
	incrementANDdecrement();
	nineXnine();
	doWhile();
	// inputFliter();
	// setbuf(stdin, NULL);/*清空缓冲区*/
	// inputMethod();

	return 0;

}
void LiteralConstant(void)
{
	printf("26 -> %d\n", 26);
	printf("032 8進位-> %d\n", 032);
	printf("0x1A 16進位 ->%d\n", 0x1A);
//八進位ASCII碼如'\062'則是字元'2'，十六進位ASCII碼如"\x48"為字元'H'，一個輸出的例子如下所示，以十六進位ASCII碼顯示"2 個HELLO"：
	printf(" \" \062 個 \x48\x45\x4c\x4c\x4f\x21 \" \n");

}

void formatSpecifier(void)
{
    printf("顯示字元 %c\n", 'A');
	printf("顯示字元編碼 %d\n", 'A');
	printf("顯示字元編碼 %c\n", 65);    
	printf("顯示十進位整數 %d\n", 15);
	printf("顯示八進位整數 %o\n", 15);
	printf("顯示十六進位整數 %X\n", 15);
	printf("顯示十六進位整數 %x\n", 15);    
	printf("顯示科學記號 %E\n", 0.001234);    
	printf("顯示科學記號 %e\n", 0.001234);
//若在%之後指定負號，例如%-6.2f，則表示靠左對齊，沒有指定則靠右對齊
	printf("example:%6.2f\n", 19.234);
	printf("example:%-6.2f\n", 19.234);
}

void inputMethod(void)
{
	int number1, number2;
    

    printf("請輸入兩個數字，中間使用空白區隔）：");
    scanf("%d %d", &number1, &number2);
    printf("您輸入的數字：%d %d\n", number1, number2);

    setbuf(stdin, NULL);/*清空缓冲区*/

    printf("請再輸入兩個數字，中間使用-號區隔）：");
    scanf("%d-%d", &number1, &number2);
    printf("您輸入的數字：%d-%d\n", number1, number2);
}

void inputFliter(void)
{
	//scanf()還可以指定可接受的字元集合
    char str[50];
    
    printf("請輸入1到5的字元：");
    scanf("%[1-5]",str);
    printf("Input Char is %s\n",str);

    //fflush(stdin); // 清除輸入緩衝區 <---適合用於winodws
    setbuf(stdin, NULL);/*清空缓冲区*/

    printf("請輸入XYZ任一字元：");
    scanf("%[XYZ]",str);
    printf("Input Char is  %s\n", str);

    setbuf(stdin, NULL);/*清空缓冲区*/
}

//條 件式 ? 成立傳回值 : 失敗傳回值
//0x7是C中整數的16進位寫法，其實就是10進位的7，將位元與1作XOR的作用其實就是位元反轉，0x7的最右邊三個位元為1，所以其實就是反轉 ch 的最後兩個字元，如下所示：
//01000001	65 （對應 ASCII的'A'）
//00000111	0x7
//01000110	70 （對應 ASCII中的'F'）
void conditionalOperator(void)
{
	int score = 0; 

    printf("輸入學生分數："); 
    scanf("%d", &score); 
    printf("該生是否及格？%c\n", (score >= 60 ? 'Y' : 'N'));

    //XOR
    char ch = 'A'; 
    printf("before encoding：%c\n", ch);

    ch = ch^0x7; 
    printf("after encoding：%c\n", ch);

    ch = ch^0x7; 
    printf("decoding：%c\n", ch);

    //Shift
    int num = 1; 

    printf("2的0次：%d\n", num);

    num = num << 1; 
    printf("2的1次：%d\n", num);

    num = num << 1; 
    printf("2的2次：%d\n", num);

    num = num << 1; 
    printf("2的3次：%d\n", num);
}

//遞增（Increment）、遞減（Decrement）、指定（Assignment）運算
//++i;      // i = i + 1; 
//--i;      // i = i - 1;
/*
您可以將遞增或遞減運算子撰寫在變數之前或變數之後，但其實兩者是有差別的，將遞增（遞減）運算子撰寫在變數前時，表示先將變數的值加（減）1，然後再傳 回變數的值，將遞增（遞減）運算子撰寫在變數之後，表示先傳回變數值，然後再對變數加（減）1，例如： 
int i = 0;
int num = 0;
num = ++i;   // 相當於i = i + 1; num = i;
printf("%d\n" ,num);
num = --i;    // 相當於i = i - 1; num = i;
printf("%d\n" ,num);

在這段程式中，num的值會前後分別顯示為1與0，再看看下面這段：
int i = 0;
int num = 0;
num = i++;    // 相當於num = i; i = i + 1;
printf("%d\n", num);
num = i--;     // 相當於 num = i; i = i - 1;
printf("%d\n", num);
*/
void incrementANDdecrement(void)
{
	int i = 0;
	int num = 0;
	num = ++i;   // 相當於i = i + 1; num = i;
	printf("%d\n" ,num);
	num = --i;    // 相當於i = i - 1; num = i;
	printf("%d\n" ,num);

	printf("--------------\n");

	i = 0;
	num = 0;
	num = i++;    // 相當於num = i; i = i + 1;
	printf("%d\n", num);
	num = i--;     // 相當於 num = i; i = i - 1;
	printf("%d\n", num);
}

void nineXnine(void)
{
    int i, j, tmp;
    for(j = 1; j < 10; j++) { 
        for(i = 2; i < 10; i++) { 
            tmp = i * j; 
            printf("%d*%d=%2d ", i, j, tmp);
        } 
        puts("");
    } 
}

//while loop
void doWhile(void)
{
	int input;
	do { 
   		printf("輸入整數值："); 
   		scanf("%d", &input); 
   		printf("輸入數為奇數？%c\n", ((input % 2) ? 'Y': 'N')); 
	} while(more());
}

int more(void)
{
	int replay;
	printf("繼續(1:繼續 0:結束)？"); 
    scanf("%d", &replay);
    return replay;
}

//goto label
void gotoLabel(void)
{
	int input = 0; 

begin: 
    printf("輸入一數："); 
    scanf("%d", &input); 

    if(input == 0) 
        goto error; 

    printf("100 / %d = %f\n", input, (double) 100 / input);
    
    return 0;
    
error: 
    puts("除數不可為 0"); 
    goto begin;
}


