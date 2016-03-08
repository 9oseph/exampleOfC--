#include "stdafx.h"

// 상속 심화 ( 가상함수 )

class virtualFunc
{
protected:
	int m_nData = 10;
public:
	// 가상 함수로 선언 및 정의 했다.
	virtual void PrintData()
	{
		cout << "virtualFunc: " << m_nData << endl;
	}

	void TestFunc()
	{
		cout << "TestFunc" << endl;

		// 실 형식의 함수가 호출된다!!!
		PrintData();
		cout << "********" << endl;
	}
};

class virtualFuncEx : public virtualFunc
{
public:
	// 기본 클래스의 가상 함수 멤버를 재정의 했다.
	// 기존 정의는 무시된다.
	virtual void PrintData()
	{
		cout << "virtualFuncEx: " << m_nData * 2 << endl;
	}
};

void virtualFuncCaller()
{
	virtualFuncEx a;
	a.PrintData();

	virtualFunc &b = a;

	// 참조 형식에 상관없이 실 형식의 함수가 호출된다.
	b.PrintData();

	// 늘 마지막에 재정의된 함수가 호출된다.
	a.TestFunc();
}

// 7.1.3 소멸자 가상화

class virtualDestructor
{
private:
	char *m_pszData;
public:
	virtualDestructor() { m_pszData = new char[32]; }
	virtual ~virtualDestructor() 
	{
		cout << "~virtualDestructor()" << endl;
		delete[] m_pszData;
	}
};

class virtualDestructorEx : public virtualDestructor
{
private:
	int *m_pnData;
public:
	virtualDestructorEx() { m_pnData = new int; }
	~virtualDestructorEx()
	{
		cout << "~virtualDestructorEx()" << endl;
		delete m_pnData;
	}
};

void virtualDestructorCaller()
{
	virtualDestructor *pData = new virtualDestructorEx;

	// 참조 형식에 맞는 소멸자가 호출된다.
	// 실 형식의 생성자가 호출되지 않는 심각한 문제 발생 ==> 소멸자를 가상화하면 해결
	delete pData;
}

// 7.2 가상 함수 테이블 (vtable)

// vtable ==> 함수 포인터 배열
// 가상 함수를 멤버로 갖는 모든 클래스는 각자 자신만의 고유한 가상함수테이블을 갖습니다.
// 이 테이블을 __vfptr 포인터로 가리킴. 

// 최초 __vfptr -> vTable
// vTableEx 인스턴스가 생기면서 __vfptr -> vTableEx 
// ==> __vfptr 로 인해 무조건 실 형식의 메서드가 호출 


class vTable
{
public:
	vTable() { cout << "vTable()" << endl; }
	virtual ~vTable() { }
	virtual void TestFunc1() { }
	virtual void TestFunc2() { }
};

class vTableEx : public vTable
{
public:
	vTableEx() { cout << "vTableEx()" << endl; }
	virtual ~vTableEx() { }
	virtual void TestFunc1() { }
	virtual void TestFunc2() { cout << "TestFunc2()" << endl; }
};

void vTableCaller()
{
	vTable *pData = new vTableEx;
	pData->TestFunc2(); // pData->__vfptr->TestFunc2(); 
	delete pData;
}

// 바인딩
// '함수나 변수의 주소가 결정되는 것'
// 컴파일 타임에 결정 => 이른 바인딩(early binding)
// 실행 도중에 결정   => 늦은 바인딩 or 동적 바인딩(dynamic binding)

void lateBindingTestFunc1(int nParam) { }
void lateBindingTestFunc2(int nParam) { }

void lateBindingCaller()
{
	int nInput = 0;
	cin >> nInput;
	void(*pfTest)(int) = nullptr;

	// 실행 중, 사용자의 입력에 따라 어떤 함수를 호출할 지 결정된다.
	if (nInput > 10)
	{
		pfTest = lateBindingTestFunc1;
	}
	else
	{
		pfTest = lateBindingTestFunc2;
	}

	pfTest(10);
}

// 7.3 순수 가상 클래스

// 순수 가상 함수를 멤버로 가진 클래스
// 순수 가상 함수 => 선언은 지금 해 두지만, 정의는 미래에 하도록 미뤄둔 함수
// ex. virtual int GetData() const = 0;

// 중요한 특징 : 1. '인스턴스를 직접 선언할 수 없다.'
//              2.순수 가상 클래스의 파생클래스는 반드시 기본 클래스의 순수 가상 함수를 재정의 해야 한다.

class DataInterface
{
public:
	DataInterface() { cout << "DataInterface()" << endl; }

	// 선언만 있고 정의는 없는 순수 가상 함수
	virtual int GetData() const = 0;
	virtual void SetData(int nParam) = 0;
};

// 후기 개발자 코드
class Data : public DataInterface
{
private:
	int m_nData = 0;
public:
	Data() { cout << "Data()" << endl; }

	// 순수 가상 함수는 파생 클래스에서 '반드시' 정의해야 한다.
	virtual int GetData() const { return m_nData; }
	virtual void SetData(int nParam) { m_nData = nParam; }
};

void interfaceCaller()
{
	// 순수 가상 클래스는 인스턴스를 선언 및 정의할 수 없다.
	// DataInterface a;
	Data a;
	a.SetData(5);
	cout << a.GetData() << endl;
}

// 7.3.1 인터페이스 상속

// 다른 장치(객체)들과 상호작용할 생각이라면 가장 많이 사용되는 보편적 인터페이스를 선택

class CMyObject
{
protected:
	int m_nDeviceID;
public:
	CMyObject() { }
	virtual ~CMyObject() { }

	// 모든 파생 클래스는 이 메서드를 가졌다고 가정할 수 있다.
	virtual int GetDeviceID() = 0;
};

// 초기 제작자가 만든 함수 
void PrintID(CMyObject *pObj)
{
	// 실제로 어떤 것일지는 모르지만, 그래도 ID는 출력할 수 있다.
	cout << "Device ID: " << pObj->GetDeviceID() << endl;
}

// 후기 제작자의 코드
class CMyTV : public CMyObject
{
public:
	CMyTV(int nID) { m_nDeviceID = nID; }

	virtual int GetDeviceID()
	{
		cout << "CMyTV::GetDeviceID()" << endl;
		return m_nDeviceID;
	}
};

class CMyPhone : public CMyObject
{
public:
	CMyPhone(int nID) { m_nDeviceID = nID; }
	virtual int GetDeviceID()
	{
		cout << "CMyPhone::GetDeviceID()" << endl;
		return m_nDeviceID;
	}
};

void objCaller()
{
	CMyTV a(5);
	CMyPhone b(10);

	// 실제 객체가 무엇이든 알아서 자신의 ID를 출력한다.
	::PrintID(&a);
	::PrintID(&b);

	a.GetDeviceID();
	b.GetDeviceID();
}

// 7.3.2 추상 자료형의 사용 예

// "사용자가 입력한 모양을 그리자"
// 구현 자체가 어려울 것은 없는데 성능 상의 문제로 반드시 생각해봐야 할 중요한 문제가 있습니다.
// 1. 사용자가 입력할 수 있는 모양의 종류는 몇 가지인가?
// 2. 사용자가 입력한 모양을 화면에 출력할 때 어떤 모양인지에 따라 각각 다른 함수가 호출되도록
//    코드를 작성할 것인가요?
// 3. 사용자가 입력한 모양이 무엇인지 판단하기 위해 switch-case문을 사용할 것인가요?
//
// ==> 빠른 연산이 필요한 순간에 switch-case문이나 다중 if문을 사용하는 것은 매우 비효율!

class CPerson
{
protected:
#define DEFAULT_FARE 1000
	unsigned int m_nFare = 0;
public:
	CPerson() { }
	virtual ~CPerson() { cout << "virtual ~CPerson()" << endl; }

	// 요금 계산 인터페이스
	virtual void CalcFare() = 0;

	virtual unsigned int GetFare() const { return m_nFare; }
};

// 초기 혹은 후기 개발자
class CBaby : public CPerson
{
public:
	// 영유아(0~7세) 요금 계산
	virtual void CalcFare() 
	{ 
		m_nFare = 0;  // 0%  
	}
};

class CChild : public CPerson
{
public:
	// 어린이(8~13세) 요금 계산
	virtual void CalcFare()
	{
		m_nFare = DEFAULT_FARE * 50 / 100; // 50%
	}
};

class CTeen : public CPerson
{
public:
	// 청소년(14~19세) 요금 계산
	virtual void CalcFare()
	{
		m_nFare = DEFAULT_FARE * 75 / 100; // 50%
	}
};

class CAdult : public CPerson
{
public:
	// 어린이(8~13세) 요금 계산
	virtual void CalcFare()
	{
		m_nFare = DEFAULT_FARE;
	}
};

void CalcPersonFare()
{
	CPerson* arList[3] = { 0 };
	int nAge = 0;

	// 1. 자료 입력 : 사용자 입력에 따라서 생성할 객체 선택
	for (auto &person : arList)
	{
		cout << "나이를 입력하세요 : ";
		cin >> nAge;
		if (nAge < 8)
		{
			person = new CBaby;
		}
		else if (nAge < 14)
		{
			person = new CChild;
		}
		else if (nAge < 20)
		{
			person = new CTeen;
		}
		else
		{
			person = new CAdult;
		}

		// 생성한 객체에 맞는 요금이 자동으로 계산된다.
		// 다중 if, switch-case 문을 이 한 줄의 코드로 대체 가능!!!
		person->CalcFare();
	}

	// 2. 자료 출력 : 계산한 요금을 활용하는 부분
	for (auto person : arList)
	{
		cout << person->GetFare() << "원" << endl;
	}

	// 3. 자료 삭제 및 종료
	for (auto person : arList)
	{
		delete person;
	}
}

// 7.4 상속과 형변환

// const_cast<>     : 상수형 포인터에서 const 제거
// static_cast<>    : 컴파일 시 상향 혹은 하향 형 변환
// dynamic_cast<>   : 런타임시 상향 혹은 하향 형 변환
// reinterpret_cast : C 의 형 변환 연산자와 흡사

// 7.4.2 dynamic_cast

// 동적으로 생성된 어떤 객체가 있다고 가정
// 그것을 가리키는 포인터가 기본 형식인 경우 구체적으로 어떤 객체에 대한 인스턴스인지 확인 필요
// 이럴때 사용하기 딱 좋은 것이  dynamic_cast
// 단, dynamic_cast 가 등장했다는 것은 뭔가 좋지 못한 방향으로 흘러가고 있다는 증거!!!

class CShape
{
public:
	CShape() { }
	virtual ~CShape() { }
	virtual void Draw() { cout << "CShape::Draw()" << endl; }
};



























