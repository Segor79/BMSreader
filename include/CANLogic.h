#pragma once
#include <EasyPinD.h>
#include <CANLibrary.h>
#include "BMS_low_level_abstraction.h"



extern CAN_HandleTypeDef hcan;

namespace CANLib
{
	void HAL_CAN_Send(can_object_id_t id, uint8_t *data, uint8_t length);

	EasyPinD can_rs(GPIOA, {GPIO_PIN_15, GPIO_MODE_OUTPUT_OD, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}, GPIO_PIN_SET);




	//*********************************************************************
	// CAN Library settings
	//*********************************************************************

	/// @brief Number of CANObjects in CANManager
	static constexpr uint8_t CFG_CANObjectsCount = 25;

	/// @brief The size of CANManager's internal CAN frame buffer
	static constexpr uint8_t CFG_CANFrameBufferSize = 16;

	//*********************************************************************
	// CAN Manager & CAN Object configuration
	//*********************************************************************
	CANManager<CFG_CANObjectsCount, CFG_CANFrameBufferSize> can_manager(&HAL_CAN_Send);

	// ******************** common blocks ********************
	// 0x0040	BlockInfo
	// request | timer:15000
	// byte	1 + 7	{ type[0] data[1..7] }
	// Основная информация о блоке. См. "Системные параметры".
	CANObject<uint8_t, 7> obj_block_info(0x0040);

	// 0x0041	BlockHealth
	// request | event
	// byte	1 + 7	{ type[0] data[1..7] }
	// Информация о здоровье блока. См. "Системные параметры".
	CANObject<uint8_t, 7> obj_block_health(0x0041);

	// 0x0042	BlockCfg
	// request
	// byte	1 + 1 + X	{ type[0] param[1] data[2..7] }
	// Чтение и запись настроек блока. См. "Системные параметры".
	CANObject<uint8_t, 7> obj_block_features(0x0042);

	// 0x0043	BlockError
	// request | event
	// byte	1 + X	{ type[0] data[1..7] }
	// Ошибки блока. См. "Системные параметры".
	CANObject<uint8_t, 7> obj_block_error(0x0043);

	// ******************** specific blocks ********************

	// 0x0044	HighVoltage
	// request | timer:1000
	// uint16_t	100мВ	1 + 2	{ type[0] data[1..2] }
	// Общее напряжение АКБ
	CANObject<uint16_t, 1> obj_high_voltage(0x0044, 1000, CAN_ERROR_DISABLED);

	// 0x0045	HighCurrent
	// request | timer:1000
	// int16_t	100мА	1 + 2	{ type[0] data[1..2] }
	// Общий ток разряда / заряда АКБ
	CANObject<int16_t, 1> obj_high_current(0x0045, 1000, CAN_ERROR_DISABLED);

	// 0x0046	MaxTemperature
	// request | timer:5000 | event
	// int8_t	°C	1 + 1	{ type[0] data[1] }
	// Максимально зафиксированная температура.
	CANObject<int8_t, 1> obj_max_temperature(0x0046, 5000, 300);

	// 0x0047	LowVoltageMinMaxDelta
	// request | timer:5000 | event
	// uint16_t	мВ	1 + 6	{ type[0] v1[1..2] v2[3..4] v3[5..6] }
	// Напряжение на банках: Минимальное, Максимальное, Дельта.
	CANObject<uint16_t, 3> obj_low_voltage_min_max_delta(0x0047, 5000, 300);

	// 0x0048	Temperature1
	// request
	// int8_t	°C	1 + 7	{ type[0] t1[1] t2[2] t3[3] t4[4] t5[5] t6[6] t7[7] }
	// Температура: MOS, Balancer, Temp1, Temp2, Temp3, Temp4, Temp5.
	CANObject<int8_t, 7> obj_temperature_1(0x0048);

	// 0x0049	Temperature2
	// request
	// int8_t	°C	1 + 7	{ type[0] t1[1] t2[2] t3[3] t4[4] t5[5] t6[6] t7[7] }
	// Температура: Temp6, Temp7, Temp8, Temp9, Temp10, Temp11, Temp12.
	CANObject<int8_t, 7> obj_temperature_2(0x0049);

	// 0x004A	Temperature3
	// request
	// int8_t	°C	1 + 7	{ type[0] t1[1] t2[2] t3[3] t4[4] t5[5] t6[6] t7[7] }
	// Температура: Temp13, Temp14, Temp15, Temp16, Temp17, Temp18, Temp19.
	CANObject<int8_t, 7> obj_temperature_3(0x004A);

	// 0x004B	LowVoltage1-3
	// request
	// uint16_t	мВ	1 + 6	{ type[0] v1[1..2] v2[3..4] v3[5..6] }
	// Напряжение на банках: 1, 2, 3.
	CANObject<uint16_t, 3> obj_low_voltage_1_3(0x004B);

	// 0x004C	LowVoltage4-6
	// request
	// uint16_t	мВ	1 + 6	{ type[0] v1[1..2] v2[3..4] v3[5..6] }
	// Напряжение на банках: 4, 5, 6.
	CANObject<uint16_t, 3> obj_low_voltage_4_6(0x004C);

	// 0x004D	LowVoltage7-9
	//  request
	//  uint16_t	мВ	1 + 6	{ type[0] v1[1..2] v2[3..4] v3[5..6] }
	//  Напряжение на банках: 7, 8, 9.
	CANObject<uint16_t, 3> obj_low_voltage_7_9(0x004D);

	// 0x004E	LowVoltage10-12
	// request
	// uint16_t	мВ	1 + 6	{ type[0] v1[1..2] v2[3..4] v3[5..6] }
	// Напряжение на банках: 10, 11, 12.
	CANObject<uint16_t, 3> obj_low_voltage_10_12(0x004E);

	// 0x004F	LowVoltage13-15
	// request
	// uint16_t	мВ	1 + 6	{ type[0] v1[1..2] v2[3..4] v3[5..6] }
	// Напряжение на банках: 13, 14, 15.
	CANObject<uint16_t, 3> obj_low_voltage_13_15(0x004F);

	// 0x0050	LowVoltage16-18
	// request
	// uint16_t	мВ	1 + 6	{ type[0] v1[1..2] v2[3..4] v3[5..6] }
	// Напряжение на банках: 16, 17, 18.
	CANObject<uint16_t, 3> obj_low_voltage_16_18(0x0050);

	// 0x0051	LowVoltage19-21
	// request
	// uint16_t	мВ	1 + 6	{ type[0] v1[1..2] v2[3..4] v3[5..6] }
	// Напряжение на банках: 19, 20, 21.
	CANObject<uint16_t, 3> obj_low_voltage_19_21(0x0051);

	// 0x0052	LowVoltage22-24
	// request
	// uint16_t	мВ	1 + 6	{ type[0] v1[1..2] v2[3..4] v3[5..6] }
	// Напряжение на банках: 22, 23, 24.
	CANObject<uint16_t, 3> obj_low_voltage_22_24(0x0052);

	// 0x0053	LowVoltage25-27
	// request
	// uint16_t	мВ	1 + 2+2+2	{ type[0] v1[1..2] v2[3..4] v3[5..6] }
	// Напряжение на банках: 25, 26, 27.
	CANObject<uint16_t, 3> obj_low_voltage_25_27(0x0053);

	// 0x0054	LowVoltage28-30
	// request
	// uint16_t	мВ	1 + 2+2+2	{ type[0] v1[1..2] v2[3..4] v3[5..6] }
	// Напряжение на банках: 28, 29, 30.
	CANObject<uint16_t, 3> obj_low_voltage_28_30(0x0054);

	// 0x0055	LowVoltage31-33
	// request
	// uint16_t	мВ	1 + 2+2+2	{ type[0] v1[1..2] v2[3..4] v3[5..6] }
	// Напряжение на банках: 31, 32, 33.
	CANObject<uint16_t, 3> obj_low_voltage_31_33(0x0055);

	// 0x0056	BatteryPercent
	// request | timer:10000
	// uint8_t	%	1 + 1	{ type[0] val[1] }
	//	<30: WARN, <15: CRIT, else: NORMAL
	// Уровень заряда АКБ, проценты.
	CANObject<uint8_t, 1> obj_battery_percent(0x0056, 10000);

	// 0x0057	BatteryPower
	// request | timer:250
	// int16_t	Вт	1 + 2	{ type[0] w[1..2] }
	// all: NORMAL
	// Общая мощность потребления / зарядки.
	CANObject<int16_t, 1> obj_battery_power(0x0057, 250);

	// 0x0058	BatteryState
	// request | event
	// int8_t	bitmask	1 + 1	{ type[0] val[1] }
	// Состояние АКБ ( зарядка, разрядка, ... )
	CANObject<int8_t, 1> obj_battery_state(0x0058);


	void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
	{
		CAN_RxHeaderTypeDef RxHeader = {0};
		uint8_t RxData[8] = {0};
		
		if( HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK )
		{
			CANLib::can_manager.IncomingCANFrame(RxHeader.StdId, RxData, RxHeader.DLC);
		}
		
		return;
	}

	void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
	{
		Leds::obj.SetOn(Leds::LED_RED, 100);
		
		DEBUG_LOG_TOPIC("CAN", "RX error event, code: 0x%08lX\n", HAL_CAN_GetError(hcan));
		
		return;
	}

	void HAL_CAN_Send(can_object_id_t id, uint8_t *data, uint8_t length)
	{
		CAN_TxHeaderTypeDef TxHeader = {0};
		uint8_t TxData[8] = {0};
		uint32_t TxMailbox = 0;
		
		TxHeader.StdId = id;
		TxHeader.ExtId = 0;
		TxHeader.RTR  = CAN_RTR_DATA;
		TxHeader.IDE = CAN_ID_STD;
		TxHeader.DLC = length;
		TxHeader.TransmitGlobalTime = DISABLE;
		memcpy(TxData, data, length);
		
		while( HAL_CAN_GetTxMailboxesFreeLevel(&hcan) == 0 )
		{
			Leds::obj.SetOn(Leds::LED_RED);
		}
		Leds::obj.SetOff(Leds::LED_RED);
		
		if( HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK )
		{
			Leds::obj.SetOn(Leds::LED_RED, 100);

			DEBUG_LOG_TOPIC("CAN", "TX error event, code: 0x%08lX\n", HAL_CAN_GetError(&hcan));
		}
		
		return;
	}







	void HardwareSetup()
	{
		can_rs.Init();
		
		HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_ERROR | CAN_IT_BUSOFF | CAN_IT_LAST_ERROR_CODE);
		HAL_CAN_Start(&hcan);
	}
	
	inline void Setup()
	{
		HardwareSetup();
		
		// system blocks
		set_block_info_params(obj_block_info);
		set_block_health_params(obj_block_health);
		set_block_features_params(obj_block_features);
		set_block_error_params(obj_block_error);

		// common blocks
		can_manager.RegisterObject(obj_block_info);
		can_manager.RegisterObject(obj_block_health);
		can_manager.RegisterObject(obj_block_features);
		can_manager.RegisterObject(obj_block_error);

		// specific blocks
		can_manager.RegisterObject(obj_high_voltage);
		can_manager.RegisterObject(obj_high_current);
		can_manager.RegisterObject(obj_max_temperature);
		can_manager.RegisterObject(obj_low_voltage_min_max_delta);
		can_manager.RegisterObject(obj_temperature_1);
		can_manager.RegisterObject(obj_temperature_2);
		can_manager.RegisterObject(obj_temperature_3);
		can_manager.RegisterObject(obj_low_voltage_1_3);

		can_manager.RegisterObject(obj_low_voltage_4_6);
		can_manager.RegisterObject(obj_low_voltage_7_9);
		can_manager.RegisterObject(obj_low_voltage_10_12);
		can_manager.RegisterObject(obj_low_voltage_13_15);
		can_manager.RegisterObject(obj_low_voltage_16_18);
		can_manager.RegisterObject(obj_low_voltage_19_21);
		can_manager.RegisterObject(obj_low_voltage_22_24);
		can_manager.RegisterObject(obj_low_voltage_25_27);
		can_manager.RegisterObject(obj_low_voltage_28_30);
		can_manager.RegisterObject(obj_low_voltage_31_33);
		can_manager.RegisterObject(obj_battery_percent);
		can_manager.RegisterObject(obj_battery_power);
		
		// Set versions data to block_info.
		obj_block_info.SetValue(0, (About::board_type << 3 | About::board_ver), CAN_TIMER_TYPE_NORMAL);
		obj_block_info.SetValue(1, (About::soft_ver << 2 | About::can_ver), CAN_TIMER_TYPE_NORMAL);
		
		return;
	}
	
	inline void Loop(uint32_t &current_time)
	{
		can_manager.Process(current_time);
		
		// Set uptime to block_info.
		static uint32_t iter = 0;
		if(current_time - iter > 1000)
		{
			iter = current_time;

			uint8_t *data = (uint8_t *)&current_time;
			obj_block_info.SetValue(2, data[0], CAN_TIMER_TYPE_NORMAL);
			obj_block_info.SetValue(3, data[1], CAN_TIMER_TYPE_NORMAL);
			obj_block_info.SetValue(4, data[2], CAN_TIMER_TYPE_NORMAL);
			obj_block_info.SetValue(5, data[3], CAN_TIMER_TYPE_NORMAL);
		}
		
		current_time = HAL_GetTick();
		
		return;
	}

	void UpdateMaxTemperature()
	{
		// 0x0046	MaxTemperature
		// request | timer:5000 | event
		// int8_t	°C	1 + 1	{ type[0] data[1] }
		// Ограничения: <60:WARN, <80: CRIT
		// Максимально зафиксированная температура.
		int8_t max_temp = 0;
		int8_t curr_temp = 0;

		for (uint8_t i = 0; i < 7; i++)
		{
			curr_temp = obj_temperature_1.GetValue(i);
			if (curr_temp > max_temp)
				max_temp = curr_temp;
		}
		for (uint8_t i = 0; i < 7; i++)
		{
			curr_temp = obj_temperature_2.GetValue(i);
			if (curr_temp > max_temp)
				max_temp = curr_temp;
		}
		for (uint8_t i = 0; i < 7; i++)
		{
			curr_temp = obj_temperature_3.GetValue(i);
			if (curr_temp > max_temp)
				max_temp = curr_temp;
		}

		timer_type_t timer_type = CAN_TIMER_TYPE_NORMAL;
		event_type_t event_type = CAN_EVENT_TYPE_NONE;

		if (max_temp >= 60 && max_temp < 80)
		{
			timer_type = CAN_TIMER_TYPE_WARNING;
		}
		else if (max_temp >= 80)
		{
			timer_type = CAN_TIMER_TYPE_CRITICAL;
		}

		// TODO: надо ещё обсудить по event_type и его присваивать
		obj_max_temperature.SetValue(0, max_temp, timer_type, event_type);
	}

	void UpdateCANObjects_BMS(uint8_t bms_raw_packet_data[BMS_BOARD_PACKET_SIZE])
	{

		uint32_t *BMS_header = (uint32_t *)bms_raw_packet_data;
		if (*BMS_header != 0xFFAA55AA)
		{
			DEBUG_LOG_TOPIC("BMS", "Header error! Expected: 0x%08X, presented: 0x%08X\n", 0xFFAA55AA, *BMS_header);
			
			return;
		}
		
		uint16_t crc = 0x0000;
		for(uint8_t i = 4; i < 138; ++i)
		{
			crc += bms_raw_packet_data[i];
		}
		if( ((crc >> 8) & 0xFF) != bms_raw_packet_data[138] || (crc & 0xFF) != bms_raw_packet_data[139])
		{
			//DEBUG_LOG("ERROR: BMS CRC error! Expected: 0x%04X, presented: 0x%04X", bms_raw_data_crc(bms_raw_packet_data), get_bms_raw_data_crc(bms_raw_packet_data));
			DEBUG_LOG_TOPIC("BMS", "CRC error!");
			
			return;
		}
		

		// reverse_array(bms_raw_packet_data, BMS_BOARD_PACKET_SIZE);
		// packet_structure_reversed_t *reversed_bms_packet = (packet_structure_reversed_t *)bms_raw_packet_data;

		packet_structure_t *bms_packet_struct = (packet_structure_t *)bms_raw_packet_data;

		// 0x0044	HighVoltage
		// request | timer:1000
		// uint16_t	100мВ	1 + 2	{ type[0] data[1..2] }
		// all: NORMAL
		// Общее напряжение АКБ
		swap_endian(bms_packet_struct->voltage);
		obj_high_voltage.SetValue(0, bms_packet_struct->voltage, CAN_TIMER_TYPE_NORMAL); // BMS reports voltage in 10 mV/bit, we need 100 mV/bit

		// 0x0045	HighCurrent
		// request | timer:1000
		// int16_t	100мА	1 + 2	{ type[0] data[1..2] }
		// Ограничения: all: NORMAL
		// Общий ток разряда / заряда АКБ
		swap_endian(bms_packet_struct->current);
		obj_high_current.SetValue(0, bms_packet_struct->current, CAN_TIMER_TYPE_NORMAL); // 100mA/bit

		// 0x0046	MaxTemperature
		// we will set it at the end of the update
		// obj_max_temperature.SetValue(0, (int8_t)0, CAN_TIMER_TYPE_NORMAL);

		// 0x0047	LowVoltageMinMaxDelta
		// request | timer:5000 | event
		// uint16_t	мВ	1 + 6	{ type[0] v1[1..2] v2[3..4] v3[5..6] }
		// Ограничения: Согластно тех.паспорту банок АКБ
		// Напряжение на банках: Минимальное, Максимальное, Дельта.
		swap_endian(bms_packet_struct->vmin_voltage);
		swap_endian(bms_packet_struct->vmax_voltage);
		
		timer_type_t timer_type = CAN_TIMER_TYPE_NORMAL;
		event_type_t event_type = CAN_EVENT_TYPE_NONE;
		
		if(bms_packet_struct->vmin_voltage >= 2700 && bms_packet_struct->vmin_voltage <= 3000)
		{
			timer_type = CAN_TIMER_TYPE_WARNING;
		}
		else if(bms_packet_struct->vmin_voltage < 2700 || bms_packet_struct->vmax_voltage > 4200)
		{
			timer_type = CAN_TIMER_TYPE_CRITICAL;
		}
		
		obj_low_voltage_min_max_delta.SetValue(0, bms_packet_struct->vmin_voltage, timer_type, event_type);
		obj_low_voltage_min_max_delta.SetValue(1, bms_packet_struct->vmax_voltage, timer_type, event_type);
		obj_low_voltage_min_max_delta.SetValue(2, (bms_packet_struct->vmax_voltage - bms_packet_struct->vmin_voltage), CAN_TIMER_TYPE_NONE, CAN_EVENT_TYPE_NONE);

		// 0x0048	Temperature1
		// request
		// int8_t	°C	1 + 7	{ type[0] t1[1] t2[2] t3[3] t4[4] t5[5] t6[6] t7[7] }
		// Температура: MOS, Balancer, Temp1, Temp2, Temp3, Temp4, Temp5.
		swap_endian(bms_packet_struct->temperature_mosfet);
		obj_temperature_1.SetValue(0, bms_packet_struct->temperature_mosfet);

		swap_endian(bms_packet_struct->temperature_balancer);
		obj_temperature_1.SetValue(1, bms_packet_struct->temperature_balancer);

		for (uint8_t i = 0; i < 4; i++)
		{
			swap_endian(bms_packet_struct->temperature_sensors[i]);
			obj_temperature_1.SetValue(i + 2, bms_packet_struct->temperature_sensors[i]);
		}

		uint8_t cells_voltage_index = 0;
		// 0x004B	LowVoltage1-3
		// request
		// uint16_t	мВ	1 + 6	{ type[0] v1[1..2] v2[3..4] v3[5..6] }
		// Напряжение на банках: 1, 2, 3.
		for (uint8_t i = 0; i < 3; i++)
		{
			if (cells_voltage_index >= BMS_BATTERY_NUMBER_OF_CELLS)
				break;

			swap_endian(bms_packet_struct->cells_voltage[cells_voltage_index]);
			obj_low_voltage_1_3.SetValue(i, bms_packet_struct->cells_voltage[cells_voltage_index++]);
		}

		// 0x004C	LowVoltage4-6
		// request
		// uint16_t	мВ	1 + 6	{ type[0] v1[1..2] v2[3..4] v3[5..6] }
		// Напряжение на банках: 4, 5, 6.
		for (uint8_t i = 0; i < 3; i++)
		{
			if (cells_voltage_index >= BMS_BATTERY_NUMBER_OF_CELLS)
				break;

			swap_endian(bms_packet_struct->cells_voltage[cells_voltage_index]);
			obj_low_voltage_4_6.SetValue(i, bms_packet_struct->cells_voltage[cells_voltage_index++]);
		}

		// 0x004D	LowVoltage7-9
		//  request
		//  uint16_t	мВ	1 + 6	{ type[0] v1[1..2] v2[3..4] v3[5..6] }
		//  Напряжение на банках: 7, 8, 9.
		for (uint8_t i = 0; i < 3; i++)
		{
			if (cells_voltage_index >= BMS_BATTERY_NUMBER_OF_CELLS)
				break;

			swap_endian(bms_packet_struct->cells_voltage[cells_voltage_index]);
			obj_low_voltage_7_9.SetValue(i, bms_packet_struct->cells_voltage[cells_voltage_index++]);
		}

		// 0x004E	LowVoltage10-12
		// request
		// uint16_t	мВ	1 + 6	{ type[0] v1[1..2] v2[3..4] v3[5..6] }
		// Напряжение на банках: 10, 11, 12.
		for (uint8_t i = 0; i < 3; i++)
		{
			if (cells_voltage_index >= BMS_BATTERY_NUMBER_OF_CELLS)
				break;

			swap_endian(bms_packet_struct->cells_voltage[cells_voltage_index]);
			obj_low_voltage_10_12.SetValue(i, bms_packet_struct->cells_voltage[cells_voltage_index++]);
		}

		// 0x004F	LowVoltage13-15
		// request
		// uint16_t	мВ	1 + 6	{ type[0] v1[1..2] v2[3..4] v3[5..6] }
		// Напряжение на банках: 13, 14, 15.
		for (uint8_t i = 0; i < 3; i++)
		{
			if (cells_voltage_index >= BMS_BATTERY_NUMBER_OF_CELLS)
				break;

			swap_endian(bms_packet_struct->cells_voltage[cells_voltage_index]);
			obj_low_voltage_13_15.SetValue(i, bms_packet_struct->cells_voltage[cells_voltage_index++]);
		}

		// 0x0050	LowVoltage16-18
		// request
		// uint16_t	мВ	1 + 6	{ type[0] v1[1..2] v2[3..4] v3[5..6] }
		// Напряжение на банках: 16, 17, 18.
		for (uint8_t i = 0; i < 3; i++)
		{
			if (cells_voltage_index >= BMS_BATTERY_NUMBER_OF_CELLS)
				break;

			swap_endian(bms_packet_struct->cells_voltage[cells_voltage_index]);
			obj_low_voltage_16_18.SetValue(i, bms_packet_struct->cells_voltage[cells_voltage_index++]);
		}

		// 0x0051	LowVoltage19-21
		// request
		// uint16_t	мВ	1 + 6	{ type[0] v1[1..2] v2[3..4] v3[5..6] }
		// Напряжение на банках: 19, 20, 21.
		for (uint8_t i = 0; i < 3; i++)
		{
			if (cells_voltage_index >= BMS_BATTERY_NUMBER_OF_CELLS)
				break;

			swap_endian(bms_packet_struct->cells_voltage[cells_voltage_index]);
			obj_low_voltage_19_21.SetValue(i, bms_packet_struct->cells_voltage[cells_voltage_index++]);
		}

		// 0x0052	LowVoltage22-24
		// request
		// uint16_t	мВ	1 + 6	{ type[0] v1[1..2] v2[3..4] v3[5..6] }
		// Напряжение на банках: 22, 23, 24.
		for (uint8_t i = 0; i < 3; i++)
		{
			if (cells_voltage_index >= BMS_BATTERY_NUMBER_OF_CELLS)
				break;

			swap_endian(bms_packet_struct->cells_voltage[cells_voltage_index]);
			obj_low_voltage_22_24.SetValue(i, bms_packet_struct->cells_voltage[cells_voltage_index++]);
		}

		for (uint8_t i = 0; i < 3; i++)
		{
			if (cells_voltage_index >= BMS_BATTERY_NUMBER_OF_CELLS)
				break;

			swap_endian(bms_packet_struct->cells_voltage[cells_voltage_index]);
			obj_low_voltage_25_27.SetValue(i, bms_packet_struct->cells_voltage[cells_voltage_index++]);
		}

		for (uint8_t i = 0; i < 3; i++)
		{
			if (cells_voltage_index >= BMS_BATTERY_NUMBER_OF_CELLS)
				break;

			swap_endian(bms_packet_struct->cells_voltage[cells_voltage_index]);
			obj_low_voltage_28_30.SetValue(i, bms_packet_struct->cells_voltage[cells_voltage_index++]);
		}

		for (uint8_t i = 0; i < 3; i++)
		{
			if (cells_voltage_index >= BMS_BATTERY_NUMBER_OF_CELLS)
				break;

			swap_endian(bms_packet_struct->cells_voltage[cells_voltage_index]);
			obj_low_voltage_31_33.SetValue(i, bms_packet_struct->cells_voltage[cells_voltage_index++]);
		}
		
		// 0x0056	BatteryPercent
		// request | timer:10000
		// uint8_t	%	1 + 1	{ type[0] val[1] }
		//	<30: WARN, <15: CRIT, else: NORMAL
		// Уровень заряда АКБ, проценты.
		timer_type_t timer_type1 = CAN_TIMER_TYPE_NORMAL;
		if (bms_packet_struct->percent < 15)
		{
			timer_type1 = CAN_TIMER_TYPE_CRITICAL;
		}
		else if (bms_packet_struct->percent < 30)
		{
			timer_type1 = CAN_TIMER_TYPE_WARNING;
		}
		obj_battery_percent.SetValue(0, bms_packet_struct->percent, timer_type1);

		// 0x0057	BatteryPower
		// request | timer:1000
		// int16_t	Вт	1 + 2	{ type[0] w[1..2] }
		// all: NORMAL
		// Общая мощность потребления / зарядки.
		// BMS data endian is already swapped
		//obj_battery_power.SetValue(0, bms_packet_struct->voltage * bms_packet_struct->current / 100000, CAN_TIMER_TYPE_NORMAL);
		swap_endian(bms_packet_struct->power);
		obj_battery_power.SetValue(0, bms_packet_struct->power, CAN_TIMER_TYPE_NORMAL);

		// 0x0046	MaxTemperature
		// request | timer:5000 | event
		// int8_t	°C	1 + 1	{ type[0] data[1] }
		// Ограничения: <60:WARN, <80: CRIT
		// Максимально зафиксированная температура.
		UpdateMaxTemperature();
	}

	void UpdateCANObjects_ExternalTemperature(int8_t *temperature_data, uint8_t data_count)
	{
		if (temperature_data == nullptr)
			return;

		// 0x0046	MaxTemperature
		// we will set it at the end of the update
		// obj_max_temperature.SetValue(0, (int8_t)0, CAN_TIMER_TYPE_NORMAL);

		uint8_t data_index = 0;

		// 0x0048	Temperature1
		// request
		// int8_t	°C	1 + 7	{ type[0] t1[1] t2[2] t3[3] t4[4] t5[5] t6[6] t7[7] }
		// Температура: MOS, Balancer, Temp1, Temp2, Temp3, Temp4, Temp5.

		if (data_index >= data_count)
			return;
		obj_temperature_1.SetValue(7, temperature_data[data_index++]);

		// 0x0049	Temperature2
		// request
		// int8_t	°C	1 + 7	{ type[0] t1[1] t2[2] t3[3] t4[4] t5[5] t6[6] t7[7] }
		// Температура: Temp6, Temp7, Temp8, Temp9, Temp10, Temp11, Temp12.
		for (uint8_t i = 0; i < 7; i++)
		{
			if (data_index >= data_count)
				return;
			obj_temperature_2.SetValue(i, temperature_data[data_index++]);
		}

		// 0x004A	Temperature3
		// request
		// int8_t	°C	1 + 7	{ type[0] t1[1] t2[2] t3[3] t4[4] t5[5] t6[6] t7[7] }
		// Температура: Temp13, Temp14, Temp15, Temp16, Temp17, Temp18, Temp19.
		for (uint8_t i = 0; i < 7; i++)
		{
			if (data_index >= data_count)
				return;
			obj_temperature_3.SetValue(i, temperature_data[data_index++]);
		}

		// 0x0046	MaxTemperature
		// request | timer:5000 | event
		// int8_t	°C	1 + 1	{ type[0] data[1] }
		// Ограничения: <60:WARN, <80: CRIT
		// Максимально зафиксированная температура.
		UpdateMaxTemperature();
	}
}
