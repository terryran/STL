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
	//容量，大小，数据区

protected:

	int bubble(int low ,int high);					//冒泡
	bool copyFrom(T const * A,int low,int high);	//内部拷贝
	void expand();									//扩容
	void merge(int low , int  mid ,int high );		//归并
	void swap(T &A ,T &B);							//交换
	
public:

	Vector();										//默认构造函数
	Vector(int c);									//初始最大容量
	Vector(const T * A,int low,int high);			//数组构造向量
	Vector(Vector<T> const & A,int low,int high);	//拷贝构造函数,从low到high
	Vector(Vector<T> const & A);					//拷贝构造函数
	~Vector();										//默认析构函数
	
	T & operator[](int rank);						//重载[]，方便访问元素
	T & get(int rank);								//获取指定秩位置的元素	
	T & remove(int rank);							//删除指定秩处的元素

	int	size();										//返回长度
	int insert(int rank,const T & e);				//在指定秩处插入元素
	int insert(const T & e);						//在最后一处插入元素
	int remove(int low, int high);					//删除指定指定区间的元素
	int	find(const T & e);							//查找元素e，返回他的秩
	int find(const T & e,int low ,int high);		//在指定区间内查找元素e，返回他的秩
	int search(const T & e);						//有序向量中，搜索元素e，返回他的秩
	int uniquify();									//去重，去除向量中重复的元素
	int binarySeach(T const & e,int low,int high);	//二分查找

	void bubbleSort(int low , int high);			//冒泡排序
	void mergeSort(int low, int high);				//归并排序
	void put(int rank,const T & e);					//替换指定秩处的元素
	void sort();									//将元素按照升序排列

	bool disOrdered();								//判断向量是否按非降序排列
	bool empty();									//判断是否为空
	
	
};
}//命名空间
#endif
