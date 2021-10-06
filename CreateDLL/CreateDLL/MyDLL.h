#pragma once

#include <string>
#include <iostream>

class AFX_EXT_CLASS Person {
public:
	Person(std::string name, int age, std::string address);
	void ShowInfo();

private:
	int age;
	std::string name;
	std::string address;
};
