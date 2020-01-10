package serveur;

import experts.*;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.net.Socket;

/**

 */
public class WorkerRunnable implements Runnable {
	public static int itemCount = 1;
	protected Socket clientSocket = null;
	protected String serverText = null;
	protected int numClient;
	
	// Constructeur de base
	// itemCount est pour identifier chaque client
	public WorkerRunnable(Socket clientSocket, String serverText) {
		this.clientSocket = clientSocket;
		this.serverText = serverText;
		this.numClient = WorkerRunnable.itemCount;
		System.out.println(this.chat("Connect� !"));
		WorkerRunnable.itemCount++;
	}
	
	// Permet d'afficher un message en sachant la provenance 
	public String chat(String msg) {
		return "Client n�" + this.numClient + " : " + msg;
	}
	
	// WorkerRunnable impl�mente Runnable, il y a donc sans surprise une m�thode run
	public void run() {
		// Le stream d'input : Il lit la socket directement
		InputStream input = null;
		
		// On r�cup�re le r�sultat de la socket dans un BufferedReader qui lui m�me contient un InputStreamReader pointant sur l'InputStream
		BufferedReader in;

		// On convertir le r�sultat dans un String, que l'on peut manipuler 
		String inputLine;
		try {
			// On essaye de r�cup�rer le contenu de la socket
			input = clientSocket.getInputStream();
			in = new BufferedReader(new InputStreamReader(input));
			
			// M�thode bloquante : Tant qu'on ne re�oit pas de message, le Worker reste bloqu� � cet endroit
			// C'est pour cela que ce serveur est multithreading : Chaque client est bloquant, ce qui
			// veut dire qu'un serveur non multithreading n'est capable de g�rer qu'un seul client � la fois
			// Une fois la connexion finie d'une mani�re ou d'une autre, readLine() renvoit null. C'est aussi simple que �a
			while (null != (inputLine = in.readLine())) {
				// Si la connexion est rompue, readLine() renvoit juste un caract�re vide non null. Ce if permet de le filtrer.
				if (!inputLine.equals("")) {
					System.out.println(this.chat(inputLine));
					FormeCOR experts = new CercleCOR(
							new TriangleCOR()
							);
					System.out.println(experts.gerer(inputLine));
					// G�rer ici avec une cha�ne d'expert
				}
			}
			
			// La connexion s'est termin�e normalement
			System.out.println(this.chat("Connexion finie."));
		} catch (IOException e) {
			// La connexion a �t� coup�e d'un coup (erreur de connexion, time out, arr�t forc� du client)
			System.out.println(this.chat("Connexion rompue !"));
		} finally {
			// Je ferme l'output de la socket puis l'input
			OutputStream output;
			try {
				output = clientSocket.getOutputStream();
				output.close();
				input.close();
			} catch (IOException e) {
			}
		}
	}
}