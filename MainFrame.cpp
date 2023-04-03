#include "MainFrame.h"
#include <wx/wx.h>
#include <limits>
#include <cmath>

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title) {
	wxFont textBoxFont(35, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	wxFont buttonFont(25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	panel->SetBackgroundColour(*wxBLACK);
	wxTextValidator validator(wxFILTER_NUMERIC);
	textbox->SetFont(textBoxFont);
	textbox->SetBackgroundColour(*wxLIGHT_GREY);
	textbox->SetValidator(validator);
	textbox->SetMaxLength(18);



	wxButton* toggleNegative = new wxButton(panel, 2, "+/-", wxPoint(2, 528), wxSize(125, 70));
	Buttons[0] = toggleNegative;
	wxButton* zero = new wxButton(panel, 3, "0", wxPoint(127, 528), wxSize(125, 70));
	Buttons[1] = zero;
	wxButton* comma = new wxButton(panel, 4, ".", wxPoint(252, 528), wxSize(125, 70));
	Buttons[2] = comma;
	wxButton* equals = new wxButton(panel, 5, "=", wxPoint(377, 528), wxSize(125, 70));
	Buttons[3] = equals;

	wxButton* one = new wxButton(panel, 11, "1", wxPoint(2,458), wxSize(125,70) );
	Buttons[4] = one;
	wxButton* two = new wxButton(panel, 22, "2", wxPoint(127, 458), wxSize(125, 70));
	Buttons[5] = two;
	wxButton* three = new wxButton(panel, 33, "3", wxPoint(252, 458), wxSize(125, 70));
	Buttons[6] = three;
	wxButton* addition = new wxButton(panel, 6, "+", wxPoint(377, 458), wxSize(125, 70));
	Buttons[7] = addition;
	

	wxButton* four = new wxButton(panel, 44, "4", wxPoint(2, 388), wxSize(125, 70));
	Buttons[8] = four;
	wxButton* five = new wxButton(panel, 55, "5", wxPoint(127, 388), wxSize(125, 70));
	Buttons[9] = five;
	wxButton* six = new wxButton(panel, 66, "6", wxPoint(252, 388), wxSize(125, 70));
	Buttons[10] = six;
	wxButton* subtraction = new wxButton(panel, 7, "-", wxPoint(377, 388), wxSize(125, 70));
	Buttons[11] = subtraction;
	

	wxButton* seven = new wxButton(panel, 77, "7", wxPoint(2, 318), wxSize(125, 70));
	Buttons[12] = seven;
	wxButton* eight = new wxButton(panel, 88, "8", wxPoint(127, 318), wxSize(125, 70));
	Buttons[13] = eight;
	wxButton* nine = new wxButton(panel, 99, "9", wxPoint(252, 318), wxSize(125, 70));
	Buttons[14] = nine;
	wxButton* multiply = new wxButton(panel, 8, "x", wxPoint(377, 318), wxSize(125, 70));
	Buttons[15] = multiply;

	wxButton* modulo = new wxButton(panel, 9, "%", wxPoint(2, 248), wxSize(125, 70));
	Buttons[16] = modulo;
	wxButton* clearAll = new wxButton(panel, 10, "CE", wxPoint(127, 248), wxSize(125, 70));
	Buttons[17] = clearAll;
	wxButton* clear = new wxButton(panel, 12, "C", wxPoint(252, 248), wxSize(125, 70));
	Buttons[18] = clear;
	wxButton* divide = new wxButton(panel, 13, "÷", wxPoint(377, 248), wxSize(125, 70));
	Buttons[19] = divide;

	for (int i = 0; i < 20; i++) {
		Buttons[i]->SetFont(buttonFont);
	};
	


	panel->Bind(wxEVT_BUTTON, &MainFrame::onButtonClicked, this);
}

void MainFrame::onButtonClicked(wxCommandEvent& event) {
	switch (event.GetId())
	{
	case 4:
		currentValue = textbox->GetValue();
		if ((wxAtof(currentValue) - floor(wxAtof(currentValue))) > 0) {
			break;
		}
		else {
			textbox->SetValue(currentValue + ".");
			break;
		}
	case 12://clear current
		textbox->SetValue("");
		break;
	case 10: //clear all
		currentValue = "";
		num1 = 0;
		num2 = 0;
		textbox->SetValue("");
		break;
	case 2:// toggle negative
		currentValue = textbox->GetValue();
		if ((wxAtof(currentValue) - floor(wxAtof(currentValue))) > 0) {
			textbox->SetValue(wxString::Format("%f", wxAtof(currentValue) * -1));
			break;
		}
		else {
			textbox->SetValue(wxString::Format("%d", wxAtoi(currentValue) * -1));
			break;
		}		
	case 6:
		num1 = wxAtof(textbox->GetValue());
		lastOperationUsed = 0; //add
		textbox->SetValue("");
		break;
	case 7:
		num1 = wxAtof(textbox->GetValue());
		lastOperationUsed = 1; //substract
		textbox->SetValue("");
		break;
	case 8:
		num1 = wxAtof(textbox->GetValue());
		lastOperationUsed = 2; //multiply
		textbox->SetValue("");
		break;
	case 13:
		num1 = wxAtof(textbox->GetValue());
		lastOperationUsed = 3; //divide
		textbox->SetValue("");
		break;
	case 9:
		num1 = wxAtof(textbox->GetValue());
		lastOperationUsed = 4; //modulo
		textbox->SetValue("");
		break;
	case 5:// equals button pressed
		num2 = wxAtoi(textbox->GetValue());
		switch (lastOperationUsed) {
		case 0: // add
			if (operationCompleted) {
				result = wxAtoi(textbox->GetValue()) + num2;
				if ((result - floor(result)) > 0) {
					textbox->SetValue(wxString::Format("%f", result));
				}
				else {
					textbox->SetValue(wxString::Format("%d", (int)result));
				}
			}
			if ((num1 > 0 && (num2 == result_Max)) || (num2 > 0 && (num1 == result_Max))) {
				wxMessageBox("Integer Overflow Detected!");
				break;
			}
			else if ((num1 < 0 && (num2 == result_Min)) || (num2 < 0 && (num1 == result_Min))) {
				wxMessageBox("Integer Overflow Detected!");
				break;
			}
			else {
				result = num1 + num2;
				if ((result - floor(result)) > 0) {
					textbox->SetValue(wxString::Format("%f", result));
					operationCompleted = true;
				}
				else {
					textbox->SetValue(wxString::Format("%d", (int)result));
					operationCompleted = true;
				}
				break;
			}
		case 1: // subtract
			if (operationCompleted) {
				result = wxAtoi(textbox->GetValue()) - num2;
				if ((result - floor(result)) > 0) {
					textbox->SetValue(wxString::Format("%f", result));
				}
				else {
					textbox->SetValue(wxString::Format("%d", (int)result));
				}
			}
			if ((num1 > 0 && (num2 == result_Max)) || (num2 > 0 && (num1 == result_Max))) {
				wxMessageBox("Integer Overflow Detected!");
				break;
			}
			else if ((num1 < 0 && (num2 == result_Min)) || (num2 < 0 && (num1 == result_Min))) {
				wxMessageBox("Integer Overflow Detected!");
				break;
			}
			else {
				result = num1 - num2;
				if ((result - floor(result)) > 0) {
					textbox->SetValue(wxString::Format("%f", result));
					operationCompleted = true;
				}
				else {
					textbox->SetValue(wxString::Format("%d", (int)result));
					operationCompleted = true;
				}
				break;
			}
		case 2: //multiply
			if (operationCompleted) {
				result = wxAtoi(textbox->GetValue()) * num2;
				if ((result - floor(result)) > 0) {
					textbox->SetValue(wxString::Format("%f", result));
				}
				else {
					textbox->SetValue(wxString::Format("%d", (int)result));
				}
			}
			if ( (num1 > 0 && (num2 == result_Max)) || (num2 > 0 && (num1 == result_Max)) ) {
				wxMessageBox("Integer Overflow Detected!");
				break;
			}
			else if ( (num1 < 0 && (num2 == result_Min)) || (num2 < 0 && (num1 == result_Min)) ) {
				wxMessageBox("Integer Overflow Detected!");
				break;
			}
			else {
				result = num1 * num2;
				if ((result - floor(result)) > 0) {
					textbox->SetValue(wxString::Format("%f", result));
					operationCompleted = true;
				}
				else {
					textbox->SetValue(wxString::Format("%d", (int)result));
					operationCompleted = true;
				}
				break;
			}
		case 3: // divide
			if (num1 == 0 || num2 == 0) {
				wxMessageBox("Division by zero not allowed!");
			}
			if (operationCompleted) {
				result = wxAtof(textbox->GetValue()) / num2;
				if ((result - floor(result)) > 0) {
					textbox->SetValue(wxString::Format("%f", result));
				}
				else {
					textbox->SetValue(wxString::Format("%d", (int)result));
				}
			}
			if ((num1 > 0 && (num2 == result_Max)) || (num2 > 0 && (num1 == result_Max))) {
				wxMessageBox("Integer Overflow Detected!");
				break;
			}
			else if ((num1 < 0 && (num2 == result_Min)) || (num2 < 0 && (num1 == result_Min))) {
				wxMessageBox("Integer Overflow Detected!");
				break;
			}
			else {
				result = num1 / num2;
				if ((result - floor(result)) > 0) {
					textbox->SetValue(wxString::Format("%f", result));
					operationCompleted = true;
				}
				else {
					textbox->SetValue(wxString::Format("%d", (int)result));
					operationCompleted = true;
				}
				break;
			}
		case 4: //mod
			if (operationCompleted) {
				break;
			}
			if ((num1 > 0 && (num2 == result_Max)) || (num2 > 0 && (num1 == result_Max))) {
				wxMessageBox("Integer Overflow Detected!");
				break;
			}
			else if ((num1 < 0 && (num2 == result_Min)) || (num2 < 0 && (num1 == result_Min))) {
				wxMessageBox("Integer Overflow Detected!");
				break;
			}
			else {
				result = fmod(num1,num2);
				if ((result - floor(result)) > 0) {
					textbox->SetValue(wxString::Format("%f", result));
					operationCompleted = true;
				}
				else {
					textbox->SetValue(wxString::Format("%d", (int)result));
					operationCompleted = true;
				}
				break;
			}
		}
		break;
		//numbers 0 - 9
	case 3:
		currentValue = textbox->GetValue();
		textbox->SetLabel(currentValue + "0");
		break;
	case 11:
		currentValue = textbox->GetValue();
		textbox->SetValue(currentValue + "1");
		break;
	case 22:
		currentValue = textbox->GetValue();
		textbox->SetValue(currentValue + "2");
		break;
	case 33:
		currentValue = textbox->GetValue();
		textbox->SetValue(currentValue + "3");
		break;
	case 44:
		currentValue = textbox->GetValue();
		textbox->SetValue(currentValue + "4");
		break;
	case 55:
		currentValue = textbox->GetValue();
		textbox->SetValue(currentValue + "5");
		break;
	case 66:
		currentValue = textbox->GetValue();
		textbox->SetValue(currentValue + "6");
		break;
	case 77:
		currentValue = textbox->GetValue();
		textbox->SetValue(currentValue + "7");
		break;
	case 88:
		currentValue = textbox->GetValue();
		textbox->SetValue(currentValue + "8");
		break;
	case 99:
		currentValue = textbox->GetValue();
		textbox->SetValue(currentValue + "9");
		break;
	}
	//end of numbers
}