#include "stdafx.h"

// 복사 생성자
// 객체의 복사본을 생성할 때 호출되는 생성자, 작성을 생략하면 컴파일러가 알아서 만들어준다.
// 꼭 만들어야 하는 경우 : 클래스 내부에서 메모리를 동적 할당 및 해제 하고 이를 멤버 포인터 변수로 
// 관리하고 있는 경우
class CopyConstructor
{
private:
	int m_nData = 0;
public:
	CopyConstructor() { cout << "CopyConstructor()" << endl; }

	// 복사 생성자 선언 및 정의
	// 사용자는 복사 생성자를 호출하는 경우 값에의한 전달인지 참조에 의한 전달인지 알 수 없다
	// 참조 원본의 값이 바뀌는 경우를 막기 위해 const로 변조를 방지한다.
	CopyConstructor(const CopyConstructor &rhs)
	//	: m_nData(rhs.m_nData) 이렇게 쓰는 방법도 좋다.
	{
		// 새로 생성되는 객체든, 원본 객체든 두 가지 모두 m_nData를 멤버로 가지다 보니
		// 복사본 생성의 순간에 이 둘이 한꺼번에 나타난다.
		// 이 둘을 구별 하고자 l-value 에는 의도적으로 this->m_nData 로 표현
		this->m_nData = rhs.m_nData;  
		cout << "CopyConstructor(const CopyConstructor &)" << endl;
	}

	int GetData(void) const { return m_nData; }
	void SetData(int nParam) { m_nData = nParam; }
};

void CopyConstructorCaller()
{
	// 디폴트 생성자가 호출되는 경우
	CopyConstructor a;
	a.SetData(10);

	// 복사 생성자가 호출되는 경우, 복사의 원본은 a, a 에 대한 참조는 rhs
	// 호출되는 경우 
	// 1. 명시적으로 객체의 복사본을 생성하는 방식으로 선언 CTest a;
	// 2. CTest b(a); 함수 형태로 호출되는 경우, 
	// 이 경우 클래스가 매개변수로 사용되는 경우와 반환형식으로 사용되는 경우로 나뉨
	// 반환 형식으로 사용되는 경우 '이름 없는 임시 객체'를 만들어낸다. 성능저하
	CopyConstructor b(a);
	cout << b.GetData() << endl;
}

class ShallowCopy
{
private:
	// 포인터 멤버 데이터
	int *m_pnData = nullptr;
public:
	ShallowCopy(int nParam)
	{
		m_pnData = new int;
		*m_pnData = nParam;
	}

	ShallowCopy(const ShallowCopy &rhs)
	{
		cout << "ShallowCopy(const ShallowCopy &)" << endl;
		
		// 메모리를 할당한다. 새로운 객체를 생성하여 복사해야 하므로 
		m_pnData = new int;

		// 포인터가 가리키는 위치에 값을 복사한다.
		*m_pnData = *rhs.m_pnData;
	}

	~ShallowCopy()
	{
		delete m_pnData;
	}

	int GetData()
	{
		if (m_pnData != nullptr)
		{
			return *m_pnData;
		}
		return 0;
	}

	ShallowCopy& operator=(const ShallowCopy &rhs)
	{
		// 단순 대입은 이미 객체가 있는 상태에서 수행하므로 메모리 할당은 필요없다.
		*m_pnData = *rhs.m_pnData;

		// 객체 자신에 대한 참조를 반환한다.
		return *this;
	}
};

void ShallowCopyCaller()
{
	ShallowCopy a(10);
	// 깊은 복사를 수행할 별도의 복사 생성자가 없기 때문에 컴파일러가 만든 복사생성자가 작동.
	// 대략 이런 동작 : m_pnData = rhs.m_pnData;
	ShallowCopy b(a);
	cout << a.GetData() << endl;
	cout << b.GetData() << endl;

	// 단순 대입을 시도하면 모든 멤버의 값을 그대로 복사한다.
	// 기본적으로 얕은 복사가 수행됨
	a = b;
}

class ShallowCopy2
{
private:
	int *m_pnData = nullptr;
public:
	ShallowCopy2(int nParam)
	{
		m_pnData = new int;
		*m_pnData = nParam;
	}

	// 복사 생성자 선언 및 정의
	ShallowCopy2(const ShallowCopy2 &rhs)
	{
		cout << "ShallowCopy2(const ShallowCopy2 &)" << endl;

		// 메모리를 할당한다.
		m_pnData = new int;
		*m_pnData = *rhs.m_pnData;
	}

	// 객체가 소멸할 때 동적 할당했던 메모리를 해제한다.
	~ShallowCopy2()
	{
		delete m_pnData;
	}

	// 단순 대입 연산자 정의
	ShallowCopy2& operator=(const ShallowCopy2 &rhs)
	{
		*m_pnData = *rhs.m_pnData;

		// 객체 자신에 대한 참조 반환
		return *this;
	}

	int GetData()
	{
		if (m_pnData != nullptr)
		{
			return *m_pnData;
		}
		return 0;
	}
};

void ShallowCopy2Caller()
{
	ShallowCopy2 a(10);
	ShallowCopy2 b(20);

	a = b;
	cout << a.GetData() << endl;
}

class ImTypeCast
{
private:
	int m_nData = 0;
public:
	// 매개변수가 하나뿐인 생성자는 형 변환이 가능하다.
	ImTypeCast(int nParam) : m_nData(nParam)
	{
		cout << "ImTypeCast(int)" << endl;
	}

	ImTypeCast(const ImTypeCast &rhs) : m_nData(rhs.m_nData)
	{
		cout << "ImTypeCast(const ImTypeCast &)" << endl;
	}

	~ImTypeCast()
	{
		cout << "~ImTypeCast()" << endl;
	}

	int GetData() { return m_nData; }
	void SetData(int nParam) { m_nData = nParam; }
};

void TestImTypeCast(ImTypeCast &Param)
{
	// 클래스를 매개변수로 사용할 거라면 참조형식을 사용; 묵시적 변환 생성자를 지원하는 클래스인지 확인
	cout << "TestImTypeCast(): " << Param.GetData() << endl;
}

void ImTypeCastCaller()
{
	// int 자료형에서 ImTypeCast 형식으로 변환될 수 있다.
	// 매개변수 형식이 ImTypeCast 이지만 변환생성자를 제공하므로 5를 실인수 기술 가능
	// TestImTypeCast(5);

	cout << "****Begin****" << endl;

	// 새로운 객체를 생성하고 참조로 전달한다.
	//TestImTypeCast(5);

	// 함수가 반환되면서 임시 객체는 소멸한다.
	cout << "****End****" << endl;
}

// 허용되는 변환
// - 클래스가 변환 생성자를 제공하면 두 형식 사이에 호환성이 생긴다.
// - 가령 CTest 에서 int 자료형에 대한 변환 생성자를 제공 했다면, int -> CTest but CTest -> int 는 변환 안됨.
// - 형 변환 연산자(형 변환자) 를 만들어 넣으면 불가능한 변환이 가능해짐

class autoTypeCast
{
private:
	int m_nData = 0;
public:
	explicit autoTypeCast(int nParam) : m_nData(nParam) { }

	// autoTypeCast 는 int 자료형으로 변환될 수 있다.
	operator int(void) { return m_nData; }

	int GetData() const { return m_nData; }
	void SetData(int nParam) { m_nData = nParam; }
};

void autoTypeCastCaller()
{
	autoTypeCast a(10);
	cout << a.GetData() << endl;

	// autoTypeCast to int 
	cout << a << endl;
	cout << (int)a << endl;
	cout << static_cast<int>(a) << endl;
}

// 임시 객체와 이동 시맨틱
// 변환 생성자가 묵시적으로 호출되는 것을 explicit 예약어로 막으려는 이유는 
// 사용자 코드에서 보이지 않는 객체가 생성되고 소멸하는 것을 막기 위함.
// 이보다 더 은밀한 임시 객체도 있다.
// 일단 이름이 없다. 생성 직후 곧바로 소멸
// => 내부 연산이 최소화되도록 코드를 최대한 줄이는 방법으로 대응
// '함수의 반환 형식이 클래스인 경우' 에 발생!!!

class tempObject
{
private:
	int m_nData = 0;
	// 변수 이름을 저장하기 위한 멤버
	char *m_pszName = nullptr;
public:
	tempObject(int nParam, char *pszName) : m_nData(nParam), m_pszName(pszName)
	{
		cout << "tempObject(int): " << m_pszName << endl;
	}

	~tempObject()
	{
		cout << "~tempObject(): " << m_pszName << endl;
	}

	tempObject(const tempObject &rhs) : m_nData(rhs.m_nData), m_pszName(rhs.m_pszName)
	{
		cout << "tempObject(const tempObject &): " << m_pszName << endl;
	}

	tempObject& operator=(const tempObject &rhs)
	{
		// 단순 대입 연산자
		cout << "operator=" << endl;
		// 값은 변경하지만 이름은 그대로 둔다.
		m_nData = rhs.m_nData;
		// strcpy(m_pszName, rhs.m_pszName);

		return *this;
	}

	int GetData() { return m_nData; }
	void SetData(int nParam) { m_nData = nParam; }
};

tempObject TestTempObject(int nParam)
{
	// tempObject 클래스의 인스턴스인 a는 지역변수이다.
	// 따라서 함수가 반환되면 소멸한다.
	tempObject a(nParam, "a");

	return a;
}

void tempObjectCaller()
{
	tempObject b(5, "b");
	cout << "****Before****" << endl;

	// 함수가 반환되면서 임시 객체가 생성되었다가 대입 연산 후 즉시 소멸한다!
	b = TestTempObject(10);
	cout << "****After****" << endl;
	cout << b.GetData() << endl;
}

// 실행 결과
//tempObject(int) : b					 ==> tempObject b(5, "b");
//****Before****
//tempObject(int) : a					 ==> tempObject a(nParam, "a"); 
//tempObject(const tempObject &) : a	 ==> b = TestTempObject(10);	이름 없는 임시 객체 복사 생성
//~tempObject() : a						 ==> return a;					함수 반환, 이름 없는 임시 객체의 원본 객체 소멸
//operator=								 ==> b = TestTempObject(10);
//~tempObject() : a						 ==> b = TestTempObject(10);	이름 없는 임시 객체 소멸
//****After****
//10
//~tempObject() : b

class moveSemantics
{
private:
	int m_nData = 0;
public:
	moveSemantics() { cout << "moveSemantics()" << endl; }
   ~moveSemantics() { cout << "~moveSemantics()" << endl; }

	// 복사 생성자 : 깊은 복사 
	moveSemantics(const moveSemantics &rhs) : m_nData(rhs.m_nData)
	{
		cout << "moveSemantics(const moveSemantics &)" << endl;
	}

	// 이동 생성자 : 얕은 복사
	moveSemantics(const moveSemantics &&rhs) : m_nData(rhs.m_nData)
	{
		cout << "moveSemantics(const moveSemantics &&)" << endl;
	}

	int GetData() const { return m_nData; }
	void SetData(int nParam) { m_nData = nParam; }
};

moveSemantics TestMoveSemantics(int nParam)
{
	cout << "**TestMoveSemantics(): Begin**" << endl;

	moveSemantics a;
	a.SetData(nParam);
	cout << "**TestMoveSemantics(): End**" << endl;

	return a;
}

void moveSemanticsCaller()
{
	moveSemantics b;
	cout << "*****Before*****" << endl;
	b = TestMoveSemantics(20);
	cout << "*****After*****" << endl;
	moveSemantics c(b);
}

// 이동 시맨틱 => 복사 생성자와 대입 연산자에 r-value 참조를 조합, 새로운 생성 및 대입의 경우를 만들어냄
// 어차피 사라질 객체에 대해 얕은 복사를 함으로서 성능을 높일 수 있다.

