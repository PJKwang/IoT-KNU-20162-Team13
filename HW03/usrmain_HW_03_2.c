/*
  Copyright (C) 2009 Sung Ho Park
  Contact: ubinos.org@gmail.com

  This file is part of the exe_helloworld component of the Ubinos.

  GNU General Public License Usage
  This file may be used under the terms of the GNU
  General Public License version 3.0 as published by the Free Software
  Foundation and appearing in the file license_gpl3.txt included in the
  packaging of this file. Please review the following information to
  ensure the GNU General Public License version 3.0 requirements will be
  met: http://www.gnu.org/copyleft/gpl.html.

  GNU Lesser General Public License Usage
  Alternatively, this file may be used under the terms of the GNU Lesser
  General Public License version 2.1 as published by the Free Software
  Foundation and appearing in the file license_lgpl.txt included in the
  packaging of this file. Please review the following information to
  ensure the GNU Lesser General Public License version 2.1 requirements
  will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.

  Commercial Usage
  Alternatively, licensees holding valid commercial licenses may
  use this file in accordance with the commercial license agreement
  provided with the software or, alternatively, in accordance with the
  terms contained in a written agreement between you and rightful owner.
*/

/* -------------------------------------------------------------------------
	Include
 ------------------------------------------------------------------------- */
#include "../ubiconfig.h"

// standard c library include
#include <stdio.h>
#include <sam4e.h>

// ubinos library include
#include "itf_ubinos/itf/bsp.h"
#include "itf_ubinos/itf/ubinos.h"
#include "itf_ubinos/itf/bsp_fpu.h"

// chipset driver include
#include "ioport.h"
#include "pio/pio.h"

// new estk driver include
#include "lib_new_estk_api/itf/new_estk_led.h"
#include "lib_new_estk_api/itf/new_estk_glcd.h"
#include "lib_sensor/itf/lib_sensor.h"
#include "lib_motor_driver/itf/lib_motor_driver.h"
#include "lib_EV3_sensor/itf/lib_EV3_sensor.h"
#include "lib_sensorcalib/itf/lib_sensorcalib.h"
#include "lib_switch/itf/lib_switch.h"





// custom library header file include
//#include "../../lib_default/itf/lib_default.h"

// user header file include

/* -------------------------------------------------------------------------
	Global variables
 ------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------
	Prototypes
 ------------------------------------------------------------------------- */
static void rootfunc(void * arg);


/* -------------------------------------------------------------------------
	Function Definitions
 ------------------------------------------------------------------------- */
int usrmain(int argc, char * argv[]) {
	int r;

	printf("\n\n\n\r");
	printf("================================================================================\n\r");
	printf("exe_ubinos_test (build time: %s %s)\n\r", __TIME__, __DATE__);
	printf("================================================================================\n\r");

	r = task_create(NULL, rootfunc, NULL, task_getmiddlepriority(), 256, "root");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	ubik_comp_start();

	return 0;
}

static void rootfunc(void * arg) {

		motor_init();   //모터 초기화
		glcd_init();     //LCD 초기화

		sensor_init(NXT_DIGITAL_SENSOR_SONA,0,0,0);  //NXT 센서 초기화 함수, NXT_DIGITAL 센서 타입

		glcd_clear();  //LCD clear
		for(;;)
		{


			glcdGotoChar(0,0);        //graphic LCD의 위치 좌상단부터 (0,0)

			switch(get_level(sensor_get(0), MAX_SONA_4LEVEL, sona_4value))  //get_level(센서 입력받기, 4, sona_4value[MAX_SONA_4LEVEL] = {0,20 ,40,60})
			{
				case SONA_NEAR:                                                           // 근처 값에 속한다면
					glcd_printf("SONA_NEAR : %d " , sensor_get(0));               // 센서에서 입력 받은 값 출력
					motor_set(0,-1000);                                                    // 모터 속도 -1000
					break;
				case SONA_MIDDLE:                                                       // 중간 값에 속한다면
					glcd_printf("SONA_MIDDLE : %d " , sensor_get(0));             
					motor_set(0,0);                                                          // 모터 속도 0
					break;
				case SONA_FAR:                                                             // 먼 값에 속한다면
					glcd_printf("SONA_FAR : %d " , sensor_get(0));
					motor_set(0,500);                                                       // 모터 속도 500
					break;
				case SONA_SOFAR:                                                         // 아주 먼 값에 속한다면
					glcd_printf("SONA_SOFAR : %d " , sensor_get(0));
					motor_set(0,1000);                                                     // 모터 속도 1000
					break;

				default:
					glcd_printf("SONA_DEFAULT : %d " , sensor_get(0));
					motor_set(0,300);
					break;

			}

			task_sleep(30);         //초음파 Sensing 주기 30ms
		}



}

