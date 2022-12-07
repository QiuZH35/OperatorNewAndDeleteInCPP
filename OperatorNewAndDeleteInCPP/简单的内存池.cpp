#include <iostream>
using namespace std;

class CGirl
{
public:
	int m_xw;
	int m_bh;
	static char* m_pool;   

	static bool initpool()  //��ʼ���ڴ�
	{
		m_pool = (char*)malloc(18); //��ϵͳ����18�ֽڵ��ڴ�,m_pool[0]��һƬ�ڴ棬m_pool[9]�ڶ�Ƭ�ڴ�
		if (m_pool == 0)return false;//�������ʧ�ܷ���false
		memset(m_pool, 0, 18);//��ʼ���ڴ��
		cout << "�ڴ�ص���ʼ��ַ��" << (void*)m_pool << endl;
		return true;
	}

	CGirl(int bh, int xw) { m_xw = xw, m_bh = bh, cout << "����CGirl()���캯��" << endl; }
	~CGirl() { cout << "����~CGirl()��������" << endl; }
	void* operator new(size_t size)
	{
		if (m_pool[0] == 0)
		{
			cout << "�����һ���ڴ�� : " << (void*)(m_pool + 1) << endl;
			m_pool[0] = 1;  //��ǵ�һ���ڴ��״̬
			return m_pool + 1;  //���ط�����ڴ�

		}
		if (m_pool[9] == 0)
		{
			cout << "����ڶ����ڴ�� : " << (void*)(m_pool + 9) << endl;
			m_pool[9] = 1;  //��ǵڶ����ڴ��״̬
			return m_pool + 9;  //���ط�����ڴ�

		}

		//������λ�ö�����ʹ��ʱ������ϵͳ����
		void* ptr = malloc(size);
		cout << "���뵽ϵͳ�ڴ棺" << ptr << endl;
		return ptr;
	}

	void operator delete(void* p)
	{
		
		if (p == nullptr) return;//�Կ�ָ��delete�ǰ�ȫ�ġ�

		if (p == m_pool+1)
		{
			cout << "�ͷ��ڴ�ص�һ���ڴ�" << endl;
			m_pool[0] = 0;
			return;
		}
		if (p == m_pool + 9)
		{
			cout << "�ͷ��ڴ�ص�һ���ڴ�" << endl;
			m_pool[9] = 0;
			return;
		}
		
		free(p);
		cout << "�ͷ�ϵͳ�ڴ�" << endl;
	}

	static void freepool()
	{
		if (m_pool == 0) return;
		free(m_pool);
		cout << "�ڴ�����ͷ�" << endl;
	}
};

char* CGirl::m_pool = 0;//
int main()
{
	CGirl::initpool();
	CGirl* g1 = new CGirl(3, 8);
	cout << "g1=" << g1 << " ��ţ�" << g1->m_bh << " ��Χ��" << g1->m_xw << endl;
	CGirl* g2 = new CGirl(3, 8);
	cout << "g2=" << g2 << " ��ţ�" << g2->m_bh << " ��Χ��" << g2->m_xw << endl;
	delete g1;
	CGirl* g3 = new CGirl(3, 8);
	cout << "g3=" << g3 << " ��ţ�" << g3->m_bh << " ��Χ��" << g3->m_xw << endl;
	CGirl* g4 = new CGirl(3, 8);
	cout << "g4=" << g4 << " ��ţ�" << g4->m_bh << " ��Χ��" << g4->m_xw << endl;
	CGirl* g5 = new CGirl(3, 8);
	cout << "g5=" << g5 << " ��ţ�" << g5->m_bh << " ��Χ��" << g5->m_xw << endl;
	CGirl* g6 = new CGirl(3, 8);
	cout << "g6=" << g6 << " ��ţ�" << g6->m_bh << " ��Χ��" << g6->m_xw << endl;
	delete g2;

	delete g3;

	delete g4;
	delete g5;
	delete g6;
	CGirl::freepool();
	return 0;
}