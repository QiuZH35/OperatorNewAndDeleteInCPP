#include <iostream>
using namespace std;

class CGirl
{
public:
	int m_xw;
	int m_bh;
	static char* m_pool;   

	static bool initpool()  //初始化内存
	{
		m_pool = (char*)malloc(18); //向系统申请18字节的内存,m_pool[0]第一片内存，m_pool[9]第二片内存
		if (m_pool == 0)return false;//如果申请失败返回false
		memset(m_pool, 0, 18);//初始化内存池
		cout << "内存池的起始地址：" << (void*)m_pool << endl;
		return true;
	}

	CGirl(int bh, int xw) { m_xw = xw, m_bh = bh, cout << "调用CGirl()构造函数" << endl; }
	~CGirl() { cout << "调用~CGirl()析构函数" << endl; }
	void* operator new(size_t size)
	{
		if (m_pool[0] == 0)
		{
			cout << "分配第一块内存池 : " << (void*)(m_pool + 1) << endl;
			m_pool[0] = 1;  //标记第一块内存池状态
			return m_pool + 1;  //返回分配的内存

		}
		if (m_pool[9] == 0)
		{
			cout << "分配第二块内存池 : " << (void*)(m_pool + 9) << endl;
			m_pool[9] = 1;  //标记第二块内存池状态
			return m_pool + 9;  //返回分配的内存

		}

		//当以上位置都不能使用时，将向系统申请
		void* ptr = malloc(size);
		cout << "申请到系统内存：" << ptr << endl;
		return ptr;
	}

	void operator delete(void* p)
	{
		
		if (p == nullptr) return;//对空指针delete是安全的。

		if (p == m_pool+1)
		{
			cout << "释放内存池第一块内存" << endl;
			m_pool[0] = 0;
			return;
		}
		if (p == m_pool + 9)
		{
			cout << "释放内存池第一块内存" << endl;
			m_pool[9] = 0;
			return;
		}
		
		free(p);
		cout << "释放系统内存" << endl;
	}

	static void freepool()
	{
		if (m_pool == 0) return;
		free(m_pool);
		cout << "内存池已释放" << endl;
	}
};

char* CGirl::m_pool = 0;//
int main()
{
	CGirl::initpool();
	CGirl* g1 = new CGirl(3, 8);
	cout << "g1=" << g1 << " 编号：" << g1->m_bh << " 胸围：" << g1->m_xw << endl;
	CGirl* g2 = new CGirl(3, 8);
	cout << "g2=" << g2 << " 编号：" << g2->m_bh << " 胸围：" << g2->m_xw << endl;
	delete g1;
	CGirl* g3 = new CGirl(3, 8);
	cout << "g3=" << g3 << " 编号：" << g3->m_bh << " 胸围：" << g3->m_xw << endl;
	CGirl* g4 = new CGirl(3, 8);
	cout << "g4=" << g4 << " 编号：" << g4->m_bh << " 胸围：" << g4->m_xw << endl;
	CGirl* g5 = new CGirl(3, 8);
	cout << "g5=" << g5 << " 编号：" << g5->m_bh << " 胸围：" << g5->m_xw << endl;
	CGirl* g6 = new CGirl(3, 8);
	cout << "g6=" << g6 << " 编号：" << g6->m_bh << " 胸围：" << g6->m_xw << endl;
	delete g2;

	delete g3;

	delete g4;
	delete g5;
	delete g6;
	CGirl::freepool();
	return 0;
}