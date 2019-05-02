#include "taskCalc.h"
#include "taskMenu.h"
#include <stdio.h>
#include <math.h>
#include "color.h"

#define	STT_CALC_WAIT		0
#define STT_CALC_SUMA		1
#define STT_CALC_DIFERENCIA	2
#define STT_CALC_AGM5		3
#define STT_CALC_SEND_MSG	4
#define STT_CALC_RECEIVE_MSG	5


#define CALC_SUMA	1
#define CALC_DIFERENCIA 2
#define CALC_AGM5	3

#define OFF		0
#define ON		1

int taskCalc_state;
int taskCalc_iDebugMode;

float taskCalc_fNum1;
float taskCalc_fNum2;
float taskCalc_fResultado;

float taskCalc_fAritmeticMean;
float taskCalc_fGeometricMean;

int cnt;

void taskCalc_init()
{
	taskCalc_state = STT_CALC_WAIT;

	// Depuración
	taskCalc_setDebugMode(OFF);
}

void taskCalc_run()
{	
	switch(taskCalc_state)
	{
		case STT_CALC_WAIT:
			if (taskCalc_iDebugMode)
			{
				setColorBoldCyan(); 
				printf ("\nSTT_CALC_WAIT");
				resetColor();
			}
			// Sic
			break;

		case STT_CALC_SUMA:
			taskCalc_fResultado  = taskCalc_fNum1 + taskCalc_fNum2;
			
			taskCalc_state = STT_CALC_SEND_MSG;
			break;

		case STT_CALC_DIFERENCIA:
			taskCalc_fResultado  = taskCalc_fNum1 - taskCalc_fNum2;
			
			taskCalc_state = STT_CALC_SEND_MSG;
			break;

		case STT_CALC_AGM5:

			taskCalc_fAritmeticMean = taskCalc_fNum1;
			taskCalc_fGeometricMean = taskCalc_fNum2;
 			
			float tmp;

			for(cnt = 0 ;cnt <=4 ; cnt=cnt+1)
			{ 
				tmp = taskCalc_fAritmeticMean;
				
				taskCalc_fAritmeticMean = (taskCalc_fAritmeticMean + taskCalc_fGeometricMean)/2;
				taskCalc_fGeometricMean = sqrt (tmp * taskCalc_fGeometricMean);
			}
			taskCalc_fResultado = taskCalc_fAritmeticMean;
			
			taskCalc_state = STT_CALC_SEND_MSG;
			break;
		
		case STT_CALC_SEND_MSG:
			if(taskCalc_iDebugMode)
			{
				char* tmp_sFormat = "\nSTT_CALC_SEND_MESG float %.4f";
				setColorBoldCyan();
				printf(tmp_sFormat,taskCalc_fResultado);
				resetColor();
			}
			taskMenu_message(taskCalc_fResultado);
			
			taskCalc_state = STT_CALC_WAIT;
			break;

		default:
			setColorBoldRed();
			printf("\nSTT CALC");
			resetColor();
	}
}

void taskCalc_setState(int arg_state)
{
	taskCalc_state = arg_state;
}

void taskCalc_message(int arg_opcion, float arg_num1, float arg_num2)
{	
	if (taskCalc_iDebugMode)
	{
		char* tmp_sFormat = "\ntaskCalc_message(char %d, float %.4f, float %.4f)";
		setColorBoldCyan();
		printf(tmp_sFormat, arg_opcion, arg_num1, arg_num2);
		resetColor();
	}
	
	taskCalc_fNum1 = arg_num1;
	taskCalc_fNum2 = arg_num2;

	switch(arg_opcion)
		
        {
                 case CALC_SUMA:
                	 taskCalc_state = STT_CALC_SUMA;
                	 break;

                 case CALC_DIFERENCIA:
                	 taskCalc_state = STT_CALC_DIFERENCIA;
                	 break;

                 case CALC_AGM5:
                	 taskCalc_state = STT_CALC_AGM5;
                	 break;

                 default:
                	setColorBoldRed();
			printf("\ntaskCalc_message default!");
			resetColor();
                	taskCalc_state = STT_CALC_WAIT;
         }
}


void taskCalc_setDebugMode(int arg_debugMode){
        taskCalc_iDebugMode = arg_debugMode;
	
}
