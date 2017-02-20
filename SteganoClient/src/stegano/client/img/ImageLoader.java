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
        String[] imgNames = dir.list();
        if(imgNames != null) {
            for (String s :
                    imgNames) {
                System.out.println(s);
            }
            Random rand = new Random();
            String randomImgName = imgNames[rand.nextInt(imgNames.length)];
            randomImage = new Image("file:\\" + path + "\\" + randomImgName);
        }
        return randomImage;
    }
}
