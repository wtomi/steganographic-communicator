package stegano.client.img;

import javafx.scene.image.*;
import stegano.client.model.MyImage;

import java.nio.ByteBuffer;

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


}
