README.md




cc onpush.c -lpaho-mqtt3c  -lpthread -L ../org.eclipse.paho.mqtt.c/build/output



# Introduction


## PahoのC言語用MQTT Clientをインストール

https://eclipse.org/paho/clients/c/


```
git clone http://git.eclipse.org/gitroot/paho/org.eclipse.paho.mqtt.c.git
cd org.eclipse.paho.mqtt.c.git
make
sudo make install
```

＊Macの場合は、Makefileの230行目をコメントアウト


## milkcocoa_clangをコンパイルして実行

```
git clone git@github.com:milk-cocoa/c-examples.git
cd c-examples
```

自分のアプリにあわせてapp.hを修正する。

```
cc onpush.c -o onpush -lpaho-mqtt3c  -lpthread -L ../org.eclipse.paho.mqtt.c/build/output
./onpush
```

### 認証

認証が必要な場合は、Milkcocoaのシークレットトークンを用いて作成したJWTokenを、TOKENマクロで定義する。
その際先頭に'j'を付与する。

