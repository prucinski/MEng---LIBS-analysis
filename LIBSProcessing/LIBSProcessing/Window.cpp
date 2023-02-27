#include "Window.h"

using namespace System;

using namespace System::Windows::Forms;

[STAThread]

void main()

{

    Application::EnableVisualStyles();

    Application::SetCompatibleTextRenderingDefault(false);

    LIBSProcessing::Window form;

    Application::Run(% form);

}