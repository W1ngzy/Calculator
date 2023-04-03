#pragma once
#include <wx/wx.h>
#include <limits>
#include <wx/longlong.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
	wxPanel* panel = new wxPanel(this);
	wxTextCtrl* textbox = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(2, 196), wxSize(501, 50), wxTE_RIGHT);
private:
	wxString currentValue;
	int lastOperationUsed = 0;
	bool operationCompleted = false;
	double num1 = 0;
	double num2 = 0;
	double result_Max = std::numeric_limits<double>::max();
	double result_Min = std::numeric_limits<double>::min();
	double result = 0;
	wxButton* Buttons[20];
	void onButtonClicked(wxCommandEvent& event);
};