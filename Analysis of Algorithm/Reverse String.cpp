#include <iostream>
using namespace std;

#define swap(a,b) { a^=b; b^=a; a^=b; }

void reverseStringIP(char* str)
{
	char *end = str;
	while (*end++ != '\0');
	for (end -= 2; end > str; --end, ++str) {
		swap(*end, *str);
	}
}

char* reverseStringNIP(char* str)
{
	int length = 0;
	for (char* ptr = str; *ptr != '\0'; ++ptr)
		++length;
	
	char* reverse_string = new char[length + 1];
	reverse_string[length] = '\0';

	for (int i = 0; i < length; ++i, ++str) {
		reverse_string[length - 1 - i] = *str;
	}

	return reverse_string;
}

int main()
{
	char str_test[] = "DataStructure";
	
	cout << "Input String: " << str_test << endl;
	reverseStringIP(str_test);
	cout << "After reverse (in-place): " << str_test << endl;

	cout << "Input String: " << str_test << endl;
	cout << "After reverse (not-in-place): " << reverseStringNIP(str_test) << endl;

	system("pause");
	return 0;
}