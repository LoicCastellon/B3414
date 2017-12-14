import java.io.*;
import java.net.*;
import java.nio.file.*;
import java.text.*;

/**
 *
 * WebServer is a very simple web-server. Any request is responded with a very
 * simple web-page.
 * 
 * @author Lo�c CASTELLON & Florian MUTIN, 3IF4
 * @version 1.0
 */
public class WebServer {

  /**
   * WebServer constructor.
   */
  protected void start() {
	  
    ServerSocket s;

    System.out.println("Webserver starting up on port 80");
    System.out.println("(press ctrl-c to exit)");
    try {
      // create the main server socket
      s = new ServerSocket(3000);
    } catch (Exception e) {
      System.out.println("Error: " + e);
      return;
    }

    System.out.println("Waiting for connection");
    for (;;) {
      try {
        // wait for a connection
        Socket remote = s.accept();
        // remote is now the connected socket
        System.out.println("Connection, sending data.");
        BufferedReader in = new BufferedReader(new InputStreamReader(
                remote.getInputStream()));
        PrintStream out = new PrintStream(remote.getOutputStream());

        // read the data sent. We basically ignore it,
        // stop reading once a blank line is hit. This
        // blank line signals the end of the client HTTP
        // headers.
        
        String str = ".";
        String message = "";
        while (!str.equals("")){
          str = in.readLine();
          message += str;
        }
        System.out.println(message);        
        
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        //GET
        if(message.substring(0, 3).equals("GET")){
        		System.out.println("REQUETE GET");
        		String file="";
        		if(message.substring(5, 6).equals(" ")){
        			file = "pageParDefaut.html";
        		}
        		else{
	        		int i = 5;
	        		while(message.charAt(i)!=' '){
	        			file+=message.charAt(i);
	        			i++;
	        		}
        		}
        		System.out.println("file :"+file);
        		
                File f = new File(file);
                if(f.exists()){
            		System.out.println("Existe: 200");
        	        Path path = Paths.get(file);
        	        byte[] data = Files.readAllBytes(path);
        	        
        	        SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
        	    	String dateMofification = sdf.format(f.lastModified());
        	    	
        	        // Send the response
        	        // Send the headers
        	        out.println("HTTP/1.0 200 OK");
        	        
            		String type = file.substring(file.indexOf(".")+1);

            		if(type.equals("html") || type.equals("txt")){
            	        out.println("Content-Type: texte html/txt");
            		}
            		else if(type.equals("jpg")){
            	        out.println("Content-Type: image jpg/png");
            		}
            		else if(type.equals("mp3")){
            	        out.println("Content-Type: musique mp3");
            		}
               		else if(type.equals("wmv")){
            	        out.println("Content-Type: video wmv");
            		}
        	        out.println("Content-length: "+data.length);
            		System.out.println("Content-length: "+data.length);
        	        out.println("Last-modified: "+dateMofification);
            		System.out.println("Last-modified: "+dateMofification);
        	        out.println("Server: Bot");
        	        // this blank line signals the end of the headers
        	        out.println("");
        	  
        	        // Send the file
        	        out.write(data);
        	        out.flush();
                }
                else{
            		System.out.println("N'existe pas : 404");
        	        // Send the response
        	        // Send the headers
        	        out.println("HTTP/1.0 404 Not Found");
        	        out.println("Content-Type: text/html");
        	        out.println("Server: Bot");
        	        // this blank line signals the end of the headers
        	        out.println("");
        	        // Send the HTML page
        	        out.println("<H1>404 Fichier introuvable</H1>");
        	        out.flush();
                }
        	
        }
        
        // HEAD
        else if(message.substring(0, 4).equals("HEAD")) {
	            System.out.println("REQUETE HEAD");
	    		String file="";
	    		if(message.substring(6, 7).equals(" ")){
	    			file = "pageParDefaut.html";
	    		}
	    		else{
	        		int i = 6;
	        		while(message.charAt(i)!=' '){
	        			file+=message.charAt(i);
	        			i++;
	        		}
	    		}
        		System.out.println("file :"+file);
	    		
	            File f = new File(file);
                if(f.exists()){
            		System.out.println("Existe: 200");
        	        Path path = Paths.get(file);
        	        byte[] data = Files.readAllBytes(path);
        	        
        	        SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
        	    	String dateMofification = sdf.format(f.lastModified());

        	        // Send the response
        	        // Send the headers
        	        out.println("HTTP/1.0 200 OK");
        	        
            		String type = file.substring(file.indexOf(".")+1);

            		if(type.equals("html") || type.equals("txt")){
            	        out.println("Content-Type: texte html/txt");
            		}
            		else if(type.equals("jpg")){
            	        out.println("Content-Type: image jpg/png");
            		}
            		else if(type.equals("mp3")){
            	        out.println("Content-Type: musique mp3");
            		}
               		else if(type.equals("wmv")){
            	        out.println("Content-Type: video wmv");
            		}
        	        out.println("Content-length: "+data.length);
            		System.out.println("Content-length: "+data.length);
        	        out.println("Last-modified: "+dateMofification);
            		System.out.println("Last-modified: "+dateMofification);
        	        out.println("Server: Bot");
        	        // this blank line signals the end of the headers
        	        out.println("");

        	        out.flush();
                }
                else{
            		System.out.println("N'existe pas : 404");
        	        // Send the response
        	        // Send the headers
        	        out.println("HTTP/1.0 404 Not Found");
        	        out.println("Content-Type: text/html");
        	        out.println("Server: Bot");
        	        // this blank line signals the end of the headers
        	        out.println("");
        	        // Send the HTML page
        	        out.println("<H1>404 Fichier introuvable</H1>");
        	        out.flush();
                }
	        
        }
        
        // DELETE
        else if(message.substring(0, 6).equals("DELETE")) {
	            System.out.println("REQUETE DELETE");
	    		String file="";
	    		if(message.substring(8, 9).equals(" ")){
	        		System.out.println("pas de nom derriÃ¨re DELETE : 403");
        	        // Send the response
        	        // Send the headers
        	        out.println("HTTP/1.0 403 Forbidden");
        	        out.println("Content-Type: text/html");
        	        out.println("Server: Bot");
        	        // this blank line signals the end of the headers
        	        out.println("");
        	        // Send the HTML page
        	        out.println("<H1>403 Interdiction de supprimer la page par defaut</H1>");
        	        out.flush();
	    		}
	    		else{
	        		int i = 8;
	        		while(message.charAt(i)!=' '){
	        			file+=message.charAt(i);
	        			i++;
	        		}
	        		System.out.println("file :"+file);
		    		
		            File f = new File(file);
	                if(f.exists()){
	                	f.delete();
	            		System.out.println("Suppression : 200");

	        	        // Send the response
	        	        // Send the headers
	        	        out.println("HTTP/1.0 200 OK");
	        	        out.println("Server: Bot");
	        	        // this blank line signals the end of the headers
	        	        out.println("");
	        	        out.println("<H1>Fichier "+file+" supprime</H1>");
	        	        out.flush();
	                }
	                else{
	            		System.out.println("N'existe pas : 404");
	        	        // Send the response
	        	        // Send the headers
	        	        out.println("HTTP/1.0 404 Not Found");
	        	        out.println("Content-Type: text/html");
	        	        out.println("Server: Bot");
	        	        // this blank line signals the end of the headers
	        	        out.println("");
	        	        // Send the HTML page
	        	        out.println("<H1>404 Fichier introuvable</H1>");
	        	        out.flush();
	                }
	    		}
	        
        }
        
        // PUT
        else if(message.substring(0, 3).equals("PUT")) {
	            System.out.println("REQUETE PUT");
	    		String file="";
	    		if(message.substring(5, 6).equals(" ")){
	        		System.out.println("pas de nom derriÃ¨re PUT : 400");
        	        // Send the response
        	        // Send the headers
        	        out.println("HTTP/1.0 400 Bad Request");
        	        out.println("Content-Type: text/html");
        	        out.println("Server: Bot");
        	        // this blank line signals the end of the headers
        	        out.println("");
        	        // Send the HTML page
        	        out.println("<H1>400 Veuillez entrez un nom de fichier pour votre requete PUT</H1>");
        	        out.flush();
	    		}
	    		else{
	        		int i = 5;
	        		while(message.charAt(i)!=' '){
	        			file+=message.charAt(i);
	        			i++;
	        		}
	        		System.out.println("file :"+file);
		    		
		            File f = new File(file);
	                if(!f.exists()){
	            		System.out.println("Fichier cree : 201");
	            		f.createNewFile();

	        	        // Send the response
	        	        // Send the headers
	        	        out.println("HTTP/1.0 201 CREATED");
	        	        out.println("Server: Bot");
	        	        // this blank line signals the end of the headers
	        	        out.println("");
	        	        out.println("<H1>Fichier "+file+" cree</H1>");
	        	        out.flush();
	        	        
	        	        //REMPLISSAGE DU FICHIER
	            		int indexStart = message.indexOf("deflatecontent-length:");
	            		int indexEnd = message.indexOf("Connection");
	            		String longueurStr = message.substring(indexStart+23,indexEnd);
	            		int longueur = Integer.valueOf(longueurStr);
	            		System.out.println("deflatecontent-length: "+longueur);
	            		
	                    String messagePut = "";
	                    for(int k=0;k<longueur;k++)
	                    {
	                      messagePut += (char) in.read();
	                    }
	                    System.out.println("CONTENT-PUT :"+messagePut);
	                    
	                    FileWriter outFile = new FileWriter(f);
	                    outFile.write(messagePut);
	                    outFile.close();
	                }
	                else{
	            		System.out.println("Fichier dÃ©jÃ  existant : 403");
	        	        // Send the response
	        	        // Send the headers
	        	        out.println("HTTP/1.0 403 Forbidden");
	        	        out.println("Content-Type: text/html");
	        	        out.println("Server: Bot");
	        	        // this blank line signals the end of the headers
	        	        out.println("");
	        	        // Send the HTML page
	        	        out.println("<H1>403 Fichier deja existant </H1>");
	        	        out.flush();
	                }
	    		}
	        
        }

        // POST
        else if(message.substring(0, 4).equals("POST")) {
	            System.out.println("REQUETE POST");
	    		String file="";
	    		if(message.substring(6, 7).equals(" ")){
	        		System.out.println("pas de nom derriÃ¨re PUT : 400");
        	        // Send the response
        	        // Send the headers
        	        out.println("HTTP/1.0 400 Bad Request");
        	        out.println("Content-Type: text/html");
        	        out.println("Server: Bot");
        	        // this blank line signals the end of the headers
        	        out.println("");
        	        // Send the HTML page
        	        out.println("<H1>400 Veuillez entrez un nom de fichier pour votre requete POST</H1>");
        	        out.flush();
	    		}
	    		else{
	        		int i = 6;
	        		while(message.charAt(i)!=' '){
	        			file+=message.charAt(i);
	        			i++;
	        		}
	        		System.out.println("file :"+file);
		    		
		            File f = new File(file);
	                if(f.exists()){
	            		System.out.println("Fichier trouve : 200");

	        	        // Send the response
	        	        // Send the headers
	        	        out.println("HTTP/1.0 200 OK");
	        	        out.println("Server: Bot");
	        	        // this blank line signals the end of the headers
	        	        out.println("");
	        	        out.println("<H1>Fichier "+file+" complete</H1>");
	        	        
	        	        //REMPLISSAGE DU FICHIER
	            		int indexStart = message.indexOf("deflatecontent-length:");
	            		int indexEnd = message.indexOf("Connection");
	            		String longueurStr = message.substring(indexStart+23,indexEnd);
	            		int longueur = Integer.valueOf(longueurStr);
	            		System.out.println("deflatecontent-length: "+longueur);
	            		
	                    String messagePut = "";
	                    for(int k=0;k<longueur;k++)
	                    {
	                      messagePut += (char) in.read();
	                    }
	                    System.out.println("CONTENT-PUT :"+messagePut);
	                    
	                    FileWriter outFile = new FileWriter(f,true);
	                    outFile.append(messagePut);
	                    outFile.close();
	                }
	                else{
	            		System.out.println("N'existe pas : 404");
	        	        // Send the response
	        	        // Send the headers
	        	        out.println("HTTP/1.0 404 Not Found");
	        	        out.println("Content-Type: text/html");
	        	        out.println("Server: Bot");
	        	        // this blank line signals the end of the headers
	        	        out.println("");
	        	        // Send the HTML page
	        	        out.println("<H1>404 Fichier introuvable</H1>");
	        	        out.flush();
	                }
	    		}
        }
        
        else{
            System.out.println("REQUETE INCONNUE");
	        // Send the response
	        // Send the headers
	        out.println("HTTP/1.0 500 Internal Server Error");
	        out.println("Content-Type: text/html");
	        out.println("Server: Bot");
	        // this blank line signals the end of the headers
	        out.println("");
	        // Send the HTML page
	        out.println("<H1>500 Cas non pris en compte</H1>");
	        out.flush();
        }
        
        
        
        

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        remote.close();
      } catch (Exception e) {
        System.out.println("Error: " + e);
      }
    }
  }

  /**
   * Start the application.
   * 
   * @param args
   *            Command line parameters are not used.
   */
  public static void main(String args[]) {
    WebServer ws = new WebServer();
    ws.start();
  }
}