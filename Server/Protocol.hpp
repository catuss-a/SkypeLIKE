#ifndef __PROTOCOL_HPP__
# define __PROTOCOL_HPP__

struct Protocol
{
	enum Type {
		CONNECTION = 0,
		ESTABLISHED,
		NOTIFY,
		CONTACT,
		CALL,
		ERR,
		TEXT = 7
	};

	enum Notify {
		CONNECTED = 0,
		DISCONNECTED,
		BUSY,
		ABSENT
	};

	enum Contact {
		ADD = 0,
		REMOVE,
		ACCEPT,
		REJECT
	};

	enum Call {
		REQUEST = 0,
		ACCEPTED,
		REJECTED,
		HANGUP,
		SUSPEND,
		RESUME
	};

	enum Error {
		CONNECTING = 0,
		CONTACTNOEXIST
	};

	enum Sequence {
		SEQUENCE_ESC = 0x10,
		SEQUENCE_INS = 0x04,
		PROTO_FOOTER = 0x1004
	};

	enum RawData {
		AUDIO = 0
	};
};

#endif /* !__PROTOCOL_HPP__ */
