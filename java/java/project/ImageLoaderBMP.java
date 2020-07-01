package project;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

public class ImageLoaderBMP extends ImageLoader {

	@Override
	protected BufferedImage input(File f) throws IOException {
		return ImageIO.read(f);
	}

}
