#include"workerManager.h"


WorkerManager::WorkerManager()
{
	//1���ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�

	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		//��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2���ļ����ڵ�����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3���ļ������ұ���ְ������
	int num = this->get_EmpNum();
	//cout << "ְ������Ϊ�� " << num << endl;
	this->m_EmpNum = num;

	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//���ļ��е����ݴ浽������
	this->init_Emp();

	//���Դ���
	//for (int i = 0; i < this->m_EmpNum; i++)
	//{
	//	cout << "ְ����ţ� " << this->m_EmpArray[i]->m_Id
	//		<< " ������ " << this->m_EmpArray[i]->m_Name
	//		<< " ���ű�ţ� " << this->m_EmpArray[i]->m_DeptId << endl;
	//}

}

//չʾ�˵�
void WorkerManager::Show_Menu()
{
	cout << "*********************************************" << endl;
	cout << "**********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  **************" << endl;
	cout << "*************  1.����ְ����Ϣ  **************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  **************" << endl;
	cout << "*************  3.ɾ����ְְ��  **************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  **************" << endl;
	cout << "*************  5.����ְ����Ϣ  **************" << endl;
	cout << "*************  6.���ձ������  **************" << endl;
	cout << "*************  7.��������ĵ�  **************" << endl;
	cout << "*********************************************" << endl;
	cout << endl;
}

//0.�˳�ϵͳ
void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);//�˳�����
}

//1.����ְ��
void WorkerManager::Add_Emp()
{
	cout << "���������ְ��������" << endl;

	int addNum = 0;//�����û�����������
	cin >> addNum;

	if (addNum > 0)
	{
	    //�����¿ռ��С
		int newSize = this->m_EmpNum + addNum;
		//�����¿ռ�
		Worker ** newSpace = new Worker * [newSize];
		//��ԭ���ռ������ݿ������¿ռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//�������������
		for (int i = 0; i < addNum; i++)
		{
			int id;//ְ�����
			string name;//ְ������
			int dSelect;//����ѡ��

			cout << "�������" << i + 1 << " ����ְ����ţ�" << endl;
			cin >> id;
			cout << "�������" << i + 1 << " ����ְ��������" << endl;
			cin >> name;
			cout << "��ѡ���ְ����λ�� " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
			    worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			//��������ְ��ָ�뱣�浽������
			newSpace[this->m_EmpNum + i] = worker;

		}

		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;
		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;
		//�����µ�ְ������
		this->m_EmpNum = newSize;
		//����ְ����Ϊ�յı�־
		this->m_FileIsEmpty = false;
		//��ʾ��Ϣ
		cout << "�ɹ����" << addNum << "����ְ��" << endl;
		//���浽�ļ���
		this->save();
	}
	else
		cout << "��������" << endl;

	//��������� �����ص��ϼ�Ŀ¼
	system("pause");
	system("cls");

}

//�����ļ�
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); //������ķ�ʽ���ļ� --д�ļ�

	if (!ofs.is_open())
	{
		cout << "�ļ���ʧ��" << endl;
		return;
	}

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}

//ͳ���ļ�������
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}
	ifs.close();

	return num;
}

//��ʼ��Ա��
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else 
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();

}

//2����ʾְ��
void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//���ö�̬���ó���ӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");

}

//����ְ������ж�ְ���Ƿ���ڣ��������򷵻�ְ������������λ�ã��������򷵻�-1
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}


//3��ɾ��ְ��
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "������Ҫɾ����ְ����ţ�" << endl;
		int id;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1)
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];//����ǰ��
			}
			this->m_EmpNum--;//������������Ա����
			this->save();//����ͬ�����µ��ļ���
			cout << "ɾ���ɹ���" << endl;
		}
		else
			cout << "ְ�������ڣ�" << endl;
	}
	system("pause");
	system("cls");
	
}

//4���޸�ְ��
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "������Ҫ�޸ĵ�ְ����ţ�" << endl;
		int id;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1)
		{
			delete this->m_EmpArray[index];//�ͷŸ�ְ������Ϣ

			int newId;
			string newName;
			int dSelect;

			cout << "�鵽�� " << id << "��ְ������������ְ���ţ� " << endl;
			cin >> newId;
			cout << "�������������� " << endl;
			cin >> newName;
			cout << "�������λ�� " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, 1);
				break;
			case 2:
				worker = new Manager(newId, newName, 2);
				break;
			case 3:
				worker = new Boss(newId, newName, 3);
				break;
			default:
				break;
			}
			this->m_EmpArray[index] = worker;

			this->save();//����ͬ�����µ��ļ���
			cout << "�޸ĳɹ���" << endl;
		}
		else
			cout << "ְ�������ڣ�" << endl;
	}
	system("pause");
	system("cls");

}

//5������ְ��
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2������������" << endl;

		int select;
		cin >> select;

		if (select == 1)//��ְ����Ų���
		{
			cout << "��������ҵ�ְ����ţ�" << endl;
			int id;
			cin >> id;
			int index = this->IsExist(id);
			if (index != -1)
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else
				cout << "ְ�������ڣ�" << endl;
		}
		else if (select == 2)//����������
		{
			cout << "��������ҵ�ְ��������" << endl;
			string name;
			cin >> name;

			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
					this->m_EmpArray[i]->showInfo();

					flag = true;
				}
				
			}
			if (flag == false)
				cout << "����ʧ�ܣ����޴���" << endl;
		}
		else
			cout << "����ѡ������" << endl;
			
	}
	system("pause");
	system("cls");

}

//6������ְ��
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1����ְ���������" << endl;
		cout << "2����ְ����Ž���" << endl;
		int select;
		cin >> select;

		//ѡ������
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//��ְ���������
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
						minOrMax = j;

				}
				else if (select == 2)//��ְ����Ž���
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
						minOrMax = j;

				}
			}

			//��������
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
			
		cout << "����ɹ��������Ľ��Ϊ��" << endl;
		this->save();
		this->Show_Emp();
	}

}

//7������ļ�
void WorkerManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);//ɾ���ļ������´���
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//ɾ��������ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//ɾ����������ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;

		}
		cout << "��ճɹ���" << endl;

	}
	else if (select == 2)
	{
		//return;
		system("pause");
		system("cls");
	}
	else
		cout << "����ѡ������" << endl;

	system("pause");
	system("cls");

}


WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if(this->m_EmpArray[i] != NULL)
				delete this->m_EmpArray[i];
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}