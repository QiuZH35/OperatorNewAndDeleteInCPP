
#include <iostream>
using namespace std;
//重载new和delete运算符的目的是为了自定义内存分配的细节。（内存池：快速分配和归还，无碎片）
//在C++中，使用new时，编译器做了两件事：
//（1）调用标准库函数operator new()分配内存；
//（2）调用构造函数初始化内存；
//使用delete时，也做了两件事：
//（1）调用析构函数；
//（2）调用标准库函数operator delete()释放内存；
//构造和析构函数由编译器调用，我们无法控制，
//但是我们可以重载内存分配函数operator new()和operator delete()。
// 
//重载内存分配函数语法：void* operator new(size_t size) 
// 参数必须是size_t ,返回值必须是void* (原因是分配的内存还没有定义其类型)
// 
//重载内存释放函数语法：void operator delete(void* ptr)
//参数必须是void* (指向由operator new()开辟的内存)，返回值必须是void (析构函数没有返回值)
//
//重载的new 和delete 可以是全局函数，也可以是类成员函数
//为类成员函数重载时，尽管不显示使用static，但实际上仍在创建static成员函数。
//编译器看到使用new 创建自定义类的对象时，会优先选择类成员重载函数版本而不是全局版本。


class CGirl1
{
public :
	int m_xw;
	int m_bh;
	CGirl1(int bh, int xw) { m_xw = xw, m_bh = bh, cout << "调用CGirl()构造函数" << endl; }
	~CGirl1() { cout << "调用~CGirl()析构函数" << endl; }
	void* operator new(size_t size)
	{
		cout << "调用class重载new分配内存:" << size << "字节" << endl;
		void* p = malloc(size);
		if (p) {
			cout << "成功分配内存，内存地址：" << p << endl;
		}
		else
		{
			cout << "内存分配失败" << endl;
		}
		return p;
	}
	void operator delete(void* p)
	{
		cout << "调用class重载delete函数" << endl;
		if (p == nullptr) return;//对空指针delete是安全的。
		free(p);

	}

};
void* operator new(size_t size)
{
	cout << "调用全局重载new分配内存:"<<size<<"字节" << endl;
	void* p = malloc(size);
	if (p) {
		cout << "成功分配内存，内存地址：" << p << endl;
	}
	else
	{
		cout << "内存分配失败"<< endl;
	}
	return p;
}
void operator delete(void* p)
{
	cout << "调用全局重载delete函数" << endl;
	if (p == nullptr) return;//对空指针delete是安全的。
	free(p);

}

int main2()
{
	int* p1 = new int(4);
	cout << "p1=" << p1 << " *p1=" << *p1 << endl;
	delete p1;

	CGirl1* g1 = new CGirl1(3, 8);
	cout << "g1=" << g1 << " 编号：" << g1->m_bh << " 胸围：" << g1->m_xw << endl;
	delete g1;
	return 0;
}