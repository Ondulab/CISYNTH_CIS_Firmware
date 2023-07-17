/**
 ******************************************************************************
 * @file           : icm20602.c
 * @brief          : 6-axis motion tracking chip
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include "main.h"
#include "basetypes.h"

/* Private includes ----------------------------------------------------------*/
#include "icm20602.h"
#include "spi.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define REG_XG_OFFS_TC_H 0x04
#define REG_XG_OFFS_TC_L 0x05
#define REG_YG_OFFS_TC_H 0x07
#define REG_YG_OFFS_TC_L 0x08
#define REG_ZG_OFFS_TC_H 0x0A
#define REG_ZG_OFFS_TC_L 0x0B
#define REG_SELF_TEST_X_ACCEL 0x0D
#define REG_SELF_TEST_Y_ACCEL 0x0E
#define REG_SELF_TEST_Z_ACCEL 0x0F
#define REG_XG_OFFS_USRH 0x13
#define REG_XG_OFFS_USRL 0x14
#define REG_YG_OFFS_USRH 0x15
#define REG_YG_OFFS_USRL 0x16
#define REG_ZG_OFFS_USRH 0x17
#define REG_ZG_OFFS_USRL 0x18
#define REG_SMPLRT_DIV 0x19
#define REG_CONFIG 0x1A
#define REG_GYRO_CONFIG 0x1B
#define REG_ACCEL_CONFIG 0x1C
#define REG_ACCEL_CONFIG_2 0x1D
#define REG_LP_MODE_CFG 0x1E
#define REG_ACCEL_WOM_X_THR 0x20
#define REG_ACCEL_WOM_Y_THR 0x21
#define REG_ACCEL_WOM_Z_THR 0x22
#define REG_FIFO_EN 0x23
#define REG_FSYNC_INT 0x36
#define REG_INT_PIN_CFG 0x37
#define REG_INT_ENABLE 0x38
#define REG_FIFO_WM_INT_STATUS 0x39
#define REG_INT_STATUS 0x3A
#define REG_ACCEL_XOUT_H 0x3B
#define REG_ACCEL_XOUT_L 0x3C
#define REG_ACCEL_YOUT_H 0x3D
#define REG_ACCEL_YOUT_L 0x3E
#define REG_ACCEL_ZOUT_H 0x3F
#define REG_ACCEL_ZOUT_L 0x40
#define REG_TEMP_OUT_H 0x41
#define REG_TEMP_OUT_L 0x42
#define REG_GYRO_XOUT_H 0x43
#define REG_GYRO_XOUT_L 0x44
#define REG_GYRO_YOUT_H 0x45
#define REG_GYRO_YOUT_L 0x46
#define REG_GYRO_ZOUT_H 0x47
#define REG_GYRO_ZOUT_L 0x48
#define REG_SELF_TEST_X_GYRO 0x50
#define REG_SELF_TEST_Y_GYRO 0x51
#define REG_SELF_TEST_Z_GYRO 0x52
#define REG_FIFO_WM_TH1 0x60
#define REG_FIFO_WM_TH2 0x61
#define REG_SIGNAL_PATH_RESET 0x68
#define REG_ACCEL_INTEL_CTRL 0x69
#define REG_USER_CTRL 0x6A
#define REG_PWR_MGMT_1 0x6B
#define REG_PWR_MGMT_2 0x6C
#define REG_I2C_IF 0x70
#define REG_FIFO_COUNTH 0x72
#define REG_FIFO_COUNTL 0x73
#define REG_FIFO_R_W 0x74
#define REG_WHO_AM_I 0x75
#define REG_XA_OFFSET_H 0x77
#define REG_XA_OFFSET_L 0x78
#define REG_YA_OFFSET_H 0x7A
#define REG_YA_OFFSET_L 0x7B
#define REG_ZA_OFFSET_H 0x7D
#define REG_ZA_OFFSET_L 0x7E
#define REG_WHO_AM_I_CONST 0X12

/* Private macro -------------------------------------------------------------*/
#define ON_ERROR_GOTO(cond, symbol) \
		if (!(cond)) { goto symbol; }

// extra steps, but I'm paranoid about some compilers/systems not handling the
// conversion from uint8_t to int16_t correctly
#define UINT8_TO_INT16(dst, src_high, src_low) \
		do { \
			dst = (src_high); \
			dst <<= 8; \
			dst |= (src_low); \
		} while (0);

/* Private variables ---------------------------------------------------------*/
// TODO: Look into getting real temp sensitivity.
static float _temp_sensitivity = 326.8;

static struct icm20602_dev dev={
		.accel_dlpf = ICM20602_ACCEL_DLPF_10_2_HZ,
		.accel_fifo = FALSE,
		.accel_g = ICM20602_ACCEL_RANGE_2G,
		.gyro_dlpf = ICM20602_GYRO_DLPF_5_HZ,
		.gyro_dps = ICM20602_GYRO_RANGE_1000_DPS,
		.sample_rate_div = 0,
		.use_accel = TRUE,
		.use_gyro = TRUE,
};

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

//Writes a register byte to the driver
uint8_t icm20602_write(uint8_t reg, uint8_t *data, uint16_t len)
{
	int rv = 0;
	HAL_GPIO_WritePin(MEMS_CS_GPIO_Port, MEMS_CS_Pin, GPIO_PIN_RESET);
	while(HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY);
	rv = HAL_SPI_Transmit(&hspi2, &reg, 1, 1000);
	while(HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY);
	rv += HAL_SPI_Transmit(&hspi2, data, len, 1000);
	HAL_GPIO_WritePin(MEMS_CS_GPIO_Port, MEMS_CS_Pin, GPIO_PIN_SET);
	return rv;
}

//Read a register byte to the driver
uint8_t icm20602_read(uint8_t reg, uint8_t *data, uint16_t len)
{
	int rv = 0;
	reg |= 0b10000000;
	HAL_GPIO_WritePin(MEMS_CS_GPIO_Port, MEMS_CS_Pin, GPIO_PIN_RESET);
	while(HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY);
	rv = HAL_SPI_Transmit(&hspi2, &reg, 1, 1000);
	while(HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY);
	rv += HAL_SPI_Receive(&hspi2, data, len, 1000);
	HAL_GPIO_WritePin(MEMS_CS_GPIO_Port, MEMS_CS_Pin, GPIO_PIN_SET);
	return rv;
}

/// Used to convert raw accelerometer readings to G-force.
float icm20602_get_accel_sensitivity(enum icm20602_accel_g accel_g)
{
	float f = 0.0;

	switch (accel_g) {
	case (ICM20602_ACCEL_RANGE_2G):
    										f = 16384.0;
	break;
	case (ICM20602_ACCEL_RANGE_4G):
    										f = 8192.0;
	break;
	case (ICM20602_ACCEL_RANGE_8G):
    										f = 4096.0;
	break;
	case (ICM20602_ACCEL_RANGE_16G):
    										f = 2048.0;
	break;
	}

	return f;
}

/// Used to convert raw gyroscope readings to degrees per second.
float icm20602_get_gyro_sensitivity(enum icm20602_gyro_dps gyro_dps)
{
	float f = 0;

	switch (gyro_dps) {
	case (ICM20602_GYRO_RANGE_250_DPS):
    										f = 131.0;
	break;
	case (ICM20602_GYRO_RANGE_500_DPS):
    										f = 65.5;
	break;
	case (ICM20602_GYRO_RANGE_1000_DPS):
    										f = 32.8;
	break;
	case (ICM20602_GYRO_RANGE_2000_DPS):
    										f = 16.4;
	break;
	}

	return f;
}

/***** Global Functions *****/

int8_t icm20602_init(void)
{
	uint8_t tmp = 0;
	int8_t r = 0;

	// General Procedure:
	//  1. reset chip
	//  2. set clock for PLL for optimum performance as documented in datasheet
	//  3. place accelerometer and gyroscope into standby
	//  4. disable fifo
	//  5. configure chip
	//  6. enable accelerometer and gyroscope

	// full reset of chip
	tmp = 0x80;
	r = icm20602_write(REG_PWR_MGMT_1, &tmp, 1);
	ON_ERROR_GOTO((0 == r), return_err);

	HAL_Delay(100);

	// verify we are able to read from the chip
	r = icm20602_read(REG_WHO_AM_I, &tmp, 1);
	ON_ERROR_GOTO((0 == r), return_err);
	if (REG_WHO_AM_I_CONST != tmp) {
		r = -1;
		ON_ERROR_GOTO((0 == r), return_err);
	}

	/*Reset path*/
	tmp = 0x03;
	r = icm20602_write(REG_SIGNAL_PATH_RESET, &tmp, 1);
	ON_ERROR_GOTO((0 == r), return_err);

	HAL_Delay(100);

	// set clock to internal PLL
	tmp = 0x01;
	r = icm20602_write(REG_PWR_MGMT_1, &tmp, 1);
	ON_ERROR_GOTO((0 == r), return_err);

	HAL_Delay(15);

	// place accel and gyro on standby
	tmp = 0x3F;
	r = icm20602_write(REG_PWR_MGMT_2, &tmp, 1);
	ON_ERROR_GOTO((0 == r), return_err);

	// disable fifo
	tmp = 0x01;
	r = icm20602_write(REG_USER_CTRL, &tmp, 1);
	ON_ERROR_GOTO((0 == r), return_err);

	// disable chip I2C communications
	tmp = 0x40;
	r = icm20602_write(REG_I2C_IF, &tmp, 1);
	ON_ERROR_GOTO((0 == r), return_err);

	if (dev.use_accel) {
		if (ICM20602_ACCEL_DLPF_BYPASS_1046_HZ == dev.accel_dlpf) {
			tmp = (1 << 3);
			r =  icm20602_write(REG_ACCEL_CONFIG_2, &tmp, 1);
			ON_ERROR_GOTO((0 == r), return_err);
		}
		else {
			tmp = dev.accel_dlpf;
			r =  icm20602_write(REG_ACCEL_CONFIG_2, &tmp, 1);
			ON_ERROR_GOTO((0 == r), return_err);
		}

		tmp = (dev.accel_g) << 2;
		r =  icm20602_write(REG_ACCEL_CONFIG, &tmp, 1);
		ON_ERROR_GOTO((0 == r), return_err);
	}

	if (dev.use_gyro) {
		if (ICM20602_GYRO_DLPF_BYPASS_3281_HZ == dev.gyro_dlpf) {
			// bypass dpf and set dps
			tmp = 0x00;
			r =  icm20602_write(REG_CONFIG, &tmp, 1);
			ON_ERROR_GOTO((0 == r), return_err);

			tmp = (dev.gyro_dps << 3) | 0x02; // see table page 37 of datasheet
			r =  icm20602_write(REG_GYRO_CONFIG, &tmp, 1);
			ON_ERROR_GOTO((0 == r), return_err);
		}
		else if (ICM20602_GYRO_DLPF_BYPASS_8173_HZ == dev.gyro_dlpf) {
			// bypass dpf and set dps
			tmp = 0x00;
			r =  icm20602_write(REG_CONFIG, &tmp, 1);
			ON_ERROR_GOTO((0 == r), return_err);

			tmp = (dev.gyro_dps << 3) | 0x01; // see table page 37 of datasheet
			r =  icm20602_write(REG_GYRO_CONFIG, &tmp, 1);
			ON_ERROR_GOTO((0 == r), return_err);
		}
		else {
			// configure dpf and set dps
			tmp = dev.gyro_dlpf;
			r =  icm20602_write(REG_CONFIG, &tmp, 1);
			ON_ERROR_GOTO((0 == r), return_err);

			tmp = dev.gyro_dps << 3;
			r =  icm20602_write(REG_GYRO_CONFIG, &tmp, 1);
			ON_ERROR_GOTO((0 == r), return_err);
		}
	}

	/*Disale low power mode*/
	tmp = 0x00;
	r = icm20602_write(REG_LP_MODE_CFG, &tmp, 1);
	ON_ERROR_GOTO((0 == r), return_err);

	// enable FIFO if requested
	tmp = ((dev.use_accel) && (dev.accel_fifo)) ? 0x08 : 0x00;
	tmp |= ((dev.use_gyro) && (dev.gyro_fifo)) ? 0x10 : 0x00;
	r =  icm20602_write(REG_FIFO_EN, &tmp, 1);
	ON_ERROR_GOTO((0 == r), return_err);

	// configure sample rate divider (TODO: is this gyro only?)
	// note: SAMPLE_RATE = INTERNAL_SAMPLE_RATE / (1 + SMPLRT_DIV)
	tmp = (0 != dev.sample_rate_div) ? dev.sample_rate_div - 1 : 1;
	r =  icm20602_write(REG_SMPLRT_DIV, &tmp, 1);
	ON_ERROR_GOTO((0 == r), return_err);

	tmp = 0;
	tmp |= (dev.use_gyro) ? 0 : 0x07; // 0 - on, 1 - disabled
	tmp |= (dev.use_accel) ? 0 : 0x38; // 0 - on, 1 - disabled
	r =  icm20602_write(REG_PWR_MGMT_2, &tmp, 1);
	ON_ERROR_GOTO((0 == r), return_err);

	return_err:

	return r;
}

int8_t icm20602_read_accel(float * p_x, float * p_y,
		float * p_z)
{
	float accel_sensitivity;
	int16_t x, y, z;
	int8_t r = 0;

	accel_sensitivity = icm20602_get_accel_sensitivity(dev.accel_g);

	r = icm20602_read_accel_raw(&x, &y, &z);
	if (0 == r) {
		*p_x = ((float) x) / accel_sensitivity;
		*p_y = ((float) y) / accel_sensitivity;
		*p_z = ((float) z) / accel_sensitivity;
	}

	return r;
}

int8_t icm20602_read_gyro(float * p_x, float * p_y,
		float * p_z)
{
	float gyro_sensitivity;
	int16_t x, y, z;
	int8_t r = 0;

	gyro_sensitivity = icm20602_get_gyro_sensitivity(dev.gyro_dps);

	r = icm20602_read_gyro_raw(&x, &y, &z);
	if (0 == r) {
		*p_x = ((float) x) / gyro_sensitivity;
		*p_y = ((float) y) / gyro_sensitivity;
		*p_z = ((float) z) / gyro_sensitivity;
	}

	return r;
}

int8_t icm20602_read_data(float * p_ax, float * p_ay,
		float * p_az, float * p_gx, float * p_gy, float * p_gz, float * p_t)
{
	float accel_sensitivity;
	float gyro_sensitivity;
	int16_t ax, ay, az, gx, gy, gz, t;
	int8_t r = 0;

	accel_sensitivity = icm20602_get_accel_sensitivity(dev.accel_g);
	gyro_sensitivity = icm20602_get_gyro_sensitivity(dev.gyro_dps);

	r = icm20602_read_data_raw(&ax, &ay, &az, &gx, &gy, &gz, &t);
	if (0 == r) {
		*p_ax = ((float) ax) / accel_sensitivity;
		*p_ay = ((float) ay) / accel_sensitivity;
		*p_az = ((float) az) / accel_sensitivity;
		*p_gx = ((float) gx) / gyro_sensitivity;
		*p_gy = ((float) gy) / gyro_sensitivity;
		*p_gz = ((float) gz) / gyro_sensitivity;
		*p_t = ((float) t) / _temp_sensitivity;
	}

	return r;
}

int8_t icm20602_read_accel_raw(int16_t * p_x, int16_t * p_y,
		int16_t * p_z)
{
	uint8_t buf[8] = {0};
	int8_t r = 0;

	r = icm20602_read(REG_ACCEL_XOUT_H, buf, 8);
	if (0 == r) {
		UINT8_TO_INT16(*p_x, buf[0], buf[1]);
		UINT8_TO_INT16(*p_y, buf[2], buf[3]);
		UINT8_TO_INT16(*p_z, buf[4], buf[5]);
		// buf[6] and buf[7] hold temperature
	}

	return r;
}

int8_t icm20602_read_gyro_raw(int16_t * p_x, int16_t * p_y,
		int16_t * p_z)
{
	uint8_t buf[6] = {0};
	int8_t r = 0;

	r = icm20602_read(REG_GYRO_XOUT_H, buf, 6);
	if (0 == r) {
		UINT8_TO_INT16(*p_x, buf[0], buf[1]);
		UINT8_TO_INT16(*p_y, buf[2], buf[3]);
		UINT8_TO_INT16(*p_z, buf[4], buf[5]);
	}

	return r;
}

int8_t icm20602_read_data_raw(int16_t * p_ax,
		int16_t * p_ay, int16_t * p_az, int16_t * p_gx, int16_t * p_gy,
		int16_t * p_gz, int16_t * p_t)
{
	uint8_t buf[14] = {0};
	int8_t r = 0;

	r = icm20602_read(REG_ACCEL_XOUT_H, buf, 14);
	if (0 == r) {
		UINT8_TO_INT16(*p_ax, buf[0], buf[1]);
		UINT8_TO_INT16(*p_ay, buf[2], buf[3]);
		UINT8_TO_INT16(*p_az, buf[4], buf[5]);
		UINT8_TO_INT16(*p_t, buf[6], buf[7]);
		UINT8_TO_INT16(*p_gx, buf[8], buf[9]);
		UINT8_TO_INT16(*p_gy, buf[10], buf[11]);
		UINT8_TO_INT16(*p_gz, buf[12], buf[13]);
	}

	return r;
}

int8_t icm20602_read_accel_fifo(float * p_x, float * p_y,
		float * p_z)
{
	float accel_sensitivity;
	int16_t x, y, z;
	int8_t r = 0;

	accel_sensitivity = icm20602_get_accel_sensitivity(dev.accel_g);

	r = icm20602_read_fifo_accel_raw(&x, &y, &z);
	if (0 == r) {
		*p_x = ((float) x) / accel_sensitivity;
		*p_y = ((float) y) / accel_sensitivity;
		*p_z = ((float) z) / accel_sensitivity;
	}

	return r;
}

int8_t icm20602_read_gyro_fifo(float * p_x, float * p_y,
		float * p_z)
{
	float gyro_sensitivity;
	int16_t x, y, z;
	int8_t r = 0;

	//gyro_sensitivity = _get_gyro_sensitivity(dev.gyro_dps);

	r = icm20602_read_fifo_gyro_raw(&x, &y, &z);
	if (0 == r) {
		*p_x = ((float) x) / gyro_sensitivity;
		*p_y = ((float) y) / gyro_sensitivity;
		*p_z = ((float) z) / gyro_sensitivity;
	}

	return r;
}

int8_t icm20602_read_fifo_data(float * p_ax, float * p_ay,
		float * p_az, float * p_gx, float * p_gy, float * p_gz, float * p_t)
{
	float accel_sensitivity;
	float gyro_sensitivity;
	int16_t ax, ay, az, gx, gy, gz, t;
	int8_t r = 0;

	accel_sensitivity = icm20602_get_accel_sensitivity(dev.accel_g);
	gyro_sensitivity = icm20602_get_gyro_sensitivity(dev.gyro_dps);

	r = icm20602_read_fifo_data_raw(&ax, &ay, &az, &gx, &gy, &gz, &t);
	if (0 == r) {
		*p_ax = ((float) ax) / accel_sensitivity;
		*p_ay = ((float) ay) / accel_sensitivity;
		*p_az = ((float) az) / accel_sensitivity;
		*p_gx = ((float) gx) / gyro_sensitivity;
		*p_gy = ((float) gy) / gyro_sensitivity;
		*p_gz = ((float) gz) / gyro_sensitivity;
		*p_t = ((float) t) / _temp_sensitivity;
	}

	return r;
}

int8_t icm20602_read_fifo_accel_raw(int16_t * p_x,
		int16_t * p_y, int16_t * p_z)
{
	uint8_t buf[6] = {0};
	int8_t r = 0;

	r = icm20602_read(REG_FIFO_R_W, buf, 6);
	if (0 == r) {
		UINT8_TO_INT16(*p_x, buf[0], buf[1]);
		UINT8_TO_INT16(*p_y, buf[2], buf[3]);
		UINT8_TO_INT16(*p_z, buf[4], buf[5]);
	}

	return r;
}

int8_t icm20602_read_fifo_gyro_raw(int16_t * p_x,
		int16_t * p_y, int16_t * p_z)
{
	uint8_t buf[6] = {0};
	int8_t r = 0;

	r = icm20602_read(REG_FIFO_R_W, buf, 6);
	if (0 == r) {
		UINT8_TO_INT16(*p_x, buf[0], buf[1]);
		UINT8_TO_INT16(*p_y, buf[2], buf[3]);
		UINT8_TO_INT16(*p_z, buf[4], buf[5]);
	}

	return r;
}

int8_t icm20602_read_fifo_data_raw(int16_t * p_ax,
		int16_t * p_ay, int16_t * p_az, int16_t * p_gx, int16_t * p_gy,
		int16_t * p_gz, int16_t * p_t)
{
	uint8_t buf[14] = {0};
	int8_t r = 0;

	r = icm20602_read(REG_FIFO_R_W, buf, 14);
	if (0 == r) {
		UINT8_TO_INT16(*p_ax, buf[0], buf[1]);
		UINT8_TO_INT16(*p_ay, buf[2], buf[3]);
		UINT8_TO_INT16(*p_az, buf[4], buf[5]);
		UINT8_TO_INT16(*p_t, buf[6], buf[7]);
		UINT8_TO_INT16(*p_gx, buf[8], buf[9]);
		UINT8_TO_INT16(*p_gy, buf[10], buf[11]);
		UINT8_TO_INT16(*p_gz, buf[12], buf[13]);
	}

	return r;
}
