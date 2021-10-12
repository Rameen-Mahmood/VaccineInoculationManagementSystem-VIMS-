
#ifndef APPLICATION_MANAGER
#define APPLICATION_MANAGER

#include <iostream>
#include <iomanip>
#include <deque>
#include <algorithm>
#include "vaccine_data.h"
using namespace std;

class ApplicationManager //manages logic of application 
{
  private:
    string password;
    string username;
    Individual individual;
    deque <Individual> people = Vaccination_Data::GetInstance()->GetPeople();
  
  public:
    bool exists;
    ApplicationManager(){};
   
    bool confirm_username(string login_username)
    { 
      int i=0;
      while(i < people.size())
      {
        while (people[i].username != login_username)
        {
          cout<<login_username<<endl;
          
          cout<<"Username does not match, please enter again"<<endl;
          cin>>login_username;
      
          exists=false;
        }
        
        exists = true;
      
        i++;
      }
     
      return exists;
    }

    bool confirm_password(string login_password)
    {
      int i=0;
      while(i < people.size() )
      {
        if (people[i].password != login_password)
        {
          do 
          {
         cout<<"Password does not match, please enter again"<<endl;
          cin>>login_password;
          } while (people[i].password != password);
          exists=false;
        }
        
        i++;
      }
      exists=true;
      return exists;
    }
       

    void DisplayUserInformation()
  {
      Vaccination_Data::GetInstance()->print_peoples_info();
   }


};

#endif
