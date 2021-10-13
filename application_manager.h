
#ifndef APPLICATION_MANAGER
#define APPLICATION_MANAGER

#include <iostream>
#include <iomanip>
#include <deque>
#include "vaccine_data.h" 
using namespace std;

class ApplicationManager //manages the application of the user — confirms the username and password, and if they are correct, display user information
{
  private:
    string password;
    string username;
    Individual individual;
    bool exists;
    
    deque <Individual> people = Vaccination_Data::GetInstance()->GetPeople(); //using the getter function in Vaccination_Data class, we are getting the deque from the Vaccination_Data class and storing it into the deque "people"
  
  public:
    ApplicationManager(){}; //default constructor
   
    bool confirm_username(string login_username) //taking the user entered username and verifiying if it matches the username the user previously set
    { 
      int i=0;
      while(i < people.size()) //iterates until the size of the deque
      {
        while (people[i].username != login_username) //if they are not equal
        {
          cout<<"Username does not match, please enter again"<<endl;
          cin>>login_username; //keeps asking for the username until it is correct
      
          exists=false; //sets exists (which indicates the users existance of application) to false
        }
        
        exists = true; //if they are equal, the user account exists
      
        i++; //increment i 
      }
     
      return exists;
    }

    bool confirm_password(string login_password) //taking the user entered password and verifiying if it matches the password the user previously set
    {
      int i=0;
      while(i < people.size() )
      {
        while (people[i].password != login_password) //if they are not equal
        { 
          cout<<"Password does not match, please enter again"<<endl;
          cin>>login_password; //keeps asking for the password until it is correct
      
          exists=false;//sets exists (which indicates the users existance of application) to false
        }
        
        i++; //increment i 
      }
      exists=true;
      return exists;
    }

    void DisplayUserInformation() //Displays user information — this function allows the transfer of updated appointment booking information into the print_peoples_info() function in Vaccination_Data class
    {
      Vaccination_Data::GetInstance()->print_peoples_info();
    }


};

#endif
