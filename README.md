```c
/**
 * @brief Different traffic states of the LwM2M socket.
 *
 * This information can be used to give hints for the network interface
 * that can decide what kind of power management should be used.
 *
 * These hints are given from CoAP layer messages, so usage of DTLS might affect the
 * actual number of expected datagrams.
 */
enum lwm2m_socket_states {
	LWM2M_SOCKET_STATE_ONGOING,	 /**< Ongoing traffic is expected. */
	LWM2M_SOCKET_STATE_ONE_RESPONSE, /**< One response is expected for the next message. */
	LWM2M_SOCKET_STATE_LAST,	 /**< Next message is the last one. */
	LWM2M_SOCKET_STATE_NO_DATA,	 /**< No more data is expected. */
};
```



```c
/**
 * @brief Observe callback events
 */
enum lwm2m_observe_event {
	LWM2M_OBSERVE_EVENT_OBSERVER_ADDED,    /**< Observer added */
	LWM2M_OBSERVE_EVENT_OBSERVER_REMOVED,  /**< Observer removed */
	LWM2M_OBSERVE_EVENT_NOTIFY_ACK,        /**< Notification ACKed */
	LWM2M_OBSERVE_EVENT_NOTIFY_TIMEOUT,    /**< Notification timed out */
};
```



```c
/**
 * @brief LwM2M RD client events
 *
 * LwM2M client events are passed back to the event_cb function in
 * lwm2m_rd_client_start()
 */
enum lwm2m_rd_client_event {
	LWM2M_RD_CLIENT_EVENT_NONE,
	LWM2M_RD_CLIENT_EVENT_BOOTSTRAP_REG_FAILURE,
	LWM2M_RD_CLIENT_EVENT_BOOTSTRAP_REG_COMPLETE,
	LWM2M_RD_CLIENT_EVENT_BOOTSTRAP_TRANSFER_COMPLETE,
	LWM2M_RD_CLIENT_EVENT_REGISTRATION_FAILURE,
	LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE,
	LWM2M_RD_CLIENT_EVENT_REG_TIMEOUT,
	LWM2M_RD_CLIENT_EVENT_REG_UPDATE_COMPLETE,
	LWM2M_RD_CLIENT_EVENT_DEREGISTER_FAILURE,
	LWM2M_RD_CLIENT_EVENT_DISCONNECT,
	LWM2M_RD_CLIENT_EVENT_QUEUE_MODE_RX_OFF,
	LWM2M_RD_CLIENT_EVENT_ENGINE_SUSPENDED,
	LWM2M_RD_CLIENT_EVENT_NETWORK_ERROR,
	LWM2M_RD_CLIENT_EVENT_REG_UPDATE,
	LWM2M_RD_CLIENT_EVENT_DEREGISTER,
	LWM2M_RD_CLIENT_EVENT_SERVER_DISABLED,
};
```



```c
/** @brief LwM2M object path structure */
struct lwm2m_obj_path {
	uint16_t obj_id;         /**< Object ID */
	uint16_t obj_inst_id;    /**< Object instance ID */
	uint16_t res_id;         /**< Resource ID */
	uint16_t res_inst_id;    /**< Resource instance ID */
	uint8_t  level;          /**< Path level (0-4). Ex. 4 = resource instance. */
};
```

# build

```shell
west build -b qemu_x86 -- -DEXTRA_CONF_FILE=overlay-bootstrap.conf
```

# zeth

```shell
./net-setup.sh start
./net-setup.sh stop

sudo iptables -t nat -A POSTROUTING -j MASQUERADE -s 192.0.2.1
sudo sysctl -w net.ipv4.ip_forward=1
sudo service dnsmasq restart
```

