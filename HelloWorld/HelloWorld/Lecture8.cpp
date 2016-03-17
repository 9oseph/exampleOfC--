#include "stdafx.h"

// ������ ����� ���� ����

// 1. friend �Լ� �� Ŭ���� : Ŭ�������� �����ϴ� �������� �������� ������ ���� �ʵ��� ��.
//							 ���� Ŭ������ Ŭ���� ��� ���迡 ������ ���� �ʰ� ���ο� ���踦 ������ �� �ִ�.
// 2. ���� ���� : friend �Լ��� Ŭ���� ������ �̿��ؼ� �� ��Ҹ� �ǹ̿� ���� ���� ����ȭ

// ==> Ŭ������ ��ü�� ȿ�������� ����ϴ� ���

class friendFunc
{
private:
	int m_nData = 0;
public:
	friendFunc(int nParam) : m_nData(nParam) { }
	int GetData() const { return m_nData; }
	void SetData(int nParam) { m_nData = nParam; }
	void print(const friendFunc &rData) { cout << m_nData << endl; }

	// friend �Լ��� �����Ѵ�. 
	friend void PrintData(const friendFunc &);
};

// ���� �Լ��� friendFunc �ʹ� �����ϴ�.
void PrintData(const friendFunc &rData)
{
	// ������ �Լ��̹Ƿ� �������� �������� ������ ���� �ʰ� 
	// private ����� ���� �����Ѵ�.
	cout << "PrintData(): " << rData.m_nData << endl;
}

void friendFuncCaller()
{
	friendFunc a(5);
	PrintData(a);
}

// ���� ���� ���� �͵��� ������ �����ϰ� ����
// �ݴ�� ���� ������ ���̶� ������ ��ٸ� ���� �� ����� �� �ϵ��� �����ִ� ��

// 8.1.3 friend class

class CNode
{
	// friend Ŭ���� ���� 
	friend class CMyList;

private:
	// ���� ���� ����Ʈ�� ������ ������
	char m_szName[32];
	CNode *pNext = nullptr;

public:
	explicit CNode(const char *pszName)
	{
		strcpy_s(m_szName, sizeof(m_szName), pszName);
	}
};

class CMyList
{
private:
	CNode m_HeadNode;

public:
	CMyList() : m_HeadNode("Dummy Head") { }
	~CMyList()
	{
		// ����Ʈ�� ��� �����͵��� ��� ����ϰ� ����
		CNode *pNode = m_HeadNode.pNext;
		CNode *pDelete = nullptr;

		while (pNode != nullptr)
		{
			pDelete = pNode;
			pNode = pNode->pNext;

			cout << pDelete->m_szName << endl;
			delete pDelete;
		}

		m_HeadNode.pNext = nullptr;
	}

	void AddNewNode(const char *pszName)
	{
		CNode *pNode = new CNode(pszName);

		// ����Ʈ�� ���ο� ��带 �߰� 
		pNode->pNext = m_HeadNode.pNext;
		m_HeadNode.pNext = pNode;
	}
};

void listCall()
{
	CMyList list;
	list.AddNewNode("joseph");
	list.AddNewNode("hyolim");
	list.AddNewNode("taiji");
}

// 8.2 ���� ����

// Ŭ������ ���� 
// ��� ����, ģ�� ����, �Ű����� Ȥ�� ��ȯ �������� ���Ǵ� ����, ���� ����
// ���� ���� ; ������ �� ���ο� �ϳ��� �̷�� ���
// 1. composition ; '���� ��ҵ�' ���θ��� ������ �ν��Ͻ��� �Ҹ��� �� ���� ��ҵ鵵 �Բ� �Ҹ�
// 2. aggregation ; ��� �� �ϳ��� �ý����� �̷����� ���� ���������� �и��Ǿ� ���������� Ȱ�밡��, �Ҹ���� ����

// ==> "�𿩼� �� �� ���� �� ����� �̷�°� �ƴϸ� ���� �������� �͵��� �𿩼� ������� �и� ���� ����ü�ΰ�"

class compositionNode
{
	friend class compositionList;

private:
	// ���� ���� ����Ʈ�� ������ ������
	char m_szName[32];
	compositionNode *pNext = nullptr;
public:
	explicit compositionNode(const char *pszName)
	{
		strcpy_s(m_szName, sizeof(m_szName), pszName);
	}
};

class compositionList
{
private:
	compositionNode m_HeadNode;

public:
	compositionList() : m_HeadNode("Dummy Head") { }
	~compositionList()
	{
		// ����Ʈ�� ��� �����͵��� ��� ����ϰ� ����
		compositionNode *pNode   = m_HeadNode.pNext;
		compositionNode *pDelete = nullptr;

		while (pNode != nullptr)
		{
			pDelete = pNode;
			cout << pDelete->m_szName << endl;

			pNode = pDelete->pNext;
			delete pDelete;
		}
	}
};












