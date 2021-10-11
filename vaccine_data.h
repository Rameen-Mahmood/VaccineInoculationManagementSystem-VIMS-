#ifndef VACCINE_DATA
#define VACCINE_DATA

#include <iostream>
#include <fstream>
#include <deque>

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
    // deque <Individual> peopleToVaccinate;
  
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
    string getFirstName() const
    {
      return fname;
    }
    string getLastName() const
    {
      return lname;
    }
    int getID() const
    {
      return ID;
    }
    int getAge() const
    {
      return age;
    }
    char getSex() const
    {
      return sex;
    }
    string get_vaccination_status() const
    {
      return vaccination_status;
    }
   
  friend class Vaccination_Data;
  friend class ApplicationManager;
};

class Vaccination_Data
{
  private:
   // queue <Individual> peopleToVaccinate;
    //string *location;
    string *location = new string[223];
    string vaccine1[223]; //number of regions are 223
    string vaccine2[223];
    string vaccine3[223];
    string vaccine4[223];
    string vaccine5[223];
    string vaccine6[223];
    string vaccine7[223];
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
  
    int GetNumberOfPeople()
    {
      return number_of_people;
    }
    deque <Individual> GetPeople()
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
      // cout<<"Name: "<<getFirstName()<<" "<<getLastName()<<endl;
      // cout<<"ID: "<<getID()<<endl;
      // cout<<"Age: "<<getAge()<<endl;
      // cout<<"Sex: "<<getSex()<<endl;
     
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
      }
        cout<<endl;
    }
  friend class ApplicationManager;
};
Vaccination_Data* Vaccination_Data :: v_data = NULL;

#endif