#include "stdafx.h"

// 상속 기본

// 객체지향 프로그래밍에서 가장 중요한 요소는? 설계!!!
// 설계의 핵심은? '관계 규정'

class inheritMyData
{
private: // 누구도 접근 불가능
	int m_nData = 0;  

public: // 누구나 접근 가능
	inheritMyData() { cout << "inheritMyData()" << endl; }
	int GetData() { return m_nData; }
	void SetData(int nParam) { m_nData = nParam; }

protected: // 파생 클래스만 접근 가능
	void PrintData() { cout << "inheritMyData::PrintData()" << endl; }
};

class inheritMyDataEx : public inheritMyData
{
public:
	inheritMyDataEx() { cout << "inheritMyDataEx()" << endl; }
	void TestFunc()
	{
		// 기본 클래스 멤버에 접근, public 으로 상속받아서가능  
		PrintData(); // protected 이므로 파생 클래스에서만 사용가능
		SetData(5);
		cout << "inheritMyData::GetData()" << endl;
	}
};

void inheritMyDataCaller()
{
	// 파생 클래스의 생성자는 먼저 호출되지만, 실행은 나중에 된다!
	inheritMyDataEx data;

	// 기본 클래스 멤버에 접근 (inheritMyData)
	// 파생 클래스의 인스턴스로 기본 클래스의 메서드를 호출한다.
	data.SetData(10);
	cout << data.GetData() << endl;

	// 파생 클래스 멤버에 접근
	data.TestFunc();
}

// 6.2 메서드 재정의 override(무시하다)
// 메서드를 재정의 하면 기존의 것은 '무시'된다.

class methodOver
{
private:
	int m_nData = 0;
public:
	int GetData() { return m_nData; }
	void SetData(int nParam) { m_nData = nParam; }
};

class methodOverEx : public methodOver
{
public:
	// 파생 클래스에서 기본 클래스의 메서드를 재정의했다.
	void SetData(int nParam)
	{
		// 입력 데이터의 값을 보정하는 새로운 기능을 추가한다.
		if (nParam < 0)
		{
			methodOver::SetData(0);
			// SetData(0); ==> 재귀호출 발생. 즉, methodOverEx::SetData() 를 호출
			// 파생형식에서 기본 형식의 동일한 메서드를 호출 하려면 반드시 소속 클래스를 명시해야 한다.
		}

		if (nParam > 10)
		{
			methodOver::SetData(10);
			// SetData(10);
		}
	}
};

void methodOverCaller()
{
	// 구형에는 값을 보정하는 기능이 없다.
	methodOver a;
	a.SetData(-10);
	cout << a.GetData() << endl;

	// 신형에는 값을 보정하는 기능이 있다.
	methodOverEx b;
	b.SetData(15);
	cout << b.GetData() << endl;

}

void methodOverCaller2()
{
	// 파생 형식을 기본 형식으로 참조하는 것은 매우 자연스러운 일.
	// 실제형식, 참조형식
	// 실 형식과 참조 형식이 다른 경우 묵시적 호출로 어떤 메서드가 호출되는가?
	// ==> '참조 형식'(참조자 혹은 포인터)

	methodOverEx ex;
	methodOver &rData = ex; 
	rData.SetData(15);  // methodOver 의 참조자로 참조형식의 메서드가 호출됨
	cout << rData.GetData() << endl;

	// SetData() 를 호출 했는데 참조형식이 methodOver 입니다. 따라서 동적 할당된 실 형식이 methodOverEx 임에도 methodOver::SetData()
	// 가 호출된다. 그리고 이 코드는 잠재적으로 메모리 릭 오류가 있다.
	// ==> delete pData 연산을 실행 하더라도 methodOverEx 의 소멸자가 호출되지 않기 때문이다.
	// '소멸자 가상화' 
	methodOver *pData = new methodOverEx;
	pData->SetData(5);
	delete pData; // 실 형식인 methodOver 의 소멸자만 호출, methodOverEx 의 소멸자는 호출되지 않는 문제가 있다.
}

// 멤버 데이터 재정의 : 문법적으로는 가능하지만, 결코 바람직 하지 않다! 절대로 하지 말것!

// 상속에서의 생성자와 소멸자
// 6.3.1 호출 순서

class inheritConstructorA
{
protected:
	char *m_pszData;
public:
	inheritConstructorA() 
	{ 
		cout << "inheritConstructorA()" << endl; 
		m_pszData = new char[32];
	}

	~inheritConstructorA() 
	{ 
		cout << "~inheritConstructorA()" << endl; 
		delete[] m_pszData;
	}
};

class inheritConstructorB : public inheritConstructorA
{
public:
	inheritConstructorB() { cout << "inheritConstructorB()" << endl; }
	~inheritConstructorB() { cout << "~inheritConstructorB()" << endl; }
};

class inheritConstructorC : public inheritConstructorB
{
public:
	inheritConstructorC() { cout << "inheritConstructorC()" << endl; }
	~inheritConstructorC() 
	{ 
		cout << "~inheritConstructorC()" << endl; 
		// 여기서 기본 클래스의 멤버를 해제 해 버리면 기본 클래스의 소멸자 실행시 문제 발생.
		// 파생 클래스에서 기본 클래스의 멤버 변수에 직접 쓰기 연산하지 않는 것이 정답!
		// 파생 클래스에서 기본 클래스의 멤버 변수를 초기화 하지 않는다!!!
		// delete[] m_pszData;
	}
};

// 파생 클래스의 생성자가 먼저 호출되고 이어서 상위로 올라가듯 호출
// 실행 순서야 어떻건 파생 클래스 생성자가 기본 클래스의 생성자를 '선택' 하고 호출한다.
// 만약, 생성자가 여러 형태로 다중 정의된 경우?
// ==> 파생 클래스에서 상위 클래스 생성자는 하나만 '선택', 선택하지 않으면 디폴트 생성자 호출

void inheritConstructorCaller()
{
	cout << "begin" << endl;
	inheritConstructorC data;
	cout << "end" << endl;
}

// 생성자와 소멸자는 객체 자신의 초기화 및 해제만 생각해야 한다!!

// 6.3.2 생성자 선택

class selectConstructor
{
public:
	selectConstructor() { cout << "selectConstructor()" << endl; }
	selectConstructor(int nParam) { cout << "selectConstructor(int)" << endl; }
	selectConstructor(double dParam) { cout << "selectConsturctor(double)" << endl; }
};

class selectConstructorEx : public selectConstructor
{
public:
	// C++11 '생성자 상속' ==> 파생 클래스를 만들 때 다중 정의된 상위 클래스의 생성자들을 그대로 가져오는 문법
	using selectConstructor::selectConstructor;

	selectConstructorEx() { cout << "selectConstructorEx()" << endl; }

	// 기본 클래스의 세 가지 생성자 중 int 선택
	selectConstructorEx(int nParam) : selectConstructor(nParam)
	{
		cout << "selectConsturctorEx(int)" << endl;
	}

	selectConstructorEx(double) : selectConstructor()
	{
		cout << "selectConsturctorEx(double)" << endl;
	}
};

void selectConstructorCaller()
{
	selectConstructorEx	a;
	cout << "***********" << endl;
	selectConstructorEx b(5);
	cout << "***********" << endl;
	selectConstructorEx c(3.3);
}












