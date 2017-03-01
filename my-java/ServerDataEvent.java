import java.nio.channels.SocketChannel;

class ServerDataEvent {
	public NioHelloServer server;
	public SocketChannel socket;
	public byte[] data;
	
	public ServerDataEvent(NioHelloServer server, SocketChannel socket, byte[] data) {
		this.server = server;
		this.socket = socket;
		this.data = data;
	}
}
