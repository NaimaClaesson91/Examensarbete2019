#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>

#include "rn2483.h"
#include "uart.h"
#include "snooze.h"
#include "gpio.h"


void rn2483_reset(int band){
    char cmd[40];
    sprintf(cmd, "mac reset %d", band);
    uart_print(cmd);
}

void rn2483_auto_baud(void){

    uart_tx_disable();
    DDRD |= (1 << DDD1);
    PORTD &= ~(1 << PORTD1);

    // Time break = 13 / baudrate
    _delay_us(1350);
    PORTD |= (1 << PORTD1);
    uart_tx_enable();
    uart_print_char(0x55);
}


void rn2483_get_hweui(char * hweui){

    uart_print("sys get hweui");
    uart_getstring(hweui, DEV_EUI_LENGTH);
    size_t length = strlen(hweui);
    hweui[length-2] = '\0'; // remove \r\n
}


void rn2483_set_freq(void){

    // 1% duty_cycle / 8 channels = 0.125
    // ((100 / 0.125) - 1 = 799))
    int duty_cycle = 799;

    char frequencies[8][10] = {"867100000", "867300000", "867500000", "867700000", "867900000"};
    rn2483_reset(868);
    rn2483_wait_for_ok();

    for(int channel = 0; channel < 8; channel++){
        rn2483_set_ch_duty_cycle(channel, duty_cycle);
        rn2483_wait_for_ok();

        if(channel > 2){
            rn2483_set_ch_freq(channel, frequencies[channel-3]);
            rn2483_wait_for_ok();
        }

        if(channel == 1){
            rn2483_set_ch_data_range(channel, 0, 6);
        }else{
            rn2483_set_ch_data_range(channel, 0, 5);
        }
        rn2483_wait_for_ok();

        rn2483_set_ch_status_on(channel);
        rn2483_wait_for_ok();
    }

    rn2483_set_output_power(1);
    rn2483_wait_for_ok();
}


void rn2483_join_otaa(char * dev_eui, char * app_eui, char * app_key){
    
    rn2483_set_device_eui(dev_eui);
    rn2483_wait_for_ok();

    rn2483_set_app_eui(app_eui);
    rn2483_wait_for_ok();

    rn2483_set_app_key(app_key);
    rn2483_wait_for_ok();

    rn2483_set_adaptive_data_rate_on();
    rn2483_wait_for_ok();

    rn2483_set_data_rate(5);
    rn2483_wait_for_ok();

    rn2483_set_sync_word("34");
    rn2483_wait_for_ok();

    rn2483_join("otaa");
    rn2483_wait_for_ok();
    rn2483_wait_for_join_response();

    _delay_ms(7000);
}


void rn2483_transmit_unconfirmed_package(loraData_t * lora_data){
    char cmd[100];
    sprintf(cmd, "mac tx uncnf 1 %02X%02X%02X%02X%02X%02X", lora_data->battStatusHigh, lora_data->battStatusLow, lora_data->humHigh, lora_data->humLow, lora_data->tempHigh, lora_data->tempLow);
    uart_print(cmd);
    rn2483_wait_for_ok();
    rn2483_wait_for_tx_response();
    _delay_ms(100);
}


void rn2483_set_ch_duty_cycle(int channel, int duty_cycle){
    char cmd[40];
    sprintf(cmd, "mac set ch dcycle %d %d", channel, duty_cycle);
    uart_print(cmd);
}


void rn2483_set_ch_freq(int channel, char * frequency){
    char cmd[40];
    sprintf(cmd, "mac set ch freq %d %s", channel, frequency);
    uart_print(cmd);
}

void rn2483_wait_for_ok(){
    char response[20];

    do{
        uart_getstring(response, 20);
    }
    while(strncmp(response, "ok", 2));
}


void rn2483_wait_for_tx_response(){
    char response[30];

    do{
        uart_getstring(response, 30);
    }
    while(strncmp(response, "mac_tx", 6));
}


void rn2483_wait_for_join_response(){
    
    char response[30];
    static uint8_t join_attempts = 0;
    uart_getstring(response, 30);

    if(join_attempts >= 10){

        for(int i = 0; i < 5; i++){
            gpio_led_on();
            _delay_ms(1000);
            gpio_led_off();
            _delay_ms(1000);
        }

        rn2483_sleep("4294967295");
        _delay_ms(10);
        snooze_shut_down();
        _delay_ms(100);
        return;     

    }
    else if(strncmp(response, "denied", 6) == 0){
        gpio_led_on();
        _delay_ms(100); //not joined blink
        gpio_led_off();

        _delay_ms(10000);
        rn2483_join("otaa");
        rn2483_wait_for_ok();
        
        join_attempts++;
        rn2483_wait_for_join_response();
        
    }
    else if(strncmp(response, "accepted", 8) == 0){
        for(int i = 0; i < 3; i++){
            gpio_led_on();
            _delay_ms(100); //joined blink
            gpio_led_off();
            _delay_ms(500);
        }

        return;
    }
    
}


void rn2483_set_ch_data_range(int channel, int min_range, int max_range){
    char cmd[40];
    sprintf(cmd, "mac set ch drrange %d %d %d", channel, min_range, max_range);
    uart_print(cmd);
}


void rn2483_set_ch_status_on(int channel){
    char cmd[40];
    sprintf(cmd, "mac set ch status %d on", channel);
    uart_print(cmd);
}


void rn2483_set_output_power(int power){
    char cmd[40];
    sprintf(cmd, "mac set pwridx %d", power);
    uart_print(cmd);
}


void rn2483_set_device_eui(char * dev_eui){
    char cmd[40];
    sprintf(cmd, "mac set deveui %s", dev_eui);
    uart_print(cmd);
}


void rn2483_set_app_eui(char * app_eui){
    char cmd[40];
    sprintf(cmd, "mac set appeui %s", app_eui);
    uart_print(cmd);
}


void rn2483_set_app_key(char * app_key){
    char cmd[40];
    sprintf(cmd, "mac set appkey %s", app_key);
    uart_print(cmd);
}


void rn2483_set_adaptive_data_rate_on(void){
    char cmd[40];
    sprintf(cmd, "mac set adr on");
    uart_print(cmd);
}


void rn2483_set_data_rate(int rate){
    char cmd[40];
    sprintf(cmd, "mac set dr %d", rate);
    uart_print(cmd);
}


void rn2483_set_sync_word(char * word){
    char cmd[40];
    sprintf(cmd, "mac set sync %s", word);
    uart_print(cmd);
}


void rn2483_join(char * mode){
    char cmd[40];
    sprintf(cmd, "mac join %s", mode);
    uart_print(cmd);
}


void rn2483_sleep(char * sleep_time){
    char cmd[40];
    sprintf(cmd, "sys sleep %s", sleep_time);
    uart_print(cmd);
}
