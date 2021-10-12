#ifndef APPOINTMENT_SCHEDULING
#define APPOINTMENT_SCHEDULING

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Appointment_scheduling 
{
  private:

    int num_of_entries=31;
    int index; 
    string confirmed_time;
     
    string preferred_day;
    string *AppointmentID = new string[num_of_entries];
    string *AppointmentDay = new string[num_of_entries];
    string *AppointmentTime1 = new string[num_of_entries];
    string *AppointmentTime2 = new string [num_of_entries];
    
  
    static Appointment_scheduling *appts;
   
    string preferred_hour;

  public:
    Appointment_scheduling(){};

  static Appointment_scheduling* GetInstance()
    {
      if (appts == NULL)
      {
        appts = new Appointment_scheduling();
        return appts;
      }
      return appts;
    }

  inline string GetAppointmentDay()
  {
    return AppointmentDay[index];
  }
  inline string GetAppointmentTime()
  {
    return confirmed_time;
  }
  inline string GetAppointmentID()
  {
    return AppointmentID[index];
  }

  void read_appointment_data(string preferred_day)
{
  ifstream read_file;
  read_file.open("appointments.csv");
  // check for possible errors
  if(read_file.fail())
  {
    cerr << "Error, file could not be opened"<<endl;
    exit(1);
  }

  getline(read_file, AppointmentID[0], ','), getline(read_file, AppointmentDay[0],','), getline(read_file,AppointmentTime1[0],','),getline(read_file, AppointmentTime2[0],'\n');

  int i = 1;
  while (!read_file.eof())
  {
    getline(read_file, AppointmentID[i],',');
    getline(read_file, AppointmentDay[i],',');
    getline(read_file, AppointmentTime1[i],',');
    getline(read_file, AppointmentTime2[i],'\n');
  
    i++; //increment i 
  }

 for (int j = 1 ; j<i; j++) 
  {
    if (preferred_day == AppointmentDay[j])
    {
      cout<<"The available times are (in 24 hour format) is: "<<endl;
      cout<<AppointmentTime1[j]<<" "<<AppointmentTime2[j]<<endl;
    }
  }

  cout<<"Enter your preferred time from the available times."<<endl;
  cin>>preferred_hour;

  ofstream write_file;
  write_file.open("appointments.csv");
  //Adding the headings in the begining
  write_file << AppointmentID[0]<< "," <<AppointmentDay[0]<<","<<AppointmentTime1[0]<< ","<<AppointmentTime2[0]<<endl;

  cout<<i<<endl;
  for (int y = 1 ; y < i; y++) //Writing the file with the original columns and adding the temperature difference column. Starting with y = 1 as the numerical values start after the headings. 
  {
   
    if ((preferred_hour==AppointmentTime1[y]) && (preferred_day == AppointmentDay[y]))
    {
      index=y;
      confirmed_time=AppointmentTime1[y];
      AppointmentTime1[y]="";
      cout<<"Your appointment for November " <<AppointmentDay[y]<<", 2021 at " << confirmed_time <<"hrs "<<"is now confirmed."<<endl;
    }
    else if ((preferred_hour==AppointmentTime2[y]) &&(preferred_day == AppointmentDay[y]))
    {
      index=y;
      confirmed_time=AppointmentTime2[y];
      AppointmentTime2[y]="";
      AppointmentTime2[y]="";
      cout<<"Your appointment for November " <<AppointmentDay[y]<<", 2021 at " << confirmed_time <<"hrs "<<"is now confirmed."<<endl;
    }
    
    write_file << AppointmentID[y]<< "," <<AppointmentDay[y]<<","<<AppointmentTime1[y]<< ","<<AppointmentTime2[y]<<endl;
  
  }
  read_file.close(); // close file
  write_file.close();
  }

  ~Appointment_scheduling()
  {
    delete[] AppointmentID;
    delete[] AppointmentDay;
    delete[] AppointmentTime1;
    delete[] AppointmentTime2;
  }  
  friend class Vaccination_Data;
};
Appointment_scheduling *Appointment_scheduling :: appts = NULL; 

#endif