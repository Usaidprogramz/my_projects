#include <iostream>
#include <string>

using namespace std;

	void Data()
	{
	string vehicalno;
	string DriverName;
	cout<<"please enter the numberplate"<<endl;
	cin>>vehicalno;
	cout<<"please enter the driver name"<<endl;
	cin>>DriverName;
	cout<<"the car number = "<<vehicalno<<" and driver "<<DriverName<<" is added"<<endl;
    }

int main(){
	
	system ("pause");
	cout<<"\t\t***WELCOME TO CAR  PARKING***\n";
	
	int input;
	float car=0, bike=0, bus=0;
	float amount=0, count=0;
	
	while (true){
// Menue
	cout<<"press 1 for Car"<<endl;
	cout<<"press 2 for Bike"<<endl;
	cout<<"press 3 for Bus"<<endl;
	cout<<"press 4 for show Records"<<endl;
	cout<<"press 5 for to delete the Records"<<endl;
	cout<<"press 6 to exit"<<endl;
	cin>>input;
	cin.clear();
    cin.ignore(1000,'\n');
	
	if (input == 1)
	{
		if(count <= 2)
		{
		count = count+1;
		amount = amount + 200;
		car++;
		system("CLS");
		Data();
    }
	else{
	cout<<"parking is full\n";
	exit (0);
    }
	}
	
    else if (input == 2)
    {
	    if(count <= 2)
	{
		count = count+1;
		amount = amount + 100;
		bike++;
		system("CLS");
		Data();
	}
	else
	{
	cout<<"parking is full\n";
	exit (0);
	}
	}
	else if (input == 3)
	{
		if(count <= 2){
			count = count+1;
			amount = amount + 300;
		bus++;
		system("CLS");
		Data();
	}
	else
	{
	cout<<"parking is full\n";
	exit (0);	
	}
	}
	
// Stored Data
	else if (input == 4){
		cout<<"number of car is "<<car<<endl;
		cout<<"number of bike is "<<bike<<endl;
		cout<<"number of buses is "<<bus<<endl;
		cout<<"total amount is = "<<amount<<endl;
		cout<<"total number of vehical is ="<<count<<endl;
		
	}
	else if (input == 5){
		car = 0;
		bike = 0;
		bus = 0;
		amount = 0;
		count = 0;
		system("CLS");
		cout<<" ALL RECORD DELETED!\n";
	}
	else if (input == 6){
		
		cout<<"Exiting Program...."<<endl;
		exit (0);
	}
	else{
		system("CLS");
		cout<<"Invalid input please choose valid option(1-6)."<<endl;
		
	}	
}

return 0;	
	
}
