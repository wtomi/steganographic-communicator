package stegano.client.model;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.collections.ObservableMap;

import java.util.HashMap;
import java.util.Map;
import java.util.Observable;

/**
 * Created by tommy on 19.02.2017.
 */
public class World {
    private static World ourInstance = new World();

    private ObservableList<Contact> contacts = FXCollections.observableArrayList();
    private ObservableMap<String, Conversation> conversations = FXCollections.observableHashMap();
    private String myUserName = null;

    public static World getInstance() {
        return ourInstance;
    }

    private World() {
    }

    public Conversation getConversation(String userName) {
        Conversation conversation = conversations.get(userName);
        if(conversation == null) {
            final Conversation newConversation = new Conversation(userName);
            Platform.runLater(() -> conversations.put(userName, newConversation));
            return newConversation;
        } else {
            return conversation;
        }
    }

    public ObservableList<Contact> getContacts() {
        return contacts;
    }

    public ObservableMap<String, Conversation> getConversations() {
        return conversations;
    }

    public String getMyUserName() {
        return myUserName;
    }

    public void setMyUserName(String myUserName) {
        this.myUserName = myUserName;
    }
}
