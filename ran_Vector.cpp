#include"ran_Vector.h" 
#include<stdio.h >
namespace ran{
/*------------------------------------------以下为私有函数实现------------------------------------------*/
template<typename T>	void Vector<T>::expand()
{
	if( _length < _capaciity ) return;
	_capaciity > DEFAULT_CAPA ? _capaciity <<= 1 : _capaciity = DEFAULT_CAPA;//左移一位，相当于成2
	T *oldElem = _elem; _elem = new T[_capaciity];
	for(int i=0 ; i<_length ; i++)  _elem[i] = oldElem[i];
	delete [] oldElem;
}//扩容

template<typename T>	bool Vector<T>::copyFrom(T const * A,int low,int high)
{
	_elem = new T[ _capaciity = 2*(high-low) ];
	_length = 0;
	while (low < high)
		_elem[ _length++] = A[low++]; 
	return true;
}

template<typename T>	void Vector<T>::merge(int low , int  mid ,int high )
{
	T *A = _elem + low ; int lb = mid -low; //B的长度,length of B
	T *B = new T[lb];
	for(int i=0 ; i < lb; B[i]=A[i++]) ;
	int lc = high - mid; T *C = _elem + mid;
	for( int i = 0 ,j =0 ,k = 0 ; j<lb ;)	//如果j>bc，则表示B段（复制出来的段）已走完，而C段是排好序的，直接退出循环即可
	{
		if((k < lc)&&( C[k] <  B[j] )) A[i++] = C[k++];
		if(lc <= k || (B[j] <= C[k] )) A[i++] = B[j++];
	}
	delete [] B;
}//归并实现

template<typename T>	void Vector<T>::swap(T & A ,T & B)
{
	T  temp(1); 
	temp = A;
	A = B;
	B = temp;
}

/*------------------------------------------以上为私有函数实现------------------------------------------*/

/*------------------------------------------以下为构造和析构函数实现------------------------------------------*/
template<typename T>	Vector<T>::Vector()
{
	_elem = new T[ _capaciity = DEFAULT_CAPA ];
	_length = 0;
}

template<typename T>	Vector<T>::Vector(int c)
{
	_elem = new T[ _capaciity = c ];
	_length = 0;
}

template<typename T>	Vector<T>::Vector(const T * A,int low,int high)
{
	copyFrom(A,low,high);
}

template<typename T>	Vector<T>::Vector(Vector<T> const & A,int low,int high)
{
	copyFrom(A._elem , low , high);
}

template<typename T>	Vector<T>::Vector(Vector<T> const & A)
{
	copyFrom(A._elem , 0 , A._length);
}

template<typename T>	Vector<T>::~Vector()
{
	delete [] _elem;	
}			
/*------------------------------------------以以上为构造和析构函数实现------------------------------------------*/

/*------------------------------------------以下为成员函数实现------------------------------------------*/
template<typename T>	int Vector<T>::size()
{ return this._length; }

template<typename T>	T & Vector<T>::operator[] (int rank)
{
	return _elem[ rank ];	//Vector<T> a; a[i]和a._elem[i]一个意思。感觉有点奇怪
}

template<typename T>	T & Vector<T>::get(int rank)
{ return _elem[rank]; }//获取指定秩位置的元素

template<typename T>	void Vector<T>::put(int rank,const T & e)
{ _elem[rank] = e; return true; }//替换指定秩处的元素

template<typename T>	int Vector<T>::insert(int rank,const T & e)
{
	expand();
	for(int i = _length; i > rank ; i--)
		_elem[i]=_elem[i-1]; 	//刚刚好length处没有元素
	_elem[rank] = e; _length++;
	return rank;
}//在指定秩处插入元素

template<typename T>	int Vector<T>::insert(const T & e)
{
	return insert(_length,e);
}//在指定秩处插入元素

template<typename T>	int Vector<T>::remove(int low,int high)
{ 
	if(low == high) return 0;
	while(high < _length) _elem[low++] = _elem[high++];
	_length = low;		//Low是递增后的值
	return high-low;	//返回删除的元素个数
}//删除指定秩处的元素

template<typename T>	T& Vector<T>::remove(int rank )
{ T e = _elem[rank]; remove(rank, rank+1); return e; }

template<typename T>	int	Vector<T>::find(const T & e , int low ,int high)
{
	while((low < high--)&&(e != _elem[high])) ;
	return high;
}//查找元素e，返回他的秩

template<typename T>	int	Vector<T>::find(const T & e)
{
	return find(e,0,_length);
}//查找元素e，返回他的秩

template<typename T>	int Vector<T>::search(const T & e)
{
	//默认二分查找
}//有序向量中，搜索元素e，返回他的秩，默认采用二分查找

template<typename T>	int Vector<T>::uniquify()
{
	int oldLength = _length;
	int i = 1;
	while (i < _length)
		find(_elem[i],0,i) < 0 ? i++ :remove(i );
	return _length - oldLength;
}//去重，去除向量中重复的元素,效率极地为O（N2）

template<typename T>	bool Vector<T>::disOrdered()
{
	int n = 0;
	for(int i = 1; i < _length ; i++ ) if( _elem[i-1]>_elem[i] ) n++;
	return n;
}//判断向量是否按非降序排列

template<typename T>	void Vector<T>::sort()
{ mergeSort(0,_length); return true; }//将元素按照非降序排列，默认采用归并排序

template<typename T>	bool Vector<T>::empty()
{  
	if( _length == 0 ) return true; 
	else return false;
}

template<typename T>	void Vector<T>::mergeSort(int low, int high)
{
	if(high - low < 2) return ;	//递归基，表示只剩一个元素。必定有序
	int mid = (low + high)>>1;	//取中位数
	mergeSort(low , mid);		//一分为二
	mergeSort(mid , high);
	merge(low , mid ,high);		//归并
}//归并排序

template<typename T>	int  Vector<T>::binarySeach(T const & e ,int low, int high)
{
	//if(high - low < 2 ) return low;
	//int mid = (low+high)>>1;
	//if(e < _elem[mid] ) binarySeach( e , low , mid);
	//else binarySeach( e ,mid , high);
	//return low;
	//递归版不够灵活

	while(high-low>1)
	{
		int mid = (high + low )>>1;
		e< _elem[mid] ? high = mid : low = mid;
	}
	return e == _elem[low] ? low : -1;

}//二分查找

template<typename T>	int Vector<T>::bubble(int low ,int high)
{
	int last = low;
	for(int j = low;j < high; ++j)//此处++j不可写成j++
	{
		if(_elem[j-1] > _elem[j]) 
		{
			swap(_elem[j-1],_elem[j]);
			last = j;
		}
	}
	return last; //记录下最后一次交换的rank，之后的序列有序。
}

template<typename T>	void Vector<T>::bubbleSort(int low ,int high)
{
	while(low <( high = bubble(low , high) )) ;
}
/*------------------------------------------以上为成员函数实现------------------------------------------*/
}