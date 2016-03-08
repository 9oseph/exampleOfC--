#include "stdafx.h"

// ���� ������
// ��ü�� ���纻�� ������ �� ȣ��Ǵ� ������, �ۼ��� �����ϸ� �����Ϸ��� �˾Ƽ� ������ش�.
// �� ������ �ϴ� ��� : Ŭ���� ���ο��� �޸𸮸� ���� �Ҵ� �� ���� �ϰ� �̸� ��� ������ ������ 
// �����ϰ� �ִ� ���
class CopyConstructor
{
private:
	int m_nData = 0;
public:
	CopyConstructor() { cout << "CopyConstructor()" << endl; }

	// ���� ������ ���� �� ����
	// ����ڴ� ���� �����ڸ� ȣ���ϴ� ��� �������� �������� ������ ���� �������� �� �� ����
	// ���� ������ ���� �ٲ�� ��츦 ���� ���� const�� ������ �����Ѵ�.
	CopyConstructor(const CopyConstructor &rhs)
	//	: m_nData(rhs.m_nData) �̷��� ���� ����� ����.
	{
		// ���� �����Ǵ� ��ü��, ���� ��ü�� �� ���� ��� m_nData�� ����� ������ ����
		// ���纻 ������ ������ �� ���� �Ѳ����� ��Ÿ����.
		// �� ���� ���� �ϰ��� l-value ���� �ǵ������� this->m_nData �� ǥ��
		this->m_nData = rhs.m_nData;  
		cout << "CopyConstructor(const CopyConstructor &)" << endl;
	}

	int GetData(void) const { return m_nData; }
	void SetData(int nParam) { m_nData = nParam; }
};

void CopyConstructorCaller()
{
	// ����Ʈ �����ڰ� ȣ��Ǵ� ���
	CopyConstructor a;
	a.SetData(10);

	// ���� �����ڰ� ȣ��Ǵ� ���, ������ ������ a, a �� ���� ������ rhs
	// ȣ��Ǵ� ��� 
	// 1. ��������� ��ü�� ���纻�� �����ϴ� ������� ���� CTest a;
	// 2. CTest b(a); �Լ� ���·� ȣ��Ǵ� ���, 
	// �� ��� Ŭ������ �Ű������� ���Ǵ� ���� ��ȯ�������� ���Ǵ� ���� ����
	// ��ȯ �������� ���Ǵ� ��� '�̸� ���� �ӽ� ��ü'�� ������. ��������
	CopyConstructor b(a);
	cout << b.GetData() << endl;
}

class ShallowCopy
{
private:
	// ������ ��� ������
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
		
		// �޸𸮸� �Ҵ��Ѵ�. ���ο� ��ü�� �����Ͽ� �����ؾ� �ϹǷ� 
		m_pnData = new int;

		// �����Ͱ� ����Ű�� ��ġ�� ���� �����Ѵ�.
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
		// �ܼ� ������ �̹� ��ü�� �ִ� ���¿��� �����ϹǷ� �޸� �Ҵ��� �ʿ����.
		*m_pnData = *rhs.m_pnData;

		// ��ü �ڽſ� ���� ������ ��ȯ�Ѵ�.
		return *this;
	}
};

void ShallowCopyCaller()
{
	ShallowCopy a(10);
	// ���� ���縦 ������ ������ ���� �����ڰ� ���� ������ �����Ϸ��� ���� ��������ڰ� �۵�.
	// �뷫 �̷� ���� : m_pnData = rhs.m_pnData;
	ShallowCopy b(a);
	cout << a.GetData() << endl;
	cout << b.GetData() << endl;

	// �ܼ� ������ �õ��ϸ� ��� ����� ���� �״�� �����Ѵ�.
	// �⺻������ ���� ���簡 �����
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

	// ���� ������ ���� �� ����
	ShallowCopy2(const ShallowCopy2 &rhs)
	{
		cout << "ShallowCopy2(const ShallowCopy2 &)" << endl;

		// �޸𸮸� �Ҵ��Ѵ�.
		m_pnData = new int;
		*m_pnData = *rhs.m_pnData;
	}

	// ��ü�� �Ҹ��� �� ���� �Ҵ��ߴ� �޸𸮸� �����Ѵ�.
	~ShallowCopy2()
	{
		delete m_pnData;
	}

	// �ܼ� ���� ������ ����
	ShallowCopy2& operator=(const ShallowCopy2 &rhs)
	{
		*m_pnData = *rhs.m_pnData;

		// ��ü �ڽſ� ���� ���� ��ȯ
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
	// �Ű������� �ϳ����� �����ڴ� �� ��ȯ�� �����ϴ�.
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
	// Ŭ������ �Ű������� ����� �Ŷ�� ���������� ���; ������ ��ȯ �����ڸ� �����ϴ� Ŭ�������� Ȯ��
	cout << "TestImTypeCast(): " << Param.GetData() << endl;
}

void ImTypeCastCaller()
{
	// int �ڷ������� ImTypeCast �������� ��ȯ�� �� �ִ�.
	// �Ű����� ������ ImTypeCast ������ ��ȯ�����ڸ� �����ϹǷ� 5�� ���μ� ��� ����
	// TestImTypeCast(5);

	cout << "****Begin****" << endl;

	// ���ο� ��ü�� �����ϰ� ������ �����Ѵ�.
	//TestImTypeCast(5);

	// �Լ��� ��ȯ�Ǹ鼭 �ӽ� ��ü�� �Ҹ��Ѵ�.
	cout << "****End****" << endl;
}

// ���Ǵ� ��ȯ
// - Ŭ������ ��ȯ �����ڸ� �����ϸ� �� ���� ���̿� ȣȯ���� �����.
// - ���� CTest ���� int �ڷ����� ���� ��ȯ �����ڸ� ���� �ߴٸ�, int -> CTest but CTest -> int �� ��ȯ �ȵ�.
// - �� ��ȯ ������(�� ��ȯ��) �� ����� ������ �Ұ����� ��ȯ�� ��������

class autoTypeCast
{
private:
	int m_nData = 0;
public:
	explicit autoTypeCast(int nParam) : m_nData(nParam) { }

	// autoTypeCast �� int �ڷ������� ��ȯ�� �� �ִ�.
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

// �ӽ� ��ü�� �̵� �ø�ƽ
// ��ȯ �����ڰ� ���������� ȣ��Ǵ� ���� explicit ������ �������� ������ 
// ����� �ڵ忡�� ������ �ʴ� ��ü�� �����ǰ� �Ҹ��ϴ� ���� ���� ����.
// �̺��� �� ������ �ӽ� ��ü�� �ִ�.
// �ϴ� �̸��� ����. ���� ���� ��ٷ� �Ҹ�
// => ���� ������ �ּ�ȭ�ǵ��� �ڵ带 �ִ��� ���̴� ������� ����
// '�Լ��� ��ȯ ������ Ŭ������ ���' �� �߻�!!!

class tempObject
{
private:
	int m_nData = 0;
	// ���� �̸��� �����ϱ� ���� ���
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
		// �ܼ� ���� ������
		cout << "operator=" << endl;
		// ���� ���������� �̸��� �״�� �д�.
		m_nData = rhs.m_nData;
		// strcpy(m_pszName, rhs.m_pszName);

		return *this;
	}

	int GetData() { return m_nData; }
	void SetData(int nParam) { m_nData = nParam; }
};

tempObject TestTempObject(int nParam)
{
	// tempObject Ŭ������ �ν��Ͻ��� a�� ���������̴�.
	// ���� �Լ��� ��ȯ�Ǹ� �Ҹ��Ѵ�.
	tempObject a(nParam, "a");

	return a;
}

void tempObjectCaller()
{
	tempObject b(5, "b");
	cout << "****Before****" << endl;

	// �Լ��� ��ȯ�Ǹ鼭 �ӽ� ��ü�� �����Ǿ��ٰ� ���� ���� �� ��� �Ҹ��Ѵ�!
	b = TestTempObject(10);
	cout << "****After****" << endl;
	cout << b.GetData() << endl;
}

// ���� ���
//tempObject(int) : b					 ==> tempObject b(5, "b");
//****Before****
//tempObject(int) : a					 ==> tempObject a(nParam, "a"); 
//tempObject(const tempObject &) : a	 ==> b = TestTempObject(10);	�̸� ���� �ӽ� ��ü ���� ����
//~tempObject() : a						 ==> return a;					�Լ� ��ȯ, �̸� ���� �ӽ� ��ü�� ���� ��ü �Ҹ�
//operator=								 ==> b = TestTempObject(10);
//~tempObject() : a						 ==> b = TestTempObject(10);	�̸� ���� �ӽ� ��ü �Ҹ�
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

	// ���� ������ : ���� ���� 
	moveSemantics(const moveSemantics &rhs) : m_nData(rhs.m_nData)
	{
		cout << "moveSemantics(const moveSemantics &)" << endl;
	}

	// �̵� ������ : ���� ����
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

// �̵� �ø�ƽ => ���� �����ڿ� ���� �����ڿ� r-value ������ ����, ���ο� ���� �� ������ ��츦 ����
// ������ ����� ��ü�� ���� ���� ���縦 �����μ� ������ ���� �� �ִ�.

