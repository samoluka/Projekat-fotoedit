package project;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Stroke;
import java.awt.image.BufferedImage;

import javax.swing.JPanel;

import com.sun.java.accessibility.util.Translator;

public class SelectionRect extends Selection {
	protected int x, y, width, height;

	public SelectionRect(int x, int y, int width, int height) {
		super();
		this.x = x;
		this.y = y;
		this.width = width;
		this.height = height;
	}

	@Override
	public String zaStampu(int yy) {
		return x + " " + (yy - y) + " " + width + " " + height;
	}

	@Override
	public void paint(JPanel p, BufferedImage img) {
		Graphics g = p.getGraphics();
		int[] koord = translate(p, img);
		Graphics2D g2d = (Graphics2D) g.create();
		Stroke dashed = new BasicStroke(3, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 0, new float[] { 9 }, 0);
		g2d.setStroke(dashed);
		g2d.setColor(Color.white);
		g2d.drawRect(koord[0], koord[1], koord[2], koord[3]);
	}

	int[] translate(JPanel p, BufferedImage img) {
		double pw = 0;
		if (img.getWidth() > p.getWidth()) {
			pw = (img.getWidth() - p.getWidth()) / (double) img.getWidth();
		}
		double ph = 0;
		if (img.getHeight() > p.getHeight()) {
			ph = (img.getHeight() - p.getHeight()) / (double) img.getHeight();
		}
		double v = Math.max(ph, pw);
		int ww = (int) (width * (1 - v));
		int hh = (int) (height * (1 - v));
		int nw = (int) (img.getWidth() * (1 - v));
		int nh = (int) (img.getHeight() * (1 - v));
		int xx = 0;
		if (nw < p.getWidth()) {
			xx += (int) ((p.getWidth() - nw) / 2.0);
		}
		int yy = 0;
		if (nh < p.getHeight()) {
			yy += (int) ((p.getHeight() - nh) / 2.0);
		}
		int startX = (int) (xx + x * (1 - v));
		int startY = (int) (yy + y * (1 - v));
		return new int[] { startX, startY, ww, hh };
	}

	@Override
	public String zaSave() {
		return x + " " + y + " " + width + " " + height + "\n";
	}

}
