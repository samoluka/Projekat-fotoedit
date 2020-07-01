package project;

public class OperationNoOperand extends Operation {

	public OperationNoOperand(String name, Project p) {
		super(name, p);
		// TODO Auto-generated constructor stub
	}

	@Override
	protected void initFrame() {
		
	}

	@Override
	public void DoOperation() {
		text = name;
		p.doPreview(text);
	}

}
