#include <BMSManager.h>

void BMSManager::SetModel(uint8_t idx, BMSDeviceInterface &device)
{
	if(idx >= _max_dev) return;
	if(device.IsInitiated() == true) return;
	
	device.PrepareInit(this, idx);
	device.Init();
	_device[idx] = &device;
	
	return;
}

void BMSManager::Tick(uint32_t &time)
{
	for(uint8_t idx = 0; idx < _max_dev; ++idx)
	{
		if(_error[idx].is_error == true)
		{
			_error[idx].is_error = false;
			
			_callback_error(idx, _error[idx].code);
		}
		
		_device[idx]->Tick(time);
	}
	
	return;
}

void BMSManager::DataRx(uint8_t idx, const uint8_t *raw, const uint8_t length)
{
	if(idx >= _max_dev) return;
	if(_device[idx] == nullptr) return;

	_error[idx].code = _device[idx]->DataRx(raw, length);
	if(_error[idx].code != 0)
	{
		_error[idx].is_error = true;
	}
	
	return;
}

void BMSManager::DataTx(uint8_t idx, const uint8_t *raw, const uint8_t length)
{
	_callback_tx(idx, raw, length);
	
	return;
}
