import java.io.*;
import java.net.Socket;
public class Client {
  //Methods
  Client(String pHost, int pPort){
    this.HOST = pHost;
    this.PORT = pPort;
  }
  public boolean CreateSocket(){
    try{
        socket = new Socket(HOST, PORT);
        return true;
      } catch (Exception e){
        System.err.println("Can't create socket. Exception: " + e.getMessage());
        return false;
      }
    }
  public void SendArrayToServer(int[]array){
      try {
        ObjectOutputStream outputStream = new ObjectOutputStream(socket.getOutputStream());
        outputStream.writeObject(array);
        GetArrayFromServer();
      } catch (Exception e){
        e.printStackTrace();
      }
    }
  private void GetArrayFromServer(){
      try {
        ObjectInputStream inputStream = new ObjectInputStream(socket.getInputStream());
        int[]array = (int[])inputStream.readObject();
        for(int i = 0; i < array.length; ++i){
          System.out.println(array[i]);
        }
      } catch (Exception e){
        e.printStackTrace();
      }
    }
  //Fields
  private final String HOST;
  private final int PORT;
  private Socket socket = null;
}
