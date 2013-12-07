//Pointer Examples
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getAdressOfOperator(void);
void pointerConst(void);
void pointrOperate_PartII(void);
void pointerArray(void);
void getArrayValueFromPointer(void);

int main(int argc,char *argv[])
{
	getAdressOfOperator();
	pointerConst();
	pointrOperate_PartII();
	pointerArray();
	getArrayValueFromPointer();

	printf("Argc %d , argv[0] %s\n",argc,argv[0]);

	return 0;
}


//指標運算（Pointer arithmetic）
//int *iptr;
//float *fptr;
//char *cptr;
void getAdressOfOperator(void)
{
	//如果您想知道變數的記憶體位址為何，您可以使用&運算子，&是「取址運算子」（Address-of operator），它可以取出變數的記憶體位址
	//直接存取變數即直接對所分配到的記憶體空間作存取，指標（Pointer）則提供了間接性，指標可指向特定的記憶體位址，而不直接操作變數或物件
	int var = 10;
	printf("Variable var value is %d\n",var);
	printf("Variable var adress is %X\n",&var);

	//指標擁有兩種操作特性，一是操作指標所儲存的位址，一是操作指標所指向位址之資料，您可以使用提取 （Dereference）運算子*來提取指標所指向位址的資料
	//int *ptr;
	//ptr --> adress
	//*ptr ---> value
	int *ptr;  //宣告一個指標
	ptr = &var; //將ptr指向 var的位址
	printf("Pointer ptr adress is %X\n",ptr);
	printf("Pointer ptr adress of value is %d\n",*ptr);

	//如果已經取得了記憶體位置，當將某個值指定給*prt時，該記憶體位置的值也會跟著改變，相當於告訴程式，將值放到ptr所指向的記憶體位址
	*ptr = 20;
	printf("New Pointer ptr adress is %X\n",ptr);
	printf("New Pointer ptr adress of value is %d , var is %d\n",*ptr,var);

	//有時候，您只希望儲存記憶體的位址，然後將之與另一個記憶體位址作比較，這時並不需要關心型態的問題，您可以使用void*來宣告指標
	//由於void型態的指標沒有任何的型態資訊，所以只用來持有位址資訊，您不可以使用*運算子對void型態指標提取值，而必須作轉型動作至對應的型態
	void *vptr = &var ; 
    // 下面這句不可行，void型態指標不可取值 
    // printf("%d\n", *vptr);
 
    // 轉型為int型態指標並指定給iptr 
    int *iptr = (int*) vptr;
    printf("%d\n", *iptr);
}

void pointerConst(void)
{
	//順便來看一下const宣告的變數，被const宣告的變數一但被指定值，就不能再改變變數的值， 但是以下這樣是可以改變變數值的：
	const int var = 10;
	int *vptr = &var; //宣告一個指向INT的指標，並指到var的位址
	*vptr = 20;
	printf("%d\n", var);

	//以上的程式會顯示20，如果您不想要該記憶體位置的值被改變，則可以用const宣告指標，例如：
	//const int var_2 = 10;
	//const int *vptr_2 = &var_2;
	//*vptr_2 = 20; // error, assignment of read-only location 
}

/*

如果宣告指標但不指定初值，則指標指向的位址是未知的，存取未知位址的記憶體內容是危險的，例如：
int *ptr; 
*ptr = 10;

這個程式片段並未初始指標就指定值給*ptr，所以會造成不可預知的結果（通常是記憶體區段錯誤），
最好為指標設定初值，如果指標一開始不指向任何的位址，則可設定初值為0，表示不指向任何位址，例如：
int *iptr = 0;

在這邊必須注意一個指標宣告常犯的錯誤，在指標宣告時，可以靠在名稱旁邊，也可以靠在關鍵字旁邊，例如： 
int *ptr1; 
int* ptr2;

這兩個宣告方式都是可允許的，一般比較傾向用第一個，因為可以避免以下的錯誤：
int* prt1, ptr2;

這樣的宣告方式，初學者可能以為ptr2也是指標，但事實上並不是，以下的宣告ptr1與ptr2才都是指標：
int *ptr1, *ptr2;

//
順便來看一下const宣告的變數，被const宣告的變數一但被指定值，就不能再改變變數的值， 但是以下這樣是可以改變變數值的：
const int var = 10;
int *vptr = &var;
*vptr = 20;
printf("%d\n", var);

以上的程式會顯示20，如果您不想要該記憶體位置的值被改變，則可以用const宣告指標，例如：
const int var = 10;
const int *vptr = &var;
*vptr = 20; // error, assignment of read-only location 

另外還有指標常數，也就是您一旦指定給指標值，就不能指定新的記憶體位址值給它，例如：
int x = 10;
int y = 20;
int* const vptr = &x;
vptr = &y;  // error,  assignment of read-only variable `vptr'
*/

void pointrOperate_PartII(void)
{
	//記憶體位址的顯示單位是位元組；由於宣告的是int型態的指標，
	//所以每加1就會前進4個位元組的長度，如果您宣告的是double型態的指標，則每加 1就會前進8個位元組
	//int 4 byte , double 8 byte
	int *int_ptr = 0;

    printf("int ptr 位置：%d\n", int_ptr);
    printf("int ptr + 1：%d\n", int_ptr + 1);
    printf("int ptr + 2：%d\n", int_ptr + 2); 

    double *double_ptr = 0;

    printf("double_ptr 位置：%d\n", double_ptr);
    printf("double_ptr + 1：%d\n", double_ptr + 1);
    printf("double_ptr + 2：%d\n", double_ptr + 2);
}

#define LENGTH 10
void pointerArray(void)
{
	int array[10] = {0};

	printf("arr :\t\t%X\n", array);
    printf("&arr[0] :\t%X\n", &array[0]);

    int arr_one[LENGTH] = {0}; 
    int *ptr = arr_one; 
    int i;
    
    for(i = 0; i < LENGTH; i++) { 
        printf("&arr_one[%d]: %X", i ,&arr_one[i]); 
        printf("\t\tptr + %d: %X\n", i, ptr + i);
    } 
/*
arr :		582A5BB0
&arr[0] :	582A5BB0
&arr_one[0]: 582A5B80		ptr + 0: 582A5B80
&arr_one[1]: 582A5B84		ptr + 1: 582A5B84
&arr_one[2]: 582A5B88		ptr + 2: 582A5B88
&arr_one[3]: 582A5B8C		ptr + 3: 582A5B8C
&arr_one[4]: 582A5B90		ptr + 4: 582A5B90
&arr_one[5]: 582A5B94		ptr + 5: 582A5B94
&arr_one[6]: 582A5B98		ptr + 6: 582A5B98
&arr_one[7]: 582A5B9C		ptr + 7: 582A5B9C
&arr_one[8]: 582A5BA0		ptr + 8: 582A5BA0
&arr_one[9]: 582A5BA4		ptr + 9: 582A5BA4
*/
}

//利用指標運算來取出陣列的元素值
void getArrayValueFromPointer(void)
{
	int arr[5] = {10,20,30,40,50};
	int *ptr = arr; // or int *ptr = &arr[0]
	for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
	{
		printf("arr[%d]=%d\n",i,*(ptr+i));
	}
	putchar('\n');

    // 以陣列方式存取資料 
    for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        printf("ptr[%d]: %d\n", i, ptr[i]);
    }
    putchar('\n');

    // 以指標方式存取資料 
    for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        printf("*(arr + %d): %d\n", i , *(arr + i));
    }
    putchar('\n');
 
    // 以陣列方式存取資料 
    // 以陣列方式存取資料 
    for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        printf("arr[%d]: %d\n", i, arr[i]);
    }
    putchar('\n');

}

