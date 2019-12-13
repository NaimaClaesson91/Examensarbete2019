#ifndef _RN2483_H_
#define _RN2483_H_

#define DEV_EUI_LENGTH 20

typedef struct
{
  uint8_t humHigh;
  uint8_t humLow;
  uint8_t tempHigh;
  uint8_t tempLow;
  uint8_t battStatusHigh;
  uint8_t battStatusLow;

}loraData_t;



void rn2483_set_freq(void);

void rn2483_join_otaa(char * dev_eui, char * app_eui, char * app_key);

void rn2483_transmit_unconfirmed_package(loraData_t * lora_data);

void rn2483_set_ch_freq(int channel, char * frequency);

void rn2483_set_ch_data_range(int channel, int min_range, int max_range);

void rn2483_set_ch_status_on(int channel);

void rn2483_set_output_power(int power);



void rn2483_set_device_eui(char * dev_eui);

void rn2483_set_app_eui(char * app_eui);

void rn2483_set_app_key(char * app_key);

void rn2483_set_adaptive_data_rate_on(void);

void rn2483_set_data_rate(int rate);

void rn2483_set_sync_word(char * word);

void rn2483_join(char * mode);



void rn2483_wait_for_ok(void);

void rn2483_wait_for_response(void);

void rn2483_sleep(char * sleep_time);

void rn2483_auto_baud(void);

void rn2483_get_hweui(char * hweui);

void rn2483_set_ch_duty_cycle(int channel, int duty_cycle);


#endif // _RN2483_H_