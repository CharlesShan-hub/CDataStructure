typedef int ElemType;

typedef struct{
	ElemType *elem;
	int TableLen;
}SSTable;

//折半查找
int Binary_Search(SSTable L,EleType key){
	int low=0, high=L.TableLen-1,mid;
	while(low<=high){
		mid = (low+high)/2;
		if(L.elem[mid]==key)
			return mid;
		else if(L.elem[mid]>key)
			high = mid-1;
		else
			low = mid+1;
	}
	return -1;
}
