#include "stdafx.h"

// 최근 C++ 개발의 특징 중 하나는 '일반화' 특정 플랫폼에 종속적인 코드를 만들어내기 보다는 JAVA/ C# 과 같은
// 추상성이 높고 생산성이 높은 환경을 만들고자 하는 경향이 뚜렷.
// C++ 에서는 template 으로 추상성을 대폭 높일 수 있다.
// 연산자 다중 정의는 템플릿을 향한 초석!

class operatorOver
{
private:
	int m_nData = 0;
public:
	// 변환 생성자
	operatorOver(int nParam) : m_nData(nParam)
	{
		cout << "operatorOver(int)" << endl;
	}

	// 복사 생성자
	operatorOver(const operatorOver &rhs) : m_nData(rhs.m_nData) 
	{
		cout << "operatorOver(const operatorOver &)" << endl;
	}

	// 이동 생성자
	operatorOver(const operatorOver &&rhs) : m_nData(rhs.m_nData)
	{
		cout << "operatorOver(const operatorOver &&)" << endl;
	}

	// 형 변환
	operator int() { return m_nData; }

	// +
	operatorOver operator+(const operatorOver &rhs)
	{
		cout << "operator+" << endl;

		operatorOver result(0);
		result.m_nData	= this->m_nData + rhs.m_nData;

		return result;
	}

	// =
	operatorOver& operator=(const operatorOver &rhs)
	{
		cout << "operator=" << endl;

		m_nData = rhs.m_nData;

		return *this;
	}
};

void operatorOverCaller()
{
	cout << "begin" << endl;
	operatorOver a(0), b(3), c(4);

	// b + c 연산시 이름없는 객체가 만들어지며, a 에 대입하는 것은 이 임시 객체이다.
	a = b + c;
	cout << a << endl;
	cout << "end" << endl;
}

class operOverAssign
{
private:
	int *m_pnData = nullptr;
public:
	explicit operOverAssign(int nParam)
	{
		m_pnData = new int(nParam);
	}

	~operOverAssign() { delete m_pnData; }

	operator int() { return *m_pnData; }

	// 단순 대입연사자 다중정의
	operOverAssign& operator=(const operOverAssign &rhs)
	{
		if (this == &rhs) // rhs == operOverAssign, &rhs == &operOverAssign == this, *this == rhs
		{
			return *this;  // r-value 가 자신이면 대입을 수행하지 않음
		}

		// 본래 가리키던 메모리 삭제
		delete m_pnData;

		// 새로 할당한 메모리에 값을 저장
		m_pnData = new int(*rhs.m_pnData);

		return *this;
	}

	operOverAssign& operator+=(const operOverAssign &rhs)
	{
		// 현재 값 처리 
		int *pnNewData = new int(*m_pnData);

		// 누적할 값 처리 
		*pnNewData += *rhs.m_pnData;

		// 기존 데이터를 삭제하고 새 메모리로 대체
		delete m_pnData;
		m_pnData = pnNewData;

		return *this;
	}

};

void operOverAssignCaller()
{
	operOverAssign a(0), b(5);
	a = b;
	cout << a << endl;

	a = a; // 이런 경우 원본을 삭제하여 문제 발생

	a += b;
	cout << a << endl;
}

// 이동 대입 연산자

class operOverAssignMove
{
private:
	int *m_pnData = nullptr;
public:
	explicit operOverAssignMove(int nParam)
	{
		cout << "operOverAssignMove(int)" << endl;
		m_pnData = new int(nParam);
	}

	operOverAssignMove(const operOverAssignMove &rhs)
	{
		cout << "operOverAssignMove(const operOverAssignMove &)" << endl;
		m_pnData = new int(*rhs.m_pnData);
	}

	~operOverAssignMove() { delete m_pnData; }

	operator int() { return *m_pnData; }

	// 덧셈 연산자 다중 정의
	operOverAssignMove operator+(const operOverAssignMove &rhs)
	{
		//operOverAssignMove result(*this->m_pnData + *rhs.m_pnData);  
		//return result;   

		// 호출자 함수에서 이름 없는 임시 객체가 생성된다.
		return operOverAssignMove(*m_pnData + *rhs.m_pnData);
	}

	// 단순 대입 연산자 다중정의
	operOverAssignMove& operator=(const operOverAssignMove &rhs)
	{
		//*m_pnData = *rhs.m_pnData;
		//return *this;

		cout << "operator=" << endl;
		if (this == &rhs)
		{
			return *this;
		}

		delete m_pnData;
		m_pnData = new int(*rhs.m_pnData);

		return *this;
	}

	// 이동 대입 연산자 다중 정의
	operOverAssignMove& operator=(operOverAssignMove &&rhs)
	{
		cout << "operator=(Move)" << endl;

		// 얕은 복사를 수행하고 원본은 Null 초기화
		m_pnData = rhs.m_pnData;
		rhs.m_pnData = nullptr;

		return *this;
	}
};

void operOverAssignMoveCaller()
{
	operOverAssignMove a(0), b(3), c(4);
	cout << "befor" << endl;

	// 이동대입 연산자가 실행된다.
	a = b + c;
	cout << "after" << endl;
	a = b;
	cout << a << endl;
}

// 이동 시멘틱은 [이동 생성자 + 이동 대입연산자] 로 구현된다.

// 배열 연산자

class operOverArray
{
private:
	// 배열 메모리
	int *m_pnData = nullptr;
	// 배열 요소의 갯수
	int m_nSize = 0;
	// 배열 리사이즈 버퍼
	int *m_pnResize = nullptr;
public:
	operOverArray(int nSize)
		: m_nSize(nSize)
	{
		// 전달된 갯수 만큼 int 자료를 담을 수 있는 메모리를 확보한다.
		m_pnData = new int[m_nSize];
		memset(m_pnData, 0, sizeof(int) * m_nSize);
	}

	~operOverArray() 
	{ 
		delete[] m_pnData; 
		delete[] m_pnResize;
	}

	// 상수형 참조인 경우의 배열 연산자
	int operator[](int nIndex) const
	{
		cout << "operator[] const" << endl;
		return m_pnData[nIndex];
	}

	// 일반적인 배열 연산자 
	int& operator[](int nIndex)
	{
		cout << "operator[]" << endl;

		if (nIndex >= m_nSize)
		{
			// 인덱스가 배열의 사이즈보다 큰 경우 인덱스의 크기 만큼 배열의 사이즈를 변경하고 
			// 해당 인덱스를 반환한다.

			m_pnResize = new int[nIndex];
			memset(m_pnResize, 0, sizeof(int) * nIndex);
			memcpy(m_pnResize, m_pnData, m_nSize);

			delete[] m_pnData;
			m_pnData = new int[nIndex];
			m_pnData = m_pnResize;
			m_nSize = nIndex;
		}
		return m_pnData[nIndex];
	}

	// 관계 연산자
	//int operator==(const operOverArray &rhs)
	//{
	//	if (m_pszData != nullptr && rhs.m_pszData != nullptr)
	//	{
	//		if (strcmp(m_pszData, rhs.m_pszData) == 0)
	//		{
	//			return 1;
	//		}
	//	}
	//	return 0;
	//}
};

void TestOperOverArray(const operOverArray &arParam)
{
	cout << "TestOperOverArray()" << endl;

	// 상수형 참조 이므로 'operator[](int nIndex) const' 호출
	cout << arParam[8] << endl;
}

void operOverArrayCaller()
{
	// 현재 배열의 '경계 검사'를 하지 않고 있다.
	// 그러므로 요소 갯수가 5인 배열에 대해 -1 이나 5 이상의 인덱스를 부여한다면, 오류 발생
	// 이를 해결하는 기법 소개
	// 요소의 갯수가 5 인데 인덱스가 5 이상인 경우? ==> 거기에 맞추어 메모리를 늘린다.
	// 메모리는 무한정하지 않고, 잦은 메모리 할당과 해제는 성능을 떨어뜨린다. 주의

	operOverArray arr(5);
	for (int i = 0; i < 5; ++i)
	{
		// int& operator[](int nIndex) 호출됨, 반환 형식이 참조자 이므로 l-value 가 될 수 있다.
		arr[i] = i * 10;
	}
	TestOperOverArray(arr);
}

// 단항 증감연산자 ( 전위, 후위 주의)

class operOverIncrement
{
private:
	int m_nData = 0;
public:
	operOverIncrement(int nParam) : m_nData(nParam) { }

	// 형 변환
	operator int() { return m_nData; }

	// 전위 증가 연산자
	int operator++()
	{
		cout << "operator++()" << endl;
		return ++m_nData;
	}

	// 후위 증가 연산자
	int operator++(int)
	{
		cout << "operator++(int)" << endl;
		int nData = m_nData;
		m_nData++;

		return nData;
	}
};

void operOverIncrementCaller()
{
	operOverIncrement a(10);
	cout << ++a << endl;
	cout << a++ << endl;
	cout << a << endl;
}





