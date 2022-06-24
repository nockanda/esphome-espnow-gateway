#include <ESP8266WiFi.h>
#include <espnow.h>

byte board[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

typedef void (*esp_rc_cb_t)(int id, float temp, float humi);

esp_rc_cb_t recv_callback;

struct mysensor{
  int id;
  float temp;
  float humi;
};

struct payload{
  int id;
  char msg;
};

mysensor dht11;
payload mypayload;

void OnDataRecv(uint8_t * mac, uint8_t * data, uint8_t len) {
  memcpy(&dht11,data,sizeof(dht11));

  #ifdef ESP_LOGD
        ESP_LOGD("nockanda", "아이디: %d, 온도: %f, 습도: %f\n",dht11.id, dht11.temp,dht11.humi);
  #endif
  
  
  recv_callback(dht11.id, dht11.temp,dht11.humi);
}

//송신콜백함수 원형:
void OnDataSent(uint8_t *mac, uint8_t status) {
   //status가 0일때 송신 완료!
   #ifdef ESP_LOGD
   if(status == 0){
      ESP_LOGD("nockanda", "성공\n");
   }else{
      ESP_LOGD("nockanda", "실패\n");
   }
        
   #endif
   
}

class {
public:
    void begin() {
        WiFi.mode(WIFI_STA);  
        if (esp_now_init() == 0) {
            esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
            //나의 슬레이브를 등록해야겠다!
             esp_now_add_peer(board, ESP_NOW_ROLE_COMBO, 1, NULL, 0);//뒤에 2개는 ID, PW
             //송신완료 콜백함수 등록
             esp_now_register_send_cb(OnDataSent);
            esp_now_register_recv_cb(OnDataRecv);
        }
    }
    void set_recv_callback(esp_rc_cb_t callback){
       recv_callback = callback;
    }
    void send_data(int id, char c){
       mypayload.id = id;
       mypayload.msg = c;    
       esp_now_send(board, (uint8_t *) &mypayload, sizeof(mypayload));
    }
} NOCKANDA_ESPNOW;
