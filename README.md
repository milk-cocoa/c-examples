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

'''
cc onpush.c -o onpush -lpaho-mqtt3c  -lpthread -L ../org.eclipse.paho.mqtt.c/build/output
./onpush
'''
