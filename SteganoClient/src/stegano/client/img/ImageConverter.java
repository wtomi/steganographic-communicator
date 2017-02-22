package stegano.client.img;

import javafx.scene.image.*;
import stegano.client.model.MyImage;

/**
 * Created by tommy on 20.02.2017.
 */
public class ImageConverter {

    public static WritableImage converMyImage(MyImage image) {
        WritableImage writableImage = new WritableImage(image.getWidth(), image.getHeight());
        PixelWriter pixelWriter = writableImage.getPixelWriter();
        pixelWriter.setPixels(0, 0, image.getWidth(), image.getHeight(), MyImage.getPixelFormat(),
                image.getImageData(), 0, image.getWidth() * 4);
        return writableImage;
    }

    public static WritableImage convertImageData(byte[] imgData,int width,int height) {
        if((width * height * 4) != imgData.length)
            throw new RuntimeException("Image dimensions doesn't match image data length");
        WritableImage writableImage = new WritableImage(width, height);
        PixelWriter pixelWriter = writableImage.getPixelWriter();
        pixelWriter.setPixels(0, 0, width, height, MyImage.getPixelFormat(),
                imgData, 0, width * 4);
        return writableImage;
    }


}
