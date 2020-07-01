package project;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import javax.imageio.ImageIO;

public class ImageLoaderPAM extends ImageLoader {

	@Override
	protected BufferedImage input(File f) throws IOException {
		FileWriter input = new FileWriter("input.txt");
		input.write(f.getAbsolutePath() + "\n");
		input.close();
		try {
			Project.doCommand("\"Program za poop c++.exe\" input.txt tmp\\tmppam.bmp");
		} catch (IOException | InterruptedException e) {
			return null;
		}
		BufferedImage tmp = ImageIO.read(new File("tmp\\tmppam.bmp"));
		return tmp;
	}
}
