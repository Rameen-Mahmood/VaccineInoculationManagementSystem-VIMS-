#ifndef VACCINE_DATA
#define VACCINE_DATA

#include <iostream>
#include <fstream>
#include <deque>
#include "appointment_scheduling.h"

class Individual //stores attributes of users registering for the vaccine
{
  //friend class Login;
  protected:
    string username;
    string password;
    string fname;
    string lname;
    int ID;
    int age;
    char sex;
    string vaccination_status;
    int AppointmentTime;
    int AppointmentDay;
  
    //getter functions 
    string getUsername()
    {
      return username;
    }
    string getPassword()
    {
      return password;
    }
  
  public:
    Individual(){}; //default constructor
    Individual(string fname, string lname, int ID, int age, char sex, string username, string password, string vaccination_status) //parametrized constructor
    { 
      this->fname = fname;
      this->lname = lname;
      this->ID = ID;
      this->age = age;
      this->sex = sex;
      this->username = username;
      this->password = password;
      this->vaccination_status=vaccination_status;
    };
    //getter functions
    inline string getFirstName() const
    {
      return fname;
    }
    inline string getLastName() const
    {
      return lname;
    }
    inline int getID() const
    {
      return ID;
    }
    inline int getAge() const
    {
      return age;
    }
    inline char getSex() const
    {
      return sex;
    }
    inline string get_vaccination_status() const
    {
      return vaccination_status;
    }
  //allowing for friendship between Individual class and Vaccination_Data and ApplicationManager class
  friend class Vaccination_Data;
  friend class ApplicationManager;
};

class Vaccination_Data //Singleton class which reads vaccination data from file, stores it and then displays available vaccines based on users' preference
{
  private:
    int number_of_regions = 223; //number of regions are 22, hence 223 entries as first line is the headings
  
    //using dynamic memory allocation for the following arrays 
    string *location = new string[number_of_regions];
    string *vaccine1 = new string[number_of_regions]; 
    string *vaccine2 = new string[number_of_regions];
    string *vaccine3 = new string[number_of_regions];
    string *vaccine4 = new string[number_of_regions];
    string *vaccine5 = new string[number_of_regions];
    string *vaccine6 = new string[number_of_regions];
    string *vaccine7 = new string[number_of_regions];

    int number_of_people=0; //number of individuals in the deque
    static Vaccination_Data *v_data; //static instance of Singleton class
    deque <Individual> peopleToVaccinate; //deque which stores Individual objects

  public:
    Vaccination_Data(){}; //default constructor
     void addIndividual(Individual indiv) //function which stores Individual objects into the deque peopleToVaccinate
    {
      peopleToVaccinate.push_back(indiv);
      number_of_people++; //increment the number of users/Individual objects 
    } 
  
    //getter functions
    inline int GetNumberOfPeople()
    {
      return number_of_people;
    }
    inline deque <Individual> GetPeople()
    {
      return peopleToVaccinate;
    }
  
    static Vaccination_Data* GetInstance() //gets the static instance of the Vaccination_Data class
    {
      if (v_data == NULL)
      {
        v_data = new Vaccination_Data();
        return v_data;
      }
      return v_data;
    }

  void read_vaccination_data(string region) //reads from vaccination-data file, and outputs the vaccines of a certain region
  {
  ifstream read_file; 
  read_file.open("vaccination-data.csv");

  if (read_file.fail()) //if file fails to open
    {
      cout<<"Error, unable to open vaccination data file"<<endl;
      exit(1);
    }

  //read the first line of the file (headings)
  getline(read_file, location[0], ','), getline(read_file, vaccine1[0],','), getline(read_file,vaccine2[0],','),getline(read_file, vaccine3[0],','), getline(read_file, vaccine4[0],','), getline(read_file, vaccine5[0],','),getline(read_file,vaccine6[0],','),getline(read_file,vaccine7[0],'\n');

  int i = 1;
  while (!read_file.eof()) //reading and storing data into file until the file ends
  { 
    getline(read_file, location[i],',');
    getline(read_file, vaccine1[i],',');
    getline(read_file, vaccine2[i],',');
    getline(read_file, vaccine3[i],',');
    getline(read_file, vaccine4[i],',');
    getline(read_file, vaccine5[i],',');
    getline(read_file, vaccine6[i],',');
    getline(read_file, vaccine7[i],'\n');
  
    i++; //increment i
  }
//i represents the number of lines/entries in the file
 for (int j = 1 ; j<=i; j++)  //loop until the last entry of the file
  {
    if (region == location[j]) //if the region the user entered is the same as one of the locations in the file, output the vaccines available for the region
    {
      cout<<vaccine1[j]<<" "<<vaccine2[j]<<" "<<vaccine3[j]<<" "<<vaccine4[j]<<" "<<vaccine5[j]<<" "<<vaccine6[j]<<" "<<vaccine7[j]<<endl;
    }
  }
  read_file.close(); // close file
  }

  virtual void print_peoples_info() //Displaying user information
  {
    for (int i=0;i<number_of_people;i++)
    {
    cout<<endl;
    cout<<"Individual " << i << endl;
    cout<<"Name: "<<peopleToVaccinate[i].fname<<" "<<peopleToVaccinate[i].lname<<endl;
    cout<<"ID: "<<peopleToVaccinate[i].ID<<endl;
    cout<<"Age: "<<peopleToVaccinate[i].age<<endl;
    cout<<"Sex: "<<peopleToVaccinate[i].sex<<endl;
    cout<<"Vaccinated: "<<peopleToVaccinate[i].vaccination_status<<endl;
    cout<<"Username: "<<peopleToVaccinate[i].username<<endl;
    cout<<"Password: "<<peopleToVaccinate[i].password<<endl;

    //Display appointment time if user booked the appointment
    if (Appointment_scheduling::GetInstance()->GetAppointmentID() != "")
    {
    cout<<"Appointment date is scheduled at: November "<<Appointment_scheduling::GetInstance()->GetAppointmentDay()<<", 2021 at 8"<<Appointment_scheduling::GetInstance()->GetAppointmentTime()<<":00 hrs"<<endl;
    cout<<"Appointment ID: "<<Appointment_scheduling::GetInstance()->GetAppointmentID()<<endl;
    }
    else if (Appointment_scheduling::GetInstance()->GetAppointmentID() == "") //if user has not booked the appointment
    {
      cout<<"Appointment not scheduled as of yet. "<<endl;
    }
    }
      cout<<endl;
  }
    ~Vaccination_Data() //deconstructor
    {
      delete[] location;
      delete[] vaccine1;
      delete[] vaccine2;
      delete[] vaccine3;
      delete[] vaccine4;
      delete[] vaccine5;
      delete[] vaccine6;
      delete[] vaccine7;
    }
  friend class ApplicationManager; //allows friendship with ApplicationManager class
};
Vaccination_Data* Vaccination_Data :: v_data = NULL; //initializing the v_data instance to NULL

#endif