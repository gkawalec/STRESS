double HR1        ;
	double AR1        ;
	double HR2        ;
	double AR2        ;
	double HR3        ;
	double AR3        ;
	double HR4        ;
	double AR4        ;
	double HR5        ;
	double AR5        ;
	double HR6        ;
	double AR6        ;
	double HR7        ;
	double AR7        ;
	double HR8        ;
	double AR8        ;
	double HR9        ;
	double AR9        ;
	double HR10        ;
	double AR10       ;
	double HR11        ;
	double AR11        ;
	double HR12        ;
	double AR12        ;
	double HR13        ;
	double AR13        ;
	double HR14        ;
	double AR14        ;
	double HR15        ;
	double AR15        ;
	double HR16        ;
	double AR16        ;
	double HR17        ;
	double AR17        ;
	double HR18        ;
	double AR18        ;
	double HR19        ;
	double AR19        ;
	double HR20        ;
	double AR20        ;
	double HR21        ;
	double AR21        ;
	double HR22        ;
	double AR22        ;
	double HR23        ;
	double AR23        ;
	double HR24        ;
	double AR24        ;
	double HR25        ;
	double AR25        ;
	double HR26        ;
	double AR26        ;
	double HR27        ;
	double AR27        ;
	double HR28        ;
	double AR28        ;
	double HR29        ;
	double AR29        ;
	double HR30        ;
	double AR30        ;
	
double Get_Input(bool& HR_AR); // will get the input based on an alternating value to select AR or HR
bool HR_AR = 1; //to get HR this will equal 1, to get AR, it will be 0
double Max_HR = 0;
double Min_HR = 0;

void setup(){

    Particle.variable("HR1", &HR1, DOUBLE);
    Particle.variable("AR1", &AR1, DOUBLE);
	Particle.variable("HR2", &HR2, DOUBLE);
	Particle.variable("AR2", &AR2, DOUBLE);
	Particle.variable("HR3", &HR3, DOUBLE);
    Particle.variable("AR3", &AR3, DOUBLE);
	Particle.variable("HR4", &HR4, DOUBLE);
	Particle.variable("AR4", &AR4, DOUBLE);
	Particle.variable("HR5", &HR5, DOUBLE);
	Particle.variable("AR5", &AR5, DOUBLE);
	Particle.variable("HR6", &HR6, DOUBLE);
	Particle.variable("AR6", &AR6, DOUBLE);
	Particle.variable("HR7", &HR7, DOUBLE);
	Particle.variable("AR7", &AR7, DOUBLE);
	Particle.variable("HR8", &HR8, DOUBLE);
	Particle.variable("AR8", &AR8, DOUBLE);
	Particle.variable("HR9", &HR9, DOUBLE);
	Particle.variable("AR9", &AR9, DOUBLE);
	Particle.variable("HR10", &HR10, DOUBLE);
	Particle.variable("AR10", &AR10, DOUBLE);
	Particle.variable("HR11", &HR11, DOUBLE);
	Particle.variable("AR11", &AR11, DOUBLE);
	Particle.variable("HR12", &HR12, DOUBLE);
	Particle.variable("AR12", &AR12, DOUBLE);
	Particle.variable("HR13", &HR13, DOUBLE);
	Particle.variable("AR13", &AR13, DOUBLE);
	Particle.variable("HR14", &HR14, DOUBLE);
	Particle.variable("AR14", &AR14, DOUBLE);
	Particle.variable("HR15", &HR15, DOUBLE);
	Particle.variable("AR15", &AR15, DOUBLE);
	Particle.variable("HR16", &HR16, DOUBLE);
	Particle.variable("AR16", &AR16, DOUBLE);
	Particle.variable("HR17", &HR17, DOUBLE);
	Particle.variable("AR17", &AR17, DOUBLE);
	Particle.variable("HR18", &HR18, DOUBLE);
	Particle.variable("AR18", &AR18, DOUBLE);
	Particle.variable("HR19", &HR19, DOUBLE);
	Particle.variable("AR19", &AR19, DOUBLE);
	Particle.variable("HR20", &HR20, DOUBLE);
	Particle.variable("AR20", &AR20, DOUBLE);
	Particle.variable("HR21", &HR21, DOUBLE);
	Particle.variable("AR21", &AR21, DOUBLE);
	Particle.variable("HR22", &HR22, DOUBLE);
	Particle.variable("AR22", &AR22, DOUBLE);
	Particle.variable("HR23", &HR23, DOUBLE);
	Particle.variable("AR23", &AR23, DOUBLE);
	Particle.variable("HR24", &HR24, DOUBLE);
	Particle.variable("AR24", &AR24, DOUBLE);
	Particle.variable("HR25", &HR25, DOUBLE);
	Particle.variable("AR25", &AR25, DOUBLE);
	Particle.variable("HR26", &HR26, DOUBLE);
	Particle.variable("AR26", &AR26, DOUBLE);
	Particle.variable("HR27", &HR27, DOUBLE);
	Particle.variable("AR27", &AR27, DOUBLE);
	Particle.variable("HR28", &HR28, DOUBLE);
	Particle.variable("AR28", &AR28, DOUBLE);
	Particle.variable("HR29", &HR29, DOUBLE);
	Particle.variable("AR29", &AR29, DOUBLE);
	Particle.variable("HR30", &HR30, DOUBLE);
	Particle.variable("AR30", &AR30, DOUBLE);
	

}

void loop(){
  HR1 = Get_Input(HR_AR);
	  AR1 = Get_Input(HR_AR);
	  HR2 = Get_Input(HR_AR);
	  AR2 = Get_Input(HR_AR);
	  HR3 = Get_Input(HR_AR);
	  AR3 = Get_Input(HR_AR);
	  HR4 = Get_Input(HR_AR);
	  AR4 = Get_Input(HR_AR);
	  HR5 = Get_Input(HR_AR);
	  AR5 = Get_Input(HR_AR);
	  HR6 = Get_Input(HR_AR);
	  AR6 = Get_Input(HR_AR);
	  HR7 = Get_Input(HR_AR);
	  AR7 = Get_Input(HR_AR);
	  HR8 = Get_Input(HR_AR);
	  AR8 = Get_Input(HR_AR);
	  HR9 = Get_Input(HR_AR);
	  AR9 = Get_Input(HR_AR);
	  HR10 = Get_Input(HR_AR);
	  AR10= Get_Input(HR_AR);
	  HR11 = Get_Input(HR_AR);
	  AR11 = Get_Input(HR_AR);
	  HR12 = Get_Input(HR_AR);
	  AR12 = Get_Input(HR_AR);
	  HR13 = Get_Input(HR_AR);
	  AR13 = Get_Input(HR_AR);
	  HR14 = Get_Input(HR_AR);
	  AR14 = Get_Input(HR_AR);
	  HR15 = Get_Input(HR_AR);
	  AR15 = Get_Input(HR_AR);
	  HR16 = Get_Input(HR_AR);
	  AR16 = Get_Input(HR_AR);
	  HR17 = Get_Input(HR_AR);
	  AR17 = Get_Input(HR_AR);
	  HR18 = Get_Input(HR_AR);
	  AR18 = Get_Input(HR_AR);
	  HR19 = Get_Input(HR_AR);
	  AR19 = Get_Input(HR_AR);
	  HR20 = Get_Input(HR_AR);
	  AR20 = Get_Input(HR_AR);
	  HR21 = Get_Input(HR_AR);
	  AR21 = Get_Input(HR_AR);
	  HR22 = Get_Input(HR_AR);
	  AR22 = Get_Input(HR_AR);
	  HR23 = Get_Input(HR_AR);
	  AR23 = Get_Input(HR_AR);
	  HR24 = Get_Input(HR_AR);
	  AR24 = Get_Input(HR_AR);
	  HR25 = Get_Input(HR_AR);
	  AR25 = Get_Input(HR_AR);
	  HR26 = Get_Input(HR_AR);
	  AR26 = Get_Input(HR_AR);
	  HR27 = Get_Input(HR_AR);
	  AR27 = Get_Input(HR_AR);
	  HR28 = Get_Input(HR_AR);
	  AR28 = Get_Input(HR_AR);
	  HR29 = Get_Input(HR_AR);
	  AR29 = Get_Input(HR_AR);
	  HR30 = Get_Input(HR_AR);
	  AR30 = Get_Input(HR_AR);
    }
    
    
    

double Get_Input(bool& HR_AR){
	if (HR_AR){
		double HR = 1234.1234;
        // GET HR VALUE HERE
    
    
		HR_AR = 0;
		if (HR > Max_HR){ //update maximum value
			Max_HR = HR;
		}
		if (HR < Min_HR){ //update minimum value
			Min_HR = HR;
		}
		return HR;
	}
	else{
		double AR = 7037.32;
        // GET AR VALUE HERE
    
    
		HR_AR = 1;
		return AR;
	}
}
