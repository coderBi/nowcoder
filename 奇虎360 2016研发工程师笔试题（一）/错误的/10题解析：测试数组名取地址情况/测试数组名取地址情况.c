#include <stdio.h>

int main(){ //通过分析，arr arr[0] &arr地址都是相同的，但是由于类型存在不同 arr + 1 是在 arr的基础上偏移一个int长度。
			 //&arr 类型是 int** , &arr + 1, 是在&arr的基础上移动 （int* 所指向的数组长度的）。所以下面 &arr + 1 实际是移动到了 arr + 6 的位置。
	int arr[] = {1,2,3,4,5,6};
	printf("arr: %d\n", arr);
	printf("&arr[0]: %d\n", &arr[0]);
	printf("&arr: %d\n", &arr);
	printf("arr + 1 : %d\n", arr + 1);
	printf("&arr + 1 : %d\n", &arr +1);
	return 0;
}