import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ConnectionFactory {

    ConnectionFactory(int threadCount, int port) throws IOException {
        threadPool = Executors.newFixedThreadPool(threadCount);
        server = new ServerSocket(port);
    }
    public void ServerWork() throws IOException {
        while(!server.isClosed()){
            client = server.accept();
            threadPool.execute(new Server(client));
        }
    }

    ServerSocket server;
    Socket client;
    ExecutorService threadPool;
}
