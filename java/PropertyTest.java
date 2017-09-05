import java.io.FileInputStream;
import java.io.InputStream;
import java.io.IOException;
import java.util.Properties;

public class PropertyTest {

  public static void main(String[] args) {
    Properties prop = new Properties();
    InputStream input = null;
		
    try {
      input = new FileInputStream("config.properties");
      prop.load(input);
			
      System.out.println(prop.getProperty("application"));
      System.out.println(prop.getProperty("sql"));
    } catch (IOException ex) {
      ex.printStackTrace();
    } finally {
      if (input != null) {
        try {
          input.close();
        } catch (IOException ex) {
          ex.printStackTrace();
        }
      }
    }
  }
}
