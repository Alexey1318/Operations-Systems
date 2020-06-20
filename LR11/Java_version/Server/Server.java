import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Arrays;
public class Server {
  //Methods
  Server(int pPort) {
    this.PORT = pPort;
    serverSocket = null;
    clientSocket = null;
    clientInputStream = null;
    clientOutputStream = null;
  }
  public boolean CreateSocket(){
    try {
      serverSocket = new ServerSocket(PORT);
      System.out.println("Server ready");
      return true;
    } catch (Exception e){
      System.err.println("Port not free. Exception: " + e.getMessage());
      return false;
    }
  }
  public void ConnectionClient(){
    try{
      clientSocket = serverSocket.accept();
      System.out.println("Client connect");
    } catch (Exception e){
      System.err.println("Error client's connection. Exception: " + e.getMessage());
    }
  }
  public void GetClientsStreams(){
    try{
      clientInputStream = clientSocket.getInputStream();
      clientOutputStream = clientSocket.getOutputStream();
      System.out.println("Got client's streams");
    } catch (Exception e){
      System.err.println("Error getting client's input stream. Exception: " +
      e.getMessage());
    }
  }
  private int[] Sort(int[]array){
    Arrays.sort(array);
    return array;
  }
  public void GetArrayFromClient() {
    try {
      ObjectInputStream inputStream = new ObjectInputStream(clientInputStream);
      int[]array = (int[])inputStream.readObject();
      SendArrayToClient(array);
    } catch (Exception e){
      System.err.println("Getting array error. Exception: " + e.getMessage());
    }
  }
  private void SendArrayToClient(int[]array){
    try{
      ObjectOutputStream outputStream = new ObjectOutputStream(clientSocket.getOutputStream());
      outputStream.writeObject(Sort(array));
    } catch (Exception e){
      System.err.println("Sending array error. Exception: " + e.getMessage());
    }
  }
  // Fields
  private final int PORT;
  private ServerSocket serverSocket;
  private Socket clientSocket;
  private InputStream clientInputStream;
  private OutputStream clientOutputStream;
}
