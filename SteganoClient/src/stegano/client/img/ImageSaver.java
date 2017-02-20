package stegano.client.img;

import javafx.embed.swing.SwingFXUtils;
import javafx.scene.image.Image;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

/**
 * Created by tommy on 20.02.2017.
 */
public class ImageSaver {

    public static void saveImagePng(Image image, String path) {
        saveImage(image, path, "png");
    }

    public static void saveImageJpg(Image image, String path) {
        saveImage(image, path, "jpg");
    }

    private static void saveImage(Image image, String path, String format) {

        File outputFile = new File(path);
        BufferedImage bImage = SwingFXUtils.fromFXImage(image, null);
        try {
            ImageIO.write(bImage, format, outputFile);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

}
