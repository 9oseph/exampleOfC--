#include "stdafx.h"

// �ֱ� C++ ������ Ư¡ �� �ϳ��� '�Ϲ�ȭ' Ư�� �÷����� �������� �ڵ带 ������ ���ٴ� JAVA/ C# �� ����
// �߻��� ���� ���꼺�� ���� ȯ���� ������� �ϴ� ������ �ѷ�.
// C++ ������ template ���� �߻��� ���� ���� �� �ִ�.
// ������ ���� ���Ǵ� ���ø��� ���� �ʼ�!

class operatorOver
{
private:
	int m_nData = 0;
public:
	// ��ȯ ������
	operatorOver(int nParam) : m_nData(nParam)
	{
		cout << "operatorOver(int)" << endl;
	}

	// ���� ������
	operatorOver(const operatorOver &rhs) : m_nData(rhs.m_nData) 
	{
		cout << "operatorOver(const operatorOver &)" << endl;
	}

	// �̵� ������
	operatorOver(const operatorOver &&rhs) : m_nData(rhs.m_nData)
	{
		cout << "operatorOver(const operatorOver &&)" << endl;
	}

	// �� ��ȯ
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

	// b + c ����� �̸����� ��ü�� ���������, a �� �����ϴ� ���� �� �ӽ� ��ü�̴�.
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

	// �ܼ� ���Կ����� ��������
	operOverAssign& operator=(const operOverAssign &rhs)
	{
		if (this == &rhs) // rhs == operOverAssign, &rhs == &operOverAssign == this, *this == rhs
		{
			return *this;  // r-value �� �ڽ��̸� ������ �������� ����
		}

		// ���� ����Ű�� �޸� ����
		delete m_pnData;

		// ���� �Ҵ��� �޸𸮿� ���� ����
		m_pnData = new int(*rhs.m_pnData);

		return *this;
	}

	operOverAssign& operator+=(const operOverAssign &rhs)
	{
		// ���� �� ó�� 
		int *pnNewData = new int(*m_pnData);

		// ������ �� ó�� 
		*pnNewData += *rhs.m_pnData;

		// ���� �����͸� �����ϰ� �� �޸𸮷� ��ü
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

	a = a; // �̷� ��� ������ �����Ͽ� ���� �߻�

	a += b;
	cout << a << endl;
}

// �̵� ���� ������

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

	// ���� ������ ���� ����
	operOverAssignMove operator+(const operOverAssignMove &rhs)
	{
		//operOverAssignMove result(*this->m_pnData + *rhs.m_pnData);  
		//return result;   

		// ȣ���� �Լ����� �̸� ���� �ӽ� ��ü�� �����ȴ�.
		return operOverAssignMove(*m_pnData + *rhs.m_pnData);
	}

	// �ܼ� ���� ������ ��������
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

	// �̵� ���� ������ ���� ����
	operOverAssignMove& operator=(operOverAssignMove &&rhs)
	{
		cout << "operator=(Move)" << endl;

		// ���� ���縦 �����ϰ� ������ Null �ʱ�ȭ
		m_pnData = rhs.m_pnData;
		rhs.m_pnData = nullptr;

		return *this;
	}
};

void operOverAssignMoveCaller()
{
	operOverAssignMove a(0), b(3), c(4);
	cout << "befor" << endl;

	// �̵����� �����ڰ� ����ȴ�.
	a = b + c;
	cout << "after" << endl;
	a = b;
	cout << a << endl;
}

// �̵� �ø�ƽ�� [�̵� ������ + �̵� ���Կ�����] �� �����ȴ�.

// �迭 ������

class operOverArray
{
private:
	// �迭 �޸�
	int *m_pnData = nullptr;
	// �迭 ����� ����
	int m_nSize = 0;
	// �迭 �������� ����
	int *m_pnResize = nullptr;
public:
	operOverArray(int nSize)
		: m_nSize(nSize)
	{
		// ���޵� ���� ��ŭ int �ڷḦ ���� �� �ִ� �޸𸮸� Ȯ���Ѵ�.
		m_pnData = new int[m_nSize];
		memset(m_pnData, 0, sizeof(int) * m_nSize);
	}

	~operOverArray() 
	{ 
		delete[] m_pnData; 
		delete[] m_pnResize;
	}

	// ����� ������ ����� �迭 ������
	int operator[](int nIndex) const
	{
		cout << "operator[] const" << endl;
		return m_pnData[nIndex];
	}

	// �Ϲ����� �迭 ������ 
	int& operator[](int nIndex)
	{
		cout << "operator[]" << endl;

		if (nIndex >= m_nSize)
		{
			// �ε����� �迭�� ������� ū ��� �ε����� ũ�� ��ŭ �迭�� ����� �����ϰ� 
			// �ش� �ε����� ��ȯ�Ѵ�.

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

	// ���� ������
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

	// ����� ���� �̹Ƿ� 'operator[](int nIndex) const' ȣ��
	cout << arParam[8] << endl;
}

void operOverArrayCaller()
{
	// ���� �迭�� '��� �˻�'�� ���� �ʰ� �ִ�.
	// �׷��Ƿ� ��� ������ 5�� �迭�� ���� -1 �̳� 5 �̻��� �ε����� �ο��Ѵٸ�, ���� �߻�
	// �̸� �ذ��ϴ� ��� �Ұ�
	// ����� ������ 5 �ε� �ε����� 5 �̻��� ���? ==> �ű⿡ ���߾� �޸𸮸� �ø���.
	// �޸𸮴� ���������� �ʰ�, ���� �޸� �Ҵ�� ������ ������ ����߸���. ����

	operOverArray arr(5);
	for (int i = 0; i < 5; ++i)
	{
		// int& operator[](int nIndex) ȣ���, ��ȯ ������ ������ �̹Ƿ� l-value �� �� �� �ִ�.
		arr[i] = i * 10;
	}
	TestOperOverArray(arr);
}

// ���� ���������� ( ����, ���� ����)

class operOverIncrement
{
private:
	int m_nData = 0;
public:
	operOverIncrement(int nParam) : m_nData(nParam) { }

	// �� ��ȯ
	operator int() { return m_nData; }

	// ���� ���� ������
	int operator++()
	{
		cout << "operator++()" << endl;
		return ++m_nData;
	}

	// ���� ���� ������
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





