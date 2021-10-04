#include "pch.h"
#include "MyDLL.h"

Person::Person(std::string name, int age, std::string address) {
	this->age = age;
	this->name = name;
	this->address = address;
}

void Person::ShowInfo() {
	CString sMsg;
	sMsg.Format(_T("%d"), age);
	AfxMessageBox(sMsg);
}