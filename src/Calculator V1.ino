/* This is the initial primitive code,
 where I had to write it using Proteus VSM editor,
 which lacks literally every thing! */

#include <LiquidCrystal.h>
#include <Keypad.h>	//here I used a custom Keypad library check out the second next comment
#include <math.h>
#include <Arduino.h> //unnecessary TBH, Arduino IDE adds it automatically 


/* Here's the second next comment, if you want Proteus to run the library properly,
you will have to copy the library files (Key.cpp Key.h Keypad.cpp Keypad.h) to the following directory
C:\ProgramData\Labcenter Electronics\Proteus 8 Professional\VSM Studio\drivers\arduino\Keypad */



const byte ROWS = 6;
const byte COLS = 6; 

// Define the Keymap
char keys[ROWS][COLS] = {


  {'s','c','t','L', 'n' , '@'},

  {'a','b','T','l', 'e' , '!'},	

  {'7','8','9','/', '^' , 'r'},

  {'4','5','6','*', 'm' , 'M'},

  {'1','2','3','-', 'i' , 'C'},

  {'=','0','.','+', 'S' , 'A'}};





byte rowPins[ROWS] = {A0, A1, A2, A3, A4 ,A5}; 
byte colPins[COLS] = {1, 2, 3, 4, 5, 6};

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

double num1=0.0,num2=0.0,result=0.0;
int d1=1,d2=1,n1=0,n2=0;
bool dot1=false,dot2=false;
int num1don=0,num2don=0;
char operatorChar='\0',triop='\0',preop='\0';
int num1underway=0,num2underway=0;
double memo1=0,memo2=0;

int tempflag=0;
int flagShift=0,flagAlpha=0,saveinFlage=0;

double ad=0; //angle degrees
double ar=0;//angles radian


void setup() {
  lcd.begin(16, 2);
  lcd.print("Calculator");
  delay(200);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.blink();
  lcd.print("0");

}

void loop() {
char key=kpd.getKey();


if(key){


neg(key);
at(key);
lLefr(key);
mMiC(key);
//A S ups
SAflags(key);
//end of A S ups



//handle num1		
					if(num1don==0){

						lcd.setCursor(n1,0);
						if(dot1==false && key=='.'){
							dot1=true;
							n1++;
							lcd.print(key);	
						}

						if(key >= '0' && key <= '9' &&dot1==true){
							handlenum1d(key);
							lcd.print(key);
							num1underway=1;
						}
		
						if(key >= '0' && key <= '9' && dot1==false){
							handlenum1u(key);
							lcd.print(key);
							num1underway=1;
						}
					}
//end of handle num1

//handle num2		
					if(num2don==0&&num1don==1){

						lcd.setCursor(n2, 1);
						if(dot2==false && key=='.'){
							dot2=true;
							n2++;
							lcd.print(key);	
						}

						if(key >= '0' && key <= '9' &&dot2==true){
							handlenum2d(key);
							num2underway=1;
							lcd.print(key);
						}
		
						if(key >= '0' && key <= '9' && dot2==false){
							handlenum2u(key);
							num2underway=1;
							lcd.print(key);
						}
					}
//end of handle num2		

// 2d operation
	if (key == '+' || key == '-' || key == '*' || key == '/'||key == '^'){
	lcd.setCursor(7, 0);
	lcd.print(key);
	n1=0;d1=1;
	operatorChar= key;
	num1don=1;
	lcd.setCursor(0, 1);
	}	
//end of 2d operation

frow(key);
srow(key);








	if (key == '='&&num2underway==1){
	calculate();
	lcd.setCursor(7,0);
	lcd.print(" ");	
	lcd.setCursor(6,1);
	lcd.print("=");	
	lcd.setCursor(7,1);
	lcd.print(result,3);
	delay(250);
	lcd.clear();
	SAflags(key);
	num1=result;
	num2=0;
	num1don=1;
	lcd.setCursor(0,0);
	lcd.print(num1);
	num2don=0;
	lcd.setCursor(0,1);
	n1=0;d1=1;
	n2=0;d2=1;
	dot1=false;
	dot2=false;
	}

	if (key == '='&&num2underway==0){

	lcd.setCursor(7,0);
	lcd.print("");	
	lcd.setCursor(6,1);
	lcd.print("=");	
	lcd.setCursor(8,1);
	lcd.print(result,3);
	delay(250);
	lcd.clear();
	SAflags(key);
	num1=result;
	num2=0;
	num1don=1;
	lcd.setCursor(0,0);
	lcd.print(num1);
	num2don=0;
	lcd.setCursor(0,1);
	n1=0;d1=1;
	n2=0;d2=1;
	dot1=false;
	dot2=false;
	}


/*if(tempflag==1){
tempflag==0;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("n is ");
lcd.print(num1);}*/

}//if (key)


}//end of void loop


//voids handle num1
void handlenum1u(char key){
	num1 = num1 * 10.0 + (key - '0');
	n1++;
}
void handlenum1d(char key){
	num1 = num1 + (key - '0')*pow(0.1,d1);
	d1++;	n1++;
}
//end of voids handle num1

//voids handle num2
void handlenum2u(char key){
	num2 = num2 * 10.0 + (key - '0');
	n2++;
}
void handlenum2d(char key){
	num2 = num2 + (key - '0')*pow(0.1,d2);
	d2++;  n2++;
}
//end of voids handle num2

//void calculate
void calculate(){
num2underway=0;
num1underway=0;
  switch (operatorChar) {
    case '+':
      result = num1 + num2;
      break;
    case '-':
      result = num1 - num2;
      break;
    case '^':
      result = pow(num1,num2);
      break;
    case '*':
      result = num1 * num2;
      break;
    case '/':
      if (num2 != 0.0) {
        result = num1 / num2;
      } else {
        lcd.clear();
        lcd.print("Error");
        delay(1000);
        result = 0.0;
      }
      break;
  }
  preop=operatorChar;
  operatorChar = '\0';



}
//end of void calculate

//void angles degreed to angles radian
void arF(){
ad=num1;
ar = ad * M_PI / 180.0;
}
//end of void angles degreed to angles radian

void oneortwo(){
						if(num2underway==1&&num1underway==1){
						calculate();
						}
						if(num1underway==1&&num2underway==0){
						result=num1; num2=0;
						}
}

void SAflags(char key){
	if(key=='A'&&flagAlpha==0){
	flagAlpha=1;
	}
	if(key=='S'&&flagShift==0){
	flagShift=1;
	}

	if(flagAlpha==1){
	lcd.setCursor(15, 0);
	lcd.print("A");
	}
	if(flagAlpha==0){
	lcd.setCursor(15, 0);
	lcd.print(" ");
	}

	if(flagShift==1){
	lcd.setCursor(15, 1);
	lcd.print("S");
	}
	if(flagShift==0){
	lcd.setCursor(15, 1);
	lcd.print(" ");
	}
}
//n2 = n2 * 10.0 + (key - '0');

double customSinh(double x) {
    const int maxIterations = 10;
    double tresult = x;
    double term = x;

    for (int n = 1; n <= maxIterations; n++) {
        term *= (x * x) / ((2 * n) * (2 * n + 1));
        tresult += term;
    }

    return tresult;
}

double customArcsinh(double x) {
    double result = 0;
result=log(x+sqrt(pow(x,2)+1));

    return result;
}

// cosines

double customCosh(double x) {
double tresult=(exp(x)+exp(x*(-1)))/2;
    return tresult;
}

double customArcCosh(double x) {
    double result = log(x + sqrt(x * x - 1.0));
    return result;
}

//end of cosines

void frow(char key){
//sin

				if(key=='s'&&flagShift==0 && flagAlpha==0){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("sin(x)");

						result=sin(ar);

				}
//end of sin
//arcsin

				if( flagAlpha==1&& key=='s'&& flagShift==0){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("asin(x)");

					//	result=customAsin(num1)* (180.0 / PI);
					result = asin(num1) * 180.0 / M_PI;

				}
//end of arcsin  customSinh
//sinh

				if( flagAlpha==0&& key=='s'&& flagShift==1){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("sinh(x)");

						result=customSinh(num1);

				}
//end of sinh  
//arcsinh
				if( flagAlpha==1&& key=='s'&& flagShift==1){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("asinh(x)");

						result=customArcsinh(num1);

				}
//end of arcsinh






//cos 

				if(key=='c'&&flagShift==0 && flagAlpha==0){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("cos(x)");

						result=cos(ar);

				}
//end of cos
//arccos  
 
				if( flagAlpha==1&& key=='c'&& flagShift==0){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("acos(x)");

						result = acos(num1) * 180.0 / M_PI;

				}
//end of arccos  
//cosh  

				if( flagAlpha==0&& key=='c'&& flagShift==1){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("cosh(x)");

						result=customCosh(num1);

				}
//end of cosh  
//arccosh
				if( flagAlpha==1&& key=='c'&& flagShift==1){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("acosh(x)");

						result=customArcCosh(num1);

				}
//end of arccosh


//tan 

				if(key=='t'&&flagShift==0 && flagAlpha==0){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("tan(x)");

						result=tan(ar);

				}
//end of tan
//arctan  
 
				if( flagAlpha==1&& key=='t'&& flagShift==0){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("atan(x)");

						result = atan(num1) * 180.0 / M_PI;

				}
//end of arctan  
//tanh  

				if( flagAlpha==0&& key=='t'&& flagShift==1){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("tanh(x)");
result=(exp(num1)-exp(num1*-1))/(exp(num1)+exp(num1*-1));

				}
//end of tanh  
//arctanh
				if( flagAlpha==1&& key=='t'&& flagShift==1){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("atanh(x)");
						result=0.5*log((1+num1)/(1-num1));

				}
//end of arctanh
}













void srow(char key){
//sec

				if(key=='a'&&flagShift==0 && flagAlpha==0){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("sec(x)");

						result=1/cos(ar);

				}
//end of sec
//arcsec

				if( flagAlpha==1&& key=='a'&& flagShift==0){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("asec(x)");

					double j=1/num1;
					result = acos(j) * 180.0 / M_PI;

				}
//end of arcec 
//sech

				if( flagAlpha==0&& key=='a'&& flagShift==1){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("sech(x)");
						double shtmp;
						shtmp=customCosh(num1);
						result=1/shtmp;

				}
//end of sech  
//arcsech
				if( flagAlpha==1&& key=='a'&& flagShift==1){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("asech(x)");

						result=log((1+sqrt(1-(num1*num1)))/(num1));

				}
//end of arcsech




//csc

				if(key=='b'&&flagShift==0 && flagAlpha==0){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("csc(x)");

						result=1/sin(ar);

				}
//end of csc
//arccsc

				if( flagAlpha==1&& key=='b'&& flagShift==0){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("acsc(x)");

					double j=1/num1;
					result = asin(j) * 180.0 / M_PI;

				}
//end of arccsc 
//csch

				if( flagAlpha==0&& key=='b'&& flagShift==1){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("csch(x)");
						double cschtmp;
						cschtmp=customSinh(num1);
						result=1/cschtmp;

				}
//end of csch  
//arccsch
				if( flagAlpha==1&& key=='b'&& flagShift==1){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("acsch(x)");

					//	result=log((1+sqrt(1-(num1*num1)))/(num1));
						result=log(1/num1 + sqrt(1/(num1*num1) + 1));
				}
//end of arccsch




//cot 

				if(key=='T'&&flagShift==0 && flagAlpha==0){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("cot(x)");

						result=1/tan(ar);

				}
//end of cot
//arccot  
 
				if( flagAlpha==1&& key=='T'&& flagShift==0){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("acot(x)");

				//		result = costom(num1) * 180.0 / M_PI;
					double acottmp=1/num1;
					result = acos(acottmp) * 180.0 / M_PI;

				}
//end of acot 
//coth  

				if( flagAlpha==0&& key=='T'&& flagShift==1){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("coth(x)");
					
	result=(exp(num1)+exp(num1*(-1)))/(exp(num1)-exp(num1*(-1)));



				}
//end of coth  
//arccoth
				if( flagAlpha==1&& key=='T'&& flagShift==1){

						arF();
						lcd.setCursor(6, 0);
						lcd.print("press [=]");
						lcd.setCursor(0, 1);
						lcd.print("acoth(x)");
						result=0.5*log((1+num1)/(num1-1));

				}
//end of arccoth

}

void lLefr(char key){

	if(key=='l'){
		lcd.setCursor(6, 0);
		lcd.print("press [=]");
		lcd.setCursor(0, 1);
		lcd.print("ln(x)");

		result=log(num1);
	}

	if(key=='L'){
		lcd.setCursor(6, 0);
		lcd.print("press [=]");
		lcd.setCursor(0, 1);
		lcd.print("log(x)");

		result=log10(num1);
	}

	if(key=='e'){
		lcd.setCursor(6, 0);
		lcd.print("press [=]");
		lcd.setCursor(0, 1);
		lcd.print("e^ ");
		lcd.print(num1);

		result=exp(num1);
	}

	if(key=='!'){
		lcd.setCursor(6, 0);
		lcd.print("press [=]");
		lcd.setCursor(0, 1);
		int ftmp=1;
		ftmp=num1;
		lcd.print(num1);	
		lcd.print("! ");

	for(int i=ftmp-1;i>1;i--){
		ftmp*=i;
	}
		result=ftmp;
	}
	if(key=='r'){
		lcd.setCursor(6, 0);
		lcd.print("press [=]");
		lcd.setCursor(0, 1);
		lcd.print("sqr ");
		result=sqrt(num1);
	}

}

void mMiC(char key){

if(key=='C'){
memo1=0;
memo2=0;
saveinFlage=1;
}
	
	if(key=='m'&&saveinFlage==0){
		if(num1underway==1){
			num1=memo1;
			num1don=1;
	n1=0;d1=1;
num1underway=0;
	dot1=false;

			lcd.clear();
			lcd.setCursor(9,1);
			lcd.print(memo1);
		}
		if(num2underway==1){
			num1=memo1;
			num2don=1;

	n2=0;d2=1;
num2underway=0;
	dot2=false;
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print(memo1);
		}
	}

	if(key=='m'&&saveinFlage==1){
		if(num1underway==1){
			memo1=num1;
num1underway=0;
			saveinFlage=0;
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("M1 num1 saved!");
			num1underway=0;
	n1=0;d1=1;
num1underway=1;
	dot1=false;	
			delay(250);
			lcd.clear();
			lcd.setCursor(0,0);
		}
		if(num2underway==1){
			memo1=num1;
num2underway=0;
			saveinFlage=0;
			lcd.clear();
			lcd.setCursor(0,1);
			lcd.print("M1 num2 saved!");
			num2don=1;

	n2=0;d2=1;
num2underway=0;
	dot2=false;
			lcd.clear();
			lcd.setCursor(0,0);

		}
	}



	if(key=='M'&&saveinFlage==0){
		if(num1underway==1){
			num1=memo2;
			num1don=1;
	n1=0;d1=1;
num1underway=0;
	dot1=false;

			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print(memo2);

		}
		if(num2underway==1){
			num2=memo2;
			num2don=1;
num2underway=0;

	n2=0;d2=1;

	dot2=false;
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print(memo2);
		}
	}


	if(key=='M'&&saveinFlage==1){
		if(num1underway==1){
			memo2=num1;
			saveinFlage=0;
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("M2 num1 saved!");
			num1underway=0;
	n1=0;d1=1;
num1underway=1;
	dot1=false;	
			lcd.setCursor(0,0);
			delay(100);
			lcd.clear();
			lcd.setCursor(0,0);

		}
		if(num2underway==1){
			memo2=num2;
			saveinFlage=0;
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("M2 num2 saved!");
			num2don=1;

	n2=0;d2=1;
num2underway=0;
	dot2=false;

			delay(100);
			lcd.clear();
			lcd.setCursor(0,0);

		}
	}

	if(key=='i'){
	saveinFlage=1;}

}

void at(char key){

	if(key=='@'){

		num1=0.0;num2=0.0;result=0.0;
		d1=1;d2=1;n1=0;n2=0;
		dot1=false;dot2=false;
		num1don=0;num2don=0;
		operatorChar='\0';triop='\0';preop='\0';
		num1underway=1;num2underway=0;

		flagShift=0;flagAlpha=0;saveinFlage=0;

		ad=0; //angle degrees
		ar=0;//angles radian
		lcd.clear();
		lcd.setCursor(0,0);
		}
}

void neg(char key){

	if(key=='n'){

		if(num2underway==1){
		num2*=-1;
		lcd.setCursor(0,1);
		lcd.print("       ");
		lcd.setCursor(0,1);
		lcd.print(num2);
		n2++;
		} else if(num1underway==1){
				num1*=-1;
			lcd.setCursor(0,0);
			lcd.print("      ");
			lcd.setCursor(0,0);
			lcd.print(num1);
			n1++;

		  }
	}

}





	



