package project;

import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.border.Border;

public class OperationOneOperand extends Operation {

	private JTextField operand;
	private JButton btn;
	private JPanel pnl;

	public OperationOneOperand(String name, Project p) {
		super(name, p);
	}

	@Override
	protected void initFrame() {
		JTextField operand = new JTextField("0");
		operand.setAlignmentX(JTextField.CENTER_ALIGNMENT);
		Font font = new Font("Calibri", Font.PLAIN, 20);
		// operand.setBackground(Color.green);
		operand.setFont(font);
		System.out.println("Inicializovao operand " + operand);
		JButton btn = new JButton("OK");
		JPanel pnl = new JPanel();
		operand.setSize(250, 50);
		btn.setSize(100, 100);
		pnl.setLayout(new BorderLayout());
		f.setSize(300, 300);
		f.add(pnl);
		operand.revalidate();
		btn.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				double op = 0;
				try {
					op = Double.parseDouble(operand.getText());
				} catch (NumberFormatException ex) {
					JFrame fr = new JFrame();
					fr.setLayout(new GridLayout(2, 1));
					fr.setSize(300, 300);
					fr.setVisible(true);
					f.setVisible(false);
					JLabel l = new JLabel("Operand treba da bude broj");
					JButton b = new JButton("OK");
					b.addActionListener(new ActionListener() {
						@Override
						public void actionPerformed(ActionEvent e) {
							fr.setVisible(false);
							f.setVisible(true);
						}
					});
					fr.add(l);
					fr.add(b);
					return;
				}
				text = name + " " + op;
				f.setVisible(false);
				System.out.println(text);
				p.doPreview(text);
			}
		});
		operand.addActionListener(btn.getActionListeners()[0]);
		pnl.add(operand, BorderLayout.CENTER);
		pnl.add(btn, BorderLayout.SOUTH);
		pnl.revalidate();
	}

	@Override
	public void DoOperation() {
		f.setVisible(true);
	}

}
