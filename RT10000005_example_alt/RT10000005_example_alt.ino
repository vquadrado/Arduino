#include "esp_gap_ble_api.h"
#include "esp_bt.h"
#include "esp_bt_main.h"


uint8_t array_btmac[6]; //hexa
char ascii_btmac[13]; //12 digitos ascii + '\0' do final de string devido ao uso do sprintf

uint8_t array_raw_data[31]; //placeholder para o Advertising PDU
uint32_t raw_data_len;
uint8_t myindex;

esp_ble_adv_params_t myadvpar;

char buf[256];


static void esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param) {
  esp_err_t err;

  switch (event) {
  case ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT:
      Serial.println("[ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT]");
      break;
  case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
      delay(20);
      esp_ble_gap_stop_advertising();
      Serial.println("[ESP_GAP_BLE_ADV_START_COMPLETE_EVT]");
      break;
  case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
      delay(250);
      esp_ble_gap_start_advertising(&myadvpar);
      Serial.println("[ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT]");
      break;
  default:
      break;
  }
}



void setup() {
  Serial.begin(115200);
  esp_read_mac(array_btmac,ESP_MAC_BT);
  sprintf(ascii_btmac,"%02X%02X%02X%02X%02X%02X"
    ,array_btmac[0],array_btmac[1],array_btmac[2],array_btmac[3],array_btmac[4],array_btmac[5]);

  sprintf(buf,"BTMAC1=%s\n",ascii_btmac); Serial.print(buf);

  esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
  bt_cfg.mode = ESP_BT_MODE_BLE; //Para usar ESP_BT_MODE_BLE na funcao esp_bt_controller_enable, tem que configurar aqui tambem
  esp_bt_controller_init(&bt_cfg);
  esp_bt_controller_enable(ESP_BT_MODE_BLE);
  
  esp_bluedroid_init(); //precisa pra registrar o callback
  esp_bluedroid_enable(); //precisa pra registrar o callback

  esp_ble_gap_register_callback(esp_gap_cb); //registro do callback, eh como uma interrupcao de eventos do BLE

  memset(array_raw_data,0,sizeof(array_raw_data));
  myindex = 0;
  array_raw_data[myindex++] = 0x00; //Nao importa; vou atualizar abaixo o length
  array_raw_data[myindex++] = 0x09; //Tipo do pacote: 0x09 = nome completo
  array_raw_data[myindex++] = 'E';
  array_raw_data[myindex++] = 'S';
  array_raw_data[myindex++] = 'P';
  array_raw_data[myindex++] = '3';
  array_raw_data[myindex++] = '2';
  array_raw_data[myindex++] = '_';
  for (int i = 0; i < 12; i++) {
    array_raw_data[myindex++] = ascii_btmac[i];
  }
  array_raw_data[0] = myindex - 1; //Subtraido 1 pois o primeiro raw data byte eh o proprio length, e o length nao conta a si proprio
  raw_data_len = myindex; 

  sprintf(buf,"BTMAC2=%s\n",ascii_btmac); Serial.print(buf);

  esp_ble_gap_config_adv_data_raw(array_raw_data, raw_data_len);

  sprintf(buf,"BTMAC3=%s\n",ascii_btmac); Serial.print(buf);

//  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV,ESP_PWR_LVL_N12); //-12dBm
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV,ESP_PWR_LVL_N0); //0dBm
//  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV,ESP_PWR_LVL_P9); //+9dBm

  sprintf(buf,"BTMAC4=%s\n",ascii_btmac); Serial.print(buf);

  myadvpar.adv_int_min = 320; //200ms
  myadvpar.adv_int_max = 320; //200ms
  myadvpar.adv_type = ADV_TYPE_NONCONN_IND; //nao conectavel
  myadvpar.own_addr_type = BLE_ADDR_TYPE_PUBLIC; //usar o MAC do proprio ESP32
  myadvpar.channel_map = ADV_CHNL_ALL; //3 canais: CH37, CH38, CH39
  
  esp_ble_gap_start_advertising(&myadvpar);

  sprintf(buf,"BTMAC5=%s\n",ascii_btmac); Serial.print(buf);
}

void loop() {
}
