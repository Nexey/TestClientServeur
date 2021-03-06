package serveur;

import java.net.ServerSocket;
import java.net.Socket;
import java.io.IOException;

public class MultiThreadedServer implements Runnable {

	protected int serverPort = 8080;
	protected ServerSocket serverSocket = null;
	protected boolean isStopped = false;
	protected Thread runningThread = null;

	public MultiThreadedServer(int port) {
		this.serverPort = port;
	}

	public void run() {
		synchronized (this) {
			this.runningThread = Thread.currentThread();
		}
		// Ouvre la socket du serveur
		openServerSocket();
		while (!isStopped()) {
			Socket clientSocket = null;
			try {
				// Bloquant : Le serveur ne fait plus rien d'autre
				clientSocket = this.serverSocket.accept();
			} catch (IOException e) {
				if (isStopped()) {
					System.out.println("Arr�t du serveur.");
					return;
				}
				throw new RuntimeException("Erreur lors de l'acceptation du client", e);
			}
			
			// Cr�ation du worker qui va s'occuper d'un seul client
			// Cette partie l� n'est pas bloquante : on retourne au d�but du while jusqu'� la m�thode accept()
			new Thread(new WorkerRunnable(clientSocket, "Serveur multithreading")).start();
		}
		System.out.println("Serveur arr�t�.");
	}
	
	// On est dans un programme multi thread, la m�thode doit donc �tre synchronized : Elle n'autorise
	// qu'un thread � la fois � appeler cette fonction
	private synchronized boolean isStopped() {
		return this.isStopped;
	}
	
	public synchronized void stop() {
		this.isStopped = true;
		try {
			this.serverSocket.close();
		} catch (IOException e) {
			throw new RuntimeException("Erreur lors de la fermeture du serveur", e);
		}
	}
	
	private synchronized void openServerSocket() {
		try {
			this.serverSocket = new ServerSocket(this.serverPort);
		} catch (IOException e) {
			throw new RuntimeException("Impossible d'ouvrir le port " + this.serverPort, e);
		}
	}

}