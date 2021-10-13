//Object Oriented Programming — Final Project
//Vaccine Innoculation Management System (VIMS)
//Rameen Mahmood (rkm352) 

#include <iostream>
#include "Main_Menu.h" //include header file so that main.cpp has access to the contents in Main_Menu.h
using namespace std;

int main()
{
  Present_Menu attempt; //creating an object for Present_Menu class
  attempt.DisplayMenu(); //calling the DisplayMenu function present in the class

  return 0;
}