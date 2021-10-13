
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
    int index;
    
    deque <Individual> people = Vaccination_Data::GetInstance()->GetPeople(); //using the getter function in Vaccination_Data class, we are getting the deque from the Vaccination_Data class and storing it into the deque "people"
  
  public:
    ApplicationManager(){}; //default constructor
   
    bool confirm_username(string login_username) //taking the user entered username and verifiying if it matches the username the user previously set
    { 
      int i=0;
      exists=false;

      //i iterates through the entire loop and then the if statement checks at each i whether the login_username is equal or not. Once it reaches the end of the deque, it stops and returns false
      while (exists == false)
      {
        while (i<people.size())
        {
          if (people[i].username == login_username)
          {
            index = i; //the position where the Individual lies
            exists = true;
            break;
          }
          else
          {
            i++;
          }
        }
        if (i == people.size()) //once end of deque is reached
          {
            cout<<"The username you have entered is incorrect!"<<endl;
            exists=false;
            break;
          }
      
      }
     
      return exists;
    }

    bool confirm_password(string login_password) //function returns true if password matches, otherwise false
    {
      int i=0;
      exists=false;

      while (exists == false) 
      {
        while (i<people.size())
        {
          if (people[i].password == login_password) //checks if equal
          {
            exists = true; 
            break;
          }
          else
          {
            i++; //increments i
          }
        }
        if (i == people.size())
          {
            cout<<"The password you have entered is incorrect!"<<endl;
            exists=false;
            break;
          }
      
      }
      return exists;
    }

    void DisplayUserInformation() //Displays user information — this function allows the transfer of updated appointment booking information into the print_peoples_info() function in Vaccination_Data class
    {
      Vaccination_Data::GetInstance()->print_peoples_info(index); //we pass index (the position of the particular Individual object we are interested in) in the print_peoples_info function so that it displays information of that Individual object alone
    }


};

#endif
