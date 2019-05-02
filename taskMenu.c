#include "taskMenu.h"
#include "taskCalc.h"
#include <stdio.h>
#include <stdlib.h>
#include "color.h"
#include <ctype.h>

// MACROS
// PROTOTIPOS
#define STT_MENU_WAIT           0
#define STT_MENU_PRINT_MENU     1
#define STT_MENU_GET_NUMBERS    2
#define STT_MENU_GET_OPTION     3
#define STT_MENU_PRINT_RESULT   4
#define STT_MENU_SEND_MSG	5
#define STT_MENU_RECEIVE_MSG	6
#define STT_MENU_PROCESS_OPTION 7
#define STT_MENU_EXIT		8

#define CALC_SUMA		1
#define CALC_DIFERENCIA		2
#define CALC_AGM5		3

#define OFF			0
#define ON			1

int taskMenu_state;	// Variable de estado

int taskMenu_iOption;
int taskMenu_iDebugMode;

float taskMenu_fNum1;
float taskMenu_fNum2;
float taskMenu_fResult;

void taskMenu_init(void)
{
	// Título
	setColorBoldBlue();
	printf("\n CALCULADORA MULTITAREA");
	resetColor();
	
	taskMenu_state = STT_MENU_GET_NUMBERS;

	// depuración
	taskMenu_setDebugMode(ON);
}

void taskMenu_run(void)
{
	switch(taskMenu_state)
	{
		case STT_MENU_WAIT:
			if(taskMenu_iDebugMode)
			{
				setColorBoldCyan();
				printf("\nSTT_MENU_WAIT");
				resetColor();
			}
			break;
		
		case STT_MENU_PRINT_MENU:
			// Imprimir el menu
			printf("\n N1 = %.4f	N2 = %.4f",taskMenu_fNum1, taskMenu_fNum2);
			printf("\n1. Suma		2. Diferencia");
			printf("\n3. AGM5		4. Modificar números");
			printf("\n5. Salir ");
			taskMenu_state = STT_MENU_GET_OPTION;
			break;
			
		case STT_MENU_GET_NUMBERS:
			printf("\n Ingrese dos números enteros:");
			printf("\n N1 = "); scanf("%f", &taskMenu_fNum1);
			printf("\n N2 = "); scanf("%f", &taskMenu_fNum2);
			
			taskMenu_state = STT_MENU_PRINT_MENU;
			break;
			
		case STT_MENU_GET_OPTION:
			printf("\n Elija una opcion: ");

			if (scanf("%d", &taskMenu_iOption) == 0)
			{
				printf("cadena de caracteres no admitida\n");

				char tmp ='c';				
				for (;!isdigit(tmp);tmp = getchar() );
				{
					printf("%c", tmp);
				}

			  	//ungetc(tmp, stdin);
			  	//consume non-numeric chars from buffer
			}

			taskMenu_state = STT_MENU_PROCESS_OPTION;
			break;
		
		case STT_MENU_PROCESS_OPTION:	
			if (taskMenu_iDebugMode)
			{
				setColorBoldCyan();
				printf("\nSTT_MENU_PROCESS_OPTION");
				resetColor();
			}

			switch(taskMenu_iOption)
			{
				case 1:
					taskMenu_iOption = CALC_SUMA;
					taskMenu_state = STT_MENU_SEND_MSG;
					break;

				case 2:
					taskMenu_iOption = CALC_DIFERENCIA;
					taskMenu_state = STT_MENU_SEND_MSG;
					break;
				case 3: 
					taskMenu_iOption = CALC_AGM5;
					taskMenu_state = STT_MENU_SEND_MSG;
					break;
				case 4:
					taskMenu_state = STT_MENU_GET_NUMBERS;
					break;
				case 5:
					taskMenu_state = STT_MENU_EXIT;
					break;
				default:
					if(taskMenu_iDebugMode)
					{
						setColorBoldCyan();
						printf(": DEFAULT");
						resetColor();
					}	
					printf("\nOpcion no valida!");
					taskMenu_state = STT_MENU_GET_OPTION;
					
			}
			
			break;
		
		case STT_MENU_SEND_MSG:
			if (taskMenu_iDebugMode)
			{
				char* tmp_sFormat = "\nSTT_MENU_SEND_MSG (char %d, float %.4f, float %.4f)";
				setColorBoldCyan();
				printf(tmp_sFormat, taskMenu_iOption, taskMenu_fNum1, taskMenu_fNum2);
				resetColor();
			}
			taskCalc_message(taskMenu_iOption,taskMenu_fNum1,taskMenu_fNum2);
			
			taskMenu_state = STT_MENU_WAIT;
			break;

		case STT_MENU_PRINT_RESULT:
			printf("\nEl resultado es %.4f", taskMenu_fResult);
			
			taskMenu_state = STT_MENU_GET_OPTION;
			break;
		
		case STT_MENU_EXIT:
			printf("\n Nos vemos pronto...!! ¬(^0^)/  \n");
			exit(0); // EXIT
			break;
		
		default:
			printf("STT_MENU");
			taskMenu_state = STT_MENU_WAIT;
	}
}

void taskMenu_setState(int arg_stt)
{
	taskMenu_state = arg_stt;
}

void taskMenu_message(float arg_resultado)
{
	if(taskMenu_iDebugMode)
	{
		setColorBoldCyan();
		printf("\ntaskMenu_message(float %.4f)",arg_resultado);
		resetColor();
	}
	taskMenu_fResult = arg_resultado;

	taskMenu_state = STT_MENU_PRINT_RESULT;
}

void taskMenu_setDebugMode(int arg_debugMode){
        taskMenu_iDebugMode = arg_debugMode;
}
