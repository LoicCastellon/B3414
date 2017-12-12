/**
 * Classe rep�sentant le serveur du tchat.
 * 
 * @author Lo�c CASTELLON & Florian MUTIN 3IF4
 * 
 */

import java.io.*;
import java.net.Socket;
import java.util.ArrayList;

public class Server
{
	final public static String DECONNEXION = "deco";
	final public static String IP = "127.0.0.1";
	final public static int PORT = 5001;
	final private String FICHIER_HISTORIQUE = "src\\historique.txt";
	
	private ArrayList<Socket> sockets;
	private String historique;
	private IHMServer ihmServer;
	
	/**
	 * 
	 * @param ihmServer l'affichage graphique correspondant au serveur
	 */
	public Server(IHMServer ihmServer)
	{
		this.ihmServer = ihmServer;
		try
		{
			BufferedReader br=new BufferedReader(new InputStreamReader(new FileInputStream(FICHIER_HISTORIQUE)));
			
			historique = "";
			String ligne;
			while ((ligne=br.readLine())!=null){
				historique+=ligne+"\n";
			}
			br.close();
		}
		catch (Exception e) {
			System.err.println("Error in Server::Server:" + e);
			ihmServer.affiche("");
			ihmServer.affiche("~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
			ihmServer.affiche("~~~~~~~~~~ ERREUR ~~~~~~~~~~");
			ihmServer.affiche("~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
			ihmServer.affiche("");
	    }

		try
		{
			BufferedWriter bw = new BufferedWriter (new OutputStreamWriter (new FileOutputStream (FICHIER_HISTORIQUE)));
			bw.write(historique);
			bw.close();

			ihmServer.affiche("##### Lecture de l'historique :");
			ihmServer.affiche(historique);
		}
		catch (Exception e) {
			System.err.println("Error in Server::Server:" + e);
			ihmServer.affiche("");
			ihmServer.affiche("~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
			ihmServer.affiche("~~~~~~~~~~ ERREUR ~~~~~~~~~~");
			ihmServer.affiche("~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
			ihmServer.affiche("");
	    }

		sockets = new ArrayList<Socket>();
		
		ThreadWaitingServer threadWaitingServer = new ThreadWaitingServer(this,this.PORT,this.ihmServer);
		threadWaitingServer.start();
	}
	
	/**
	 * Envoie d'un texte au tout les clients connect�s au serveur. Ajout de ce texte � l'historique.
	 * @param texte le texte � envoyer
	 */
	public void envoyer (String texte)
	{
		historique += texte + '\n';
		try
		{
			BufferedWriter bw = new BufferedWriter (new OutputStreamWriter (new FileOutputStream (FICHIER_HISTORIQUE)));
			bw.write(historique);
			bw.close();
		}
		catch (Exception e)
		{
				System.err.println("Error in Server::envoyer:" + e);
				ihmServer.affiche("");
				ihmServer.affiche("~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				ihmServer.affiche("~~~~~~~~~~ ERREUR ~~~~~~~~~~");
				ihmServer.affiche("~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				ihmServer.affiche("");
	    }
		
		for(int i=0;i<sockets.size();i++)
		{
			try
			{
				PrintStream socOut = new PrintStream(sockets.get(i).getOutputStream());
				socOut.println(texte);
			}
			catch (Exception e)
			{
					System.err.println("Error in Server::affiche:" + e);
					ihmServer.affiche("");
					ihmServer.affiche("~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
					ihmServer.affiche("~~~~~~~~~~ ERREUR ~~~~~~~~~~");
					ihmServer.affiche("~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
					ihmServer.affiche("");
		    }
		}
	}

	/**
	 * Ajout d'un client � la liste des client connect�s.
	 * @param socket le client � ajouter
	 */
	public void add(Socket socket) {
		sockets.add(socket);
	}

	/**
	 * M�thode permettant d'obtenir l'historique de la discussion
	 * @return l'historique de la discussion
	 */
	public String getHistorique() {
		return historique;
	}

	/**
	 * Suppression d'un client de la liste des clients connect�s
	 * @param socket le client � supprimer
	 */
	public void remove(Socket socket) {
		sockets.remove(socket);
	}
}
