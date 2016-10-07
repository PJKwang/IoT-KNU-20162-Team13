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

		motor_init(); //���� �ʱ�ȭ
		glcd_init();   //LCD �ʱ�ȭ

		ev3_sensor_init(0,2);  //ev���� �ʱ�ȭ port 0, COL_REFLECT


		for(;;)
		{
			glcdGotoChar(0,0);   //graphic LCD�� ��ġ �»�ܺ��� (0,0)
			glcd_clear();           //lcd clear
			switch(get_level(ev3_sensor_get(0), MAX_COLOR_LEVEL, color_value))     //get_level(EV3 ������ ���� ��, 3, ���� ��)
			{
				case COLOR_1:     //COLOR_1 = ���� 0 (value = 0,1,2)
					glcd_printf("COLOR_1 : %d " , ev3_sensor_get(0));     // EV3 ������ ���� �� ���
					motor_set(0,-1000);                                            // COLOR_1�� ���ϸ� ���� �ӵ� = -1000
					break;
				case COLOR_2:    //COLOR_2 = ���� 1 (value = 3,4,5)
					glcd_printf("COLOR_2 : %d " , ev3_sensor_get(0));
					motor_set(0,0);                                                  // 2�� ���ϸ� ���� �ӵ� = 0
					break;
				case COLOR_3:    //COLOR_3 = ���� 2 (value = 6,7)
					glcd_printf("COLOR3 : %d " , ev3_sensor_get(0));
					motor_set(0,1000);                                             // COLOR_3�� ���ϸ� ���� �ӵ� = 1000
					break;

				default:
					glcd_printf("default : %d " , ev3_sensor_get(0));
					break;

			}

			task_sleep(50);        //������ Sencing �ֱ� : 50ms
		}



}

