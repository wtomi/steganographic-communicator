package stegano.client.model;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

/**
 * Created by tommy on 27.01.2017.
 */
public class Conversation {

    private String userName;
    private ObservableList<Message> messages = FXCollections.observableArrayList();

    public Conversation (String userName) {
        this.userName = userName;
    }

    public void addMessage(Message msg) {
        Platform.runLater(() -> messages.add(msg));
    }

    public String getUserName() {
        return userName;
    }

    public ObservableList<Message> getMessages() {
        return messages;
    }
}
