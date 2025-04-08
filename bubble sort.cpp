#include<stdio.h>
void bubbleSort(int arr[],int n){
	for(int i = 0;i<n-1;i++){
		for(int j = 0;j<n-1;j++){
			if(arr[j] > arr[j+1]){
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}
int main(){
	int arr[] = {2,4,98,48,12,62,11,90};
	int n = sizeof(arr)/sizeof(arr[0]);
	bubbleSort(arr,n);
	printf("Bubble Sort: \n");
	for(int i=0;i<n;i++){
		printf("%d\n",arr[i]);
	}
	getchar();
	getchar();
	return 0;
}
