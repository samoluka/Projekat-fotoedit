package project;

import java.awt.FileDialog;

import javax.swing.JFrame;

public class OperationComposite extends Operation {

	public OperationComposite(String name, Project p) {
		super(name, p);
		// TODO Auto-generated constructor stub
	}

	@Override
	protected void initFrame() {

	}

	@Override
	public void DoOperation() {
		FileDialog ch = new FileDialog(f, "Odaberi Operaciju", FileDialog.LOAD);
		ch.setVisible(true);
		ch.setDirectory(System.getProperty("user.dir"));
		text = "<" + ch.getFiles()[0].getAbsolutePath() + ">";
		p.doPreview(text);
	}

}
