import paho.mqtt.client as mqtt


hostname = "mqtt.thingstream.io"
clientid = "device:57048548-426f-49c9-8f5c-84261c4c51d6"  # Change pour chaque thing.
username = "KKP4ZC2ZVGGFOY5OF8VT"
password = "EY/DdlvVcxBITRpyBQzeeFmOS7oH5mRyevwYe+B0"  # Change pour chaque thing.


# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("TEST1")  # Replace with your actual topic

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    #print(msg.topic+" "+str(msg.payload))
    print(str(msg.payload))
    

# Create an MQTT client and attach our routines to it.
client = mqtt.Client(client_id="device:57048548-426f-49c9-8f5c-84261c4c51d6")
client.on_connect = on_connect
client.on_message = on_message

# Connect to the broker
client.username_pw_set("KKP4ZC2ZVGGFOY5OF8VT", "EY/DdlvVcxBITRpyBQzeeFmOS7oH5mRyevwYe+B0")
client.connect("mqtt.thingstream.io", 1883, 60)

# Blocking call that processes network traffic, dispatches callbacks and handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a manual interface.
client.loop_forever()
