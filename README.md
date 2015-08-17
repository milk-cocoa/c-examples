Milkcocoa C Examples

C言語でMilkcocoaに接続する方法を説明します。

# サンプルの説明

###app.h

アプリの設定です。

###push.c

MilkcocoaのPush APIを発行するサンプルです。

###onpush.c

MilkcocoaのPush APIを監視するサンプルです。


# Introduction

[PahoのCクライアント](https://eclipse.org/paho/clients/c/)を使ってMilkcocoaに接続します。

- MQTT Clientをインストール
- サンプルコードを修正してコンパイルし実行する

# PahoのC言語用MQTT Clientをインストール

```
git clone http://git.eclipse.org/gitroot/paho/org.eclipse.paho.mqtt.c.git
cd org.eclipse.paho.mqtt.c.git
make
sudo make install
```

*MacでのコンパイルではMakefileの230行目をコメントアウトします。

以下の行をコメントアウトします。

```
	#/sbin/ldconfig $(DESTDIR)${libdir}
```

# サンプルコードを動かしてみましょう

## 次にサンプルコードをコンパイルして動かしてみます

###コンパイルまで

まずソースコードをGithubからクローンします。

```
git clone git@github.com:milk-cocoa/c-examples.git
cd c-examples
```

app.hを自分のアプリ用に修正します。TOKENは"sdammy"にしておいてください。

```
#define TOKEN "sdammy"
#define APPID "{AppID}"
#define HOST "{AppID}.mlkcca.com"
#define PORT "1883"
```

以下のコマンドでコンパイルできます。

```
cc onpush.c -o onpush -lpaho-mqtt3c  -lpthread -L ../org.eclipse.paho.mqtt.c/build/output
```

../org.eclipse.paho.mqtt.c/build/output
は最初にMQTTクライアントをビルドした場所の/build/outputか、make installで生成物がインストールされた先のパスを指定してください。


###動作確認

以下のコマンドで実行してください。PahoのMQTTクライアントをビルドしたフォルダの/build/output以下にMQTTのダイナミックリンクライブラリが作成されます。libpaho-mqtt3a.so.1とlibpaho-mqtt3x.so.1をc-examples以下にコピーしてください。サンプルを実行するときに必要です。

```
./onpush
```

onpush.cはpushの監視を行うだけなので、"message"データストアにJSクライアントなど別の方法で適当なデータをpushしてみてください。

push.cはpush APIを一度実行するサンプルです。JSクライアントなどで"message"データストアを監視した状態で、push.cを実行してみてください。

## push.cについて軽く説明します。

まずマクロ部分ですが、app.hとpush.cに存在するマクロをまとめると以下のようになります。

```
#define TOKEN "j{JSON Web Token}"
#define APPID "{AppID}"
#define HOST "{AppID}.mlkcca.com"
#define PORT "1883"
#define CLIENTID    "ExampleClientPub1"
#define PAYLOAD     "{\"params\":{\"content\":\"from C\"}}"
#define QOS         0
```

### TOKEN

MQTTプロトコルではusernameの所に設定します。
TOKENはプレフィックスとしてsとjから始まり、s{SessionID}とj{Json Web Token}というフォーマットを受け付けます。

SessionIDはauthWithTokenというAPIの戻り値です。JSクライアント以外では、あまり今回は利用しません。
Json Web TokenはMilkcocoaの管理画面のシークレットトークンをもとに生成されたJWTを設定します。
ログインが必要ない場合はTOKENにsdammyと設定してください。

### AppID

AppIDにはあなたが作成したMilkcocoaアプリのIDを設定します。これはMQTTプロトコルのpasswordに設定します。


### HOSTとPORT

HOSTはアプリごとに作成されます。{AppID}.mlkcca.comです。
PORTはTLS通信の場合は8883、TLS無しの場合は1883です。

### CLIENTID

CLIENTIDは他のデバイスとかぶらないようにしてください。かぶると定期的に接続が切れるという症状が出ます。

### PAYLOAD

PAYLOADは実際に送るデータです。JSONフォーマットで送ります。必ずparamsというkeyを作りその中にデータを入れます。

### QOS

QOSはMQTTのメッセージ到達品質です。0,1,2の３つとも設定可能です。

### TOPIC

TOPICというマクロはありませんが、以下の関数でTOPICを生成しています。

```
    create_push_topic(topic, "message");
```

TOPICのフォーマットは、{AppID}/{データストア名}/{push|send|set|remove}です。

