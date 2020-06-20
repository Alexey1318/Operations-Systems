import java.lang.Integer;
public class MainThSv{
  public static void main(String[] args) {    
    try{
      ConnectionFactory connectionFactory = new ConnectionFactory(3, Integer.parseInt(args[0]));
      connectionFactory.ServerWork();
    }catch(Exception e){
      System.err.println("Error: " + e.getMessage());
    }
  }
}
