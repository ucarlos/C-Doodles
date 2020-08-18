//--------------------------------------------------------------------------------------------------
// Created by Ulysses Carlos on 5/3/20 using Ulysses-H270-HD3.
//--------------------------------------------------------------------------------------------------
#include <iostream>
#include <unistd.h>
#include <newt.h>
using namespace std;
const int box_width = 60;
const int box_height = 16;



void sensor_tracking(void){
    cout << "Sensor Tracking!" << endl;
    char ch;
    cin >> ch;
}

void status(void){
    cout << "Status!" << endl;
}

void search_logs(void){
    cout << "Logs!" << endl;
}

void test_sensors(void){
    cout << "Test!" << endl;
}

void database_options(void){
    cout << "Database!" << endl;
}

void email_options(void){
    cout << "Email!" << endl;
}

int main(void){
    newtComponent form, b1, b2, lb;
    newtComponent option_1, option_2;
	newtInit();
	newtCls();

	newtDrawRootText(0, 0, "CSC 4110 Project: Rain Alert Version 0.5");
	// auto i = newtLabel(20, 4, "Test");
	newtCenteredWindow(box_width, box_height, "Main Menu");

//	
	//b1 = newtCompactButton(10, 2, "Confirm");
	//b1 = newtButton(10, 1, "Fine.");
	//b2 = newtCompactButton(20, 2, "Cancel");
	form = newtForm(NULL, NULL, 0);
	lb = newtListbox(box_width / 4, 2, 10, 1);
	
	void (*function_list[5])(void);
	void (*function_pointer)(void);
	function_list[0] = &sensor_tracking;
	
	newtListboxSetWidth(lb, 30);
	
	newtListboxAppendEntry(lb, "Enable/Disable Tracking", (void *)(function_list[0]));
	// newtListboxAppendEntry(lb, "Status", (void *)"Status");
	// newtListboxAppendEntry(lb, "Search Logs", (void *)"Search");
	// newtListboxAppendEntry(lb, "Test Sensors", (void *)"Sensors");
	// newtListboxAppendEntry(lb, "Database Options", (void *)"Database");
	// newtListboxAppendEntry(lb, "Email Options", (void *)"Email");
	

	newtFormAddComponents(form, lb, NULL);
	
	
	newtRunForm(form);
	
        void (*function_p)(void);
	function_p = (void (*)(void))newtListboxGetCurrent(lb);
	function_p();
	newtFormDestroy(form);
	newtFinished();
}
