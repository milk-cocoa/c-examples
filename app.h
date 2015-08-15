
#define TOKEN "j{JSON Web Token}"
#define APPID "{AppID}"
#define HOST "{AppID}.mlkcca.com"
#define PORT "1883"

/*
//テスト用
#define TOKEN "sdammy"
#define APPID "hotia8yv36p"
#define HOST "hotia8yv36p.mlkcca.com"
#define PORT "1883"
*/

void create_push_topic(char* topic, char* path) {
	sprintf(topic, "%s/%s/push", APPID, path);
}

void create_send_topic(char* topic, char* path) {
	sprintf(topic, "%s/%s/send", APPID, path);
}
