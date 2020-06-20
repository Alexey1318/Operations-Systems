import java.io.*;
import java.net.Socket;
import java.util.Arrays;

public class Server implements Runnable {

    Server(Socket cl) {
        Server.client = cl;
    }
    @Override
    public void run() {
        while (!client.isClosed()) {
            try{
                GetClientsStreams();
                GetArrayFromClient();
                Thread.sleep(1000);
                break;
            } catch (Exception e){
                System.err.println("Error: " + e.getMessage());
            }
        }
    }
    private void GetClientsStreams() throws IOException {
        clientInputStream = client.getInputStream();
        clientOutputStream = client.getOutputStream();
        System.out.println("Got client's streams");
    }
    private int[] Sort(int[] array) {
        Arrays.sort(array);
        return array;
    }
    private void GetArrayFromClient() throws IOException, ClassNotFoundException {
        ObjectInputStream inputStream = new ObjectInputStream(clientInputStream);
        int[] array = (int[]) inputStream.readObject();
        System.out.println("Received array: ");
        for (int count = 0; count < array.length; ++count) {
            System.out.print(array[count] + " ");
        }
        SendArrayToClient(array);
    }
    private void SendArrayToClient(int[] array) throws IOException {
        ObjectOutputStream outputStream = new ObjectOutputStream(clientOutputStream);
        outputStream.writeObject(Sort(array));
        outputStream.flush();
        System.out.println("\nSending array to client");
    }

    private static Socket client;
    private OutputStream clientOutputStream;
    private InputStream clientInputStream;
}
