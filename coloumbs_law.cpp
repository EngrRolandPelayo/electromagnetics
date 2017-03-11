#include <iostream>
#include <iomanip>
#include <math.h>
#include <conio.h>
#include <fcntl.h>
#include <cctype>
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
CONSOLE_CURSOR_INFO cursor;

const int ESCAPE=27;

void gotoXY(int, int);
void setCursorSize(){
	cursor.dwSize = 100;
	cursor.bVisible = true;
	SetConsoleCursorInfo(console, &cursor);
}
struct Color
{
    int color;

    Color(int color_): color(color_) {}

    Color operator + (const Color & other) const { return Color(this->color | other.color); }
};

#define FORE_LIGHT(color) const Color cfl##color##_ = FOREGROUND_##color | FOREGROUND_INTENSITY;
#define BACK_LIGHT(color) const Color cbl##color##_ = BACKGROUND_##color | BACKGROUND_INTENSITY;
#define FORE_DARK(color)  const Color cfd##color##_ = FOREGROUND_##color;
#define BACK_DARK(color)  const Color cbd##color##_ = BACKGROUND_##color;

FORE_LIGHT(RED) FORE_LIGHT(GREEN) FORE_LIGHT(BLUE)
BACK_LIGHT(RED) BACK_LIGHT(GREEN) BACK_LIGHT(BLUE)
FORE_DARK (RED) FORE_DARK (GREEN) FORE_DARK (BLUE)
BACK_DARK (RED) BACK_DARK (GREEN) BACK_DARK (BLUE)

const Color cdefault_ = cfdRED_ + cfdGREEN_ + cfdBLUE_;

std::ostream & operator << (std::ostream & os, Color c)
{
    return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c.color), os;
}

void mainMenu();
void twoPointForce();
void nPointField();
void onePointField();
void lineChargeField();
void surfaceChargeField();

void twoPointForce(){
	system("CLS");
	int numCharges;
	double q1,q2;
	double x1,x2;
	double y1,y2;
	double z1,z2;
	char pref1,pref2;
    cout << cflBLUE_ << "--------------------------------------------------------------------------------" <<endl<<cdefault_;
	cout << "Enter magnitude of first charge: ";
	cin >> q1;
	cout << "Choose prefix of Q1 <choose letter "<<cflGREEN_<<"p,n,u,m"<<cdefault_<<"> :";
	cin >> pref1;
	cout << "Enter x coordinate of first charge: ";
	cin >> x1;
	cout << "Enter y coordinate of first charge: ";
	cin >> y1;
	cout << "Enter z coordinate of first charge: ";
	cin >> z1;
	cout << endl;
	cout << "Enter magnitude of second charge: ";
	cin >> q2;
	cout << "Choose prefix of Q2 <choose letter "<<cflGREEN_<<"p,n,u,m"<<cdefault_<<"> :";
	cin >> pref2;
	cout << "Enter x coordinate of second charge: ";
	cin >> x2;
	cout << "Enter y coordinate of second charge: ";
	cin >> y2;
	cout << "Enter z coordinate of second charge: ";
	cin >> z2;	
	
	double ax,ay,az;
	double Rx,Ry,Rz;
	double RMag;
	double Fx,Fy,Fz;
	
	Rx = (x2-x1);
	Ry = (y2-y1);
	Rz = (z2-z1);
	
	RMag = sqrt(pow(Rx,2)+pow(Ry,2)+pow(Rz,2)); 
	ax = Rx/RMag;
	ay = Ry/RMag;
	az = Rz/RMag;
	
	switch(pref1){
		case 'p':
			q1 = q1*pow(10,-12);
			break;
		case 'n':
			q1 = q1*pow(10,-9);
			break;
		case 'u':
			q1 = q1*pow(10,-6);
			break;
		case 'm':
			q1 = q1*pow(10,-3);
			break;
		default:
			q1 = q1;
			break;
	}
	switch(pref2){
		case 'p':
			q2 = q2*pow(10,-12);
			break;
		case 'n':
			q2 = q2*pow(10,-9);
			break;
		case 'u':
			q2 = q2*pow(10,-6);
			break;
		case 'm':
			q2 = q2*pow(10,-3);
			break;
		default:
			q2 = q2;
			break;
	}
	
	double qq = q1*q2;
	
	Fx = qq*ax/(4*3.14159*8.85419*pow(10,-12)*pow(RMag,2));
	Fy = qq*ay/(4*3.14159*8.85419*pow(10,-12)*pow(RMag,2));
	Fz = qq*az/(4*3.14159*8.85419*pow(10,-12)*pow(RMag,2));	
	
	cout<<endl;
	cout <<"The force on Q2 by Q1 is "<<cflGREEN_<<"("<<Fx<<")ax + ("<<Fy<<")ay + ("<<Fz<<")az"<<cdefault_<<endl;
	cout <<"The force on Q1 by Q2 is "<<cflGREEN_<<"("<<-1*Fx<<")ax + ("<<-1*Fy<<")ay + ("<<-1*Fz<<")az"<<cdefault_<<endl<<endl;
	cout <<endl;
	cout <<cflRED_<<	"Press any key to continue..."<<cdefault_;
	getch();
	mainMenu();	
}

void nPointField(){
	int numCharges;
	double q[100],q1[100];
	double x1[100],x2;
	double y1[100],y2;
	double z1[100],z2;
	double ax[100],ay[100],az[100];
	double Rx[100],Ry[100],Rz[100];
	double RMag[100];
	double Fx[100],Fy[100],Fz[100];
	char pref[100];
	cout << cflBLUE_ << "--------------------------------------------------------------------------------" <<endl<<cdefault_;
    cout << "Enter number of point charges: ";
    cin >> numCharges;
    cout << "Enter x coordinate of location where field intensity is to be known: ";
	cin >> x2;
	cout << "Enter y coordinate of location where field intensity is to be known: ";
	cin >> y2;
	cout << "Enter z coordinate of location where field intensity is to be known: ";
	cin >> z2;
	for(int i=0;i<numCharges;i++){
		cout << "Enter magnitude of point charge "<<cflGREEN_<<"Q"<<i+1<<": "<<cdefault_;
		cin >> q[i];
		cout << "Choose prefix of "<<cflGREEN_<<"Q"<<i+1<<" <choose letter p,n,u,m> :"<<cdefault_;
		cin >> pref[i];
		cout << "Enter x coordinate of point charge "<<cflGREEN_<<"Q"<<i+1<<": "<<cdefault_;
		cin >> x1[i];
		cout << "Enter y coordinate of point charge "<<cflGREEN_<<"Q"<<i+1<<": "<<cdefault_;
		cin >> y1[i];
		cout << "Enter z coordinate of point charge "<<cflGREEN_<<"Q"<<i+1<<": "<<cdefault_;
		cin >> z1[i];
		
		Rx[i] = (x2-x1[i]);
		Ry[i] = (y2-y1[i]);
		Rz[i] = (z2-z1[i]);
	
		RMag[i] = sqrt(pow(Rx[i],2)+pow(Ry[i],2)+pow(Rz[i],2)); 
		ax[i] = Rx[i]/RMag[i];
		ay[i] = Ry[i]/RMag[i];
		az[i] = Rz[i]/RMag[i];
	
		switch(pref[i]){
		case 'p':
			q1[i] = q[i]*pow(10,-12);
			break;
		case 'n':
			q1[i] = q[i]*pow(10,-9);
			break;
		case 'u':
			q1[i] = q[i]*pow(10,-6);
			break;
		case 'm':
			q1[i] = q[i]*pow(10,-3);
			break;
		default:
			q1[i] = q[i];
			break;
		}
	
		Fx[i] = q1[i]*ax[i]/(4*3.14159*8.85419*pow(10,-12)*pow(RMag[i],2));
		Fy[i] = q1[i]*ay[i]/(4*3.14159*8.85419*pow(10,-12)*pow(RMag[i],2));
		Fz[i] = q1[i]*az[i]/(4*3.14159*8.85419*pow(10,-12)*pow(RMag[i],2));	
	
		cout << "The field intensity on "<<cflGREEN_<<"("<<x2<<", " <<y2<<", "<<z2<<")"<<cdefault_<<" by a charge "<<cflGREEN_<<"Q = "<< q[i] << " "<< pref[i] << "C " <<endl<< "is "<<cflGREEN_<<"("<<Fx[i]<<")ax + ("<<Fy[i]<<")ay + ("<<Fz[i]<<")az"<<cdefault_<<endl;
	}
	double Fxt,Fyt,Fzt;
	
	for(int j=0;j<numCharges;j++){
		Fxt = Fxt + Fx[j];
		Fyt = Fyt + Fy[j];
		Fzt = Fzt + Fz[j];
	}
	cout << "The total field intensity on "<<cflGREEN_<<"("<<x2<<", " <<y2<<", "<<z2<<")"<<cdefault_<<" is "<<cflGREEN_<<"("<<Fxt<<")ax + ("<<Fyt<<")ay + ("<<Fzt<<")az"<<cdefault_<<endl; 	
	cout <<endl;
	cout << cflRED_ << "Press any key to continue..." << cdefault_ <<endl;
	getch();
	mainMenu();
}

void onePointField(){
	system("CLS");
	double q,q1;
	double x1,x2;
	double y1,y2;
	double z1,z2;
	char pref;
 	cout << cflBLUE_ << "--------------------------------------------------------------------------------" <<endl<<cdefault_;
	cout << "Enter magnitude of point charge : ";
	cin >> q;
	cout << "Choose prefix of Q <choose letter "<<cflGREEN_<<"p,n,u,m"<<cdefault_<<"> :";
	cin >> pref;
	cout << "Enter x coordinate of the point charge: ";
	cin >> x1;
	cout << "Enter y coordinate of the point charge: ";
	cin >> y1;
	cout << "Enter z coordinate of the point charge: ";
	cin >> z1;
	cout << "Enter x coordinate of location where field intensity is to be known: ";
	cin >> x2;
	cout << "Enter y coordinate of location where field intensity is to be known: ";
	cin >> y2;
	cout << "Enter z coordinate of location where field intensity is to be known: ";
	cin >> z2;
	
	double ax,ay,az;
	double Rx,Ry,Rz;
	double RMag;
	double Fx,Fy,Fz;
	
	Rx = (x2-x1);
	Ry = (y2-y1);
	Rz = (z2-z1);
	
	RMag = sqrt(pow(Rx,2)+pow(Ry,2)+pow(Rz,2)); 
	ax = Rx/RMag;
	ay = Ry/RMag;
	az = Rz/RMag;
	
	switch(pref){
		case 'p':
			q1 = q*pow(10,-12);
			break;
		case 'n':
			q1 = q*pow(10,-9);
			break;
		case 'u':
			q1 = q*pow(10,-6);
			break;
		case 'm':
			q1 = q*pow(10,-3);
			break;
		default:
			q1 = q;
			break;
	}
	
	Fx = q1*ax/(4*3.14159*8.85419*pow(10,-12)*pow(RMag,2));
	Fy = q1*ay/(4*3.14159*8.85419*pow(10,-12)*pow(RMag,2));
	Fz = q1*az/(4*3.14159*8.85419*pow(10,-12)*pow(RMag,2));	
	
	cout <<endl;
	cout << "The field intensity on "<<cflGREEN_<<"("<<x2<<", " <<y2<<", "<<z2<<")"<<cdefault_<<" by a charge "<< cflGREEN_<<"Q = "<< q << " "<< pref << "C "<<cdefault_ <<endl<< "is "<<cflGREEN_<<"("<<Fx<<")ax + ("<<Fy<<")ay + ("<<Fz<<")az"<<cdefault_<<endl;
	cout <<endl;
	cout <<	cflRED_<<"Press any key to continue..."<<cdefault_;
	getch();
	mainMenu();	

}
void lineChargeField(){
	system("CLS");
	int numCharges;
	double rhoL,rhoL1;
	double x1,x2;
	double y1,y2;
	double z1,z2;
	char pref,axis;
	cout << cflBLUE_ << "--------------------------------------------------------------------------------" <<endl<<cdefault_;
	cout << "Enter line charge density: ";
	cin >> rhoL;
	cout << "Choose prefix of line charge density <choose letter "<<cflGREEN_<<"p,n,u,m"<<cdefault_<<"> :";
	cin >> pref;
	cout << "The line charge is parallel to which axis? "<<cflGREEN_<<"(x,y,z)"<<cdefault_<<": ";
	cin >> axis;
	switch(axis){
		case 'x':
			cout << "Enter y coordinate of the line charge: ";
			cin >> y1;
			cout << "Enter z coordinate of the line charge: ";
			cin >> z1;
			cout << "Enter x coordinate of location where field intensity is to be known: ";
			cin >> x2;
			cout << "Enter y coordinate of location where field intensity is to be known: ";
			cin >> y2;
			cout << "Enter z coordinate of location where field intensity is to be known: ";
			cin >> z2;
			x1 = x2;
			break;
		case 'y':
			cout << "Enter x coordinate of the line charge: ";
			cin >> x1;
			cout << "Enter z coordinate of the line charge: ";
			cin >> z1;
			cout << "Enter x coordinate of location where field intensity is to be known: ";
			cin >> x2;
			cout << "Enter y coordinate of location where field intensity is to be known: ";
			cin >> y2;
			cout << "Enter z coordinate of location where field intensity is to be known: ";
			cin >> z2;
			y1 = y2;
			break;
		case 'z':
			cout << "Enter x coordinate of the line charge: ";
			cin >> x1;
			cout << "Enter y coordinate of the line charge: ";
			cin >> y1;
			cout << "Enter x coordinate of location where field intensity is to be known: ";
			cin >> x2;
			cout << "Enter y coordinate of location where field intensity is to be known: ";
			cin >> y2;
			cout << "Enter z coordinate of location where field intensity is to be known: ";
			cin >> z2;
			z1 = z2;
			break;		
	}
	
	double ax,ay,az;
	double Rx,Ry,Rz;
	double RMag;
	double Fx,Fy,Fz;
	
	Rx = (x2-x1);
	Ry = (y2-y1);
	Rz = (z2-z1);
	
	RMag = sqrt(pow(Rx,2)+pow(Ry,2)+pow(Rz,2)); 
	ax = Rx/RMag;
	ay = Ry/RMag;
	az = Rz/RMag;
	
	switch(pref){
		case 'p':
			rhoL1 = rhoL*pow(10,-12);
			break;
		case 'n':
			rhoL1 = rhoL*pow(10,-9);
			break;
		case 'u':
			rhoL1 = rhoL*pow(10,-6);
			break;
		case 'm':
			rhoL1 = rhoL*pow(10,-3);
			break;
		default:
			rhoL1 = rhoL;
			break;
	}
	
	Fx = rhoL1*ax/(2*3.14159*8.85419*pow(10,-12)*RMag);
	Fy = rhoL1*ay/(2*3.14159*8.85419*pow(10,-12)*RMag);
	Fz = rhoL1*az/(2*3.14159*8.85419*pow(10,-12)*RMag);	
	
	cout << endl;
	cout << "The field intensity on "<<cflGREEN_<<"("<<x2<<", " <<y2<<", "<<z2<<")"<<cdefault_<<" by a line charge "<<cflGREEN_<< rhoL << " "<< pref << "C/m " <<cdefault_<<endl<< "is "<<cflGREEN_<<"("<<Fx<<")ax + ("<<Fy<<")ay + ("<<Fz<<")az"<<cdefault_<<endl;
	cout << endl;
	cout <<	cflRED_ << "Press any key to continue..."<<cdefault_;
	getch();
	mainMenu();
	
}

void surfaceChargeField(){
	system("CLS");
	int numCharges;
	double rhoS,rhoS1;
	double loc;
	int aN;
	double x,y,z;
	char pref,axis;
	cout << cflBLUE_ << "--------------------------------------------------------------------------------" <<endl<<cdefault_;
	cout << "Enter surface charge density: ";
	cin >> rhoS;
	cout << "Choose prefix of surface charge density <choose letter "<<cflGREEN_<<"p,n,u,m"<<cdefault_<<"> :";
	cin >> pref;
	cout << "Enter the axis of the surface charge "<<cflGREEN_<<"(x,y,z)"<<cdefault_<<": ";
	cin >> axis;
	cout << "Enter the location of the surface charge on the "<<axis<<"-axis: ";
	cin >> loc;
	cout << "Where is the location of the field intensity to be measured?"<<endl;
	cout << "Enter x coordinate:";
	cin >> x;
	cout << "Enter y coordinate:";
	cin >> y;
	cout << "Enter z coordinate:";
	cin >> z;
	
	
	switch(axis){
		case 'x':
			if(x > loc){
				aN = 1;
			}else if(x < loc){
				aN = -1;
			}else{
				cout<<"The sheet charge can't be at the same location as the point under consideration";
				cout <<	"Press any key to exit to main menu...";
				getch();
				mainMenu();
			}
			break;
		case 'y':
		    if(y > loc){
				aN = 1;
			}else if(y < loc){
				aN = -1;
			}else{
				cout<<"The sheet charge can't be at the same location as the point under consideration";
				cout <<	"Press any key to exit to main menu...";
				getch();
				mainMenu();
			}
			break;
		case 'z':
			if(z > loc){
				aN = 1;
			}else if(z < loc){
				aN = -1;
			}else{
				cout<<"The sheet charge can't be at the same location as the point under consideration";
				cout <<	"Press any key to exit to main menu...";
				getch();
				mainMenu();
			}
			break;
	}
	double E;
			
	switch(pref){
		case 'p':
			rhoS1 = rhoS*pow(10,-12);
			break;
		case 'n':
			rhoS1 = rhoS*pow(10,-9);
			break;
		case 'u':
			rhoS1 = rhoS*pow(10,-6);
			break;
		case 'm':
			rhoS1 = rhoS*pow(10,-3);
			break;
		default:
			rhoS1 = rhoS;
			break;
	}
	
	E = rhoS1*aN/(2*8.85419*pow(10,-12));
	cout <<endl;
	cout << "The field intensity on "<<cflGREEN_<<"("<<x<<", " <<y<<", "<<z<<")"<<cdefault_<<" by a surface charge "<<cflGREEN_<< rhoS << " "<< pref << "C/m^2 " <<cdefault_<<endl<< "is "<<cflGREEN_<<"("<<E<<")"<<cdefault_<<"a"<< axis <<cdefault_<<endl;
	cout <<endl;
	cout <<	cflRED_ <<"Press any key to continue..."<<cdefault_;
	getch();
	mainMenu();
}

void mainMenu(){
	system("CLS");
	int inp;
	cout << cflBLUE_ << "--------------------------------------------------------------------------------" <<endl<<cdefault_;
	cout << cflRED_ << "Select function:" <<cdefault_;
	cout <<endl<<endl<< "1.Force between Two Point Charges"<<endl<<"2.Electric Field Intensity by One Point Charge"<<endl<<"3.Electric Field Intensity by N Point Charges"<<endl<<"""4.Electric Field Intensity of One Line Charge"<<endl<<"5.Electric Field Intensity of One Surface Charge"<<endl;
	cout << "6.Exit"<<endl<<endl;
	cout << cflRED_ << "Enter Choice <1-6>: "<<cdefault_;
    cin >> inp;
    switch(inp){
                case 1:
                     twoPointForce();
                     break;
                case 2:
                     onePointField();
                     break;
            	case 3:
            		 nPointField();
            	     break;
                case 4:
                     lineChargeField();
                     break;
                case 5:
                     surfaceChargeField();
                     break;
            	case 6:
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
