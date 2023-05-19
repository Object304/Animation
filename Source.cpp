#include "MyForm.h"
using namespace Graphic;
[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::Run(gcnew MyForm());
	return 0;
}