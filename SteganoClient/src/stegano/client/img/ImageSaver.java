package stegano.client.img;

import javafx.embed.swing.SwingFXUtils;
import javafx.scene.image.Image;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;

/**
 * Created by tommy on 20.02.2017.
 */
public class ImageSaver {

    public static void saveImagePng(Image image, String path) {
        saveImage(image, path, "png");
    }

    private static void saveImage(Image image, String path, String format) {
        //System.out.println(path + "\\" + LocalTime.now().toString() + ".png");
        DateTimeFormatter timeForamtter = DateTimeFormatter.ofPattern("yyyy.MM.dd.HH.mm.ss.SSS");
        String time = LocalDateTime.now().format(timeForamtter);
        File outputFile = new File(path + "\\" + time + "." + format);
        BufferedImage bImage = SwingFXUtils.fromFXImage(image, null);
        try {
            ImageIO.write(bImage, format, outputFile);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

}
