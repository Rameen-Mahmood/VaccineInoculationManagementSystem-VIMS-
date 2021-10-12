#ifndef MAIN_MENU
#define MAIN_MENU

#include <iostream>
#include <deque>
#include "vaccine_data.h"
#include "application_manager.h"
#include "appointment_scheduling.h"
// using namespace std;
 
// Vaccination_Data* Vaccination_Data :: v_data = NULL;
// Appointment_scheduling *Appointment_scheduling :: appts = NULL; 

class Present_Menu
{
  private:
  int selection;
  string region;

  string fname;
  string lname;

  string login_username;
  string login_password;
 
  int ID;
  char sex;
  string username;
  string password;
  string confirm_password;

  int age;
  string vaccination_status;
  double temperature;
  string allergies;
  string preferred_day;
  bool eligible=false;
  bool registered=false;

  public:
  Present_Menu(){};
  
  void DisplayMenu()
{
  cout<<endl<<endl;
  cout<<setw(55)<<"VACCINE INNOCULATION MANAGEMENT SYSTEM (VIMS)"<<endl<<endl;
  cout<<setw(35)<<"~MAIN MENU~"<<endl;
  cout<<"Option 1: To check which vaccine is available in your region, press 1."<<endl;
  cout<<"Option 2: To see if you are eligible for getting the vaccine, press 2."<<endl;
  cout<<"Option 3: To register for the vaccine, press 3."<<endl;
  cout<<"Option 4: To set up an appointment to get your preferred choice of vaccine, press 4."<<endl;
  cout<<"Option 5: To login and see your status, press 5."<<endl;
  cout<<"Enter your choice: "<<endl;
  cin>>selection;

  if (selection == 1)
  {
    First_Selection();
  }
  else if (selection == 2)
  {
    Second_Selection();
  }
  else if ((selection == 3) && (eligible == true))
  {
    eligible=false;
    Third_Selection();
    registered=true;
  }
  else if ((selection == 3) && (eligible == false))
  {
    cout<<"You are not eligible to register for the vaccine, first verify your eligibility!"<<endl<<endl;
    Second_Selection();

  }
  else if ((selection == 4) && (registered == true))
  {
    Fourth_Selection();
  }
  else if ((selection == 4) && (registered == false))
  {
    if (eligible == false)
    {
      cout<<"You are not eligibile for the vaccine, hence you cannot schedule an appointment for the vaccine!"<<endl<<endl;
      Second_Selection();
    }
    else
    {
      cout<<"You are not registered for the vaccine, hence you cannot schedule an appointment for the vaccine!"<<endl<<endl;
      Third_Selection();
    }
  }
  else if ((selection == 5) && (registered == true))
  {
    Fifth_Selection();
  }
   else if ((selection == 5) && (registered == false))
  {
    if (eligible == false)
    {
      cout<<"You are not eligible for the vaccine, hence no user record found!"<<endl<<endl;
      Second_Selection();
    }
    else
    {
    cout<<"You are not registered for the vaccine, hence no user record found!"<<endl<<endl;
    Third_Selection();
    }
  }
}

void First_Selection()
{
  cout<<"Enter the region whose available vaccines you'd like to see "<<endl;
  cin.ignore();
  getline(cin, region);
  static Vaccination_Data vd;
  vd.read_vaccination_data(region);
 
  DisplayMenu();
}

void Second_Selection()
{
  cout<<"Please enter your age."<<endl;
  cin>>age;
  cout<<"Have you been vaccinated before? (Yes/No)"<<endl;
  cin>>vaccination_status;
  cout<<"Do you have any allergies? (Yes/No)"<<endl;
  cin>>allergies;
  cout<<"What is your temperature?"<<endl;
  cin>>temperature;
  
  if (age < 18 || allergies=="Yes" || temperature > 99 || temperature < 94)
  {
    eligible=false;
    cout<<"You are not eligible to get the vaccine"<<endl;
    
  }
  else 
  {
    eligible=true;
    cout<<"You are eligible to get the vaccine, you may now proceed to registration."<<endl;
    DisplayMenu();

  }
   
  }

  void Third_Selection()
  {
    cout<<setw(35)<<"~VACCINE REGISTRATION~"<<endl;
    cout<<"Please enter your first name."<<endl;
    cin>>fname;
    cout<<"Please enter your last name."<<endl;
    cin>>lname;
    cout<<"Please enter your ID number [a series of integers]"<<endl;
    cin>>ID;
    cout<<"Please enter your gender (Male: M, Female: F)"<<endl;
    cin>>sex;
    cout<<"Please set your username"<<endl;
    cin>>username;
    cout<<"Please set your password"<<endl;
    cin>>password;
    
    Individual individual(fname, lname, ID, age, sex, username, password, vaccination_status);
    //individual.addIndividual(individual);
    
    Vaccination_Data::GetInstance()->addIndividual(individual);
    
    // Vaccination_Data::GetInstance()->print_peoples_info();

    registered=true;
    DisplayMenu();
  
  }

  void Fourth_Selection()
  {
    cout<<setw(35)<<"~APPOINTMENT SCHEDULE~"<<endl;
    cout<<"The appointments available are for the month of November, 2021. Please select your preferred date [1st to 30th Nov]"<<endl;
    cin>>preferred_day;

    Appointment_scheduling::GetInstance()->read_appointment_data(preferred_day);

    DisplayMenu();
  }

  void Fifth_Selection()
  {
    cout<<"Please enter your username"<<endl;
    cin>>login_username;
    ApplicationManager AM;
  
    if (AM.confirm_username(login_username) == true)
    {
      cout<<"Please enter your password"<<endl;
      cin>>login_password;
      AM.confirm_password(login_password);
    }
    if (AM.confirm_password(login_password)==true)
    {
      AM.DisplayUserInformation();
    }

    DisplayMenu();
    
  }

};

#endif