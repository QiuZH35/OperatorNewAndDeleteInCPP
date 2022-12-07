
#include <iostream>
using namespace std;
//����new��delete�������Ŀ����Ϊ���Զ����ڴ�����ϸ�ڡ����ڴ�أ����ٷ���͹黹������Ƭ��
//��C++�У�ʹ��newʱ�����������������£�
//��1�����ñ�׼�⺯��operator new()�����ڴ棻
//��2�����ù��캯����ʼ���ڴ棻
//ʹ��deleteʱ��Ҳ���������£�
//��1����������������
//��2�����ñ�׼�⺯��operator delete()�ͷ��ڴ棻
//��������������ɱ��������ã������޷����ƣ�
//�������ǿ��������ڴ���亯��operator new()��operator delete()��
// 
//�����ڴ���亯���﷨��void* operator new(size_t size) 
// ����������size_t ,����ֵ������void* (ԭ���Ƿ�����ڴ滹û�ж���������)
// 
//�����ڴ��ͷź����﷨��void operator delete(void* ptr)
//����������void* (ָ����operator new()���ٵ��ڴ�)������ֵ������void (��������û�з���ֵ)
//
//���ص�new ��delete ������ȫ�ֺ�����Ҳ���������Ա����
//Ϊ���Ա��������ʱ�����ܲ���ʾʹ��static����ʵ�������ڴ���static��Ա������
//����������ʹ��new �����Զ�����Ķ���ʱ��������ѡ�����Ա���غ����汾������ȫ�ְ汾��


class CGirl1
{
public :
	int m_xw;
	int m_bh;
	CGirl1(int bh, int xw) { m_xw = xw, m_bh = bh, cout << "����CGirl()���캯��" << endl; }
	~CGirl1() { cout << "����~CGirl()��������" << endl; }
	void* operator new(size_t size)
	{
		cout << "����class����new�����ڴ�:" << size << "�ֽ�" << endl;
		void* p = malloc(size);
		if (p) {
			cout << "�ɹ������ڴ棬�ڴ��ַ��" << p << endl;
		}
		else
		{
			cout << "�ڴ����ʧ��" << endl;
		}
		return p;
	}
	void operator delete(void* p)
	{
		cout << "����class����delete����" << endl;
		if (p == nullptr) return;//�Կ�ָ��delete�ǰ�ȫ�ġ�
		free(p);

	}

};
void* operator new(size_t size)
{
	cout << "����ȫ������new�����ڴ�:"<<size<<"�ֽ�" << endl;
	void* p = malloc(size);
	if (p) {
		cout << "�ɹ������ڴ棬�ڴ��ַ��" << p << endl;
	}
	else
	{
		cout << "�ڴ����ʧ��"<< endl;
	}
	return p;
}
void operator delete(void* p)
{
	cout << "����ȫ������delete����" << endl;
	if (p == nullptr) return;//�Կ�ָ��delete�ǰ�ȫ�ġ�
	free(p);

}

int main2()
{
	int* p1 = new int(4);
	cout << "p1=" << p1 << " *p1=" << *p1 << endl;
	delete p1;

	CGirl1* g1 = new CGirl1(3, 8);
	cout << "g1=" << g1 << " ��ţ�" << g1->m_bh << " ��Χ��" << g1->m_xw << endl;
	delete g1;
	return 0;
}