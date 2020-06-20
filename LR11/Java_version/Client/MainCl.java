import java.lang.Integer;
public class MainCl{
  public static void main(String[] args) {
    int[]array={1,-1,3,-3,0};
    Client client = new Client(args[0], Integer.parseInt(args[1]));
    if(client.CreateSocket()){
      client.SendArrayToServer(array);
    }
  }
}
