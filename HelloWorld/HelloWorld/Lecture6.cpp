#include "stdafx.h"

// ��� �⺻

// ��ü���� ���α׷��ֿ��� ���� �߿��� ��Ҵ�? ����!!!
// ������ �ٽ���? '���� ����'

class inheritMyData
{
private: // ������ ���� �Ұ���
	int m_nData = 0;  

public: // ������ ���� ����
	inheritMyData() { cout << "inheritMyData()" << endl; }
	int GetData() { return m_nData; }
	void SetData(int nParam) { m_nData = nParam; }

protected: // �Ļ� Ŭ������ ���� ����
	void PrintData() { cout << "inheritMyData::PrintData()" << endl; }
};

class inheritMyDataEx : public inheritMyData
{
public:
	inheritMyDataEx() { cout << "inheritMyDataEx()" << endl; }
	void TestFunc()
	{
		// �⺻ Ŭ���� ����� ����, public ���� ��ӹ޾Ƽ�����  
		PrintData(); // protected �̹Ƿ� �Ļ� Ŭ���������� ��밡��
		SetData(5);
		cout << "inheritMyData::GetData()" << endl;
	}
};

void inheritMyDataCaller()
{
	// �Ļ� Ŭ������ �����ڴ� ���� ȣ�������, ������ ���߿� �ȴ�!
	inheritMyDataEx data;

	// �⺻ Ŭ���� ����� ���� (inheritMyData)
	// �Ļ� Ŭ������ �ν��Ͻ��� �⺻ Ŭ������ �޼��带 ȣ���Ѵ�.
	data.SetData(10);
	cout << data.GetData() << endl;

	// �Ļ� Ŭ���� ����� ����
	data.TestFunc();
}

// 6.2 �޼��� ������ override(�����ϴ�)
// �޼��带 ������ �ϸ� ������ ���� '����'�ȴ�.

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
	// �Ļ� Ŭ�������� �⺻ Ŭ������ �޼��带 �������ߴ�.
	void SetData(int nParam)
	{
		// �Է� �������� ���� �����ϴ� ���ο� ����� �߰��Ѵ�.
		if (nParam < 0)
		{
			methodOver::SetData(0);
			// SetData(0); ==> ���ȣ�� �߻�. ��, methodOverEx::SetData() �� ȣ��
			// �Ļ����Ŀ��� �⺻ ������ ������ �޼��带 ȣ�� �Ϸ��� �ݵ�� �Ҽ� Ŭ������ ����ؾ� �Ѵ�.
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
	// �������� ���� �����ϴ� ����� ����.
	methodOver a;
	a.SetData(-10);
	cout << a.GetData() << endl;

	// �������� ���� �����ϴ� ����� �ִ�.
	methodOverEx b;
	b.SetData(15);
	cout << b.GetData() << endl;

}

void methodOverCaller2()
{
	// �Ļ� ������ �⺻ �������� �����ϴ� ���� �ſ� �ڿ������� ��.
	// ��������, ��������
	// �� ���İ� ���� ������ �ٸ� ��� ������ ȣ��� � �޼��尡 ȣ��Ǵ°�?
	// ==> '���� ����'(������ Ȥ�� ������)

	methodOverEx ex;
	methodOver &rData = ex; 
	rData.SetData(15);  // methodOver �� �����ڷ� ���������� �޼��尡 ȣ���
	cout << rData.GetData() << endl;

	// SetData() �� ȣ�� �ߴµ� ���������� methodOver �Դϴ�. ���� ���� �Ҵ�� �� ������ methodOverEx �ӿ��� methodOver::SetData()
	// �� ȣ��ȴ�. �׸��� �� �ڵ�� ���������� �޸� �� ������ �ִ�.
	// ==> delete pData ������ ���� �ϴ��� methodOverEx �� �Ҹ��ڰ� ȣ����� �ʱ� �����̴�.
	// '�Ҹ��� ����ȭ' 
	methodOver *pData = new methodOverEx;
	pData->SetData(5);
	delete pData; // �� ������ methodOver �� �Ҹ��ڸ� ȣ��, methodOverEx �� �Ҹ��ڴ� ȣ����� �ʴ� ������ �ִ�.
}

// ��� ������ ������ : ���������δ� ����������, ���� �ٶ��� ���� �ʴ�! ����� ���� ����!

// ��ӿ����� �����ڿ� �Ҹ���
// 6.3.1 ȣ�� ����

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
		// ���⼭ �⺻ Ŭ������ ����� ���� �� ������ �⺻ Ŭ������ �Ҹ��� ����� ���� �߻�.
		// �Ļ� Ŭ�������� �⺻ Ŭ������ ��� ������ ���� ���� �������� �ʴ� ���� ����!
		// �Ļ� Ŭ�������� �⺻ Ŭ������ ��� ������ �ʱ�ȭ ���� �ʴ´�!!!
		// delete[] m_pszData;
	}
};

// �Ļ� Ŭ������ �����ڰ� ���� ȣ��ǰ� �̾ ������ �ö󰡵� ȣ��
// ���� ������ ��� �Ļ� Ŭ���� �����ڰ� �⺻ Ŭ������ �����ڸ� '����' �ϰ� ȣ���Ѵ�.
// ����, �����ڰ� ���� ���·� ���� ���ǵ� ���?
// ==> �Ļ� Ŭ�������� ���� Ŭ���� �����ڴ� �ϳ��� '����', �������� ������ ����Ʈ ������ ȣ��

void inheritConstructorCaller()
{
	cout << "begin" << endl;
	inheritConstructorC data;
	cout << "end" << endl;
}

// �����ڿ� �Ҹ��ڴ� ��ü �ڽ��� �ʱ�ȭ �� ������ �����ؾ� �Ѵ�!!

// 6.3.2 ������ ����

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
	// C++11 '������ ���' ==> �Ļ� Ŭ������ ���� �� ���� ���ǵ� ���� Ŭ������ �����ڵ��� �״�� �������� ����
	using selectConstructor::selectConstructor;

	selectConstructorEx() { cout << "selectConstructorEx()" << endl; }

	// �⺻ Ŭ������ �� ���� ������ �� int ����
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












