/*****************************************************************//**
 * \file   Window.cpp
 * \brief  File running the programme.
 * 
 * 
 * \author PR
 * \date   April 2023
 *********************************************************************/

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