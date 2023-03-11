#ifndef PARAMS_H_
#define PARAMS_H_

#include "stm32f1xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif


struct params_t
        {
            uint32_t header;            // ��������� ������.
            uint16_t voltage_1;         // ���������� �� 1 ������, ��.
            uint16_t voltage_2;         // ���������� �� 2 ������, ��.
            uint16_t voltage_3;         // ���������� �� 3 ������, ��.
            uint16_t voltage_4;         // ���������� �� 4 ������, ��.
            uint16_t voltage_5;         // ���������� �� 5 ������, ��.
            uint16_t voltage_6;         // ���������� �� 6 ������, ��.
            uint16_t voltage_7;         // ���������� �� 7 ������, ��.
            uint16_t voltage_8;         // ���������� �� 8 ������, ��.
            uint16_t voltage_9;         // ���������� �� 9 ������, ��.
            uint16_t voltage_10;        // ���������� �� 10 ������, ��.
            uint16_t voltage_11;        // ���������� �� 11 ������, ��.
            uint16_t voltage_12;        // ���������� �� 12 ������, ��.
            uint16_t voltage_13;        // ���������� �� 13 ������, ��.
            uint16_t voltage_14;        // ���������� �� 14 ������, ��.
            uint16_t voltage_15;        // ���������� �� 15 ������, ��.
            uint16_t voltage_16;        // ���������� �� 16 ������, ��.
            uint16_t voltage_17;        // ���������� �� 17 ������, ��.
            uint16_t voltage_18;        // ���������� �� 18 ������, ��.
            uint16_t voltage_19;        // ���������� �� 19 ������, ��.
            uint16_t voltage_20;        // ���������� �� 20 ������, ��.
            uint16_t voltage_21;        // ���������� �� 21 ������, ��.
            uint16_t voltage_22;        // ���������� �� 22 ������, ��.
            uint16_t voltage_23;        // ���������� �� 23 ������, ��.
            uint16_t voltage_24;        // ���������� �� 24 ������, ��.
            uint16_t voltage_25;        // ���������� �� 25 ������, ��.
            uint16_t voltage_26;        // ���������� �� 26 ������, ��.
            uint16_t voltage_27;        // ���������� �� 27 ������, ��.
            uint16_t voltage_28;        // ���������� �� 28 ������, ��.
            uint16_t voltage_29;        // ���������� �� 29 ������, ��.
            uint16_t voltage_30;        // ���������� �� 30 ������, ��.
            uint16_t voltage_31;        // ���������� �� 31 ������, ��.
            uint16_t voltage_32;        // ���������� �� 32 ������, ��.
            uint16_t voltage_33;        // ���������� �� ���� ���, ��.	
            int32_t current;            // ��� ������� ��� ������, ��.
            uint8_t percent;            // ���������� ������� ���, ��������.
            uint32_t phy_capacity;      // ����������� ������� ���, ��/�.
            uint32_t rem_capacity;      // ���������� ������� ���, ��/�.
            uint32_t cycle_capacity;    // WAT?
            uint32_t uptime;            // ���-�� ������� � ��������, ������.
            int16_t temp_1;             // ����������� ������� 1, �������.
            int16_t temp_2;             // ����������� ������� 2, �������.
            int16_t temp_3;             // ����������� ������� 3, �������.
            int16_t temp_4;             // ����������� ������� 4, �������.
            int16_t temp_5;             // ����������� ������� 5, �������.
            int16_t temp_6;             // ����������� ������� 6, �������.
            uint8_t charge_fet;         // ���� ��������� ����� �������.
            uint8_t dcharge_fet;        // ���� ��������� ����� ��������.
            uint8_t balanced;           // ���� ��������� ������������.
            uint16_t tire_length;       // WAT?
            uint16_t pulses_num;        // WAT?
            uint8_t relay;              // WAT?
            uint32_t power;             // ������� ��������, ��.
            uint8_t vmax_bat;           // ����� ������� � ������������ �����������.
            uint16_t vmax;              // ���������� ������� � ������������ �����������, ��.
            uint8_t vmin_bat;           // ����� ������� � ����������� �����������.
            uint16_t vin;               // ���������� ������� � ����������� �����������, ��.
            uint16_t vmid;              // ������� ���������� �������, ��.
            uint8_t wat_123;            // WAT?
            uint16_t dcharge_fet_lost;  // ������� �� ����������� ��������, �.
            uint16_t dcharge_fet_v;     // ���������� �� ������� ����������� ��������, �.
            uint16_t charge_fet_v;      // ���������� �� ������� ����������� �������, �.
            uint16_t wat_130131;        // WAT?
            uint32_t balance_bits;      // ����� ���������������� �����.
            uint16_t logs;              // WAT?
            uint16_t crc;               // ����������� �����.
        } params;		// 	140 ����
				

typedef struct 
{
    uint16_t ID;            	// ID ������
    uint8_t type;							// ��� ���������
    uint8_t data[7];					// ������ ���������
    uint8_t length;						// ����� ������ + 1(type)
    uint16_t timer_ms;        // �������� �������� ��������� � ms
    uint32_t current_timer;		// ������� �������� ������� 
    uint8_t state;            // ���������
} _params_v;

_params_v BlockInfo = 			{0x0040};
_params_v BlockHealth = 		{0x0041};
_params_v BlockCfg = 			{0x0042};
_params_v BlockError = 		{0x0043};
_params_v HighVoltage = 		{0x0044};
_params_v HighCurrent = 		{0x0045};
_params_v MaxTemperature = {0x0046};
_params_v Temperature1 = 	{0x0047};
_params_v Temperature2 = 	{0x0048};
_params_v Temperature3 = 	{0x0049};
_params_v LowVoltage1_3 = 	{0x004A};
_params_v LowVoltage4_6 = 	{0x004B};
_params_v LowVoltage7_9 = 	{0x004C};
_params_v LowVoltage10_12 ={0x004D};
_params_v LowVoltage13_15 ={0x004E};
_params_v LowVoltage16_18 ={0x004F};
_params_v LowVoltage19_21 ={0x0050};
_params_v LowVoltage22_24 ={0x0051};
_params_v LowVoltageMinMaxDelta ={0x0052};

#ifdef __cplusplus
}
#endif

#endif /* PARAMS_H_ */
