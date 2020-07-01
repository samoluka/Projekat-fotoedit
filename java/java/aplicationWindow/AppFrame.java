package aplicationWindow;

import java.awt.BasicStroke;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FileDialog;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.HeadlessException;
import java.awt.Menu;
import java.awt.MenuBar;
import java.awt.MenuItem;
import java.awt.Point;
import java.awt.Stroke;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.LinkedList;
import javax.imageio.ImageIO;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.SwingUtilities;

import project.Operation;
import project.OperationComposite;
import project.OperationNoOperand;
import project.OperationOneOperand;
import project.Project;

@SuppressWarnings("serial")
public class AppFrame extends JFrame {

	@Override
	public void paint(Graphics g) {
		super.paint(g);
		proj.Paint(panel_2, pnl, op_panel, true);
		if (mousePt != null) {
			int startX = (int) (dx >= 0 ? mousePt.getX() : mousePt.getX() + dx);
			int startY = (int) (dy >= 0 ? mousePt.getY() : mousePt.getY() + dy);
			Graphics2D g2d = (Graphics2D) panel_2.getGraphics().create();
			Stroke dashed = new BasicStroke(3, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 0, new float[] { 9 }, 0);
			g2d.setStroke(dashed);
			g2d.drawRect(startX, startY, Math.abs(dx), Math.abs(dy));
		}
	}

	// Graficke komponente
	private JPanel panel, panel_1, panel_2, panel_3;
	private JPanel[] pnl = new JPanel[maxPanel];
	private JCheckBox[] cbactive = new JCheckBox[maxPanel];
	private MenuBar menu;
	private Menu file;
	private static int maxImg = 100;
	private static int maxPanel = 5;
	private JCheckBox lv, fv;
	private JComboBox<String> bxOneOp;
	private JComboBox<String> bxNoOp;
	private JComboBox<String> bxComp;
	private JPanel op_panel;
	private Operation op;

	// Logicke komponente

	private final String[] bxOneString = { "plus", "minus", "iminus", "mul", "div", "idiv", "pow", "log", "min", "max",
			"SetAlpha" };
	private final String[] bxCompString = { "composite operation" };
	private final String[] bxNoString = { "invers", "greyscale", "blackwhite" };
	private Project proj = new Project(this);
	private Point mousePt = new Point();
	private int dx, dy;

	public AppFrame(String title) throws HeadlessException {
		super(title);
		new File("tmp").mkdir();
		setBounds(100, 100, 757, 607);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		panel = new JPanel();
		initPanel();
		add(panel);
		menu = new MenuBar();
		file = new Menu("File");
		MenuItem open = new MenuItem("Open");
		open.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				dialogOpen();
				repaint();
			}
		});
		MenuItem export = new MenuItem("Export as..");
		export.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				dialogExport();
				repaint();
			}
		});
		MenuItem saveP = new MenuItem("Save project");
		saveP.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				proj.projectDialog(false, null);
			}
		});
		MenuItem loadP = new MenuItem("Load project");
		loadP.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				proj.projectDialog(true, panel_2);
			}
		});
		menu.add(file);
		file.add(open);
		file.add(export);
		file.add(saveP);
		file.add(loadP);
		this.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		this.addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				JFrame frame = new JFrame();
				if (JOptionPane.showConfirmDialog(frame, "Do you want to exit?", "Close Window?",
						JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE) == JOptionPane.YES_OPTION) {
					int opt = JOptionPane.showConfirmDialog(frame, "Do you want to save project?");
					if (opt == JOptionPane.YES_OPTION) {
						proj.projectDialog(false, null);
					}
					if (opt != JOptionPane.CANCEL_OPTION) {
						dispose();
						System.exit(0);
					}
				}
			}
		});

		this.setMenuBar(menu);
		setVisible(true);
		repaint();
	}

	private void initPanel() {
		GridBagLayout lay = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weighty = 1;
		panel.setLayout(lay);

		panel_1 = new JPanel(new GridLayout(2, 1));

		JPanel bxPanel = new JPanel();
		bxPanel.setLayout(new BoxLayout(bxPanel, BoxLayout.Y_AXIS));
		bxOneOp = new JComboBox<String>(bxOneString);
		op_panel = new JPanel();

		bxOneOp.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				String opcija = bxOneOp.getItemAt(bxOneOp.getSelectedIndex());
				op = new OperationOneOperand(opcija, proj);
				op.DoOperation();
			}
		});
		bxPanel.add(bxOneOp);
		bxNoOp = new JComboBox<String>(bxNoString);
		bxPanel.add(bxNoOp);
		bxNoOp.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				String opcija = bxNoOp.getItemAt(bxNoOp.getSelectedIndex());
				op = new OperationNoOperand(opcija, proj);
				op.DoOperation();
			}
		});
		bxComp = new JComboBox<String>(bxCompString);
		bxComp.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				op = new OperationComposite("<>", proj);
				op.DoOperation();
			}
		});
		JButton perform = new JButton("APPLY");
		perform.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				try {
					if (op != null)
						proj.doOperation(op.getText());
					repaint();
				} catch (IOException e1) {

				}
			}
		});
		bxPanel.add(bxComp);
		bxPanel.add(perform);
		panel_1.add(bxPanel);
		panel_1.add(op_panel);

		c.weightx = 1;
		panel.add(panel_1, c);

		panel_2 = new JPanel();
		panel_2.setBackground(Color.GRAY);

		panel_2.addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent e) {
				mousePt = e.getPoint();
			}

			@Override
			public void mouseReleased(MouseEvent e) {
				if (SwingUtilities.isMiddleMouseButton(e)) {
					proj.rmvSel(e.getX(), e.getY(), panel_2);
					repaint();
					return;
				}
				int startX = (int) (dx >= 0 ? mousePt.getX() : mousePt.getX() + dx);
				int startY = (int) (dy >= 0 ? mousePt.getY() : mousePt.getY() + dy);
				proj.addSelection(panel_2, startX, startY, Math.abs(dx), Math.abs(dy));
				mousePt = null;
				dx = 0;
				dy = 0;
				repaint();
			}
		});
		panel_2.addMouseMotionListener(new MouseMotionAdapter() {

			@Override
			public void mouseDragged(MouseEvent e) {
				dx = (int) (e.getX() - mousePt.getX());
				dy = (int) (e.getY() - mousePt.getY());
				proj.drawMainImage(panel_2);
				// proj.drawSelection(panel_2);
				int startX = (int) (dx >= 0 ? mousePt.getX() : mousePt.getX() + dx);
				int startY = (int) (dy >= 0 ? mousePt.getY() : mousePt.getY() + dy);
				Graphics2D g2d = (Graphics2D) panel_2.getGraphics().create();
				Stroke dashed = new BasicStroke(3, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 0, new float[] { 9 },
						0);
				g2d.setStroke(dashed);
				g2d.drawRect(startX, startY, Math.abs(dx), Math.abs(dy));
			}
		});

		c.weightx = 10;
		panel.add(panel_2, c);

		GridBagLayout ly = new GridBagLayout();
		panel_3 = new JPanel(ly);
		JPanel p1 = new JPanel(new BorderLayout());
		JPanel p1l = new JPanel(new GridLayout(maxPanel, 1));
		JPanel p1d = new JPanel(new GridLayout(maxPanel, 1));
		for (int i = 0; i < maxPanel; i++) {
			JPanel p = new JPanel();
			JCheckBox cb = new JCheckBox();
			cb.setVisible(false);
			cb.setSelected(true);
			cb.addActionListener(new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent e) {
					for (int i = 0; i < maxPanel; i++) {
						int j = (i + proj.getStart()) % proj.getIndx();
						if (cbactive[i] == e.getSource()) {
							JCheckBox bx = (JCheckBox) e.getSource();
							System.out.println("promenio");
							proj.setActiveAt(j, bx.isSelected());
							repaint();
							return;
						}
					}
				}
			});
			p.setVisible(false);
			p.setBackground(Color.cyan);
			p.addMouseListener(new MouseAdapter() {
				@Override
				public void mouseReleased(MouseEvent e) {
					if (SwingUtilities.isMiddleMouseButton(e)) {
						JPanel c = (JPanel) e.getSource();
						for (int i = 0; i < proj.getIndx(); i++) {
							if (c == pnl[i]) {
								proj.rmvImage(i);
								if (proj.getIndx() < maxPanel - 1) {
									pnl[proj.getIndx() + 1].setVisible(false);
									cbactive[proj.getIndx() + 1].setVisible(false);
								}
								repaint();
							}
						}
						return;
					}
					JPanel c = (JPanel) e.getSource();
					for (int i = 0; i < proj.getIndx(); i++) {
						if (c == pnl[i]) {
							int j = (i + proj.getStart()) % proj.getIndx();
							proj.setMainImage(proj.getCurrimg()[j]);
							lv.setSelected(true);
							fv.setSelected(false);
							repaint();
							return;
						}
					}
					dialogOpen();
				}

			});
			p1l.add(p);
			p1d.add(cb);
			pnl[i] = p;
			cbactive[i] = cb;
		}
		pnl[0].setVisible(true);
		pnl[0].setBackground(Color.red);
		p1.addMouseWheelListener(new MouseWheelListener() {

			@Override
			public void mouseWheelMoved(MouseWheelEvent e) {
				if (e.getWheelRotation() > 0)
					skrolup();
				else
					skroldown();
			}
		});
		p1.add(p1l, BorderLayout.CENTER);
		p1.add(p1d, BorderLayout.EAST);
		lv = new JCheckBox("Label View", true);
		lv.setBackground(Color.green);
		lv.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if (lv.isSelected())
					fv.setSelected(false);
				proj.setView(false);
				repaint();
			}
		});
		fv = new JCheckBox("Full View", false);
		fv.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if (fv.isSelected())
					lv.setSelected(false);
				proj.setView(true);
				repaint();
			}
		});
		fv.setBackground(Color.orange);
		JPanel p2 = new JPanel(new GridLayout(1, 2));
		p2.add(lv);
		p2.add(fv);
		GridBagConstraints gp = new GridBagConstraints();
		gp.fill = gp.BOTH;
		gp.weightx = 1;
		gp.gridx = 0;
		gp.gridy = 0;
		gp.weighty = 12;
		panel_3.add(p1, gp);
		gp.gridy = 1;
		gp.weighty = 1;
		panel_3.add(p2, gp);

		c.weightx = 1;
		panel.add(panel_3, c);

	}

	private void skrolup() {
		if (proj.getIndx() <= maxPanel)
			return;
		proj.setStart(proj.getStart() + 1);
		proj.setStart(proj.getStart() % proj.getIndx());
		for (int i = 0; i < 5; i++) {
			int j = (i + proj.getStart()) % proj.getIndx();
			if (j == 0)
				pnl[i].setBackground(Color.red);
			else
				pnl[i].setBackground(Color.CYAN);
		}
		for (int i = 0; i < maxPanel; i++) {
			cbactive[i].setSelected(proj.getActiveAt((i + proj.getStart()) % proj.getIndx()));
		}
		repaint();
	}

	private void skroldown() {
		if (proj.getIndx() <= maxPanel)
			return;
		proj.setStart(proj.getStart() - 1);
		if (proj.getStart() < 0)
			proj.setStart(proj.getIndx() - 1);
		for (int i = 0; i < 5; i++) {
			int j = (i + proj.getStart()) % proj.getIndx();
			if (j == 0)
				pnl[i].setBackground(Color.red);
			else
				pnl[i].setBackground(Color.CYAN);
		}
		for (int i = 0; i < maxPanel; i++) {
			cbactive[i].setSelected(proj.getActiveAt((i + proj.getStart()) % proj.getIndx()));
		}
		repaint();
	}

	private void dialogOpen() {
		FileDialog ch = new FileDialog(this, "Odaberi sliku", FileDialog.LOAD);
		ch.setVisible(true);
		ch.setDirectory(System.getProperty("user.dir"));
		if (ch.getFiles().length == 0)
			return;
		File f = ch.getFiles()[0];
		if (f != null) {
			cbactive[proj.getIndx() % maxPanel].setVisible(true);
			proj.addImage(f);
			pnl[proj.getIndx() % maxPanel].setVisible(true);
			repaint();
		}
	}

	private void dialogExport() {
		FileDialog ch = new FileDialog(this, "Odaberi sliku", FileDialog.SAVE);
		ch.setVisible(true);
		ch.setDirectory(System.getProperty("user.dir"));
		if (ch.getFiles().length == 0)
			return;
		try {
			proj.export(ch.getFiles()[0].getAbsolutePath());
		} catch (IOException e) {
			return;
		}
	}

	public static void main(String[] args) {
		AppFrame f = new AppFrame("program");
	}

}
