/// \file 1.c
/*
  ------------------------------------
    Create date: 2014-05-13 01:38
    Modified date: 2014-05-15 16:19
    Author: Sen1993
    Email: 1730806439@qq.com
  ------------------------------------
*/

#include <stdio.h>
#include <string.h>

void getfail(const char str[], int arr[]){
	int i;
	int t = 0;

	arr[0] = 0;
	for(i = 1; i < strlen(str); ++i){
		while(t > 0 && str[i] != str[t]) t = arr[t];
		if(str[i] == str[t]) arr[i] = ++t;
		else arr[i] = 0;
	}
}

int main(void){
	char str[100];
	int fail[sizeof(str)/sizeof(str[0])];
	int i;

	printf("input string: ");
	scanf("%s", str);

	printf(" a[i]: ");
	for(i = 0; i < strlen(str); ++i)
		printf("%2c ",str[i]);
	getfail((const char *)str, fail);
	printf("\n f(x): ");
	for(i = 0; i < strlen(str); ++i)
		printf("%2d ", fail[i]);
	printf("\n");

	return 0;
}
