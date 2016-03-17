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

class CRectangle : public CShape
{
public:
	virtual void Draw() { cout << "CRectangle::Draw()" << endl; }
};

class CCircle : public CShape
{
public:
	virtual void Draw() { cout << "CCircle::Draw()" << endl; }
};

void CShapeCaller()
{
	cout << "도형 번호를 입력하세요. [ 1. 사각형, 2. 원 ] : " << endl;
	int nInput(0);
	cin >> nInput;

	CShape *pShape = nullptr;
	if (nInput == 1)
	{
		pShape = new CRectangle;
	}
	else if (nInput == 2)
	{
		pShape = new CCircle;
	}
	else
	{
		pShape = new CShape;
	}

	// 좋은 예
	pShape->Draw();

	// 매우 나쁜 예
	// 가상 함수를 활용한다면, 이런 코드를 작성할 이유가 없다.
	CRectangle *pRect = dynamic_cast<CRectangle*>(pShape);
	if (pRect != nullptr)
	{
		cout << "CRectangle::Draw()" << endl;
	}
	else
	{
		CCircle *pCircle = dynamic_cast<CCircle*>(pShape);
		if (pCircle != nullptr)
		{
			cout << "CCircle::Draw()" << endl;
		}
		else
		{
			cout << "CShape::Draw()" << endl;
		}
	}
}

// dynamic_cast 연산자는 형 변환에 실패하면 null 을 반환
// 이 방법으로 바른 변환인지 확인 가능 (Run-Time Type Information(or Identification))
// dynamic_cast가 꼭 필요한 경우가 아니라면 절대로 사용하지 말아야 한다.
// ==> 성능을 떨어뜨리는 주범, 코드를 복잡하게 

// C++ 에서 RTTI 를 수행하기 위한 방법으로 typeid 연산자도 있으나 성능이 나빠지는것은 마찬가지

// switch-case 문과 RTTI 는 설계 하기에 따라 가상 함수와 추상 자료형을 사용하는 방법으로 전환하는 경우가 많음


// 7.5 상속과 연산자 다중 정의

// 파생 클래스에서 기본 클래스가 가진 생성자를 그대로 지원하고 싶다면, 일일이 맞추어 똑같이 정의해야 한다.
// ==> using 선언으로 한 큐에 해결!

// 이와 유사한 문제가 연산자 함수에도 존재
// 기본적으로 모든 연산자는 파생 형식에 자동으로 상속
// ==> 단순 대입 연산자는 예외!

class inheritOperOver
{
protected:
	int m_nData = 0;
public:
	inheritOperOver(int nParam) : m_nData(nParam) { }

	inheritOperOver operator+(const inheritOperOver &rhs)
	{
		return inheritOperOver(m_nData + rhs.m_nData);
	}

	inheritOperOver& operator=(const inheritOperOver &rhs)
	{
		m_nData = rhs.m_nData;
		return *this;
	}

	operator int() { return m_nData; }
};

class inheritOperOverEx : public inheritOperOver
{
public:
	inheritOperOverEx(int nParam) : inheritOperOver(nParam) { }

	// 단순 대입 연산자는 따로 만들어 줘야 한다.
	inheritOperOverEx operator+(const inheritOperOverEx &rhs)
	{
		return inheritOperOverEx(static_cast<int>(inheritOperOver::operator+(rhs)));
	}

	// 혹은 인터페이스를 맞춰주기 위한 연산자 다중 정의
	// 상위 클래스의 연산자 함수들을 그대로 차용한다고 선언
	using inheritOperOver::operator+;
	using inheritOperOver::operator=;
};

void inheritOperOverCaller()
{
	inheritOperOver a(3), b(4);
	cout << a + b << endl;

	inheritOperOverEx c(3), d(4), e(0);

	// inheritOperOverEx 클래스에 맞는 단순 대입 연산자가 없어서 컴파일 오류가 발생한다.
	// 문제는 이때 호출되는 연산자 함수가 inheritOperOver operator+(const inheritOperOver &rhs) 이므로
	// 단순 대입의 r-value 가 inheritOperOver 형식.
	// 이것을 inheritOperOverEx에 대입하려고 하니 오류가 발생
	e = c + d;
	cout << e << endl;
}

// 7.6 다중 상속

// 7.6.1 다중 상속과 모호성

// 여러 클래스의 장점/단점을 모두 상속
// 가급적 안쓰는게 정신 건강에 좋음

// 7.6.2 가상 상속

class virtualObject
{
public:
	virtualObject() { cout << "virtualObject()" << endl; }
	virtual ~virtualObject() {}
};

class virtualImage : public virtualObject
{
public:
	virtualImage() { cout << "virtualImage(int, int)" << endl; }
};

class virtualShape : public virtualObject
{
public:
	virtualShape() { cout << "virtualShape(int)" << endl; }
};

class virtualPicture : public virtualImage, public virtualShape
{
public:
	virtualPicture() { cout << "virtualPicture()" << endl; }
};

void virtualObjectCaller()
{
	// virtualObject 의 생성자는 두 번 호출된다.
	// 멤버가 있는 경우 중복해서 생성되게 된다.
	// 이런 경우 '가상 상속' 을 통해 중복 문제를 해결 가능
	// ex. class virtualImage : virtual public virtualObject

	virtualPicture a;
}

// 7.6.3 인터페이스 다중 상속

// 다중 상속이 유일하게 좋은 결과로 나타나는 경우
// ==> 인터페이스 다중 상속
// 인터페이스 클래스는 말 그대로 '인터페이스'만 갖는다.
// ==> 보통 순수 가상 클래스로 선언하는 경우가 많다.

class USB
{
public:
	virtual int GetUsbVersion() = 0;
	virtual int GetTransferRate() = 0;
};

class Serial
{
public:
	virtual int GetSignal() = 0;
	virtual int GetRate() = 0;
};

class Device : public USB, public Serial
{
public:
	// USB
	virtual int GetUsbVersion() { return 0; }
	virtual int GetTransferRate() { return 0; }

	// Serial
	virtual int GetSignal() { return 0; }
	virtual int GetRate() { return 0; }
};

void DeviceCaller()
{
	Device dev;
}


















