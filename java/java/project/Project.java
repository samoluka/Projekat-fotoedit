package project;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.FileDialog;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Stroke;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileFilter;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.channels.FileChannel;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.stream.Collector;
import java.util.stream.Collectors;

import javax.imageio.ImageIO;
import javax.swing.JFileChooser;
import javax.swing.JPanel;

import aplicationWindow.AppFrame;

public class Project {

	private BufferedImage[] currimg = new BufferedImage[100];
	private String[] absPath = new String[100];
	private boolean[] active = new boolean[100];
	private int indx = 0;
	private int start = 0;
	private BufferedImage mainImage;
	private boolean fullView = false;
	private BufferedImage prevImage;
	private AppFrame myApp;
	private LinkedList<Selection> sel = new LinkedList<Selection>();

	public Project(AppFrame a) {
		myApp = a;
	}

	public void drawSelection(JPanel mainPanel) {
		if (mainImage != null) {
			sel.forEach((s) -> {
				s.paint(mainPanel, mainImage);
			});
		}
	}

	public void Paint(JPanel mainPanel, JPanel[] sidePanel, JPanel preview, boolean ost) {
		if (indx != 0) {
			drawImageProportionally(mainPanel, mainImage);
			if (ost) {
				drawImageProportionally(preview, prevImage);
				for (int i = 0; i < indx && i < sidePanel.length; i++) {
					int j = (start + i) % indx;
					drawImageProportionally(sidePanel[i], currimg[j]);
				}
			}
		}
		drawSelection(mainPanel);
	}

	public void addSelection(JPanel p, int x, int y, int w, int h) {
		if (!fullView)
			return;
		if (w == 0 && h == 0)
			return;
		double v = 1 - getProportion(p, mainImage);
		int nw = (int) (mainImage.getWidth() * v);
		int nh = (int) (mainImage.getHeight() * v);
		int xx = 0;
		if (nw < p.getWidth()) {
			xx += (int) ((p.getWidth() - nw) / 2.0);
		}
		int yy = 0;
		if (nh < p.getHeight()) {
			yy += (int) ((p.getHeight() - nh) / 2.0);
		}
		int ww = (int) (w / v);
		int hh = (int) (h / v);
		int startX = (int) ((x - xx) / v);
		if (startX < 0) {
			ww += startX;
			startX = 0;
		}
		int startY = (int) ((y - yy) / v);
		if (startY < 0) {
			hh += startY;
			startY = 0;
		}
		if ((startX + ww) > mainImage.getWidth())
			ww = mainImage.getWidth() - startX;
		if ((startY + hh) > mainImage.getHeight())
			hh = mainImage.getHeight() - startY;
		sel.add(new SelectionRect(startX, startY, ww, hh));
	}

	public double getProportion(JPanel p, BufferedImage img) {
		double pw = 0;
		if (img.getWidth() > p.getWidth()) {
			pw = (img.getWidth() - p.getWidth()) / (double) img.getWidth();
		}
		double ph = 0;
		if (img.getHeight() > p.getHeight()) {
			ph = (img.getHeight() - p.getHeight()) / (double) img.getHeight();
		}
		double v = Math.max(ph, pw);
		return v;
	}

	public void setMainImage(BufferedImage mainImage) {
		fullView = false;
		this.mainImage = mainImage;
	}

	public void addImage(File f) {
		BufferedImage tmp;
		try {
			tmp = ImageLoader.in(f);
		} catch (IOException e1) {
			return;
		}
		if (mainImage == null)
			mainImage = currimg[1];
		absPath[indx] = f.getAbsolutePath();
		active[indx] = true;
		currimg[indx++] = tmp;
	}

	public boolean getActiveAt(int i) {
		return active[i];
	}

	public void setActiveAt(int i, boolean b) {
		Boolean old = active[i];
		active[i] = b;
		if (old != b && fullView) {
			try {
				fullView();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	static void doCommand(String command) throws IOException, InterruptedException {
		Process p;
		p = Runtime.getRuntime().exec(command);
		p.waitFor();
	}

	public void doOperation(String opr) throws IOException {
		int br = 0;
		for (br = 0; br < indx; br++) {
			if (mainImage == currimg[br])
				break;
		}
		FileWriter input = new FileWriter(new File("input.txt"));
		FileWriter output = new FileWriter(new File("output.txt"));
		FileWriter sel = new FileWriter(new File("selekcija.txt"));
		if (!fullView) {
			input.write(absPath[br] + "\n");
			output.write("tmp\\slika" + br + ".bmp\n");
			sel.write("-1\n");
			sel.close();
		} else {
			if (this.sel.isEmpty()) {
				sel.write("-1\n");
			} else {
				sel.write(mainImage.getHeight() + "\n");
				this.sel.forEach((s) -> {
					try {
						sel.write(s.zaStampu(mainImage.getHeight()) + "\n");
					} catch (IOException e) {
						return;
					}
				});
				sel.write("0 0 0 0\n");
			}
			sel.close();
			for (int i = 0; i < indx; i++) {
				if (active[i]) {
					input.write(absPath[i] + "\n");
					output.write("tmp\\slika" + i + ".bmp\n");
				}
			}
		}

		input.close();
		output.close();
		FileWriter oper = new FileWriter(new File("operacija.oper"));
		oper.write(opr + ";\nEND");
		oper.close();
		boolean neuspeh = false;
		try {
			doCommand("\"Program za poop c++.exe\" input.txt operacija.oper selekcija.txt output.txt");
		} catch (IOException | InterruptedException e) {
			neuspeh = true;
		}

		if (!neuspeh) {
			if (fullView) {
				for (int i = 0; i < indx; i++) {
					if (active[i]) {
						currimg[i] = ImageIO.read(new File("tmp\\slika" + i + ".bmp"));
						absPath[i] = "tmp\\slika" + i + ".bmp";
					}
				}
				fullView();

			} else {
				currimg[br] = ImageIO.read(new File("tmp\\slika" + br + ".bmp"));
				absPath[br] = "tmp\\slika" + br + ".bmp";
				if (br < indx)
					mainImage = currimg[br];
			}
			myApp.repaint();
		}
	}

	public void export(String path) throws IOException {
		if (indx == 0)
			return;
		FileWriter input = new FileWriter(new File("input.txt"));
		for (int i = 0; i < indx; i++) {
			if (active[i])
				input.write(absPath[i] + "\n");
		}
		input.close();
		try {
			doCommand("\"Program za poop c++.exe\"  input.txt " + path);
		} catch (IOException | InterruptedException e) {
			return;
		}
	}

	private void fullView() throws IOException {
		fullView = true;
		export("tmp\\output.bmp");
		mainImage = ImageIO.read(new File("tmp\\output.bmp"));
	}

	public void rmvImage(int panelNum) {
		if (indx == 1) {
			indx = 0;
			mainImage = null;
			return;
		}
		int j = (panelNum + start) % indx;
		if (mainImage == currimg[j]) {
			if (j == indx - 1)
				mainImage = currimg[indx - 2];
			else
				mainImage = currimg[j + 1];
		}
		for (int k = j; k < indx - 1; k++) {
			currimg[k] = currimg[k + 1];
			absPath[k] = absPath[k + 1];
		}
		currimg[indx - 1] = null;
		absPath[indx - 1] = null;
		indx--;
		if (start == indx)
			start--;
		return;
	}

	public int getIndx() {
		return indx;
	}

	public void setIndx(int indx) {
		this.indx = indx;
	}

	public int getStart() {
		return start;
	}

	public void setStart(int start) {
		this.start = start;
	}

	public BufferedImage getMainImage() {
		return mainImage;
	}

	public BufferedImage[] getCurrimg() {
		return currimg;
	}

	private void drawImageProportionally(JPanel p, BufferedImage image) {
		if (image != null) {
			double v = getProportion(p, image);
			int nw = (int) (image.getWidth() * (1 - v));
			int nh = (int) (image.getHeight() * (1 - v));
			int x = 0;
			if (nw < p.getWidth()) {
				x += (int) ((p.getWidth() - nw) / 2.0);
			}
			int y = 0;
			if (nh < p.getHeight()) {
				y += (int) ((p.getHeight() - nh) / 2.0);
			}
			if (image == mainImage)
				System.out.println("Sliku crtam na: " + x + " " + y + " " + nw + " " + nh + " " + v);
			p.getGraphics().drawImage(image, x, y, nw, nh, p);
		}
	}

	public void setView(boolean b) {
		fullView = b;
		if (fullView)
			try {
				fullView();
			} catch (IOException e) {
				return;
			}
		else {
			if (indx > 0)
				mainImage = currimg[0];
		}
	}

	public void doPreview(String opcija) {
		if (fullView) {
			try {
				FileWriter sel = new FileWriter(new File("selekcija.txt"));
				FileWriter input = new FileWriter(new File("input.txt"));
				for (int i = 0; i < indx; i++) {
					if (active[i])
						input.write(absPath[i] + "\n");
				}
				input.write("kalus\n");
				input.close();
				FileWriter output = new FileWriter(new File("output.txt"));
				for (int i = 0; i < indx; i++) {
					if (active[i])
						output.write("tmp\\slikaPrev" + i + ".bmp\n");
				}
				output.write("kalus\n");
				output.close();
				FileWriter oper = new FileWriter(new File("operacija.oper"));
				oper.write(opcija + ";\nEND");
				oper.close();
				if (this.sel.isEmpty()) {
					sel.write("-1\n");
				} else {
					sel.write(mainImage.getHeight() + "\n");
					this.sel.forEach((s) -> {
						try {
							sel.write(s.zaStampu(mainImage.getHeight()) + "\n");
						} catch (IOException e) {
							return;
						}
					});
					sel.write("0 0 0 0\n");
				}
				sel.close();
				boolean neuspeh = false;
				try {
					System.out.println("Krecem komandu");
					doCommand("\"Program za poop c++.exe\" input.txt operacija.oper selekcija.txt output.txt");
					System.out.println("zavrsio komandu");
				} catch (IOException | InterruptedException e) {
					neuspeh = true;
				}
				if (!neuspeh) {
					doCommand("\"Program za poop c++.exe\"  output.txt tmp\\prevSlika.bmp");
					prevImage = ImageIO.read(new File("tmp\\prevSlika.bmp"));
				}
			} catch (IOException | InterruptedException e) {
				e.printStackTrace();
			}
		} else {
			FileWriter input;
			FileWriter oper;
			FileWriter output;
			try {
				int br = 0;
				for (br = 0; br < indx; br++) {
					if (mainImage == currimg[br])
						break;
				}
				input = new FileWriter(new File("input.txt"));
				input.write(absPath[br] + "\n");
				input.close();
				oper = new FileWriter(new File("operacija.oper"));
				oper.write(opcija + ";\nEND");
				oper.close();
				output = new FileWriter(new File("output.txt"));
				output.write("tmp\\prevSlika.bmp\n");
				output.close();
				FileWriter sel = new FileWriter(new File("selekcija.txt"));
				sel.write("-1\n");
				sel.close();
				doCommand("\"Program za poop c++.exe\" input.txt operacija.oper selekcija.txt output.txt");
				prevImage = ImageIO.read(new File("tmp\\prevSlika.bmp"));
			} catch (IOException | InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		myApp.repaint();
	}

	public void rmvSel(int x, int y, JPanel p) {
		sel = (LinkedList<Selection>) sel.parallelStream().filter((s) -> {
			SelectionRect sl = (SelectionRect) s;
			int[] koord = sl.translate(p, mainImage);
			return (!(koord[0] <= x && (koord[0] + koord[2]) >= x && (koord[1] <= y) && (koord[1] + koord[3] >= y)));
		}).collect(Collectors.toCollection(LinkedList::new));
	}

	public void drawMainImage(JPanel p) {
		drawImageProportionally(p, mainImage);
	}

	public void projectDialog(boolean load, JPanel p) {
		JFileChooser f = new JFileChooser();
		if (load)
			f.setFileFilter(new javax.swing.filechooser.FileFilter() {

				@Override
				public String getDescription() {
					return "*.proj";
				}

				@Override
				public boolean accept(File f) {
					return f.getName().substring(f.getName().length() - 4).equals("proj") || f.isDirectory();
				}
			});
		else
			f.setFileSelectionMode(f.DIRECTORIES_ONLY);
		int returnVal = f.showOpenDialog(myApp);

		if (returnVal == JFileChooser.APPROVE_OPTION) {
			String dir = f.getSelectedFile().getAbsolutePath();
			try {
				if (load)
					load(f.getSelectedFile(), p);
				else
					save(dir);
			} catch (IOException | InterruptedException e) {
				e.printStackTrace();
			}
		} else {
			return;
		}
	}

	private void save(String dir) throws IOException, InterruptedException {
		FileWriter input = new FileWriter(new File("input.txt"));
		FileWriter proj = new FileWriter(new File(dir + "\\project.proj"));
		for (int i = 0; i < indx; i++) {
			input.write(absPath[i] + "\n");
		}
		input.close();
		proj.write("Slike:\n");
		FileWriter output = new FileWriter(new File("output.txt"));
		for (int i = 0; i < indx; i++) {
			output.write(dir + "\\projImage" + i + ".bmp\n");
			proj.write(dir + "\\projImage" + i + ".bmp\n");
		}
		proj.write("Selekcije:\n");
		this.sel.forEach((s) -> {
			try {
				proj.write(s.zaSave());
			} catch (IOException e) {
				return;
			}
		});
		output.close();
		FileWriter sel = new FileWriter(new File("selForSave.txt"));
		sel.close();
		FileWriter oper = new FileWriter(new File("operForSave.oper"));
		oper.write("END\n");
		oper.close();
		proj.close();
		doCommand("\"Program za poop c++.exe\" input.txt operForSave.oper selForSave.txt output.txt");
		System.out.println("Sacuvano");
	}

	public void clear() {
		indx = 0;
		start = 0;
		mainImage = null;
		fullView = false;
		prevImage = null;
		sel.clear();
	}

	private void load(File dir, JPanel p) throws FileNotFoundException {
		Scanner myReader = new Scanner(new File(dir.getAbsolutePath()));
		String line = myReader.nextLine();
		LinkedList<String> linesForimage = new LinkedList<String>();
		LinkedList<String> linesForSelection = new LinkedList<String>();
		if (!line.equals("Slike:")) {
			System.out.println(line);
			System.out.println("ne valja nesto ovde");
			return;
		}
		String s = null;
		while (myReader.hasNextLine()) {
			s = myReader.nextLine();
			if (s.equals("Selekcije:"))
				break;
			else
				linesForimage.add(s);
		}
		if (!s.equals("Selekcije:")) {
			System.out.println(s);
			System.out.println("ne valja nesto");
			return;
		}
		while (myReader.hasNextLine())
			linesForSelection.add(myReader.nextLine());
		clear();

		linesForimage.forEach((str) -> {
			addImage(new File(str));
		});
		linesForSelection.forEach(str -> {
			int x, y, w, h;
			Scanner sc = new Scanner(str);
			x = sc.nextInt();
			y = sc.nextInt();
			w = sc.nextInt();
			h = sc.nextInt();
			this.sel.add(new SelectionRect(x, y, w, h));
		});
		myApp.repaint();
	}
}
