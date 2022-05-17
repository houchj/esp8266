/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/

#include <ESP8266WiFi.h>

//定义自己的 wifi 名称和密码
#ifndef STASSID
#define STASSID "1024"
#define STAPSK  "12345678"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;


//启动函数
void setup() {
  //定义波特率
  Serial.begin(115200);
  //定义 LED 和 IO0 的引脚模式
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(0, OUTPUT);
  
  // We start by connecting to a WiFi network
  //输出调试信息，准备链接wifi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  // 设置wifi模式，并开始链接
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  //循环检查wifi连接状态，如果没成功，就继续等待
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //wifi 连接成功后，输出wifi的IP地址
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  //对LED和IO0的引脚状态，进行"取反"（1=>0 0=>1）
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  digitalWrite(0, !digitalRead(0));
  //延迟两秒
  delay(2000);
}
