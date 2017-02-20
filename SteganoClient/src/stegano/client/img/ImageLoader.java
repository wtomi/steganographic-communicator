package stegano.client.img;

import javafx.scene.image.Image;

import java.io.File;
import java.util.Random;

/**
 * Created by tommy on 20.02.2017.
 */
public class ImageLoader {

    public static Image loadRandomImageFromDir(String path) {
        Image randomImage = null;
        File dir = new File(path);
        if(dir.isDirectory()) {
            String[] imgNames = dir.list();
            for (String s :
                    imgNames) {
                System.out.println(s);
            }
            Random rand = new Random();
            String randomImgName = imgNames[rand.nextInt(imgNames.length)];
            System.out.println(path + randomImgName);
            randomImage = new Image(path + randomImgName);
        }
        return randomImage;
    }
}
