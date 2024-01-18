/**
 ******************************************************************************
 * @file           : icm42688.c
 * @brief          : 6-axis motion tracking chip ICM-42688-V (and not P version)
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include "string.h"
#include "main.h"
#include "basetypes.h"
#include "icm42688_registers.h"

/* Private includes ----------------------------------------------------------*/
#include "icm42688.h"
#include "spi.h"

// buffer for reading from sensor
uint8_t _buffer[15] = {};

uint8_t _bank = 0; ///< current user bank

// data buffer
float _t = 0.0f;
float _acc[3] = {};
float _gyr[3] = {};

///\brief Full scale resolution factors
float _accelScale = 0.0f;
float _gyroScale = 0.0f;

///\brief Full scale selections
AccelFS _accelFS;
GyroFS _gyroFS;

///\brief Accel calibration
float _accBD[3] = {};
float _accB[3] = {};
float _accS[3] = {1.0f, 1.0f, 1.0f};
float _accMax[3] = {};
float _accMin[3] = {};

///\brief Gyro calibration
float _gyroBD[3] = {};
float _gyrB[3] = {};

ICM42688_FIFO icm42688_FIFO;

/**
 * @brief      Get accelerometer data, per axis
 *
 * @return     Acceleration in g's
 */
float icm42688_accX()
{
	return _acc[0];
}
float icm42688_accY()
{
	return _acc[1];
}
float icm42688_accZ()
{
	return _acc[2];
}

/**
 * @brief      Get gyro data, per axis
 *
 * @return     Angular velocity in dps
 */
float icm42688_gyrX()
{
	return _gyr[0];
}
float icm42688_gyrY()
{
	return _gyr[1];
}
float icm42688_gyrZ()
{
	return _gyr[2];
}

/**
 * @brief      Get temperature of gyro die
 *
 * @return     Temperature in Celsius
 */
float icm42688_temp()
{
	return _t;
}

/* starts communication with the ICM42688 */
int icm42688_init()
{
	icm42688_FIFO.enFifoAccel = false;
	icm42688_FIFO.enFifoGyro = false;
	icm42688_FIFO.enFifoTemp = false;
	icm42688_FIFO.fifoSize = 0;
	icm42688_FIFO.fifoFrameSize = 0;
	memset(icm42688_FIFO.axFifo, 0, FIFO_SIZE * sizeof(float));
	memset(icm42688_FIFO.ayFifo, 0, FIFO_SIZE * sizeof(float));
	memset(icm42688_FIFO.azFifo, 0, FIFO_SIZE * sizeof(float));

	icm42688_FIFO.aSize = 0;

	memset(icm42688_FIFO.gxFifo, 0, FIFO_SIZE * sizeof(float));
	memset(icm42688_FIFO.gyFifo, 0, FIFO_SIZE * sizeof(float));
	memset(icm42688_FIFO.gzFifo, 0, FIFO_SIZE * sizeof(float));

	icm42688_FIFO.gSize = 0;

	memset(icm42688_FIFO.tFifo, 0, FIFO_SIZE * sizeof(float));

	memset(_buffer, 0, 15 * sizeof(uint8_t));

	icm42688_FIFO.tSize = 0;

	// reset the ICM42688
	icm42688_reset();

	// check the WHO AM I byte
	if(icm42688_whoAmI() != WHO_AM_I)
	{
		return -3;
	}

	// turn on accel and gyro in Low Noise (LN) Mode
	if(icm42688_writeRegister(UB0_REG_PWR_MGMT0, 0x0F) < 0)
	{
		return -4;
	}

	// 16G is default -- do this to set up accel resolution scaling
	int ret = icm42688_setAccelFS(gpm16);
	if (ret < 0) return ret;

	// 2000DPS is default -- do this to set up gyro resolution scaling
	ret = icm42688_setGyroFS(dps2000);
	if (ret < 0) return ret;

	// // disable inner filters (Notch filter, Anti-alias filter, UI filter block)
	// if (setFilters(false, false) < 0) {
	//   return -7;
	// }

	// estimate gyro bias
	if (icm42688_calibrateGyro() < 0) {
		return -8;
	}
	// successful init, return 1
	return 1;
}

/* sets the accelerometer full scale range to values other than default */
int icm42688_setAccelFS(AccelFS fssel)
{
	icm42688_setBank(0);

	// read current register value
	uint8_t reg;
	if (icm42688_readRegisters(UB0_REG_ACCEL_CONFIG0, 1, &reg) < 0) return -1;

	// only change FS_SEL in reg
	reg = (fssel << 5) | (reg & 0x1F);

	if (icm42688_writeRegister(UB0_REG_ACCEL_CONFIG0, reg) < 0) return -2;

	_accelScale = (float)(1 << (4 - fssel)) / 32768.0f;
	_accelFS = fssel;

	return 1;
}

/* sets the gyro full scale range to values other than default */
int icm42688_setGyroFS(GyroFS fssel)
{
	icm42688_setBank(0);

	// read current register value
	uint8_t reg;
	if (icm42688_readRegisters(UB0_REG_GYRO_CONFIG0, 1, &reg) < 0) return -1;

	// only change FS_SEL in reg
	reg = (fssel << 5) | (reg & 0x1F);

	if (icm42688_writeRegister(UB0_REG_GYRO_CONFIG0, reg) < 0) return -2;

	_gyroScale = (2000.0f / (float)(1 << fssel)) / 32768.0f;
	_gyroFS = fssel;

	return 1;
}

int icm42688_setAccelODR(ODR odr)
{
	icm42688_setBank(0);

	// read current register value
	uint8_t reg;
	if (icm42688_readRegisters(UB0_REG_ACCEL_CONFIG0, 1, &reg) < 0) return -1;

	// only change ODR in reg
	reg = odr | (reg & 0xF0);

	if (icm42688_writeRegister(UB0_REG_ACCEL_CONFIG0, reg) < 0) return -2;

	return 1;
}

int icm42688_setGyroODR(ODR odr)
{
	icm42688_setBank(0);

	// read current register value
	uint8_t reg;
	if (icm42688_readRegisters(UB0_REG_GYRO_CONFIG0, 1, &reg) < 0) return -1;

	// only change ODR in reg
	reg = odr | (reg & 0xF0);

	if (icm42688_writeRegister(UB0_REG_GYRO_CONFIG0, reg) < 0) return -2;

	return 1;
}

int icm42688_setFilters(uint8_t gyroFilters, uint8_t accFilters)
{
	if (icm42688_setBank(1) < 0) return -1;

	if (gyroFilters == true) {
		if (icm42688_writeRegister(UB1_REG_GYRO_CONFIG_STATIC2, GYRO_NF_ENABLE | GYRO_AAF_ENABLE) < 0) {
			return -2;
		}
	}
	else {
		if (icm42688_writeRegister(UB1_REG_GYRO_CONFIG_STATIC2, GYRO_NF_DISABLE | GYRO_AAF_DISABLE) < 0) {
			return -3;
		}
	}

	if (icm42688_setBank(2) < 0) return -4;

	if (accFilters == true) {
		if (icm42688_writeRegister(UB2_REG_ACCEL_CONFIG_STATIC2, ACCEL_AAF_ENABLE) < 0) {
			return -5;
		}
	}
	else {
		if (icm42688_writeRegister(UB2_REG_ACCEL_CONFIG_STATIC2, ACCEL_AAF_DISABLE) < 0) {
			return -6;
		}
	}
	if (icm42688_setBank(0) < 0) return -7;
	return 1;
}

int icm42688_enableDataReadyInterrupt()
{
	// push-pull, pulsed, active HIGH interrupts
	if (icm42688_writeRegister(UB0_REG_INT_CONFIG, 0x18 | 0x03) < 0) return -1;

	// need to clear bit 4 to allow proper INT1 and INT2 operation
	uint8_t reg;
	if (icm42688_readRegisters(UB0_REG_INT_CONFIG1, 1, &reg) < 0) return -2;
	reg &= ~0x10;
	if (icm42688_writeRegister(UB0_REG_INT_CONFIG1, reg) < 0) return -3;

	// route UI data ready interrupt to INT1
	if (icm42688_writeRegister(UB0_REG_INT_SOURCE0, 0x18) < 0) return -4;

	return 1;
}

int icm42688_disableDataReadyInterrupt()
{
	// set pin 4 to return to reset value
	uint8_t reg;
	if (icm42688_readRegisters(UB0_REG_INT_CONFIG1, 1, &reg) < 0) return -1;
	reg |= 0x10;
	if (icm42688_writeRegister(UB0_REG_INT_CONFIG1, reg) < 0) return -2;

	// return reg to reset value
	if (icm42688_writeRegister(UB0_REG_INT_SOURCE0, 0x10) < 0) return -3;

	return 1;
}

/* reads the most current data from ICM42688 and stores in buffer */
int icm42688_getAGT()
{
	if (icm42688_readRegisters(UB0_REG_TEMP_DATA1, 14, _buffer) < 0) return -1;

	// combine bytes into 16 bit values
	int16_t rawMeas[7]; // temp, accel xyz, gyro xyz
	for (size_t i=0; i<7; i++) {
		rawMeas[i] = ((int16_t)_buffer[i*2] << 8) | _buffer[i*2+1];
	}

	_t = ((float)rawMeas[0] / TEMP_DATA_REG_SCALE) + TEMP_OFFSET;

	_acc[0] = ((rawMeas[1] * _accelScale) - _accB[0]) * _accS[0];
	_acc[1] = ((rawMeas[2] * _accelScale) - _accB[1]) * _accS[1];
	_acc[2] = ((rawMeas[3] * _accelScale) - _accB[2]) * _accS[2];

	_gyr[0] = (rawMeas[4] * _gyroScale) - _gyrB[0];
	_gyr[1] = (rawMeas[5] * _gyroScale) - _gyrB[1];
	_gyr[2] = (rawMeas[6] * _gyroScale) - _gyrB[2];

	return 1;
}

/* configures and enables the FIFO buffer  */
int icm42688_FIFO_enableFifo(uint8_t accel,uint8_t gyro,uint8_t temp)
{
	if(icm42688_writeRegister(FIFO_EN,(accel*FIFO_ACCEL)|(gyro*FIFO_GYRO)|(temp*FIFO_TEMP_EN)) < 0)
	{
		return -2;
	}
	icm42688_FIFO.enFifoAccel = accel;
	icm42688_FIFO.enFifoGyro = gyro;
	icm42688_FIFO.enFifoTemp = temp;
	icm42688_FIFO.fifoFrameSize = accel*6 + gyro*6 + temp*2;
	return 1;
}

/* reads data from the ICM42688 FIFO and stores in buffer */
int icm42688_FIFO_readFifo()
{
	icm42688_readRegisters(UB0_REG_FIFO_COUNTH, 2, _buffer);
	icm42688_FIFO.fifoSize = (((uint16_t) (_buffer[0]&0x0F)) <<8) + (((uint16_t) _buffer[1]));
	// read and parse the buffer
	for (size_t i=0; i < icm42688_FIFO.fifoSize/icm42688_FIFO.fifoFrameSize; i++) {
		// grab the data from the ICM42688
		if (icm42688_readRegisters(UB0_REG_FIFO_DATA, icm42688_FIFO.fifoFrameSize, _buffer) < 0) {
			return -1;
		}
		if (icm42688_FIFO.enFifoAccel) {
			// combine into 16 bit values
			int16_t rawMeas[3];
			rawMeas[0] = (((int16_t)_buffer[0]) << 8) | _buffer[1];
			rawMeas[1] = (((int16_t)_buffer[2]) << 8) | _buffer[3];
			rawMeas[2] = (((int16_t)_buffer[4]) << 8) | _buffer[5];
			// transform and convert to float values
			icm42688_FIFO.axFifo[i] = ((rawMeas[0] * _accelScale) - _accB[0]) * _accS[0];
			icm42688_FIFO.ayFifo[i] = ((rawMeas[1] * _accelScale) - _accB[1]) * _accS[1];
			icm42688_FIFO.azFifo[i] = ((rawMeas[2] * _accelScale) - _accB[2]) * _accS[2];
			icm42688_FIFO.aSize = icm42688_FIFO.fifoSize / icm42688_FIFO.fifoFrameSize;
		}
		if (icm42688_FIFO.enFifoTemp) {
			// combine into 16 bit values
			int16_t rawMeas = (((int16_t)_buffer[0 + icm42688_FIFO.enFifoAccel*6]) << 8) | _buffer[1 + icm42688_FIFO.enFifoAccel*6];
			// transform and convert to float values
			icm42688_FIFO.tFifo[i] = ((float)rawMeas / TEMP_DATA_REG_SCALE) + TEMP_OFFSET;
			icm42688_FIFO.tSize = icm42688_FIFO.fifoSize/icm42688_FIFO.fifoFrameSize;
		}
		if (icm42688_FIFO.enFifoGyro) {
			// combine into 16 bit values
			int16_t rawMeas[3];
			rawMeas[0] = (((int16_t)_buffer[0 + icm42688_FIFO.enFifoAccel*6 + icm42688_FIFO.enFifoTemp*2]) << 8) | _buffer[1 + icm42688_FIFO.enFifoAccel*6 + icm42688_FIFO.enFifoTemp*2];
			rawMeas[1] = (((int16_t)_buffer[2 + icm42688_FIFO.enFifoAccel*6 + icm42688_FIFO.enFifoTemp*2]) << 8) | _buffer[3 + icm42688_FIFO.enFifoAccel*6 + icm42688_FIFO.enFifoTemp*2];
			rawMeas[2] = (((int16_t)_buffer[4 + icm42688_FIFO.enFifoAccel*6 + icm42688_FIFO.enFifoTemp*2]) << 8) | _buffer[5 + icm42688_FIFO.enFifoAccel*6 + icm42688_FIFO.enFifoTemp*2];
			// transform and convert to float values
			icm42688_FIFO.gxFifo[i] = (rawMeas[0] * _gyroScale) - _gyrB[0];
			icm42688_FIFO.gyFifo[i] = (rawMeas[1] * _gyroScale) - _gyrB[1];
			icm42688_FIFO.gzFifo[i] = (rawMeas[2] * _gyroScale) - _gyrB[2];
			icm42688_FIFO.gSize = icm42688_FIFO.fifoSize/icm42688_FIFO.fifoFrameSize;
		}
	}
	return 1;
}

/* returns the accelerometer FIFO size and data in the x direction, m/s/s */
void icm42688_FIFO_getFifoAccelX_mss(size_t *size, float* data)
{
	*size = icm42688_FIFO.aSize;
	memcpy(data, icm42688_FIFO.axFifo, icm42688_FIFO.aSize*sizeof(float));
}

/* returns the accelerometer FIFO size and data in the y direction, m/s/s */
void icm42688_FIFO_getFifoAccelY_mss(size_t *size, float* data)
{
	*size = icm42688_FIFO.aSize;
	memcpy(data, icm42688_FIFO.ayFifo, icm42688_FIFO.aSize*sizeof(float));
}

/* returns the accelerometer FIFO size and data in the z direction, m/s/s */
void icm42688_FIFO_getFifoAccelZ_mss(size_t *size, float* data)
{
	*size = icm42688_FIFO.aSize;
	memcpy(data, icm42688_FIFO.azFifo, icm42688_FIFO.aSize*sizeof(float));
}

/* returns the gyroscope FIFO size and data in the x direction, dps */
void icm42688_FIFO_getFifoGyroX(size_t *size, float* data)
{
	*size = icm42688_FIFO.gSize;
	memcpy(data, icm42688_FIFO.gxFifo, icm42688_FIFO.gSize*sizeof(float));
}

/* returns the gyroscope FIFO size and data in the y direction, dps */
void icm42688_FIFO_getFifoGyroY(size_t *size, float* data)
{
	*size = icm42688_FIFO.gSize;
	memcpy(data, icm42688_FIFO.gyFifo, icm42688_FIFO.gSize*sizeof(float));
}

/* returns the gyroscope FIFO size and data in the z direction, dps */
void icm42688_FIFO_getFifoGyroZ(size_t *size, float* data)
{
	*size = icm42688_FIFO.gSize;
	memcpy(data, icm42688_FIFO.gzFifo, icm42688_FIFO.gSize*sizeof(float));
}

/* returns the die temperature FIFO size and data, C */
void icm42688_FIFO_getFifoTemperature_C(size_t *size,float* data)
{
	*size = icm42688_FIFO.tSize;
	memcpy(data, icm42688_FIFO.tFifo, icm42688_FIFO.tSize*sizeof(float));
}

/* estimates the gyro biases */
int icm42688_calibrateGyro()
{
	// set at a lower range (more resolution) since IMU not moving
	const GyroFS current_fssel = _gyroFS;
	if (icm42688_setGyroFS(dps250) < 0) return -1;

	// take samples and find bias
	_gyroBD[0] = 0;
	_gyroBD[1] = 0;
	_gyroBD[2] = 0;
	for (size_t i=0; i < NUM_CALIB_SAMPLES; i++) {
		icm42688_getAGT();
		_gyroBD[0] += (icm42688_gyrX() + _gyrB[0]) / NUM_CALIB_SAMPLES;
		_gyroBD[1] += (icm42688_gyrY() + _gyrB[1]) / NUM_CALIB_SAMPLES;
		_gyroBD[2] += (icm42688_gyrZ() + _gyrB[2]) / NUM_CALIB_SAMPLES;
		HAL_Delay(1);
	}
	_gyrB[0] = _gyroBD[0];
	_gyrB[1] = _gyroBD[1];
	_gyrB[2] = _gyroBD[2];

	// recover the full scale setting
	if (icm42688_setGyroFS(current_fssel) < 0) return -4;
	return 1;
}

/* returns the gyro bias in the X direction, dps */
float icm42688_getGyroBiasX()
{
	return _gyrB[0];
}

/* returns the gyro bias in the Y direction, dps */
float icm42688_getGyroBiasY()
{
	return _gyrB[1];
}

/* returns the gyro bias in the Z direction, dps */
float icm42688_getGyroBiasZ()
{
	return _gyrB[2];
}

/* sets the gyro bias in the X direction to bias, dps */
void icm42688_setGyroBiasX(float bias)
{
	_gyrB[0] = bias;
}

/* sets the gyro bias in the Y direction to bias, dps */
void icm42688_setGyroBiasY(float bias)
{
	_gyrB[1] = bias;
}

/* sets the gyro bias in the Z direction to bias, dps */
void icm42688_setGyroBiasZ(float bias)
{
	_gyrB[2] = bias;
}

/* finds bias and scale factor calibration for the accelerometer,
this should be run for each axis in each direction (6 total) to find
the min and max values along each */
int icm42688_calibrateAccel()
{
	// set at a lower range (more resolution) since IMU not moving
	const AccelFS current_fssel = _accelFS;
	if (icm42688_setAccelFS(gpm2) < 0) return -1;

	// take samples and find min / max
	_accBD[0] = 0;
	_accBD[1] = 0;
	_accBD[2] = 0;
	for (size_t i=0; i < NUM_CALIB_SAMPLES; i++) {
		icm42688_getAGT();
		_accBD[0] += (icm42688_accX()/_accS[0] + _accB[0]) / NUM_CALIB_SAMPLES;
		_accBD[1] += (icm42688_accY()/_accS[1] + _accB[1]) / NUM_CALIB_SAMPLES;
		_accBD[2] += (icm42688_accZ()/_accS[2] + _accB[2]) / NUM_CALIB_SAMPLES;
		HAL_Delay(1);
	}
	if (_accBD[0] > 0.9f) {
		_accMax[0] = _accBD[0];
	}
	if (_accBD[1] > 0.9f) {
		_accMax[1] = _accBD[1];
	}
	if (_accBD[2] > 0.9f) {
		_accMax[2] = _accBD[2];
	}
	if (_accBD[0] < -0.9f) {
		_accMin[0] = _accBD[0];
	}
	if (_accBD[1] < -0.9f) {
		_accMin[1] = _accBD[1];
	}
	if (_accBD[2] < -0.9f) {
		_accMin[2] = _accBD[2];
	}

	// find bias and scale factor
	if ((abs(_accMin[0]) > 0.9f) && (abs(_accMax[0]) > 0.9f)) {
		_accB[0] = (_accMin[0] + _accMax[0]) / 2.0f;
		_accS[0] = 1/((abs(_accMin[0]) + abs(_accMax[0])) / 2.0f);
	}
	if ((abs(_accMin[1]) > 0.9f) && (abs(_accMax[1]) > 0.9f)) {
		_accB[1] = (_accMin[1] + _accMax[1]) / 2.0f;
		_accS[1] = 1/((abs(_accMin[1]) + abs(_accMax[1])) / 2.0f);
	}
	if ((abs(_accMin[2]) > 0.9f) && (abs(_accMax[2]) > 0.9f)) {
		_accB[2] = (_accMin[2] + _accMax[2]) / 2.0f;
		_accS[2] = 1/((abs(_accMin[2]) + abs(_accMax[2])) / 2.0f);
	}

	// recover the full scale setting
	if (icm42688_setAccelFS(current_fssel) < 0) return -4;
	return 1;
}

/* returns the accelerometer bias in the X direction, m/s/s */
float icm42688_getAccelBiasX_mss()
{
	return _accB[0];
}

/* returns the accelerometer scale factor in the X direction */
float icm42688_getAccelScaleFactorX()
{
	return _accS[0];
}

/* returns the accelerometer bias in the Y direction, m/s/s */
float icm42688_getAccelBiasY_mss()
{
	return _accB[1];
}

/* returns the accelerometer scale factor in the Y direction */
float icm42688_getAccelScaleFactorY()
{
	return _accS[1];
}

/* returns the accelerometer bias in the Z direction, m/s/s */
float icm42688_getAccelBiasZ_mss()
{
	return _accB[2];
}

/* returns the accelerometer scale factor in the Z direction */
float icm42688_getAccelScaleFactorZ()
{
	return _accS[2];
}

/* sets the accelerometer bias (m/s/s) and scale factor in the X direction */
void icm42688_setAccelCalX(float bias,float scaleFactor)
{
	_accB[0] = bias;
	_accS[0] = scaleFactor;
}

/* sets the accelerometer bias (m/s/s) and scale factor in the Y direction */
void icm42688_setAccelCalY(float bias,float scaleFactor)
{
	_accB[1] = bias;
	_accS[1] = scaleFactor;
}

/* sets the accelerometer bias (m/s/s) and scale factor in the Z direction */
void icm42688_setAccelCalZ(float bias,float scaleFactor)
{
	_accB[2] = bias;
	_accS[2] = scaleFactor;
}

/* writes a byte to ICM42688 register given a register address and data */
int icm42688_writeRegister(uint8_t subAddress, uint8_t data)
{
	int rv = 0;
	/* write data to device */
	HAL_GPIO_WritePin(MEMS_CS_GPIO_Port, MEMS_CS_Pin, GPIO_PIN_RESET);
	while(HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY);
	rv += HAL_SPI_Transmit(&hspi2, &subAddress, 1, 1000);
	while(HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY);
	rv += HAL_SPI_Transmit(&hspi2, &data, 1, 1000);
	HAL_GPIO_WritePin(MEMS_CS_GPIO_Port, MEMS_CS_Pin, GPIO_PIN_SET);

	HAL_Delay(10);

	/* read back the register */
	icm42688_readRegisters(subAddress, 1, _buffer);
	/* check the read back register against the written register */
	if(_buffer[0] == data)
	{
		return 1;
	}
	else{
		return -1;
	}
}

/* reads registers from ICM42688 given a starting register address, number of bytes, and a pointer to store data */
int icm42688_readRegisters(uint8_t subAddress, uint8_t count, uint8_t* dest)
{
	int rv = 0;
	subAddress |= 0x80;
	HAL_GPIO_WritePin(MEMS_CS_GPIO_Port, MEMS_CS_Pin, GPIO_PIN_RESET);
	while(HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(&hspi2, &subAddress, 1, 1000);
	while(HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY);
	rv += HAL_SPI_Receive(&hspi2, dest, count, 1000);
	HAL_GPIO_WritePin(MEMS_CS_GPIO_Port, MEMS_CS_Pin, GPIO_PIN_SET);
	return rv;
}

int icm42688_setBank(uint8_t bank)
{
	// if we are already on this bank, bail
	if (_bank == bank) return 1;

	_bank = bank;

	return icm42688_writeRegister(REG_BANK_SEL, bank);
}

void icm42688_reset()
{
	icm42688_setBank(0);

	icm42688_writeRegister(UB0_REG_DEVICE_CONFIG, 0x01);

	// wait for ICM42688 to come back up
	HAL_Delay(1);
}

/* gets the ICM42688 WHO_AM_I register value */
uint8_t icm42688_whoAmI()
{
	icm42688_setBank(0);

	// read the WHO AM I register
	if (icm42688_readRegisters(UB0_REG_WHO_AM_I, 1, _buffer) < 0)
	{
		return -1;
	}
	// return the register value
	return _buffer[0];
}
