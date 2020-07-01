package project;

import java.awt.Graphics;
import java.awt.image.BufferedImage;

import javax.swing.JPanel;

public abstract class Selection {

	public Selection() {
	}

	public abstract void paint(JPanel p, BufferedImage img);
	public abstract String zaStampu(int yy);
	public abstract String zaSave();
}
