#include <sapi_imu_mpu60X0.h>

#include "mpu.h"

int mpu_init( void )
{
	int ret = 0;
	if (mpu60X0Init(MPU60X0_ADDRESS_0) < 0)
		ret = -1;
	return ret;
}

void mpu_get_accelerometer( float accel[3] )
{
	mpu60X0Read();
	accel[0] = mpu60X0GetAccelX_mss();
	accel[1] = mpu60X0GetAccelY_mss();
	accel[2] = mpu60X0GetAccelZ_mss();
}
