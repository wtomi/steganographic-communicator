package stegano.client.model;

import javafx.scene.image.Image;
import javafx.scene.image.PixelFormat;
import javafx.scene.image.PixelReader;
import javafx.scene.image.WritablePixelFormat;
import stegano.client.stegano.SteganoEncryptor;

import java.nio.ByteBuffer;

/**
 * Created by tommy on 20.02.2017.
 */
public class MyImage {

    private int width;
    private int height;
    private byte[] imageData;

    public MyImage(Image image) {
        width = (int)image.getWidth();
        height = (int)image.getHeight();
        imageData = new byte[width * height * 4];
        WritablePixelFormat<ByteBuffer> pixelFormat = PixelFormat.getByteBgraInstance();
        PixelReader pixelReader = image.getPixelReader();
        pixelReader.getPixels(0, 0, width, height, pixelFormat, imageData, 0, width * 4);
    }


    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public byte[] getImageData() {
        return imageData;
    }
}
