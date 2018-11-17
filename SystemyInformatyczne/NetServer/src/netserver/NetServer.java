/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package netserver;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author michal.blaszczyk
 */
public class NetServer implements Runnable{

    private Socket csock;
    
    private static Integer threadsCount = 0;
    
    /**
     * @param csock 
     */
    public NetServer(Socket csock) {
        this.csock = csock;
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        System.out.println("whatever");
        try {
            ServerSocket ssock = new ServerSocket(8000);
            for(;;) {
                Socket csock = ssock.accept();
                //new thread
                new Thread(new NetServer(csock)).start();
                System.out.println("Connected: " + csock);              
                
            }
        } catch(IOException ex) {
            System.out.println(ex.getMessage());
        }
    }

    @Override
    public void run() {
        threadsCount++;
        try {
            PrintWriter pw = new PrintWriter(csock.getOutputStream(), true);
            pw.println("Hello from Netserver");
            //Input to server
            BufferedReader br = new BufferedReader(new InputStreamReader(csock.getInputStream()));
            String input = br.readLine();
            pw.println(input + " - has been read ;)");
            pw.println("Currently    open threads count: " + threadsCount );
            
            pw.println("Bye");
        } catch (IOException ex) {
            System.out.println(ex.getMessage());
            Logger.getLogger(NetServer.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        try {
            //End of thread
            this.csock.close();
            threadsCount--;
            //Closing socket - important to free descryptors
        } catch (IOException ex) {
            System.out.println(ex.getMessage());
            Logger.getLogger(NetServer.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }
    
}
