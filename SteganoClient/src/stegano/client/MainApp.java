package stegano.client;

import javafx.scene.image.Image;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;
import stegano.client.img.ImageLoader;
import stegano.client.img.InputOutputDirectory;
import stegano.client.sck.SocketController;

import java.io.File;
import java.io.IOException;
import java.net.URISyntaxException;

/**
 * Created by tommy on 27.01.2017.
 */
public class MainApp extends Application {

    private static Stage primaryStage;
    private static BorderPane rootLayout;

    public static BorderPane getRootLayout() {
        return rootLayout;
    }

    @Override
    public void start(Stage primaryStage) throws IOException {

        this.primaryStage = primaryStage;
        this.primaryStage.setTitle("SteganoClient");

        try {
            //InputOutputDirectory.setInputDir(new File(MainApp.class.getResource("resources/inImages").getPath()));
            Image icon = new Image(MainApp.class.getResource("resources/images/safe.png").toURI().toString());
            this.primaryStage.getIcons().add(icon);
        } catch (URISyntaxException e) {
            e.printStackTrace();
        }

        initRootLayout();
        showLoginView();
        //showConversationsView();
    }

    @Override
    public void stop() {
        SocketController.getInstance().interruptMainLoopThread();
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

    public static void showLoginView() {
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
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(MainApp.class.getResource("view/ConversationsView.fxml"));
            AnchorPane conversationView = (AnchorPane) loader.load();
            rootLayout.setCenter(conversationView);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Returns the main stage.
     *
     * @return
     */
    public static Stage getPrimaryStage() {
        return primaryStage;
    }

    public static void main(String[] args) {
        launch(args);
    }
}
