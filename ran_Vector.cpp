#include"ran_Vector.h" 
#include<stdio.h >
namespace ran{
/*------------------------------------------����Ϊ˽�к���ʵ��------------------------------------------*/
template<typename T>	void Vector<T>::expand()
{
	if( _length < _capaciity ) return;
	_capaciity > DEFAULT_CAPA ? _capaciity <<= 1 : _capaciity = DEFAULT_CAPA;//����һλ���൱�ڳ�2
	T *oldElem = _elem; _elem = new T[_capaciity];
	for(int i=0 ; i<_length ; i++)  _elem[i] = oldElem[i];
	delete [] oldElem;
}//����

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
	T *A = _elem + low ; int lb = mid -low; //B�ĳ���,length of B
	T *B = new T[lb];
	for(int i=0 ; i < lb; B[i]=A[i++]) ;
	int lc = high - mid; T *C = _elem + mid;
	for( int i = 0 ,j =0 ,k = 0 ; j<lb ;)	//���j>bc�����ʾB�Σ����Ƴ����ĶΣ������꣬��C�����ź���ģ�ֱ���˳�ѭ������
	{
		if((k < lc)&&( C[k] <  B[j] )) A[i++] = C[k++];
		if(lc <= k || (B[j] <= C[k] )) A[i++] = B[j++];
	}
	delete [] B;
}//�鲢ʵ��

template<typename T>	void Vector<T>::swap(T & A ,T & B)
{
	T  temp(1); 
	temp = A;
	A = B;
	B = temp;
}

/*------------------------------------------����Ϊ˽�к���ʵ��------------------------------------------*/

/*------------------------------------------����Ϊ�������������ʵ��------------------------------------------*/
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
/*------------------------------------------������Ϊ�������������ʵ��------------------------------------------*/

/*------------------------------------------����Ϊ��Ա����ʵ��------------------------------------------*/
template<typename T>	int Vector<T>::size()
{ return this._length; }

template<typename T>	T & Vector<T>::operator[] (int rank)
{
	return _elem[ rank ];	//Vector<T> a; a[i]��a._elem[i]һ����˼���о��е����
}

template<typename T>	T & Vector<T>::get(int rank)
{ return _elem[rank]; }//��ȡָ����λ�õ�Ԫ��

template<typename T>	void Vector<T>::put(int rank,const T & e)
{ _elem[rank] = e; return true; }//�滻ָ���ȴ���Ԫ��

template<typename T>	int Vector<T>::insert(int rank,const T & e)
{
	expand();
	for(int i = _length; i > rank ; i--)
		_elem[i]=_elem[i-1]; 	//�ոպ�length��û��Ԫ��
	_elem[rank] = e; _length++;
	return rank;
}//��ָ���ȴ�����Ԫ��

template<typename T>	int Vector<T>::insert(const T & e)
{
	return insert(_length,e);
}//��ָ���ȴ�����Ԫ��

template<typename T>	int Vector<T>::remove(int low,int high)
{ 
	if(low == high) return 0;
	while(high < _length) _elem[low++] = _elem[high++];
	_length = low;		//Low�ǵ������ֵ
	return high-low;	//����ɾ����Ԫ�ظ���
}//ɾ��ָ���ȴ���Ԫ��

template<typename T>	T& Vector<T>::remove(int rank )
{ T e = _elem[rank]; remove(rank, rank+1); return e; }

template<typename T>	int	Vector<T>::find(const T & e , int low ,int high)
{
	while((low < high--)&&(e != _elem[high])) ;
	return high;
}//����Ԫ��e������������

template<typename T>	int	Vector<T>::find(const T & e)
{
	return find(e,0,_length);
}//����Ԫ��e������������

template<typename T>	int Vector<T>::search(const T & e)
{
	//Ĭ�϶��ֲ���
}//���������У�����Ԫ��e�����������ȣ�Ĭ�ϲ��ö��ֲ���

template<typename T>	int Vector<T>::uniquify()
{
	int oldLength = _length;
	int i = 1;
	while (i < _length)
		find(_elem[i],0,i) < 0 ? i++ :remove(i );
	return _length - oldLength;
}//ȥ�أ�ȥ���������ظ���Ԫ��,Ч�ʼ���ΪO��N2��

template<typename T>	bool Vector<T>::disOrdered()
{
	int n = 0;
	for(int i = 1; i < _length ; i++ ) if( _elem[i-1]>_elem[i] ) n++;
	return n;
}//�ж������Ƿ񰴷ǽ�������

template<typename T>	void Vector<T>::sort()
{ mergeSort(0,_length); return true; }//��Ԫ�ذ��շǽ������У�Ĭ�ϲ��ù鲢����

template<typename T>	bool Vector<T>::empty()
{  
	if( _length == 0 ) return true; 
	else return false;
}

template<typename T>	void Vector<T>::mergeSort(int low, int high)
{
	if(high - low < 2) return ;	//�ݹ������ʾֻʣһ��Ԫ�ء��ض�����
	int mid = (low + high)>>1;	//ȡ��λ��
	mergeSort(low , mid);		//һ��Ϊ��
	mergeSort(mid , high);
	merge(low , mid ,high);		//�鲢
}//�鲢����

template<typename T>	int  Vector<T>::binarySeach(T const & e ,int low, int high)
{
	//if(high - low < 2 ) return low;
	//int mid = (low+high)>>1;
	//if(e < _elem[mid] ) binarySeach( e , low , mid);
	//else binarySeach( e ,mid , high);
	//return low;
	//�ݹ�治�����

	while(high-low>1)
	{
		int mid = (high + low )>>1;
		e< _elem[mid] ? high = mid : low = mid;
	}
	return e == _elem[low] ? low : -1;

}//���ֲ���

template<typename T>	int Vector<T>::bubble(int low ,int high)
{
	int last = low;
	for(int j = low;j < high; ++j)//�˴�++j����д��j++
	{
		if(_elem[j-1] > _elem[j]) 
		{
			swap(_elem[j-1],_elem[j]);
			last = j;
		}
	}
	return last; //��¼�����һ�ν�����rank��֮�����������
}

template<typename T>	void Vector<T>::bubbleSort(int low ,int high)
{
	while(low <( high = bubble(low , high) )) ;
}
/*------------------------------------------����Ϊ��Ա����ʵ��------------------------------------------*/
}