#ifndef _RAN_VECTOR_H
#define _RAN_VECTOR_H
namespace ran{

#define DEFAULT_CAPA 500

template <class T>
class Vector{

private:

	int _capaciity; 
	int _length;
	T*  _elem;
	//��������С��������

protected:

	int bubble(int low ,int high);					//ð��
	bool copyFrom(T const * A,int low,int high);	//�ڲ�����
	void expand();									//����
	void merge(int low , int  mid ,int high );		//�鲢
	void swap(T &A ,T &B);							//����
	
public:

	Vector();										//Ĭ�Ϲ��캯��
	Vector(int c);									//��ʼ�������
	Vector(const T * A,int low,int high);			//���鹹������
	Vector(Vector<T> const & A,int low,int high);	//�������캯��,��low��high
	Vector(Vector<T> const & A);					//�������캯��
	~Vector();										//Ĭ����������
	
	T & operator[](int rank);						//����[]���������Ԫ��
	T & get(int rank);								//��ȡָ����λ�õ�Ԫ��	
	T & remove(int rank);							//ɾ��ָ���ȴ���Ԫ��

	int	size();										//���س���
	int insert(int rank,const T & e);				//��ָ���ȴ�����Ԫ��
	int insert(const T & e);						//�����һ������Ԫ��
	int remove(int low, int high);					//ɾ��ָ��ָ�������Ԫ��
	int	find(const T & e);							//����Ԫ��e������������
	int find(const T & e,int low ,int high);		//��ָ�������ڲ���Ԫ��e������������
	int search(const T & e);						//���������У�����Ԫ��e������������
	int uniquify();									//ȥ�أ�ȥ���������ظ���Ԫ��
	int binarySeach(T const & e,int low,int high);	//���ֲ���

	void bubbleSort(int low , int high);			//ð������
	void mergeSort(int low, int high);				//�鲢����
	void put(int rank,const T & e);					//�滻ָ���ȴ���Ԫ��
	void sort();									//��Ԫ�ذ�����������

	bool disOrdered();								//�ж������Ƿ񰴷ǽ�������
	bool empty();									//�ж��Ƿ�Ϊ��
	
	
};
}//�����ռ�
#endif
