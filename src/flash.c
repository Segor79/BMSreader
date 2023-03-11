#include "stm32f1xx_hal.h"
#include "flash.h"
#include <string.h>

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////// ������ � ������ //////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  #define ADDR_Flash ADDR_FLASH_PAGE_64
	uint32_t address = ADDR_Flash; // ������ � ������ ��������

	
extern 	uint16_t write_data16[];
extern	uint16_t read_data16[];	
	
	uint8_t Erase_flash(uint32_t Erase_address){
  static FLASH_EraseInitTypeDef EraseInitStruct; // ��������� ��� ������� �����

  EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES; // ������������ �������, FLASH_TYPEERASE_MASSERASE - ������� ����� �����
  EraseInitStruct.PageAddress = ADDR_Flash; // �����  ��������
  EraseInitStruct.NbPages = 1;                       // ���-�� ������� ��� ��������
  //EraseInitStruct.Banks = FLASH_BANK_1; // FLASH_BANK_2 - ���� �2, FLASH_BANK_BOTH - ��� �����

  uint32_t page_error = 0; // ����������, � ������� ��������� ����� �������� ��� ��������� ��������

  ////////////////////////////// ������� ///////////////////////////////////

  HAL_FLASH_Unlock(); // �������������� ����

  if(HAL_FLASHEx_Erase(&EraseInitStruct, &page_error) != HAL_OK)
  {
		HAL_FLASH_Lock(); // ������������� ����
		return 0;
  }
  HAL_FLASH_Lock(); // ������������� ����
	return 1;
}
  ///////////////////////// ����� ������� //////////////////////////////

  // 0x00U - No error
  // 0x01U - Programming error
  // 0x02U - Write protection error
  // 0x04U - Option validity error
// ���� ���������� 32-� (FLASH_TYPEPROGRAM_WORD) ������ �����, �� �������� ����� �� ������, � ���� 64-� (FLASH_TYPEPROGRAM_DOUBLEWORD) ������, �� �� 8. 
// ���� � ���������� �������� �������� � ��� �������� ��� ���-��, �� ����� ��������� �����.
  ////////////////////////////// ������ ����� 16 bits ///////////////////////////////////
	uint8_t Write_flash_16b(uint8_t len){
  HAL_FLASH_Unlock(); // �������������� ����

  uint32_t address = ADDR_Flash; // ������ � ������ �������� 

  for(uint8_t i = 0; i < len; i++)
  {
	  if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address, write_data16[i]) != HAL_OK)
	  {
			HAL_FLASH_Lock(); // ������������� ����
			return 0;
	  }

	  address = address + 2;
  }
  HAL_FLASH_Lock(); // ������������� ����
	return 1;
}
  /////////////////////// ����� ������ ����� 16 bits ///////////////////////////


  ////////////////////////////// ������ ����� 16 bits ///////////////////////////////////
void Read_flash_16b(uint8_t len){
  address = ADDR_Flash;

  for(uint16_t i = 0; i < len; i++)
  {
	  read_data16[i] = *(uint16_t*)address; // ������ ����� �� ������
	  address = address + 2;
  }
}
  //////////////////////// ����� ������ ����� 16 bits ///////////////////////////////////


  ////////////////////////////// ������ ������ 8 bits 	������ ���� �������
	uint32_t Write_flash_8b_str(uint8_t* data, uint8_t len){
  HAL_FLASH_Unlock(); // �������������� ����

  address = ADDR_Flash + 4; // ������� ����� 

  uint16_t data16 = 0, index0 = 0, index1 = 1;

  if(len % 2 != 0) // �������� ���-�� �������� � ������� �� ��������
  {
		return 0;
  }

  for(uint16_t i = 0; i < len / 2; i++)
  {
	  data16 = ((uint16_t)data[index1] << 8) | data[index0];
	  index0 = index0 + 2;
	  index1 = index1 + 2;

	  if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address, data16) != HAL_OK)
	  {
		  uint32_t er = HAL_FLASH_GetError();
			return er;
	  }

	  address = address + 2;
  }

  HAL_FLASH_Lock(); // ������������� ����

return 1;
}
  /////////////////////// ����� ������ ������ 8 bits //////////////////////////


  ////////////////////////////// ������ ������ 8 bits ///////////////////////////////////
void Read_flash_8b_str(void){
  address = ADDR_Flash + 4;
  char buf[64] = {0,};
	
  for(uint16_t i = 0; i < 8; i++)
  {
	  buf[i] = *(uint32_t*)address++;
  }
}
  //////////////////////// ����� ������ ������ 8 bits ///////////////////////////////////


  //////////////////////// ��������� ���������������� ���� - User Data  /////////////////////////////

//  uint32_t user_bit = HAL_FLASHEx_OBGetUserData(OB_DATA_ADDRESS_DATA0);
//  snprintf(str, 64, "User_bit_0: %lu\n", user_bit);
//  HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), 100);

//  user_bit = HAL_FLASHEx_OBGetUserData(OB_DATA_ADDRESS_DATA1);
//  snprintf(str, 64, "User_bit_1: %lu\n", user_bit);
//  HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), 100);

  //////////////////////// ����� ������ /////////////////////////////
