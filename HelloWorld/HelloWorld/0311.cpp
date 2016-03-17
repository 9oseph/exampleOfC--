#include "stdafx.h"

// 임시객체 : 존재 파악

// 수(자료) 변수 
//          상수 
// ==> instance 라는 표현

//int a = 3 + 4; // 임시 결과 7은 상수 instance, 생명주기? 단순대입 연산이 끝나고

// 상속 ; 시간의 흐름을 생각해야... 설계...

// r-value 참조
// 

// 복사 생성자
// + 단순 대입 연산자
// ==> 깊은 복사

// 생성자 
// 1. 디폴트 생성자 ; 호출되는 시점, 조건이 중요 
// 2. 변환 생성자(언어 스펙에는 이 말이 없다. 매개 변수가 1개인 생성자)
// 3. 복사 생성자 ; 언제 호출되는가? 함수 호출시 매개변수 복사, 반환형식이 클래스인경우
// 4. 이동 생성자 ; r-value 가 임시 객체일때(곧 사라질 객체) 호출, 임시객체 문제 때문에 등장
//				   + 단순 대입 연산자(&& 활용)

// 이정훈 모의해킹 

class CMyData
{
public:
	CMyData() { }
	~CMyData() { }

	int GetData() const 
	{
		return m_nData;
	}

	void SetData(int nParam)
	{
		m_nData = nParam;
	}

	CMyData(int nParam) : m_nData(nParam) { }

	///////////////////
	// 허용되는 변환
	//operator int(void) { return m_nData; }                                                                                                                                                                                                                                                                                                

	CMyData& operator=(const CMyData &rhs)
	{
//		같은 일을 하는 함수는 하나만...
//		m_nData = nParam;  // 좋지 않다.
		SetData(rhs.m_nData);
		return *this;
	}

private:
	int m_nData = 0;
};

void caller()
{
	CMyData a, b;

	//a = a + b;
	a = b;
	a = 5;  // 사용자 관점에서 이것은 기본 연산, 절대 실패하면 안된다.
	        // 예외처리를 꼭 해야 한다.
	a.operator=(5); // 명백히 같은 코드
}

// 형식 변환에는 신중을 기해야 한다.


// 설계  <- 객체(요소) 규정 + 관계 정의
// -> UML

// 상속
// 1. 코드 재사용하는 방법
// 2. 규모 확장
// 3. 관계의 한 가지 유형
//    -> 클래스간의 관계

// 설계 원칙 : SOLID



// 리팩토링 : 만일 개판인 코드를 수정해야 하는 경우

// 의존관계 파악! :
// 예) 상속 : 존립 
// 
// 프로그램 개발 순서
// 1. UI 

















