package project;

import javax.swing.JFrame;

public abstract class Operation {

	protected JFrame f = new JFrame("Operacija");
	protected String name;
	protected String text;
	protected Project p;

	protected abstract void initFrame();

	public Operation(String name, Project p) {
		this.name = name;
		initFrame();
		this.p = p;
	}

	public String getText() {
		return text;
	}

	public abstract void DoOperation();

}
