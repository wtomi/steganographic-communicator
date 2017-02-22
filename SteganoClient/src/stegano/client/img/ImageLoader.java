package stegano.client.img;

import javafx.application.Platform;
import javafx.scene.control.Alert;
import javafx.scene.image.Image;
import javafx.stage.Stage;
import stegano.client.MainApp;

import java.io.File;
import java.net.URISyntaxException;
import java.util.Random;

/**
 * Created by tommy on 20.02.2017.
 */
public class ImageLoader {

    public static Image loadRandomImageFromDir(File file) {
        Image randomImage = null;
        try {
            File dir = file;
            String[] imgNames = dir.list();
            if (imgNames != null) {
                Random rand = new Random();
                String randomImgName = imgNames[rand.nextInt(imgNames.length)];
                File in = new File(dir, randomImgName);
                //System.out.println(in.toURI().toString());
                randomImage = new Image(in.toURI().toString());
            }
            return randomImage;
        } catch (IllegalArgumentException e){
            Platform.runLater(() -> {
                final Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setTitle("SteganoClient");
                alert.setHeaderText("Invalid output directory");
                alert.setContentText("Input directory can contain only pictures in formats: BMP, GIF, JPEG(JPG), PNG\n" +
                        "Menu -> Input Dir");
                Image icon = null;
                try {
                    icon = new Image(MainApp.class.getResource("resources/images/safe.png").toURI().toString());
                } catch (URISyntaxException e1) {
                    e1.printStackTrace();
                }
                Stage stage = (Stage) alert.getDialogPane().getScene().getWindow();
                stage.getIcons().add(icon);
                alert.showAndWait();
            });
        }
        return randomImage;
    }
}
