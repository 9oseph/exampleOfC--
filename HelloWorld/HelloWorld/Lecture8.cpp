#include "stdafx.h"

// 수평적 관계와 집합 관계

// 1. friend 함수 및 클래스 : 클래스에서 선언하는 접근제어 지시자의 영향을 받지 않도록 함.
//							 기존 클래스와 클래스 상속 관계에 영향을 받지 않고 새로운 관계를 형성할 수 있다.
// 2. 집합 관계 : friend 함수와 클래스 선언을 이용해서 각 요소를 의미에 따라 묶는 구조화

// ==> 클래스와 객체를 효율적으로 사용하는 방법

class friendFunc
{
private:
	int m_nData = 0;
public:
	friendFunc(int nParam) : m_nData(nParam) { }
	int GetData() const { return m_nData; }
	void SetData(int nParam) { m_nData = nParam; }
	void print(const friendFunc &rData) { cout << m_nData << endl; }

	// friend 함수로 선언한다. 
	friend void PrintData(const friendFunc &);
};

// 전역 함수로 friendFunc 와는 무관하다.
void PrintData(const friendFunc &rData)
{
	// 프렌드 함수이므로 접근제어 지시자의 영향을 받지 않고 
	// private 멤버에 직접 접근한다.
	cout << "PrintData(): " << rData.m_nData << endl;
}

void friendFuncCaller()
{
	friendFunc a(5);
	PrintData(a);
}

// 서로 관련 없는 것들은 완전히 무관하게 설계
// 반대로 따로 떨어진 것이라도 관련이 깊다면 거의 한 덩어리에 준 하도록 묶어주는 것

// 8.1.3 friend class

class CNode
{
	// friend 클래스 선언 
	friend class CMyList;

private:
	// 단일 연결 리스트로 관리할 데이터
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
		// 리스트에 담긴 데이터들을 모두 출력하고 삭제
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

		// 리스트에 새로운 노드를 추가 
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

// 8.2 집합 관계

// 클래스의 관계 
// 상속 관계, 친구 관계, 매개변수 혹은 반환 형식으로 사용되는 관계, 집합 관계
// 집합 관계 ; 여럿이 모여 새로운 하나를 이루는 경우
// 1. composition ; '구성 요소들' 새로만든 형식의 인스턴스가 소멸할 때 구성 요소들도 함께 소멸
// 2. aggregation ; 모두 모여 하나의 시스템을 이루지만 각각 개별적으로 분리되어 독립적으로 활용가능, 소멸되지 않음

// ==> "모여서 뗄 수 없는 한 덩어리를 이루는가 아니면 각자 독립적인 것들이 모여서 만들어진 분리 가능 집합체인가"

class compositionNode
{
	friend class compositionList;

private:
	// 단일 연결 리스트로 관리할 데이터
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
		// 리스트에 담긴 데이터들을 모두 출력하고 삭제
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












