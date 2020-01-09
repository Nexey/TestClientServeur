package main;

import serveur.MultiThreadedServer;

public class Main {

	public static void main(String[] args) {
		MultiThreadedServer server = new MultiThreadedServer(10000);
		new Thread(server).start();

		try {
			Thread.sleep(20 * 100000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		System.out.println("Arr�t du serveur");
		server.stop();
	}
}