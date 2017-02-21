package stegano.client.view;

import javafx.concurrent.Task;
import javafx.concurrent.WorkerStateEvent;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import stegano.client.MainApp;
import stegano.client.model.World;
import stegano.client.sck.SocketController;

import java.io.IOException;


/**
 * Created by tommy on 17.02.2017.
 */
public class LoginViewController {

    @FXML
    private Label message;

    @FXML
    private TextField serverName;

    @FXML
    private TextField serverPort;

    @FXML
    private TextField serverPassword;

    @FXML
    private TextField userName;

    @FXML
    private Button startButton;

    @FXML
    private void initialize() {

        System.out.println("I'm beging initalized");

        startButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {

                startButton.setDisable(true); //disable button until authentication finishes
                String userNameText = userName.getText();
                Task<Boolean> connectTask = SocketController.getInstance().getConnectTask(serverName.getText(), serverPassword.getText(),
                        Integer.valueOf(serverPort.getText()), userName.getText());
                connectTask.setOnSucceeded((WorkerStateEvent t) -> {
                    if (connectTask.getValue() == Boolean.TRUE) {
                        loadAndShoewConversationView();
                        World.getInstance().setMyUserName(userNameText);
                    }
                    else {
                        message.setText(connectTask.getMessage());
                        message.setVisible(true);
                        startButton.setDisable(false);
                    }
                });
                Thread t = new Thread(connectTask);
                t.setDaemon(true);
                t.start();
            }
        });
    }

    private void loadAndShoewConversationView() {
        try {
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(MainApp.class.getResource("view/ConversationsView.fxml"));
            AnchorPane personOverview = (AnchorPane) loader.load();
            MainApp.getRootLayout().setCenter(personOverview);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
