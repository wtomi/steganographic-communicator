package stegano.client;

import javafx.collections.FXCollections;
import javafx.scene.image.Image;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import stegano.client.img.ImageConverter;
import stegano.client.img.ImageLoader;
import stegano.client.img.ImageSaver;
import stegano.client.model.Contact;
import javafx.application.Application;
import javafx.collections.ObservableList;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;
import stegano.client.model.MyImage;
import stegano.client.sck.SocketController;
import stegano.client.stegano.SteganoEncryptor;
import stegano.client.view.ConversationsViewController;

import java.io.File;
import java.io.IOException;

/**
 * Created by tommy on 27.01.2017.
 */
public class MainApp extends Application {

    private Stage primaryStage;
    private static BorderPane rootLayout;

    private ObservableList<Contact> contacts = FXCollections.observableArrayList();

    public static BorderPane getRootLayout() {
        return rootLayout;
    }

    @Override
    public void start(Stage primaryStage) throws IOException {

        //Image saving test
//        for (int i = 0; i < 10; i++) {
//            File inDir = new File("../images/inImages").getCanonicalFile();
//            File outDir = new File("../images/outImages").getCanonicalFile();
//            Image image = ImageLoader.loadRandomImageFromDir(inDir.toString());
//            MyImage myImage = new MyImage(image);
//            SteganoEncryptor.encryptData(myImage.getImageData(), "Hello world");
//            String message = SteganoEncryptor.decryptData(myImage.getImageData());
//            System.out.println(message);
//            ImageSaver.saveImagePng(ImageConverter.converMyImage(myImage), outDir.toString());
//        }

        this.primaryStage = primaryStage;
        this.primaryStage.setTitle("StenoClient");

        contacts.add(new Contact("example 1"));
        contacts.add(new Contact("example 2"));

        initRootLayout();

        showLoginView();
        //showConversationsView();
    }

    /**
     * Initializes the root layout.
     */
    public void initRootLayout() {
        try {
            // Load root layout from fxml file.
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(MainApp.class.getResource("view/RootLayout.fxml"));
            rootLayout = (BorderPane) loader.load();

            // Show the scene containing the root layout.
            Scene scene = new Scene(rootLayout);
            primaryStage.setScene(scene);
            primaryStage.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void showLoginView() {
        try {
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(MainApp.class.getResource("view/LoginView.fxml"));
            VBox loginView = (VBox) loader.load();
            rootLayout.setCenter(loginView);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Shows the contacts and conversation
     */
    public void showConversationsView() {
        try {
            // Load person overview.
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(MainApp.class.getResource("view/ConversationsView.fxml"));
            AnchorPane personOverview = (AnchorPane) loader.load();

            // Set person overview into the center of root layout.
            rootLayout.setCenter(personOverview);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Returns the main stage.
     *
     * @return
     */
    public Stage getPrimaryStage() {
        return primaryStage;
    }

    public static void main(String[] args) {
        launch(args);
    }

    public ObservableList<Contact> getContacts() {
        return contacts;
    }
}
