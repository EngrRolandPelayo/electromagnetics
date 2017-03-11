#include <iostream>
#include <iomanip>
#include <math.h>
#include <conio.h>

using namespace std;

double x,y,z;
double r,phi;
double rho,theta; 

void mainMenu();


    
void carttocyl(){
	 system("CLS");
	 cout << "--------------------------------------------------------------------------------" <<endl;
     cout <<"Enter x coordinate: ";
     cin >> x;
     cout <<"Enter y coordinate: ";
     cin >> y;
     cout <<"Enter z coordinate: ";
     cin >> z;

     r = sqrt(pow(x,2)+pow(y,2));
     phi = (180/3.14159) * atan(y/x);
     z = z;
     cout <<endl<< "--------------------------------------------------------------------------------" <<endl;
     cout <<"r = "<<r<<endl;
     cout <<"phi = "<<phi<<"\370"<<endl;
     cout <<"z = "<<z<<endl<<endl;
     cout <<"Press any button to continue..."<<endl;
     
     getch();
     
     mainMenu();
}
void carttospher(){
  	 system("CLS");
	 cout << "--------------------------------------------------------------------------------" <<endl;
     cout <<"Enter x coordinate: ";
     cin >> x;
     cout <<"Enter y coordinate: ";
     cin >> y;
     cout <<"Enter z coordinate: ";
     cin >> z;
     
     rho = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
     theta = (180/3.14159) * acos(x/rho);
     phi = (180/3.14159) * atan(y/x);
     cout <<endl<< "--------------------------------------------------------------------------------" <<endl; 
     cout <<"rho = "<<rho<<endl;
     cout <<"theta = "<<theta<<"\370"<<endl;
     cout <<"phi = "<<phi<<"\370"<<endl<<endl;
     cout <<"Press any button to continue..."<<endl;
     
     getch();
     
     mainMenu();
     }

void cyltocart(){
  	 system("CLS");
	 cout << "--------------------------------------------------------------------------------" <<endl;
     cout <<"Enter r coordinate: ";
     cin >> r;
     cout <<"Enter phi coordinate: ";
     cin >> phi;
     cout <<"Enter z coordinate: ";
     cin >> z;
     
     x = r*cos(phi*3.14159/180);
     y = r*sin(phi*3.14159/180);
     z = z;
     cout <<endl<< "--------------------------------------------------------------------------------" <<endl; 
     cout <<"x = "<<x<<endl;
     cout <<"y = "<<y<<endl;
     cout <<"z = "<<z<<endl<<endl;
     cout <<"Press any button to continue..."<<endl;
     
     getch();   
     
     mainMenu();
     }

void cyltospher(){
	 system("CLS");
	 cout << "--------------------------------------------------------------------------------" <<endl;
     cout <<"Enter r coordinate: ";
     cin >> r;
     cout <<"Enter phi coordinate: ";
     cin >> phi;
     cout <<"Enter z coordinate: ";
     cin >> z;
     
     rho = sqrt(pow(r*cos(phi*180/3.14159),2)+pow(r*sin(phi*180/3.14159),2)+pow(z,2));
     theta = acos(z/r);
     phi = phi;
     cout <<endl<< "--------------------------------------------------------------------------------" <<endl; 
     cout <<"rho = "<<rho<<endl;
     cout <<"theta = "<<theta<<"\370"<<endl;
     cout <<"phi = "<<phi<<"\370"<<endl<<endl;
     cout <<"Press any button to continue..."<<endl;
     
     getch();   
     
     mainMenu();
}

void sphertocart(){
	 system("CLS");
	 cout << "--------------------------------------------------------------------------------" <<endl;
     cout <<"Enter rho coordinate: ";
     cin >> rho;
     cout <<"Enter theta coordinate: ";
     cin >> theta;
     cout <<"Enter phi coordinate: ";
     cin >> phi;
     
     x = r*sin(theta*3.14159/180)*cos(phi*3.14159/180);
     y = r*sin(theta*3.14159/180)*sin(phi*3.14159/180);
     z = r*cos(theta*3.14159/180);
     cout <<endl<< "-------------------------------------------------------------------------------" <<endl;
     cout <<"rho = "<<rho<<endl;
     cout <<"theta = "<<theta<<"\370"<<endl;
     cout <<"phi = "<<phi<<"\370"<<endl<<endl;
     cout <<"Press any button to continue..."<<endl;
     
     getch();   
     
     mainMenu();
}

void sphertocyl(){
	 system("CLS");
	 cout << "--------------------------------------------------------------------------------" <<endl;
     cout <<"Enter rho coordinate: ";
     cin >> rho;
     cout <<"Enter theta coordinate: ";
     cin >> theta;
     cout <<"Enter phi coordinate: ";
     cin >> phi;
     
     r = sqrt(pow(rho*cos(phi*3.14159/180),2)+pow(rho*sin(phi*3.14159/180),2));
     phi = phi;
     z = rho*cos(theta*3.14159/180);
     cout <<endl<< "--------------------------------------------------------------------------------" <<endl;
     cout <<"r = "<<r<<endl;
     cout <<"phi = "<<phi<<"\370"<<endl;
     cout <<"z = "<<z<<endl<<endl;
     cout <<"Press any button to continue..."<<endl;
     
     getch();   
     
     mainMenu();

}

void mainMenu(){
	system("CLS");
	int inp;
	cout << "--------------------------------------------------------------------------------" <<endl;
	cout <<"Select function:" <<endl<<endl<< "1.Cart to Cyl"<<endl<<"2.Cart to Spher"<<endl<<"3.Cyl to Cart"<<endl<<"4.Cyl to Spher"<<endl<<"5.Spher to Cart"<<endl<<"6.Spher to Cyl"<<endl;
	cout << "7.Exit"<<endl<<endl;
	cout << "Enter Choice: ";
    cin >> inp;
    switch(inp){
                case 1:
                     carttocyl();
                     break;
                case 2:
                     carttospher();
                     break;
                case 3:
                     cyltocart();
                     break;
                case 4:
                     cyltospher();
                     break;
                case 5:
                     sphertocart();
                     break;
                case 6:
                     sphertocyl();
                     break;
                case 7:
            		 return;
            		 break;
                default:
                     break;            
    }

}



int main(){
    
    mainMenu();
    return 0;
}
