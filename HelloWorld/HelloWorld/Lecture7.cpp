#include "stdafx.h"

// ��� ��ȭ ( �����Լ� )

class virtualFunc
{
protected:
	int m_nData = 10;
public:
	// ���� �Լ��� ���� �� ���� �ߴ�.
	virtual void PrintData()
	{
		cout << "virtualFunc: " << m_nData << endl;
	}

	void TestFunc()
	{
		cout << "TestFunc" << endl;

		// �� ������ �Լ��� ȣ��ȴ�!!!
		PrintData();
		cout << "********" << endl;
	}
};

class virtualFuncEx : public virtualFunc
{
public:
	// �⺻ Ŭ������ ���� �Լ� ����� ������ �ߴ�.
	// ���� ���Ǵ� ���õȴ�.
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

	// ���� ���Ŀ� ������� �� ������ �Լ��� ȣ��ȴ�.
	b.PrintData();

	// �� �������� �����ǵ� �Լ��� ȣ��ȴ�.
	a.TestFunc();
}

// 7.1.3 �Ҹ��� ����ȭ

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

	// ���� ���Ŀ� �´� �Ҹ��ڰ� ȣ��ȴ�.
	// �� ������ �����ڰ� ȣ����� �ʴ� �ɰ��� ���� �߻� ==> �Ҹ��ڸ� ����ȭ�ϸ� �ذ�
	delete pData;
}

// 7.2 ���� �Լ� ���̺� (vtable)

// vtable ==> �Լ� ������ �迭
// ���� �Լ��� ����� ���� ��� Ŭ������ ���� �ڽŸ��� ������ �����Լ����̺��� �����ϴ�.
// �� ���̺��� __vfptr �����ͷ� ����Ŵ. 

// ���� __vfptr -> vTable
// vTableEx �ν��Ͻ��� ����鼭 __vfptr -> vTableEx 
// ==> __vfptr �� ���� ������ �� ������ �޼��尡 ȣ�� 


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

// ���ε�
// '�Լ��� ������ �ּҰ� �����Ǵ� ��'
// ������ Ÿ�ӿ� ���� => �̸� ���ε�(early binding)
// ���� ���߿� ����   => ���� ���ε� or ���� ���ε�(dynamic binding)

void lateBindingTestFunc1(int nParam) { }
void lateBindingTestFunc2(int nParam) { }

void lateBindingCaller()
{
	int nInput = 0;
	cin >> nInput;
	void(*pfTest)(int) = nullptr;

	// ���� ��, ������� �Է¿� ���� � �Լ��� ȣ���� �� �����ȴ�.
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

// 7.3 ���� ���� Ŭ����

// ���� ���� �Լ��� ����� ���� Ŭ����
// ���� ���� �Լ� => ������ ���� �� ������, ���Ǵ� �̷��� �ϵ��� �̷�� �Լ�
// ex. virtual int GetData() const = 0;

// �߿��� Ư¡ : 1. '�ν��Ͻ��� ���� ������ �� ����.'
//              2.���� ���� Ŭ������ �Ļ�Ŭ������ �ݵ�� �⺻ Ŭ������ ���� ���� �Լ��� ������ �ؾ� �Ѵ�.

class DataInterface
{
public:
	DataInterface() { cout << "DataInterface()" << endl; }

	// ���� �ְ� ���Ǵ� ���� ���� ���� �Լ�
	virtual int GetData() const = 0;
	virtual void SetData(int nParam) = 0;
};

// �ı� ������ �ڵ�
class Data : public DataInterface
{
private:
	int m_nData = 0;
public:
	Data() { cout << "Data()" << endl; }

	// ���� ���� �Լ��� �Ļ� Ŭ�������� '�ݵ��' �����ؾ� �Ѵ�.
	virtual int GetData() const { return m_nData; }
	virtual void SetData(int nParam) { m_nData = nParam; }
};

void interfaceCaller()
{
	// ���� ���� Ŭ������ �ν��Ͻ��� ���� �� ������ �� ����.
	// DataInterface a;
	Data a;
	a.SetData(5);
	cout << a.GetData() << endl;
}

// 7.3.1 �������̽� ���

// �ٸ� ��ġ(��ü)��� ��ȣ�ۿ��� �����̶�� ���� ���� ���Ǵ� ������ �������̽��� ����

class CMyObject
{
protected:
	int m_nDeviceID;
public:
	CMyObject() { }
	virtual ~CMyObject() { }

	// ��� �Ļ� Ŭ������ �� �޼��带 �����ٰ� ������ �� �ִ�.
	virtual int GetDeviceID() = 0;
};

// �ʱ� �����ڰ� ���� �Լ� 
void PrintID(CMyObject *pObj)
{
	// ������ � �������� ������, �׷��� ID�� ����� �� �ִ�.
	cout << "Device ID: " << pObj->GetDeviceID() << endl;
}

// �ı� �������� �ڵ�
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

	// ���� ��ü�� �����̵� �˾Ƽ� �ڽ��� ID�� ����Ѵ�.
	::PrintID(&a);
	::PrintID(&b);

	a.GetDeviceID();
	b.GetDeviceID();
}

// 7.3.2 �߻� �ڷ����� ��� ��

// "����ڰ� �Է��� ����� �׸���"
// ���� ��ü�� ����� ���� ���µ� ���� ���� ������ �ݵ�� �����غ��� �� �߿��� ������ �ֽ��ϴ�.
// 1. ����ڰ� �Է��� �� �ִ� ����� ������ �� �����ΰ�?
// 2. ����ڰ� �Է��� ����� ȭ�鿡 ����� �� � ��������� ���� ���� �ٸ� �Լ��� ȣ��ǵ���
//    �ڵ带 �ۼ��� ���ΰ���?
// 3. ����ڰ� �Է��� ����� �������� �Ǵ��ϱ� ���� switch-case���� ����� ���ΰ���?
//
// ==> ���� ������ �ʿ��� ������ switch-case���̳� ���� if���� ����ϴ� ���� �ſ� ��ȿ��!

class CPerson
{
protected:
#define DEFAULT_FARE 1000
	unsigned int m_nFare = 0;
public:
	CPerson() { }
	virtual ~CPerson() { cout << "virtual ~CPerson()" << endl; }

	// ��� ��� �������̽�
	virtual void CalcFare() = 0;

	virtual unsigned int GetFare() const { return m_nFare; }
};

// �ʱ� Ȥ�� �ı� ������
class CBaby : public CPerson
{
public:
	// ������(0~7��) ��� ���
	virtual void CalcFare() 
	{ 
		m_nFare = 0;  // 0%  
	}
};

class CChild : public CPerson
{
public:
	// ���(8~13��) ��� ���
	virtual void CalcFare()
	{
		m_nFare = DEFAULT_FARE * 50 / 100; // 50%
	}
};

class CTeen : public CPerson
{
public:
	// û�ҳ�(14~19��) ��� ���
	virtual void CalcFare()
	{
		m_nFare = DEFAULT_FARE * 75 / 100; // 50%
	}
};

class CAdult : public CPerson
{
public:
	// ���(8~13��) ��� ���
	virtual void CalcFare()
	{
		m_nFare = DEFAULT_FARE;
	}
};

void CalcPersonFare()
{
	CPerson* arList[3] = { 0 };
	int nAge = 0;

	// 1. �ڷ� �Է� : ����� �Է¿� ���� ������ ��ü ����
	for (auto &person : arList)
	{
		cout << "���̸� �Է��ϼ��� : ";
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

		// ������ ��ü�� �´� ����� �ڵ����� ���ȴ�.
		// ���� if, switch-case ���� �� �� ���� �ڵ�� ��ü ����!!!
		person->CalcFare();
	}

	// 2. �ڷ� ��� : ����� ����� Ȱ���ϴ� �κ�
	for (auto person : arList)
	{
		cout << person->GetFare() << "��" << endl;
	}

	// 3. �ڷ� ���� �� ����
	for (auto person : arList)
	{
		delete person;
	}
}

// 7.4 ��Ӱ� ����ȯ

// const_cast<>     : ����� �����Ϳ��� const ����
// static_cast<>    : ������ �� ���� Ȥ�� ���� �� ��ȯ
// dynamic_cast<>   : ��Ÿ�ӽ� ���� Ȥ�� ���� �� ��ȯ
// reinterpret_cast : C �� �� ��ȯ �����ڿ� ���

// 7.4.2 dynamic_cast

// �������� ������ � ��ü�� �ִٰ� ����
// �װ��� ����Ű�� �����Ͱ� �⺻ ������ ��� ��ü������ � ��ü�� ���� �ν��Ͻ����� Ȯ�� �ʿ�
// �̷��� ����ϱ� �� ���� ����  dynamic_cast
// ��, dynamic_cast �� �����ߴٴ� ���� ���� ���� ���� �������� �귯���� �ִٴ� ����!!!

class CShape
{
public:
	CShape() { }
	virtual ~CShape() { }
	virtual void Draw() { cout << "CShape::Draw()" << endl; }
};



























