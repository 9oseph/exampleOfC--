#include "stdafx.h"

void constCast(const int &nParam)
{
	// 상수형 참조였으나 일반 참조로 형 변환 했다.
	// const_cast<새 형식>(대상)
	int &nNewParam = const_cast<int &>(nParam);
	nNewParam = 20;
}

void constCastCaller()
{
	int nData = 10;

	constCast(nData);
	cout << nData << endl;
}

// 정적 멤버
// 인스턴스를 생성하지 않아도 호출할 수 있는 함수 
// 전역함수를 만드려고 하는 경향이 있다. 그러나 좋은 선택이 아니다.

// 변수든 함수든 '정적 멤버'는 사실상 전역 변수나 함수와 같다. 단지 클래스의 멤버로 들어왔을 뿐
// 정적 멤버 함수는 this 포인터를 쓸 수 없고, 정적 변수는 반드시 선언과 정의를 분리해야 한다.

class staticMember
{
private:
	int m_nData;
	static int m_nCount; // 정적 멤버 변수 선언(정의는 아니다!)

public:
	staticMember(int nParam) : m_nData(nParam) { m_nCount++; }
	int GetData() { return m_nData; }
	void ResetCount() { m_nCount = 0; }

	// 정적 멤버 메서드 선언 및 정의 
	static int GetCount()
	{
		return m_nCount;
	}
};

// staticMember 클래스의 정적 멤버 변수 정의
int staticMember::m_nCount = 0;

void staticMemberCaller()
{
	staticMember a(5), b(10);

	// 정적 멤버에 접근
	cout << a.GetCount() << endl;
	b.ResetCount();

	cout << staticMember::GetCount() << endl;
}





