import java.nio.channels.SocketChannel;
import java.util.LinkedList;
import java.util.List;

public class HttpWorker implements Runnable {
	private List<ServerDataEvent> queue = new LinkedList<ServerDataEvent>();
	private String body = "<html><body><div style='position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Arial, Helvetica, sans-serif;color: blue;font-size: 40px;'>Hello, World! ... brought to you by Java</div></body></html>";
	private byte[] response = ("HTTP/1.1 200 OK\nContent-Type: text/html\nConnection: keep-alive\nContent-Length: " + body.length() + "\n\n" + body).getBytes();
	
	public void processData(NioHelloServer server, SocketChannel socket, byte[] data, int count) {
		synchronized(queue) {
			queue.add(new ServerDataEvent(server, socket, response));
			queue.notify();
		}
	}
	
	public void run() {
		ServerDataEvent dataEvent;
		
		while(true) {
			// Wait for data to become available
			synchronized(queue) {
				while(queue.isEmpty()) {
					try {
						queue.wait();
					} catch (InterruptedException e) {
					}
				}
				dataEvent = (ServerDataEvent) queue.remove(0);
			}
			
			dataEvent.server.send(dataEvent.socket, dataEvent.data);
		}
	}
}

