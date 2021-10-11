
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
    //  for (int i = Vaccination_Data::GetInstance()->GetNumberOfPeople();i>0;i++)
    // //  int i = 0;
    // //  while (i < number_of_people)
      

    //   {

    //     cout<<people[i].username<<endl;
    //     do
    //       {
    //       if (people[i].username != login_username)
    //       {
    //         cout<<Vaccination_Data::GetInstance()->GetNumberOfPeople();
    //         cout<<people[i].username<<"hehe"<<login_username;
    //         cout<<"Username does not match, please enter again"<<endl;
    //         cin>>login_username;
    //         exists=false;
          
    //       }
    //       }while(people[i].username != login_username);
    //     } 
    //     cout<<"hehe"<<endl;
    //     //username=login_username;
        
    //     exists = true;

    //     // cout<<"Please enter your password"<<endl;
    //     // cin>>password;

    //     // confirm_password(password);
      int i=0;
      while(i < people.size() )
      {
        if (people[i].username != login_username)
        {
          do 
          {
         cout<<"Username does not match, please enter again"<<endl;
          cin>>login_username;
          } while (people[i].username != username);
          exists=false;
        }
        
        i++;
      }
      exists=true;
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
      // int i=0;
      // if (exists == true)
      // {
      // while (i < people.size())
      // {
      //   //do
      //    // {
      //     if (people[i].password != login_password)
      //     {
      //       cout<<login_password<<endl<<endl<<people[i].password;
      //       cout<<"Password does not match, please enter again"<<endl;
      //       cin>>login_password;
      //       exists=false;
      //       i++;
      //     }
      //  } //while(people[i].password != login_password);

        
        
       // Display();
      

    void DisplayUserInformation()
  {
      Vaccination_Data::GetInstance()->print_peoples_info();

      for (int i=people.size();i<0;i++)
      {
        cout<<people[i].username<<endl;
        cout<<people[i].password<<endl;
       }
      // int i;
      // i=0;
      // while(i < people.size() )
      // {
      //   cout<<people[i].username<<endl;
      //   cout<<people[i].password<<endl;
        
      //   i++;
      // }
   }

};

#endif
