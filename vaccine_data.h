#ifndef VACCINE_DATA
#define VACCINE_DATA

#include <iostream>
#include <fstream>
#include <deque>
#include "appointment_scheduling.h"

using namespace std;

class Individual
{
  //friend class Login;
  protected:
    string username;
    string password;

    string getUsername()
    {
      return username;
    }
    string getPassword()
    {
      return password;
    }
  
    string fname;
    string lname;
    int ID;
    int age;
    char sex;
    string vaccination_status;
    
    int AppointmentTime;
    int AppointmentDay;
  
  public:
  //queue <Individual> myq;
    Individual(){};
    Individual(string fname, string lname, int ID, int age, char sex, string username, string password, string vaccination_status)
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
   
  friend class Vaccination_Data;
  friend class ApplicationManager;
};

class Vaccination_Data
{
  private:
    int number_of_regions = 223;
   // queue <Individual> peopleToVaccinate;
    //string *location;
    string *location = new string[number_of_regions];
    string *vaccine1 = new string[number_of_regions]; //number of regions are 223
    string *vaccine2 = new string[number_of_regions];
    string *vaccine3 = new string[number_of_regions];
    string *vaccine4 = new string[number_of_regions];
    string *vaccine5 = new string[number_of_regions];
    string *vaccine6 = new string[number_of_regions];
    string *vaccine7 = new string[number_of_regions];
    int number_of_people=0;
    static Vaccination_Data *v_data; //initialize outside of class
    deque <Individual> peopleToVaccinate;

  public:
    Vaccination_Data(){};
     void addIndividual(Individual indiv) 
    {
      peopleToVaccinate.push_back(indiv);
      number_of_people++;
    
    } 
  
    inline int GetNumberOfPeople()
    {
      return number_of_people;
    }
    inline deque <Individual> GetPeople()
    {
      return peopleToVaccinate;
    }

    static Vaccination_Data* GetInstance()
    {
      if (v_data == NULL)
      {
        v_data = new Vaccination_Data();
        return v_data;
      }
      return v_data;
    }

  void read_vaccination_data(string region)
{
  ifstream read_file;

  read_file.open("vaccination-data.csv");
  if (read_file.fail())
    {
      cout<<"Error, unable to open vaccination data file"<<endl;
      exit(1);
    }

  getline(read_file, location[0], ','), getline(read_file, vaccine1[0],','), getline(read_file,vaccine2[0],','),getline(read_file, vaccine3[0],','), getline(read_file, vaccine4[0],','), getline(read_file, vaccine5[0],','),getline(read_file,vaccine6[0],','),getline(read_file,vaccine7[0],'\n');

  int i = 1;
  while (!read_file.eof())
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

 for (int j = 1 ; j<=i; j++) 
  {
  
    if (region == location[j])
    {
      cout<<vaccine1[j]<<" "<<vaccine2[j]<<" "<<vaccine3[j]<<" "<<vaccine4[j]<<" "<<vaccine5[j]<<" "<<vaccine6[j]<<" "<<vaccine7[j]<<endl;
    }
  }
  read_file.close(); // close file
}
   virtual void print_peoples_info()
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
          if (Appointment_scheduling::GetInstance()->GetAppointmentID() != "")
          {
          cout<<"Appointment date is scheduled at: November "<<Appointment_scheduling::GetInstance()->GetAppointmentDay()<<", 2021 at 8"<<Appointment_scheduling::GetInstance()->GetAppointmentTime()<<":00 hrs"<<endl;
          cout<<"Appointment ID: "<<Appointment_scheduling::GetInstance()->GetAppointmentID()<<endl;
          }
          else if (Appointment_scheduling::GetInstance()->GetAppointmentID() == "")
          {
            cout<<"Appointment not scheduled as of yet. "<<endl;
          }
      }
        cout<<endl;
    }
    ~Vaccination_Data()
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
  friend class ApplicationManager;
};
Vaccination_Data* Vaccination_Data :: v_data = NULL;

#endif