import java.lang.Integer;
public class MainSv{
  public static void main(String[] args) {
    Server server = new Server(Integer.parseInt(args[0]));
    if(server.CreateSocket()){
      server.ConnectionClient();
      server.GetClientsStreams();
      server.GetArrayFromClient();
    }
  }
}
