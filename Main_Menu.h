#ifndef MAIN_MENU
#define MAIN_MENU

#include <iostream>
#include <deque>
#include <iomanip>
//includes these header files as it uses functions/creates object/references the classes present in these header files here
#include "vaccine_data.h"
#include "application_manager.h"
#include "appointment_scheduling.h"

class Present_Menu //this class is responsible for taking the selection of the user, and performing actions based on their selection
{
  private: //declaring variables
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
  Present_Menu(){}; //default constructor
  
  void DisplayMenu() //function to display the menu 
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
  cin>>selection; //reads user input

  //Performs validation check to see if the user entered a correct value
  while(selection != 1 && selection != 2 && selection != 3 &&selection != 4 && selection != 5)
  {
    cout<<"Wrong selection — choices range from 1 to 5. Please enter again!"<<endl;
    cin>>selection;
  }

  //certain functions are called depending on user selection
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
    eligible=false; //set eligible to false so that each user has to check their eligibility before registration
    Third_Selection();
    registered=true;//once registered, set to true
  }
  else if ((selection == 3) && (eligible == false)) //the user needs to check eligibility before registering
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
    if (eligible == false) //needs to check eligibility first
    {
      cout<<"You are not eligibile for the vaccine, hence you cannot schedule an appointment for the vaccine!"<<endl<<endl;
      Second_Selection();
    }
    else //if eligible but hasn't registered, user must register first
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

//Functions pertaining to each selection 
void First_Selection() //if the user enters 1 
{
  cout<<"Enter the region whose available vaccines you'd like to see "<<endl;
  cin.ignore(); //used to ignore whitespaces the user enters
  getline(cin, region);
  static Vaccination_Data vd; //create static instance
  vd.read_vaccination_data(region); //calling function in Vaccination_Data class
 
  DisplayMenu(); //Once this is done, displays the menu again so that the user can continue to register, login etc
}

void Second_Selection() //if the user enters 2
{ 
  //asking questions relating to eligibility criteria
  cout<<"Please enter your age [integer value]"<<endl;
  cin>>age;
  cout<<"Have you been vaccinated before? (Yes/No)"<<endl;
  cin>>vaccination_status; 
  cout<<"Do you have any allergies? (Yes/No)"<<endl;
  cin>>allergies; 
  cout<<"What is your temperature? [value between 95 and 98]"<<endl;
  cin>>temperature;
  
  //checks user input against eligibility criteria
  if (age < 18 || allergies=="Yes" || temperature > 99 || temperature < 94)
  {
    eligible=false;
    cout<<"You are not eligible to get the vaccine"<<endl;
    //exits the program after this, since registration, appointment booking and login is not available if ineligible
  }
  else 
  {
    eligible=true;
    cout<<"You are eligible to get the vaccine, you may now proceed to registration."<<endl;
    DisplayMenu();
  }
  }

  void Third_Selection() //if user enters 3
  {
    //collects information from the user for registration
    cout<<setw(55)<<"~VACCINE REGISTRATION~"<<endl;
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
    
    //add the information to Individual object
    Individual individual(fname, lname, ID, age, sex, username, password, vaccination_status);
    
    //use addIndividual member function in Vaccination_Data class to add the individual to the queue
    Vaccination_Data::GetInstance()->addIndividual(individual);
    
    registered=true; //set registered to true
    DisplayMenu(); //Display Menu again
  
  }

  void Fourth_Selection() //if user presses 3
  {
    cout<<setw(35)<<"~APPOINTMENT SCHEDULING~"<<endl;
    cout<<"The appointments available are for the month of November, 2021. Please select your preferred date [1st to 30th Nov]"<<endl;
    cin>>preferred_day; //reads input from user -- the preferred date of vaccination

    Appointment_scheduling::GetInstance()->read_appointment_data(preferred_day); //calls member function of Appointment_scheduling class

    DisplayMenu(); //displays menu again
  }

  void Fifth_Selection() //if user presses 5
  {
    cout<<"Please enter your username"<<endl;
    cin>>login_username;
    ApplicationManager application; //creates object for class ApplicationManager
  
    if (application.confirm_username(login_username) == true) //if username user enters matches the previously set username
    {
      //ask for password
      cout<<"Please enter your password"<<endl;
      cin>>login_password; 

      //check for password
      if (application.confirm_password(login_password)==true) //if password matches
      {
      application.DisplayUserInformation(); //display complete user information once both username and password match
      }
    }
    DisplayMenu(); //display menu again
  }

};

#endif