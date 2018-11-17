/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package communicator;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.WindowConstants;

/**
 *
 * @author michal.blaszczyk
 */
public class UI extends JFrame implements ActionListener {
    
    private final JScrollPane skr;
    private final JTextArea panelg;
    
    protected JTextField messagesTextField;
    protected JTextField inputTextField;
    
    public UI() {
        super("Communicator");
        setSize(400, 300);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        
        JPanel panel = new JPanel();
        this.add(panel, BorderLayout.CENTER);
        panel.setSize(this.getWidth(), this.getHeight() - 100);
        panel.setLayout(new BorderLayout());
        
        panelg = new JTextArea();
        panelg.setEditable(false);
        skr = new JScrollPane(panelg);
    panel.add(skr, BorderLayout.CENTER);
        
        JPanel panelBottom = new JPanel();
        add(panelBottom, BorderLayout.SOUTH);
        panelBottom.setLayout(new BorderLayout());
        
        this.inputTextField = new JTextField();
        panelBottom.add(this.inputTextField, BorderLayout.CENTER);
        
        JButton buttonSend = new JButton();
        buttonSend.setText("Send");
        panelBottom.add(buttonSend, BorderLayout.EAST);
        buttonSend.addActionListener(this); 
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        this.panelg.append("\n" + this.inputTextField.getText());
    }
}

