#include "stdafx.h"

void constCast(const int &nParam)
{
	// ����� ���������� �Ϲ� ������ �� ��ȯ �ߴ�.
	// const_cast<�� ����>(���)
	int &nNewParam = const_cast<int &>(nParam);
	nNewParam = 20;
}

void constCastCaller()
{
	int nData = 10;

	constCast(nData);
	cout << nData << endl;
}

// ���� ���
// �ν��Ͻ��� �������� �ʾƵ� ȣ���� �� �ִ� �Լ� 
// �����Լ��� ������� �ϴ� ������ �ִ�. �׷��� ���� ������ �ƴϴ�.

// ������ �Լ��� '���� ���'�� ��ǻ� ���� ������ �Լ��� ����. ���� Ŭ������ ����� ������ ��
// ���� ��� �Լ��� this �����͸� �� �� ����, ���� ������ �ݵ�� ����� ���Ǹ� �и��ؾ� �Ѵ�.

class staticMember
{
private:
	int m_nData;
	static int m_nCount; // ���� ��� ���� ����(���Ǵ� �ƴϴ�!)

public:
	staticMember(int nParam) : m_nData(nParam) { m_nCount++; }
	int GetData() { return m_nData; }
	void ResetCount() { m_nCount = 0; }

	// ���� ��� �޼��� ���� �� ���� 
	static int GetCount()
	{
		return m_nCount;
	}
};

// staticMember Ŭ������ ���� ��� ���� ����
int staticMember::m_nCount = 0;

void staticMemberCaller()
{
	staticMember a(5), b(10);

	// ���� ����� ����
	cout << a.GetCount() << endl;
	b.ResetCount();

	cout << staticMember::GetCount() << endl;
}





