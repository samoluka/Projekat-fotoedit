package project;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.HashMap;

import javax.imageio.ImageIO;

public abstract class ImageLoader {

	public final static HashMap<String, ImageLoader> map = new HashMap<String, ImageLoader>();
	static {
		map.put("bmp", new ImageLoaderBMP());
		map.put("pam", new ImageLoaderPAM());
	}

	public ImageLoader() {
	}

	public static BufferedImage in(File f) throws IOException {
		BufferedImage tmp = null;

		String ext = f.getName().substring(f.getName().length() - 3);
		ImageLoader ld = map.get(ext);
		if (ld != null)
			tmp = ld.input(f);
		return tmp;
	}

	protected abstract BufferedImage input(File f) throws IOException;
}
